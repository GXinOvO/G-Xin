/*************************************************************************
	> File Name: tokenization.h
	> Author: 
	> Mail: 
	> Created Time: Sat 07 Oct 2023 09:57:13 AM CST
 ************************************************************************/

#ifndef _TOKENIZATION_H

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <cmath>
#include <unordered_map>
#include <regex>
#include <set>
#include <algorithm>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct hash_tuple 
{
	template <class T1, class T2>
	size_t operator()(const std::tuple<T1, T2>& p) const
	{
		auto hash1 = std::hash<T1>()(std::get<0>(p));
		auto hash2 = std::hash<T2>()(std::get<1>(p));
		return hash1 ^ hash2;
	}
};

std::vector<std::string> TrieSplit(std::string test);

std::unordered_map<std::string, int> load_vocab_from_json(const std::string file_path);

std::vector<std::string> load_merges_from_json(const std::string file_path);

void utf32_to_utf8_string(uint32_t code, char* string);

void utf8_to_utf32(std::string const& u8, std::vector<uint32_t>& out);

std::unordered_map<int, std::string> byte_to_unicode();

std::set<std::tuple<std::string, std::string>> get_pairs(std::vector<std::string> word);

std::vector<std::string> bpe(std::vector<std::string> token);

std::vector<std::string> _tokenize(std::string text);

std::vector<std::string> Token(std::string text);

std::tuple<std::vector<int>, std::vector<int>> Encode(std::string input);

std::string Decode(std::vector<int> token_ids);

const std::string s= R"('s|'t|'re|'ve|'m|'ll|'d| ?[A-Za-z]+| ?[0-9]+| ?[\?\$\*\+\^][\s]{0,1}(?!\S) | \s+(?!\S))";
// R"('s|'t|'re|'ve|'m|'ll|'d| ?[A-Za-z]+| ?[0-9]+| ?[x00-xff]+| ?[^\sA-Z0-9x00-xff]+| ?[\?\$\*\+\^\s]+ |\s+(?!\S)|\s+)"
// const std::string s = R"([^x00-xff]+)";
std::regex pat(s);
std::unordered_map<std::string, std::vector<std::string>> cache;
std::unordered_map<std::string, int> encoder;
std::unordered_map<int, std::string> decoder;
std::vector<std::tuple<std::string, std::string>> bpe_merges;
std::unordered_map<std::string, int> byte_decoder;
std::unordered_map<int, std::string> byte_encoder;
std::unordered_map<std::tuple<std::string, std::string>, double, hash_tuple> bpe_ranks;

#define _TOKENIZATION_H
#endif
