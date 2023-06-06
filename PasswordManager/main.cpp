#include <iostream>
#include "functions.h"


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int option;
    std::cout << "Welcome to password Manager, choose one of the options below: \n";
    options_screen();

    while(option != 10) {
        std::cin >> option;
        std::string fileName;
        std::string passwordName;
        std::string yesNo;
        std::ifstream readFile(fileName);
        switch (option) {

            case 1:
                search_password();
                break;
            case 2:
                sort_passwords();
                break;
            case 3:
                add_password();
                break;
            case 5:
                std::cout<<"What file do you want to open?\n";
                std::cin >> fileName;
                std::cout << "What password do you want to delete? (provide name of password)\n";
                std::cin >> passwordName;
                std::cout <<"Are you sure? y/n\n";
                std::cin >> yesNo;
                if(yesNo == "y")
                    delete_password(fileName + ".txt", passwordName);
                else
                    continue;
                break;
            case 7:
                //this code works the same as "delete password" in case 5, I can simply just copy whole thing
                //because names of passwords have to be unique
                std::cout<<"What file do you want to open?\n";
                std::cin >> fileName;
                std::cout << "What password do you want to delete? (provide category of password)\n";
                std::cin >> passwordName;
                std::cout <<"Are you sure? y/n\n";
                std::cin >> yesNo;
                if(yesNo == "y")
                    delete_password(fileName + ".txt", passwordName);
                else
                    continue;
                break;
            case 8:
                options_screen();
                break;
            case 9:
                create_file();
                break;
            case 10:
                return 0;
            default:
                std::cout << "Wrong command\n";
                break;
        }

        std::cout << "Done, if you want to show options again, type 8, if you want to exit, type 10\n";
    }
}