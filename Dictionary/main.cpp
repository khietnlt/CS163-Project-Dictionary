#include "function.h"

int main()
{
    int menuSelect;
    string inputWord, inputMeaning, command, oldMeaning;
    Dictionary test1;
    WordGuessQuestion question;
    vector<string> suggestions;

    int choose = 0;
    cout << "-----WELCOME TO OUR DICTIONARY-----" << endl;
    cout << "1: Dictionary Slang" << endl;
    cout << "2: Dictionary Emotional" << endl;
    cout << "3: Dictionary Eng-Viet" << endl;
    cout << "4: Dictionary Viet-Eng" << endl;
    cout << "Choose Dictionary: ";
    cin >> choose;
    cout << endl;
    test1.chooseDic(choose);

    do
    {
        menu();
        command = "n";
        cout << "Enter your choice: ";
        cin >> menuSelect;

        switch (menuSelect)
        {
        case 1:
            do
            {

                // cin.ignore();
                cout << "Enter a word to search: ";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin, inputWord);

                inputWord = test1.toLowercase(inputWord);

                test1.addToHistory(inputWord);

                auto start = std::chrono::high_resolution_clock::now();
                cout << "Meaning: " << test1.search(inputWord) << endl;
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                std::cout << "Function execution time: " << duration.count() << " seconds" << std::endl;

                if (test1.search(inputWord) != "Not found definition")
                {
                    cout << "Do you want to add this word to your favorite list? (y/n): ";
                    cin >> command;
                    if (command == "y" || command == "Y")
                    {

                        auto start = std::chrono::high_resolution_clock::now();

                        test1.addToFavoriteList(inputWord);
                        // cout << "Successfully added to your favorite list" << endl;
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> duration = end - start;
                        std::cout << "Function execution time: " << duration.count() << " seconds" << std::endl;
                    }
                }
                else
                {
                    
                    suggestions = test1.autocomplete(inputWord);
                    if (!suggestions.empty())
                    {
                        cout << "Suggestions:" << endl;
                        for (const string &suggestion : suggestions)
                        {
                            cout << suggestion << endl;
                        }
                    }
                    
                    

                    // cout << "The word \"" << inputWord << "\" does not exist in the dictionary." << endl;
                    cout << "Do you want to add this word to the dictionary? (y/n): ";
                    cin >> command;
                    if (command == "y" || command == "Y")
                    {
                        cout << "Enter the meaning of the word: ";

                        cin >> inputMeaning;
                        test1.addNewWord(inputWord, inputMeaning);

                        auto start = std::chrono::high_resolution_clock::now();
                        cout << "Successfully added the new word to the dictionary" << endl;
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> duration = end - start;
                        std::cout << "Function execution time: " << duration.count() << " seconds" << std::endl;
                    }
                }
                // cin.ignore();
                cout << "Would you like to continue searching? (y/n): ";
                cin >> command;

            } while (command == "y" || command == "Y");
            break;
        case 2:
            cout << "Enter a word to add to your favorite list: ";

            cin >> inputWord;

            inputWord = test1.toLowercase(inputWord); // Convert input to lowercase

            if (test1.search(inputWord) != "Not found")
            {
                test1.addToFavoriteList(inputWord);

                auto start = std::chrono::high_resolution_clock::now();

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                std::cout << "Function execution time: " << duration.count() << " seconds" << std::endl;
            }
            else
            {
                auto start = std::chrono::high_resolution_clock::now();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                std::cout << "Function execution time: " << duration.count() << " seconds" << std::endl;

                cout << "Sorry, this word is not in the dictionary. Do you want to add this word to the dictionary? (y/n): ";

                cin >> command;
                if (command == "y" || command == "Y")
                {
                    cout << "Enter the meaning of the word: ";

                    cin >> inputMeaning;
                    test1.addNewWord(inputWord, inputMeaning);

                    auto start = std::chrono::high_resolution_clock::now();
                    cout << "Successfully added the new word to the dictionary" << endl;
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;
                    std::cout << "Function execution time: " << duration.count() << " seconds" << std::endl;
                }
            }
            break;

        case 3:
            cout << "This is your favorite list: " << endl;

            test1.viewFavoriteList();
            cout << "Do you want to remove a word from your favorite list? (y/n): ";
            cin >> command;
            if (command == "y" || command == "Y")
            {
                cout << "Enter the word to remove: ";

                cin >> inputWord;
                test1.removeFromFavoriteList(inputWord);

                auto start = std::chrono::high_resolution_clock::now();

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                std::cout << "Function execution time: " << duration.count() << " seconds" << std::endl;
            }
            break;

        case 4:
            cout << "History of searched words: " << endl;
            test1.viewHistoryOfSearchWord();
            break;

        case 5:
            cout << "Enter a new word: ";
            cin >> inputWord;
            cout << "Enter the meaning of the word: ";
            // Ignore the newline character from previous cin
            cin >> inputMeaning;

            test1.addNewWord(inputWord, inputMeaning);

            cout << "Successfully added the new word to the dictionary" << endl;
            break;

        case 6:
            cout << "Enter a word to edit the definition: ";

            cin >> inputWord;
            inputWord = test1.toLowercase(inputWord); // Convert input to lowercase

            oldMeaning = test1.searchKeyword(inputWord);
            if (oldMeaning != "Not found")
            {
                cout << "Old meaning: " << oldMeaning << endl;
                cout << "Enter the new meaning: ";
                cin >> inputMeaning;

                auto start = std::chrono::high_resolution_clock::now();
                test1.editDefinition(inputWord, inputMeaning);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                std::cout << "Function execution time: " << duration.count() << " seconds" << std::endl;
            }
            else
            {
                cout << "The word \"" << inputWord << "\" does not exist in the dictionary." << endl;
                cout << "Do you want to add this word as a new word with the provided meaning? (y/n): ";
                cin >> command;
                if (command == "y" || command == "Y")
                {
                    cout << "Enter the meaning of the word: ";

                    cin >> inputMeaning;

                    auto start = std::chrono::high_resolution_clock::now();
                    test1.addNewWord(inputWord, inputMeaning);
                    cout << "Successfully added the new word to the dictionary" << endl;
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;
                    std::cout << "Function execution time: " << duration.count() << " seconds" << std::endl;
                }
            }
            break;
        case 7:
            cout << "Enter a word to remove from the dictionary: ";

            cin >> inputWord;
            inputWord = test1.toLowercase(inputWord);
            if (test1.searchKeyword(inputWord) != "Not found")
            {

                auto start = std::chrono::high_resolution_clock::now();
                test1.removeWord(inputWord);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                std::cout << "Function execution time: " << duration.count() << " seconds" << std::endl;
            }
            else
            {
                cout << "The word \"" << inputWord << "\" does not exist in the dictionary." << endl;
            }
            break;
        case 8: // Reset the dictionary to its original state
            test1.resetDictionary();
            cout << "The dictionary has been reset to its original state." << endl;
            break;
        case 9:
            test1.viewRandomWord();
            break;
        case 10:
            question = test1.getRandomWordGuessQuestion();

            cout << "Guess the meaning of the word: " << question.word << endl;
            cout << "Options:" << endl;

            for (int i = 0; i < question.options.size(); i++)
            {
                cout << i + 1 << ". " << question.options[i] << endl;
            }

            int userChoice;
            cout << "Enter your choice (1-4): ";
            cin >> userChoice;

            if (userChoice >= 1 && userChoice <= 4)
            {
                if (question.options[userChoice - 1] == test1.searchKeyword(question.word))
                {
                    cout << "Congratulations! That's the correct meaning." << endl;
                }
                else
                {
                    cout << "Oops! That's not the correct meaning." << endl;
                    cout << "The correct meaning is: " << test1.searchKeyword(question.word) << endl;
                }
            }
            else
            {
                cout << "Invalid choice." << endl;
            }

            break;
        case 11:
            question = test1.getRandomDefGuessQuestion();

            cout << "Guess the correct word for the definition:" << endl;
            cout << question.word << endl;

            for (int i = 0; i < question.options.size(); i++)
            {
                cout << i + 1 << ". " << question.options[i] << endl;
            }

            cout << "Enter your choice (1-4): ";
            cin >> userChoice;

            if (userChoice >= 1 && userChoice <= question.options.size())
            {
                if (question.options[userChoice - 1] == question.correctDefinition)
                {
                    cout << "Congratulations! That's the correct word!" << endl;
                }
                else
                {
                    cout << "Sorry, that's not the correct word." << endl;
                    cout << "The correct word is: " << question.correctDefinition << endl;
                }
            }
            else
            {
                cout << "Invalid choice. Please choose a valid option." << endl;
            }
            break;

        
        default:
            cout << "Invalid input. Please choose a valid option." << endl;
            cin.clear(); // Clear the input buffer
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

        if (command == "n" || command == "N")
        {
            cout << "Do you want to continue with other functions of the dictionary? (y/n): ";
            cin >> command;
        }
    } while (command == "y" || command == "Y");

    cout << "Thanks for using our Dictionary.\n";

    return 0;
}
