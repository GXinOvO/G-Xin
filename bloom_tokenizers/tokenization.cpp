/*************************************************************************
	> File Name: tokenization.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 07 Oct 2023 09:57:27 AM CST
 ************************************************************************/

#include "tokenization.h"

std::vector<std::string> TrieSplit(std::string text)
{
	std::vector<std::string> result{text};
	return result;
} 

std::unordered_map<std::string, int> load_vocab_from_json(const std::string file_path)
{
	std::fstream fs(file_path);
	nlohmann::json j;
	fs >> j;
	auto &model_j = j["model"];
	const auto& vocab_j = model_j["vocab"];
	std::unordered_map<std::string, int> _vocab = vocab_j.get<std::unordered_map<std::string, int>>();
	return _vocab;
}


std::vector<std::string> load_merges_from_json(const std::string file_path)
{
	std::fstream fs(file_path);
	nlohmann::json j;
	fs >> j;
	auto &model_j = j["model"];
	const auto &merges_j = model_j["merges"];
	std::vector<std::string> _merges = merges_j.get<std::vector<std::string>>();
	return _merges;
}

void utf32_to_utf8_string(uint32_t code, char* string) 
{
	if (code < 0x80) string[0] = code;
	else if (code < 0x800) {   // 00000yyy yyxxxxxx
		string[0] = (0b11000000 | (code >> 6));
		string[1] = (0b10000000 | (code & 0x3f));
	}
	else if (code < 0x10000) {  // zzzzyyyy yyxxxxxx
		string[0] = (0b11100000 | (code >> 12));         // 1110zzz
		string[1] = (0b10000000 | ((code >> 6) & 0x3f)); // 10yyyyy
		string[2] = (0b10000000 | (code & 0x3f));        // 10xxxxx
	}
	else if (code < 0x200000) { // 000uuuuu zzzzyyyy yyxxxxxx
		string[0] = (0b11110000 | (code >> 18));          // 11110uuu
		string[1] = (0b10000000 | ((code >> 12) & 0x3f)); // 10uuzzzz
		string[2] = (0b10000000 | ((code >> 6) & 0x3f)); // 10yyyyyy
		string[3] = (0b10000000 | (code & 0x3f));         // 10xxxxxx
	}
}

void utf8_to_utf32(std::string const& u8, std::vector<uint32_t>& out) 
{
	int elem_len = 1;
	out.clear();
	for (size_t i = 0; i < u8.size(); i += elem_len) {
		uint32_t tmp = (uint32_t)u8[i] & 0xff;
		if (tmp < 0x80UL) {
			elem_len = 1;
			out.push_back(u8[i]);
		}
		else if (tmp < 0xe0UL) {
			elem_len = 2;
			out.push_back(
				((u8[i] & 0x1f) << 6)
				| (u8[i + 1] & 0x3f)
			);
		}
		else if (tmp < 0xf0UL) {
			elem_len = 3;
			out.push_back(
				((u8[i] & 0xf) << 12)
				| ((u8[i + 1] & 0x3f) << 6)
				| (u8[i + 2] & 0x3f)
			);
		}
		else if (tmp < 0xf8UL) {
			elem_len = 4;
			out.push_back(
				((u8[i] & 0x7) << 18)
				| ((u8[i + 1] & 0x3f) << 12)
				| ((u8[i + 2] & 0x3f) << 6)
				| (u8[i + 3] & 0x3f)
			);
		}
		else {
			return;
		}
	}
}

