#include <iostream> 
#include <fstream>
#include <string.h>
#include <iomanip>
#include<unordered_map>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <cstdlib> 
#include <ctime>
#include <vector>
#include <random>
#include <ncurses.h>
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
struct WordGuessQuestion {
    string word;
    string correctDefinition;
    vector<string> options;
};
struct Game {
    string questionWord;
    string correctAnswer;
    vector<string> options;
};

class Dictionary {
private:
    Trie* root = NULL;
    unordered_map<string, string> dictionary;
public:
    void addNewWord(const string& str, string meaning);
    string searchKeyword(const string& st);
    void editDefinition(const string& st, string newMeaning);
    void addToFavoriteList(const string& st);
    void addToHistory(const string& st);
    void viewFavoriteList();
    void removeFromFavoriteList(const string& st);
    void viewHistoryOfSearchWord();
    void chooseDic(int temp);
    string toLowercase(const string& str);
    void removeWord(const string& word);
    void resetDictionary();
    void viewRandomWord();
    void getAllWords(Trie* node, string currentWord, vector<string>& words);
    void getAllDefinitions(Trie* node, string prefix, vector<string>& allDefinitions);
    void viewWords(int numWords);
    WordGuessQuestion getRandomWordGuessQuestion();
    WordGuessQuestion getRandomDefGuessQuestion();
    void getAllWordsWithDifferentDefinition(Trie* node, string currentWord, const string& targetDefinition, vector<string>& words);
    vector<string> searchWordsByDefinition(const string& definition);
    void searchWordsByDefinition(Trie* node, string currentWord, const string& targetDefinition, vector<string>& words);
    string search(const string& query);
    vector<string> autocomplete(const string& prefix);
    void autocomplete(Trie* node, string currentWord, vector<string>& suggestions);

};
