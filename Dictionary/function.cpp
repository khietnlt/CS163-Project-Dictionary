#include "function.h"


void Dictionary::chooseDic(int temp)
{
    switch (temp)
    {
    case 1:
    {
        ofstream foutput;
        //ifstream finput("slang.txt");
        ifstream finput("slang.txt");
        if (!finput) {
            cerr << "Error: file not opened." << endl;
        }
        string buf;
        string data;
        std::getline(finput, buf);

        while (!finput.eof())
        {
            std::getline(finput, buf);

            data += buf + "\n";

            char* p;
            char* ch = new char[buf.length()];
            strcpy(ch, buf.c_str());
            p = strtok(ch, "`");
            char* first = p;
            p = strtok(NULL, "`");
            if (p != NULL) {
                addNewWord(first, p);
            }
        }
        finput.close();

        break;
    }

    case 2:
    {
        ifstream finput1;
        finput1.open("emotional.txt");
        if (!finput1) {
            cerr << "Error: file not opened." << endl;
        }
        string buf1;
        string data;
        // std::getline(finput1, buf1);



        while (std::getline(finput1, buf1))
        {

            char* p;
            char* ch = new char[buf1.length()];
            strcpy(ch, buf1.c_str());
            p = strtok(ch, " ");
            char* first = p;
            p = strtok(NULL, "");
            if (p != NULL) {
                addNewWord(first, p);
            }

        }
        finput1.close();

        break;
    }
case 3:
{
    Dictionary test1;

    ifstream finput1("/Users/lap15184-local/Documents/GitHub/CS163-Project-Dictionary/Dictionary/Datasets5000.txt");
    if (!finput1) {
        cerr << "Error: file not opened." << endl;
    } else {
        string line;

        while (getline(finput1, line)) {
            size_t spacePos = line.find(' ');
            if (spacePos != string::npos) {
                string keyword = line.substr(0, spacePos);
                string definition = line.substr(spacePos + 1);
                size_t firstCharIdx = definition.find_first_not_of(" \t");
                if (firstCharIdx != string::npos) {
                    definition = definition.substr(firstCharIdx);
                }
                test1.addNewWord(keyword, definition);
            }
        }
        finput1.close();
    }

    break;
}


    default:
    {
        cout << "Invalid input" << endl;
        break;
    }
    }


}


void menu()
{
    cout << "-----WELCOME TO OUR DICTIONARY-----" << endl;
    cout << "1: Search for a word" << endl;
    cout << "2: Add word to favorite list" << endl;
    cout << "3: View favorite list" << endl;
    cout << "4: View history of search word" << endl;
    cout << "5: Add new word and definition" << endl;
    cout << "6: Edit definition" << endl;
    cout << "7: Remove a word" << endl;
    cout << "8: Reset dictionary" << endl;
    cout << "9: View random word and definition" << endl;
    cout << "10: question: Guess definition" << endl;
    cout << "11: question: Guess word" << endl;
}

Trie* Trie::getNewTrie(string word, string meaning)
{
    Trie* node = new Trie;
    node->keyWord = word;
    node->definition = meaning;
    node->isEndOfName = false;
    return node;
}

void Dictionary::addNewWord(const string& str, string meaning)
{
    if (root == nullptr)
        root = new Trie;

    Trie* temp = root;

    for (char c : str) {
        if (temp->map.find(c) == temp->map.end())
            temp->map[c] = temp->getNewTrie("", "");

        temp = temp->map[c];
    }
    if (temp->isEndOfName) {
        // Word already exists, update the meaning
        temp->definition = meaning;
        return;
    }

    temp->isEndOfName = true;
    temp->keyWord = str;
    temp->definition = meaning;
}



string Dictionary::searchKeyword(const string& st)
{

    if (root == NULL)
        return "Not found";

    Trie* temp = root;

    for (int i = 0; i < st.length(); i++) {
        temp = temp->map[st[i]];
        if (temp == NULL)
            return "Not found";
    }



    if (temp->isEndOfName)
        return temp->definition;
    return "Not found";
}