std::unordered_map<int, std::string> byte_to_unicode()
{
	std::vector<unsigned short> bs;
	std::vector<unsigned short> cs;
	std::vector<std::string> _cs;
	uint32_t n = 0;
	std::stringstream ss;
	std::string temp;
	std::unordered_map<int, std::string> _map;

	// for (wchar_t i = L'!'; i <= L'~'; i++) {
	// 	bs.emplace_back((unsigned short)i);
	// }
	// for (wchar_t i = L'\xA1'; i <= L'\xAC'; i++) {
	// 	bs.emplace_back((unsigned short)i);
	// }
	// for (wchar_t i = L'\xAF'; i <= L'\xFF'; i++) {
	// 	bs.emplace_back((unsigned short)i);
	// }

	for (wchar_t i = L'!'; i <= L'~'; i++) {
		bs.emplace_back((unsigned short)i);
	}
	for (wchar_t i = L'¡'; i <= L'¬'; i++) {
		bs.emplace_back((unsigned short)i);
	}
	for (wchar_t i = L'®'; i <= L'ÿ'; i++) {
		bs.emplace_back((unsigned short)i);
	}

	cs = bs;
	for (unsigned short i = 0; i < (unsigned short)pow(2, 8); i++) {
		if (find(bs.begin(), bs.end(), i) == bs.end()) {
			bs.emplace_back((unsigned short)i);
			cs.emplace_back((unsigned short)pow(2, 8) + (unsigned short)n);
			n++;
		}
	}

	for (auto& i : cs) {
		char temp[4] = {0, 0, 0, 0};
		utf32_to_utf8_string(i, temp);
		_cs.emplace_back(temp);
	}
	
	for (uint32_t i = 0; i < _cs.size(); i++) {
		_map[bs[i]] = _cs[i];
	}

	return _map;
}

std::set<std::tuple<std::string, std::string>> get_pairs(std::vector<std::string> word)
{
	std::set<std::tuple<std::string, std::string>> pairs;
	std::string prev_char = "";
	prev_char = word[0];

	for (int i = 1; i < word.size(); i++)
	{
		std::string x = "";
		x = word[i];
		pairs.insert(std::make_tuple(prev_char, x));
		prev_char = x;
	}
	return pairs;
}

std::vector<std::string> bpe(std::vector<std::string> token)
{
	std::vector<std::string> word(token);
	std::string _token = "";
	for (auto i : token)
	{
		_token += i;
	}
	// std::cout << "_token: " << _token << std::endl;
	if (cache.find(_token) != cache.end())
	{
		return cache[_token];
	}

	std::set<std::tuple<std::string, std::string>> pairs = get_pairs(word);
	// for (auto i : pairs)
	// {
	// 	std::cout << "pairs_1: " << std::get<0>(i) << ", pairs_2: " << std::get<1>(i) << std::endl;
	// }

	if (pairs.size() == 0)
	{
		return token;
	}

	while (true)
	{
		std::tuple<std::string, std::string> bigram = *pairs.begin();
		bool is_null = true;
		for (auto _x : pairs)
		{
			if (bpe_ranks.find(_x) != bpe_ranks.end() && (is_null || bpe_ranks.at(bigram) > bpe_ranks.at(_x)))
			{
				bigram = _x;
				is_null = false;
			}
		}

		if (bpe_ranks.find(bigram) == bpe_ranks.end())
		{
			break;
		}

		std::string first = std::get<0>(bigram);
		std::string second = std::get<1>(bigram);
		std::vector<std::string> new_word;
		int i = 0;
		while (i < word.size())
		{
			auto _j = std::find(word.begin() + i, word.end(), first);
			if (_j == word.end())
			{
				for (auto it = word.begin() + i; it < word.end(); it++)
				{
					new_word.push_back(*it);
				}
				break;
			}
			else
			{
				for (auto it = word.begin() + i; it < _j; it++)
				{
					new_word.push_back(*it);
				}
				i = _j - word.begin();
			}

			if (word[i] == first && i < word.size() - 1 && word[i + 1] == second)
			{
				new_word.push_back(first + second);
				i += 2;
			}
			else 
			{
				new_word.push_back(word[i]);
				i += 1;
			}
		}
		word = new_word;
		if (word.size() == 1)
		{
			break;
		}
		else
		{
			pairs = get_pairs(word);
		}
	}

	std::string _word = "";
	for (int i = 0; i < word.size(); i++)
	{
		if (i != word.size() - 1)
		{
			_word += (word[i] + " ");
		}
		else
		{
			_word += word[i];
		}
	}

	cache[_token] = word;
	return word;
}

