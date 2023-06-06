#ifndef PASSWORDMANAGER_FUNCTIONS_H
#define PASSWORDMANAGER_FUNCTIONS_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <random>

/**
 * \ brief Displays the available options in the Password Manager program.
 */
auto options_screen(){
    std::cout << "1. Search password\n";
    std::cout << "2. Sort passwords\n";
    std::cout << "3. Add password\n";
    std::cout << "4. Edit password\n";
    std::cout << "5. Remove password\n";
    std::cout << "6. Add category\n";
    std::cout << "7. Remove category\n";
    std::cout << "8. Show options\n";
    std::cout << "9. Create file\n";
    std::cout << "10. Exit\n";
}
/**
 * \ brief Converts the contents of a text file into a vector of vectors of strings.
 * \ param fileName The name of the text file.
 * \ return A vector of vectors of strings containing the split words from the file.
 */
std::vector<std::vector<std::string>> file_to_vector(const std::string& fileName) {
    std::vector<std::vector<std::string>> wordVector;
    std::ifstream readFile(fileName + ".txt");
    if (readFile.is_open()) {
        std::string line;
        while (std::getline(readFile, line)) {
            std::vector<std::string> words;
            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                words.push_back(word);
            }
            wordVector.push_back(words);
        }
        readFile.close();
    }
    return wordVector;
}
/**
 * \ brief Displays the contents of a vector of vectors of strings.
 * \ param words A vector of vectors of strings.
 */
auto display_vector(std::vector<std::vector<std::string>> words){
    for (const auto& innerVector : words) {
        for (const auto& word : innerVector) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }
}
/**
 * \ brief Sorts a vector of vectors of strings based on a single column.
 * \ param words A vector of vectors of strings.
 * \ param position The index of the column to sort.
 * \ return The sorted vector of vectors of strings.
 */
auto sort_vector(std::vector<std::vector<std::string>> words, int position){
    std::ranges::sort(words.begin(), words.end(), [position](const std::vector<std::string>& a, const std::vector<std::string>& b) -> bool {
        return std::lexicographical_compare(a[position].begin(), a[position].end(), b[position].begin(), b[position].end(),
                                            [](char c1, char c2) {
                                                return std::tolower(c1) < std::tolower(c2);
                                            });
    } );
    return words;
}
/**
 * \ brief Sorts a vector of vectors of strings based on two columns.
 * \ param words A vector of vectors of strings.
 * \ param position1 The index of the first column to sort.
 * \ param position2 The index of the second column to sort.
 * \ return The sorted vector of vectors of strings.
 */
auto sort_vector(std::vector<std::vector<std::string>> words, int position1, int position2) {
    std::ranges::sort(words.begin(), words.end(), [position1, position2](const std::vector<std::string>& a, const std::vector<std::string>& b) -> bool {
        return std::lexicographical_compare(a[position1].begin(), a[position1].end(), b[position1].begin(), b[position1].end(),
                                            [](char c1, char c2) {
                                                return std::tolower(c1) < std::tolower(c2);
                                            }) ||
               std::lexicographical_compare(a[position2].begin(), a[position2].end(), b[position2].begin(), b[position2].end(),
                                            [](char c1, char c2) {
                                                return std::tolower(c1) < std::tolower(c2);
                                            });
    });
    return words;
}
/**
 * \ brief Displays the sorted passwords in the file.
 */
auto sort_passwords(){
    std::cout << "Provide file name:\n";
    std::string fileName;
    std::cin>>fileName;
    std::ifstream file(fileName + ".txt");
    if(file.is_open()) {
        std::cout << "How do you want to sort your passwords?\n";
        std::cout << "1. By name\n";
        std::cout << "2. By category\n";
        std::cout << "3. By name and category\n";
        int option;
        std::cin >> option;
        std::vector<std::vector<std::string>> words = file_to_vector(fileName);
        switch (option) {
            case 1:
                display_vector(sort_vector(words, 0));
                break;
            case 2:
                display_vector(sort_vector(words, 2));
                break;
            case 3:
                display_vector(sort_vector(words, 0, 2));
        }
        file.close();
    }
    else
        std::cout << "File does not exist\n";
}
/**
 * \ brief Searches for passwords in the file based on name or category.
 */
