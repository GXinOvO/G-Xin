/*************************************************************************
	> File Name: 12.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 09 Sep 2022 09:40:37 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word);
private:
    int rows, cols;
    bool dfs(vector<vector<char>>& board, string word, int i, int j, int k);
};

bool Solution::exist(vector<vector<char>>& board, string word) {
    rows = board.size();
    cols = board[0].size();
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            if(dfs(board, word, i, j, 0)) return true;
        }
    }
    return false;
}

bool Solution::dfs(vector<vector<char>>& board, string word, int i, int j, int k) {
    if(i < 0 || i >= rows || j < 0 || j >= cols || board[i][j] != word[k]) return false;
    if(k == word.size() - 1) return true;
    board[i][j] = '\0';
    bool res = dfs(board, word, i + 1, j, k + 1) || dfs(board, word, i - 1, j, k + 1) || dfs(board, word, i, j + 1, k + 1) || dfs(board, word, i, j - 1, k + 1);
    board[i][j] = word[k];
    return res;
}

int main() {
    vector<vector<char>> board;
    vector<char> v;
    board.clear();
    int rows, cols;
    char x;
    string word;
    cin >> rows >> cols >> word;
    for(int i = 0; i < rows; ++i) {
        v.clear();
        for(int j = 0; j < cols; ++j) {
            cin >> x;
            v.push_back(x);
        }
        board.push_back(v);
    }
    Solution t1;
    if(t1.exist(board, word)) cout << "True" << endl;
    else cout << "False" << endl;
    return 0;
}