std::vector<std::string> _tokenize(std::string text)
{
	std::vector<std::string> bpe_tokens;
	std::smatch result;
	std::string::const_iterator iter_begin = text.cbegin();
	std::string::const_iterator iter_end = text.cend();

	while(std::regex_search(iter_begin, iter_end, result, pat))
	{
		std::cout << "result: " << result[0].str() << std::endl;
		std::vector<std::string> temp;
		std::vector<uint32_t> text;
		// utf8_to_utf32(result[0], text);
		// for (int i = 0; i < text.size(); i++)
		// {
		// 	std::cout << "text: " << text[i] << std::endl;
		// }
		// std::cout << "text_size: " << text.size() << std::endl;
		for(uint32_t i = 0; i < result[0].str().size(); i++)
		{
			std::cout << "split: " << (unsigned)(unsigned char)result[0].str()[i] << std::endl;
			temp.push_back(byte_encoder[(unsigned  char)result[0].str()[i]]);
		}
		//utf8_to_utf32(temp, text);
		// for (int i = 0; i < text.size(); i++)
		// {
		// 	std::cout << "text: " << text[i] << std::endl;
		// }
		// std::cout << "text_size: " << text.size() << std::endl;
		for (int i = 0; i < temp.size(); i++)
		{
			std::cout << i << ": " << (int)temp[i][0] << std::endl;
		}
		// std::cout << "size: " << temp.size() << std::endl;

		std::vector<std::string> _temp = bpe(temp);
		// for (auto i : _temp)
		// {
		// 	std::cout << "_temp: " << i << std::endl;
		// }
		for(auto i : _temp)
		{
			bpe_tokens.push_back(i);
		}
		iter_begin = result[0].second;
	}
	return bpe_tokens;
}

std::vector<std::string> Token(std::string text)
{
	// std::vector<std::string> no_split_token{"<|endoftext|>"};
	std::vector<std::string> tokens = TrieSplit(text);
	std::vector<std::string> tokenized_text;

	tokens = _tokenize(text);
	for (auto i : tokens)
	{
		tokenized_text.emplace_back(i);
	}
	return tokenized_text;
}

std::tuple<std::vector<int>, std::vector<int>> Encode(std::string input)
{
	std::vector<std::string> tokenized_text;
	std::vector<int> ids;
	std::vector<int> mask;

	tokenized_text = Token(input);

	for (auto i : tokenized_text)
	{
		ids.emplace_back(encoder[i]);
	}	
	for (int i = 0; i < tokenized_text.size(); i++)
	{
		mask.push_back(1);
	}
	return std::make_tuple(ids, mask);
}

std::string Decode(std::vector<int> token_ids)
{
	std::vector<std::string> tokens;
	std::vector<uint32_t> tokens_decode;
	std::string text = "";

	for (auto i : token_ids)
	{
		// std::cout << "ids: " << i << std::endl;
		tokens.push_back(decoder[i]);
		// std::cout << "decoder: " << decoder[i] << std::endl;
	}
	
	for (auto &i : tokens)
	{
		std::string temp;
		utf8_to_utf32(i, tokens_decode);

		for (auto i : tokens_decode)
		{
			char str[4] = { 0, 0, 0, 0};
			utf32_to_utf8_string(i, str);
			temp += byte_decoder[str];
		}
		i = temp;
		tokens_decode.clear();
	}
	
	for (auto i : tokens)
	{
		text  += i;
	}
	return text;
}

