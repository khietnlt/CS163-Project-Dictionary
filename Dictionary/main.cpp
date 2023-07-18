#include "function.h"

int main()
{
    int menuSelect;
    string inputWord, inputMeaning, command;
    Dictionary test1;

    /*  test1.addNewWord("Alice", "80");
      test1.addNewWord("Pooja", "85");
      test1.addNewWord("Ramesh", "83");
      test1.addNewWord("Mark", "88");*/

    int choose = 0;
    cout << "-----WELCOME TO OUR DICTIONARY-----" << endl;
    cout << "1: Dictionary Slang" << endl;
    cout << "2: Dictionary Emotional" << endl;
    //cout << "3: Dictionary for A" << endl;
    cout << "Choose Dictionary: ";
    cin >> choose;
    cout << endl;
    test1.chooseDic(choose);
    do {


        menu();
        cout << endl;
        fflush(stdin);

        cin >> menuSelect;
        switch (menuSelect)
        {
        case 1:
            cout << "Input a word: ";
            cin >> inputWord;
            test1.addToHistory(inputWord);
            cout << test1.searchKeyword(inputWord) << endl;
            if (test1.searchKeyword(inputWord) != "Not found")
            {
                cout << "You want to add this word to your favorite list? (1/0) ";
                cin >> command;
                if (command == "1")
                {
                    test1.addToFavoriteList(inputWord);
                    cout << "Sucessfully add to your favorite list" << endl;
                }
            }
            break;

        case 2:
            cout << "Enter word to add to favorite list: " << endl;
            cin >> inputWord;
            if (test1.searchKeyword(inputWord) != "Not found") {
                test1.addToFavoriteList(inputWord);
            }
            else {
                cout << "Sorry this word is not in Dictionary. Do you want to add this word to dictionary? (1/0) ";
                cin >> command;
                if (command == "1")
                {
                    cout << "Enter word meaning: ";
                    cin >> inputMeaning;
                    test1.addNewWord(inputWord, inputMeaning);
                    cout << "Sucessfully add new word to dictionary" << endl;
                }
            }
            break;

        case 3:
            cout << "This is your favorite list: " << endl;
            test1.viewFavoriteList();
            break;

        case 4:
            cout << "History of search word: " << endl;
            test1.viewHistoryOfSearchWord();
            break;

        case 5:
            cout << "Enter a new word: ";
            cin >> inputWord;
            cout << "Enter word meaning: ";
            cin >> inputMeaning;
            test1.addNewWord(inputWord, inputMeaning);
            break;

        case 6:
            cout << "Enter word to edit definition: ";
            cin >> inputWord;
            cout << "Enter new meaning: ";
            cin >> inputMeaning;
            test1.editDefinition(inputWord, inputMeaning);
            break;

        case 7:
            cout << "Not ready" << endl;
            break;

        case 8:
            cout << "Not ready" << endl;
            break;

        case 9:
            cout << "Not ready" << endl;
            break;

        default:
            cout << "Invalid input" << endl;
            break;
        }

        fflush(stdin);
        cout << "\nWould you like to continue or exit? (1/0) ";
        cin >> command;
    } while (command == "1");

    cout << "Thanks for using our Dictionary.\n";

    return 0;
}