auto search_password(){
    std::cout<< "What file do you want to open?\n";
    std::string fileName;
    std::cin >> fileName;
    std::ifstream readFile(fileName + ".txt");
    if(readFile.is_open()){
        std::string line;
        std::string findPassword;
        std::cout << "What password you want to find (provide name or category)\n";
        std::cin >> findPassword;
        while (std::getline(readFile, line)){
            if(line.find(findPassword) != std::string::npos)
                std::cout << line << std::endl;
        }
        readFile.close();
    }
    else
        std::cout << "File don't exist";
}
/**
 * \ brief Generates a random password based on the provided parameters.
 * \ param length The length of the generated password.
 * \ param uppercase Whether to include uppercase letters in the password.
 * \ param lowercase Whether to include lowercase letters in the password.
 * \ param specialChars Whether to include special characters in the password.
 * \ return The generated password.
 */
std::string generate_password(int length, bool uppercase, bool lowercase, bool specialChars)
{
    std::string characters = "";
    if (uppercase)
        characters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (lowercase)
        characters += "abcdefghijklmnopqrstuvwxyz";
    if (specialChars)
        characters += "!@#$%^&*()";
    std::string password = "";
    for (int i = 0; i < length; ++i)
    {
        int randomIndex = rand() % characters.length();
        password += characters[randomIndex];
    }
    return password;
}
/**
 * \ brief Adds a new password to the file.
 */
auto add_password(){
    std::string password;
    std::string name;
    std::string category;
    std::string yesNo;
    std::string fileName;
    std::string line;
    int choice;
    std::cout << "What file do you want to open?\n";
    std::cin >> fileName;
    std::ifstream readFile(fileName + ".txt");
    if(readFile.is_open()) {
        std::cout << "Provide name for your password: \n";
        std::cin >> name;
        bool unique = true;
        while (std::getline(readFile, line))
            if (line.find(name) != std::string::npos)
                unique = false;
        if (unique) {
            std::cout << "How do you want to provide password?\n 1. Type own \n 2. Generate automaticly\n";
            std::cin >> choice;
            switch (choice) {
                case 1:
                    std::cout << "Provide password: \n";
                    std::cin >> password;
                    break;
                case 2:
                    int length;
                    bool uppercase;
                    bool lowercase;
                    bool specialChars;
                    std::cout << "What length do you want your password to be?\n";
                    std::cin >> length;
                    std::cout << "You want to have lowercase's? y/n\n";
                    std::cin >> yesNo;
                    if (yesNo == "y")
                        lowercase = true;
                    else
                        lowercase = false;
                    std::cout << "You want to have uppercase's? y/n\n";
                    std::cin >> yesNo;
                    if (yesNo == "y")
                        uppercase = true;
                    else
                        uppercase = false;
                    std::cout << "You want to have special characters? y/n\n";
                    std::cin >> yesNo;
                    if (yesNo == "y")
                        specialChars = true;
                    else
                        specialChars = false;

                    password = generate_password(length, uppercase, lowercase, specialChars);
                    break;
                default:
                    std::cout << "Wrong command";
                    break;
            }
            std::cout << "Provide category: \n";
            std::cin >> category;
            std::ofstream write(fileName + ".txt", std::ios_base::app);
            write << name << " " << password << " " << category << std::endl;
            write.close();
        } else
            std::cout << "Name have to be unique\n";
    }
    else
        std::cout << "File don't exist\n";
}
/**
 * \ brief Deletes a password from the file based on the provided string.
 * \ param filename The file name.
 * \ param searchStr The string to search for and delete.
 */
auto delete_password(const std::string& filename, const std::string& searchStr)
{
    std::ifstream inputFile(filename);
    std::ofstream outputFile(filename + ".tmp");
    std::string line;
    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            if (line.find(searchStr) != std::string::npos) {
                continue;
            }
            outputFile << line << std::endl;
        }

        inputFile.close();
        outputFile.close();
        std::remove(filename.c_str());
        std::rename((filename + ".tmp").c_str(), filename.c_str());
    } else {
        std::cout << "File does not exist." << std::endl;
    }
}
/**
 * \ brief Creates a new file.
 */
auto create_file(){
    std::string fileName;
    std::cout << "Provide name for file you want to create:\n";
    std::cin >> fileName;
    std::ofstream outputFile(fileName + ".txt");
    if(outputFile.is_open()){
        std::cout <<"File created successfully\n";
        outputFile.close();
    }
    else
        std::cout << "Fail to create file\n";
}


#endif //PASSWORDMANAGER_FUNCTIONS_H