int main()
{
	std::string file = "./tokenizer.json";
	// std::cout << "--------------------------------------" << std::endl;
	// std::cout << "|            byte_encoder            |" << std::endl;
	// std::cout << "--------------------------------------" << std::endl;
	byte_encoder = byte_to_unicode();
	int size = 0;
	// for (auto encoder : byte_encoder)
	// {
	// 	std::cout << "Key: " << encoder.first << ", Value: " << encoder.second << std::endl;
	// 	size++;
	// }
	// std::cout << "size: " << size << std::endl;
	
	// std::cout << "--------------------------------------" << std::endl;
	// std::cout << "|               encoder              |" << std::endl;
	// std::cout << "--------------------------------------" << std::endl;

	// size = 0;
	encoder = load_vocab_from_json(file);
	for (auto &i : encoder)
	{
		decoder[i.second] = i.first;
	}
	// for (auto i : encoder)
	// {
	// 	std::cout << "Key: " << i.first << ", Value: " << i.second << std::endl;
	// 	size++;
	// }
	// std::cout << "size: " << size << std::endl;

	// std::cout << "--------------------------------------" << std::endl;
	// std::cout << "|               decoder              |" << std::endl;
	// std::cout << "--------------------------------------" << std::endl;
	// size = 0;
	// for (auto i : decoder)
	// {
	// 	std::cout << "Key: " << i.first << ", Value: " << i.second << std::endl;
	// 	size++;
	// }
	// std::cout << "size: " << size << std::endl;

	// std::cout << "--------------------------------------" << std::endl;
	// std::cout << "|                merges              |" << std::endl;
	// std::cout << "--------------------------------------" << std::endl;
	std::vector<std::string> _bpe_merges = load_merges_from_json(file);
	// for (int i = 0; i < _bpe_merges.size(); i++)
	// {
	// 	std::cout << i << ": " << _bpe_merges[i] << std::endl;
	// }
	// std::cout << _bpe_merges.size() << std::endl;

	double index = 0;
	for (auto i : _bpe_merges)
	{
		std::tuple<std::string, std::string> temp;
		uint32_t pos = i.find(' ');
		std::get<0>(temp) = i.substr(0, pos);
		std::get<1>(temp) = i.substr(pos + 1, i.size() - pos);
		bpe_merges.emplace_back(temp);
		bpe_ranks[temp] = index++;
	}

	// std::cout << "--------------------------------------" << std::endl;
	// std::cout << "|              bpe_merges            |" << std::endl;
	// std::cout << "--------------------------------------" << std::endl;

	// size = 0;
	// for (auto tuple : bpe_merges)
	// {
	// 	std::cout << "first: " << std::get<0>(tuple) << ", second: " << std::get<1>(tuple) << std::endl;
	// 	size++;
	// }
	// std::cout << "size: " << size << std::endl;

	// std::cout << "--------------------------------------" << std::endl;
	// std::cout << "|               bpe_ranks            |" << std::endl;
	// std::cout << "--------------------------------------" << std::endl;

	// size = 0;
	// for (auto pair : bpe_ranks)
	// {
	// 	std::tuple<std::string, std::string> key = pair.first;
	// 	double value = pair.second;
	// 	std::cout << "Key: " << std::get<0>(key) << ", Value: " << std::get<1>(key) << ".   double: " << value << std::endl;
	// 	size++;
	// }
	// std::cout << "size: " << size << std::endl;

	// std::string str = "I am yinxun.";
	// std::string str = "A chat between a curious human and an artificial intelligence assistant. The assistant gives helpful, detailed, and polite answers to the human's questions.\n\nHuman: <s>今天还行哈</s>Assistant: <s>";
	// std::string str = "A chat between a curious human and an artificial intelligence assistant.";
	std::string str = "? a";
	// std::vector<std::string> token = Token(str);
	std::tuple<std::vector<int>, std::vector<int>> token = Encode(str);

	// for (auto i : std::get<0>(token))
	// {
	// 	std::cout << "token_1: " << i << std::endl;
	// }

	// for (auto i : std::get<1>(token))
	// {
	// 	std::cout << "token_2: " << i << std::endl;
	// }


	// std::cout << "--------------------------------------" << std::endl;
	// std::cout << "|                 token              |" << std::endl;
	// std::cout << "--------------------------------------" << std::endl;

	// for (int i = 0; i < token.size(); i++)
	// {
	// 	std::cout << i << ": " << token[i] << std::endl;
	// }
	// std::cout << "size: " << token.size() << std::endl;


	std::cout << "--------------------------------------" << std::endl;
	std::cout << "|                 cache              |" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	for (auto i : cache)
	{
		std::vector<std::string> string = i.second;
		std::cout << "first: " << i.first << std::endl;
		for (auto j : string)
		{
			std::cout << "str: " << j << std::endl;
		}
		size++;
	}
	std::cout << "size: " << size << std::endl;

	std::vector<int> ids = std::get<0>(token);
	std::cout << "[";
	for (int i = 0; i < ids.size(); i++)
	{
		std::cout << ids[i];
		if (i != ids.size() - 1) std::cout << ", ";
	}
	std::cout << "]" << std::endl;
	std::cout << "size: " << size << std::endl;
	// std::string ids = Decode(std::get<0>(token));
	// std::cout << ids << std::endl;

	return 0;
}