vector<string> Dictionary::searchWordsByDefinition(const string& definition) {
    vector<string> words;
    searchWordsByDefinition(root, "", definition, words);

    return words;
}

void Dictionary::searchWordsByDefinition(Trie* node, string currentWord, const string& targetDefinition, vector<string>& words) {
    if (node == NULL)
        return;

    if (node->isEndOfName && toLowercase(node->definition) == toLowercase(targetDefinition)) {
        words.push_back(currentWord);
    }


    for (auto& it : node->map) {
        char c = it.first;
        Trie* nextNode = it.second;
        searchWordsByDefinition(nextNode, currentWord + c, targetDefinition, words);
    }
}

string Dictionary::toLowercase(const string& str) {
    string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string Dictionary::search(const string& query) {
    string normalizedQuery = toLowercase(query);

    if (root == nullptr)
        return "Not found";

    Trie* temp = root;

    for (int i = 0; i < normalizedQuery.length(); i++) {
        temp = temp->map[normalizedQuery[i]];
        if (temp == nullptr)
            break;
    }

    if (temp != nullptr && temp->isEndOfName)
        return temp->definition;
    vector<string> wordsWithDefinition = searchWordsByDefinition(normalizedQuery);
    if (!wordsWithDefinition.empty()) {
        string result;
        for (const string& word : wordsWithDefinition) {
            result += word + ", ";
        }
        result.erase(result.length() - 2); // Remove the trailing comma and space
        return result;
    }

    return "Not found";
}

void Dictionary::editDefinition(const string& st, string newMeaning)
{

    if (root == NULL)
        return;

    Trie* temp = root;



    for (int i = 0; i < st.length(); i++) {
        temp = temp->map[st[i]];
        if (temp == NULL)
            return;
    }



    if (temp->isEndOfName)
        temp->definition = newMeaning;
    return;
}

void Dictionary::addToFavoriteList(const string& st)
{
    ofstream myfile("FavoriteList.txt", ios::app); // Append mode
    if (myfile.is_open())
    {
        string meaning = searchKeyword(st);
        if (meaning != "Not found")
        {
            myfile << st << ": " << meaning << '\n';
            cout << "Successfully added to your favorite list" << endl;
        }
        else
        {
            cout << "The word \"" << st << "\" does not exist in the dictionary." << endl;
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

void Dictionary::addToHistory(const string& st)
{
    ofstream foutput;
    ifstream finput;
    finput.open("HistoryList.txt");
    foutput.open("HistoryList.txt", ios::app);

    if (finput.is_open())
        foutput << st << "\n";

    finput.close();
    foutput.close();
}

void Dictionary::viewFavoriteList()
{
    string line;
    ifstream myfile("FavoriteList.txt");
    if (myfile.is_open())
    {
        int count = 0;
        while (getline(myfile, line))
        {
            size_t colonPos = line.find(": ");
            if (colonPos != string::npos)
            {
                string word = line.substr(0, colonPos);
                string definition = line.substr(colonPos + 2);
                cout << count + 1 << ". Word: " << word << endl;
                cout << "   Definition: " << definition << endl;
                count++;
            }
        }
        myfile.close();

        if (count == 0)
        {
            cout << "Your favorite list is empty." << endl;
        }
    }
    else
    {
        cout << "Unable to open file";
    }
}
void Dictionary::removeFromFavoriteList(const string& st) {
    ifstream favFile("FavoriteList.txt");
    vector<string> lines;
    string line;

    if (!favFile.is_open()) {
        cout << "Unable to open the favorite list file." << endl;
        return;
    }

    while (getline(favFile, line)) {
        if (line != st) {
            lines.push_back(line);
        }
    }

    favFile.close();

    ofstream outFile("FavoriteList.txt");
    for (const string& l : lines) {
        outFile << l << '\n';
    }

    outFile.close();

    cout << "Word removed from your favorite list." << endl;
}
void Dictionary::viewHistoryOfSearchWord()
{
    string line;
    ifstream myfile("HistoryList.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}


void Dictionary::removeWord(const string& word) {
    Trie* current = root;
    for (char ch : word) {
        if (current->map.find(ch) == current->map.end()) {
            cout << "The word \"" << word << "\" does not exist in the dictionary." << endl;
            return;
        }
        current = current->map[ch];
    }

    if (!current->isEndOfName) {
        cout << "The word \"" << word << "\" does not exist in the dictionary." << endl;
        return;
    }

    // If word found, mark the last node as not end of word
    current->isEndOfName = false;
    cout << "Successfully removed the word \"" << word << "\" from the dictionary." << endl;
}
void Dictionary::resetDictionary() {
    delete root;
    root = nullptr;
}

void Dictionary::viewRandomWord() {
    Trie* current = root;
    if (current->map.empty()) {
        cout << "Dictionary is empty. No word to view." << endl;
        return;
    }

    // Seed the random number generator
    srand(time(NULL));

    vector<string> words;
    getAllWords(current, "", words);

    // Pick a random word from the list
    if (words.empty()) {
        cout << "Dictionary is empty. No word to view." << endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, words.size() - 1);

    int randomIndex = dis(gen);
    string randomWord = words[randomIndex];

    // Display the randomly picked word and its definition
    current = root;
    for (int i = 0; i < randomWord.length(); i++) {
        current = current->map[randomWord[i]];
    }

    cout << "Random Word: " << randomWord << endl;
    cout << "Definition: " << current->definition << endl;
}

void Dictionary::getAllWords(Trie* node, string currentWord, vector<string>& words) {
    if (node->isEndOfName) {
        words.push_back(currentWord);
    }

    for (auto& it : node->map) {
        char c = it.first;
        Trie* nextNode = it.second;
        getAllWords(nextNode, currentWord + c, words);
    }
}
void Dictionary::getAllDefinitions(Trie* node, string prefix, vector<string>& allDefinitions) {
    if (node->isEndOfName) {
        allDefinitions.push_back(node->definition);
    }

    for (auto& it : node->map) {
        Trie* child = it.second;
        getAllDefinitions(child, prefix + it.first, allDefinitions);
    }
}


void Dictionary::viewWords(int numWords) {
    Trie* current = root;
    if (current->map.empty()) {
        cout << "Dictionary is empty. No words to view." << endl;
        return;
    }

    vector<string> words;
    getAllWords(current, "", words);

    if (words.empty()) {
        cout << "Dictionary is empty. No words to view." << endl;
        return;
    }

    cout << "Viewing " << min(numWords, static_cast<int>(words.size())) << " words from the dictionary:" << endl;

    for (int i = 0; i < min(numWords, static_cast<int>(words.size())); i++) {
        current = root;
        string currentWord = words[i];

        for (char c : currentWord) {
            current = current->map[c];
        }

        cout << i + 1 << ". Word: " << currentWord << endl;
        cout << "   Definition: " << current->definition << endl;
    }
}

WordGuessQuestion Dictionary::getRandomWordGuessQuestion() {
    WordGuessQuestion question;

    Trie* current = root;
    vector<string> words;
    getAllWords(current, "", words);

    if (words.empty()) {
        question.word = "No words in the dictionary";
        return question;
    }

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, words.size() - 1);

    int randomIndex = dis(gen);
    string randomWord = words[randomIndex];

    current = root;
    for (char c : randomWord) {
        current = current->map[c];
    }

    question.word = randomWord;
    question.correctDefinition = current->definition;

    vector<string> allDefinitions;
    getAllDefinitions(root, "", allDefinitions);

    // Remove all occurrences of the correct definition from all definitions
    vector<string> filteredDefinitions;
    for (const string& def : allDefinitions) {
        if (def != question.correctDefinition) {
            filteredDefinitions.push_back(def);
        }
    }

    allDefinitions = filteredDefinitions;


    // Shuffle all definitions
    std::shuffle(allDefinitions.begin(), allDefinitions.end(), gen);

    int numOptions = 4;
    question.options.push_back(question.correctDefinition); // Add the correct definition as an option

    // Add distinct incorrect definitions as options
    for (const string& incorrectDefinition : allDefinitions) {
        question.options.push_back(incorrectDefinition);
        if (question.options.size() >= numOptions) {
            break;
        }
    }

    // Shuffle the options
    std::shuffle(question.options.begin(), question.options.end(), gen);

    return question;
}
/*
WordGuessQuestion Dictionary::getRandomDefGuessQuestion() {
    WordGuessQuestion question;

    Trie* current = root;
    vector<string> words;
    getAllWords(current, "", words);

    if (words.empty()) {
        question.word = "No words in the dictionary";
        return question;
    }

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, words.size() - 1);

    int randomIndex = dis(gen);
    string randomWord = words[randomIndex];

    current = root;
    for (char c : randomWord) {
        current = current->map[c];
    }

    question.correctDefinition = randomWord;
    question.word = current->definition;

    vector<string> allDefinitions;
    vector<string> incorrectWords;
    getAllDefinitions(root, "", allDefinitions);
    Trie* current_test = root;
    vector<string> def;
    getAllWordsWithDifferentDefinition(current_test, "", question.word, def);
    std::shuffle(def.begin(), def.end(), gen);

    incorrectWords= def.size() > 3 ? vector<string>(def.begin(), def.begin() + 3) : def;
    if (incorrectWords.size() < 3) {
        cout<< "Not enough words with distinct definitions";

    }
    question.options.push_back(question.correctDefinition); // Add the correct answer as an option

    // Add distinct incorrect answers as options
    for (const string& incorrectWord : incorrectWords) {
        question.options.push_back(incorrectWord);
        if (question.options.size() >= 4) {
            break;
        }
    }

    // Shuffle the options
    std::shuffle(question.options.begin(), question.options.end(), gen);

    return question;
}
*/
WordGuessQuestion Dictionary::getRandomDefGuessQuestion() {
    WordGuessQuestion question;

    Trie* current = root;
    vector<string> words;
    getAllWords(current, "", words);

    if (words.empty()) {
        question.word = "No words in the dictionary";
        return question;
    }

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, words.size() - 1);

    int randomIndex = dis(gen);
    string randomWord = words[randomIndex];

    current = root;
    for (char c : randomWord) {
        current = current->map[c];
    }

    question.correctDefinition = randomWord;
    question.word = current->definition;


    vector<string> options;

    for (const string& word : words) {
        current = root;
        for (char c : word) {
            current = current->map[c];
        }
        if (current->definition != question.word) {
            options.push_back(word);
        }
    }

    if (options.size() < 3) {
        question.options.push_back(question.correctDefinition); // Add the correct answer as the only option
        question.word = "Not enough words with distinct definitions";
        return question;
    }

    // Randomly select 3 options from the list of options
    std::shuffle(options.begin(), options.end(), gen);
    question.options.push_back(question.correctDefinition); // Add the correct answer as an option
    for (size_t i = 0; i < 3; ++i) {
        question.options.push_back(options[i]);
    }

    // Shuffle the options
    std::shuffle(question.options.begin(), question.options.end(), gen);

    return question;
}

vector<string> Dictionary::autocomplete(const string& prefix) {
    vector<string> suggestions;
    Trie* node = root;

    // Traverse to the node representing the last character of the prefix
    for (char c : prefix) {
        if (!node->map.count(c)) {
            return suggestions; // Prefix not found in dictionary
        }
        node = node->map[c];
    }

    // Traverse the subtree under the prefix node to find all possible suggestions
    autocomplete(node, prefix, suggestions);

    return suggestions;
}

void Dictionary::autocomplete(Trie* node, string currentWord, vector<string>& suggestions) {
    if (node->isEndOfName) {
        suggestions.push_back(currentWord);
    }

    for (auto& it : node->map) {
        char c = it.first;
        Trie* nextNode = it.second;
        autocomplete(nextNode, currentWord + c, suggestions);
    }
}

