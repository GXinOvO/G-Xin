#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main()
{
    string str = "胡光耀yinxun? ";
    // regex xp(R"([a-zA-Z]+| ?\?\s(?!\S) | \s+(?!\S) | \s+)");
    regex xp(R"('s|'t|'re|'ve|'m|'ll|'d| ?[A-Za-z]+| ?[0-9]+| ?[\?\$\*\+\^][\s]*(?!\S))");
	std::string::const_iterator iter_begin = str.cbegin();
	std::string::const_iterator iter_end = str.cend();
    smatch m;
    while(regex_search(iter_begin, iter_end, m, xp))
    {

        for (uint32_t i = 0; i < m[0].str().size(); i++)
        {
            cout << m[0].str()[i] << endl;
        }
        cout << "size: " << m[0].str().size() << endl;
        iter_begin = m[0].second;
    }
    return 0;
}