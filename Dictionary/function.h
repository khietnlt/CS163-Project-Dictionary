#include <iostream> 
#include <fstream>
#include <string.h>
#include <conio.h>
#include <iomanip>
#include<unordered_map>
#include <string>
using namespace std;



void menu();

class Trie {
private:
    bool isEndOfName;
    unordered_map<char, Trie*> map;
    string keyWord;
    string definition;
    friend class Dictionary;
public:
    Trie* getNewTrie(string word, string meaning);
};

class Dictionary {
private:
    Trie* root = NULL;
public:
    void addNewWord(const string& str, string meaning);
    string searchKeyword(const string& st);
    void editDefinition(const string& st, string newMeaning);
    void addToFavoriteList(const string& st);
    void addToHistory(const string& st);
    void viewFavoriteList();
    void viewHistoryOfSearchWord();
    void chooseDic(int temp);
};
