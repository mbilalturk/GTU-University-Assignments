#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "os.h"
#include "directory.h"

using namespace std;

// Inıtılization of static variables
Directory* program::OS::rootDirectory = nullptr;
Directory* program::OS::currentDirectory = nullptr;

// A function that takes input from user
void program::Prepare::getCommand(Directory& root) const {
    string command;

    do {
        cout << "> ";
        getline(cin, command);
        applyCommand(root, command);
        try {
            // If command is not valid and if command is ls, wont write to a txt file
            if(isValid(command) && command.find("ls") == std::string::npos)
                save(command.append("\n"));
        }
        catch(invalid_argument e) {}
    }
    while(command != "exit");
}

// A function that applies command according to user's input
void program::Prepare::applyCommand(Directory& root, string command) const {
    try {
        if(isValid(command)) {
            // Call appropriate function according to input
            if(command.find("ls") != std::string::npos) {
                // Determine how directories and files will be output
                if(command.size() == 2)
                    root.ls(0);
                else
                    root.ls(1);
            }
            else if(command.find("mkdir") != std::string::npos) {
                int indexOfSpace = command.find_first_of(' ');
                string dirName = command.substr(indexOfSpace+1,command.size());
                root.mkdir(dirName); 
            }
            else if(command.find("rm") != std::string::npos) {
                int indexOfSpace = command.find_first_of(' ');
                string dirName = command.substr(indexOfSpace+1,command.size());
                root.rm(dirName); 
            }
            else if(command.find("cd") != std::string::npos) {
                // If user typed path, determine directoryies and go to them one by one
                if(command.find("/") != std::string::npos) {
                    vector<int> index;
                    index.push_back(3);
                    for(int i=0; i<command.size(); ++i) {
                        if(command[i] == '/')
                            index.push_back(i+1);
                    }
                    index.push_back(command.size()+1);
                    for(int i=0; i<index.size()-1; ++i) {
                        string dirName = command.substr(index.at(i), index.at(i+1)-(index.at(i)+1));
                        root.cd(dirName);
                    }
                }
                // If user only directory name, go there
                else {
                    int indexOfSpace = command.find_first_of(' ');
                    string dirName = command.substr(indexOfSpace+1,command.size());
                    root.cd(dirName);   
                }   
            }
            else if(command.find("cp") != std::string::npos) {
                int indexOfFirstSpace = command.find_first_of(' ');
                int indexOfSecondSpace = command.find_last_of(' ');

                string sourceName = command.substr(indexOfFirstSpace+1,indexOfSecondSpace-(indexOfFirstSpace+1));
                string destinationName = command.substr(indexOfSecondSpace+1, command.size());

                // If any file in users OS will be copied, call this cp function that takes one parameter,
                // else call other cp function
                if(destinationName == ".")
                    root.cp(sourceName);
                else
                    root.cp(sourceName, destinationName);
            }
            else if(command.find("cat") != std::string::npos) {
                // Determine haw many files will be output, 
                vector<int> index;
                for(int i=0; i<command.size(); ++i) {
                    if(command[i] == ' ')
                        index.push_back(i+1);
                }
                index.push_back(command.size()+1);
                for(int i=0; i<index.size()-1; ++i) {
                    string dirName = command.substr(index.at(i), index.at(i+1)-(index.at(i)+1));
                    root.cat(dirName);
                }
            }
            else if(command.find("touch") != std::string::npos) {
                int indexOfSpace = command.find_first_of(' ');
                string dirName = command.substr(indexOfSpace+1,command.size());
                root.touch(dirName); 
            }
            else if(command.find("ln") != std::string::npos) {
                int indexOfFirstSpace = command.find_first_of(' ');
                int indexOfSecondSpace = command.find_last_of(' ');

                string sourceName = command.substr(indexOfFirstSpace+1,indexOfSecondSpace-(indexOfFirstSpace+1));
                string destinationName = command.substr(indexOfSecondSpace+1, command.size());
                root.ln(sourceName, destinationName);
            }
        }
    }
    catch(const std::out_of_range& e) {
        cout << command << ": missing operand\n";
    }
    catch(const invalid_argument& e) {
        cout << command << ": command not found\n";
    }
    
}

// Check if the command is valid
bool program::Prepare::isValid(string command) const {
    if(command.find("ls") != std::string::npos) {
        if(command.size() == 2)  
            return true;
        else if(command.size() > 2) {
            string subdir = command.substr(2, command.size());
            if(subdir != " -R")
                throw invalid_argument("");
            return true;
        }
        else
            throw invalid_argument("");
        return true;
    }
    else if(command.find("mkdir") != std::string::npos) {
        if(command.at(5) != ' ')
            throw invalid_argument("");
        return true;
    }
    else if(command.find("rm") != std::string::npos) {
        if(command.at(2) != ' ')
            throw invalid_argument("");
        return true;
    }
    else if(command.find("cd") != std::string::npos) {
        if(command.find("/") != std::string::npos) {
            if(command.at(2) != ' ')
                throw invalid_argument("");
            return true;
        }
        else {
            if(command.at(2) != ' ')
                throw invalid_argument("");
            return true;
        }
    }   
    else if(command.find("cp") != std::string::npos) {
        int indexOfFirstSpace = command.find_first_of(' ');
        string substr = command.substr(indexOfFirstSpace+1,command.size());

        indexOfFirstSpace = substr.find_first_of(' ');
        int indexOfSecondSpace = substr.find_last_of(' ');

        if(command.at(2) != ' ' || substr.find(' ') == std::string::npos || indexOfFirstSpace != indexOfSecondSpace)
            throw invalid_argument("");        
        return true;
    }
    else if(command.find("cat") != std::string::npos) {
        if(command.at(3) != ' ')
            throw invalid_argument("");
        return true;
    }
    else if(command.find("touch") != std::string::npos) {
        if(command.at(5) != ' ')
            throw invalid_argument("");
        return true;
    }
    else if(command.find("ln") != std::string::npos) {
        int indexOfFirstSpace = command.find_first_of(' ');
        string substr = command.substr(indexOfFirstSpace+1,command.size());

        indexOfFirstSpace = substr.find_first_of(' ');
        int indexOfSecondSpace = substr.find_last_of(' ');

        if(command.at(2) != ' ' || substr.find(' ') == std::string::npos || indexOfFirstSpace != indexOfSecondSpace)
            throw invalid_argument("");        
        return true;
    }

    throw invalid_argument("");
    return true;
}

// Hold the time when directory or file is created 
string program::OS::createTime() const {
    time_t currentTime = time(nullptr);

    tm* timeInfo = localtime(&currentTime);

    char timeBuffer[80];
    strftime(timeBuffer, sizeof(timeBuffer), "%b %d %H:%M", timeInfo);

    return timeBuffer;
}

// Save the command to a txt file so that all commands that have been taken will be saved
void program::Prepare::save(string commmand) const {
    ofstream out("commands.txt", ios::app);

    if(!out.is_open()) {
        cerr << "File could not open";
        return;
    }

    out << commmand;

    out.close();
}

// Reload the commands have been taken before
void program::Prepare::reload(Directory& root) const {
    fstream in;
    in.open("commands.txt");

    if(!in.is_open()) {
        cerr << "File could not open\n";
        return;
    }

    string command;
    while(getline(in,command)) {
        command.erase(command.size());
        applyCommand(root, command);
    }

    in.close();
}
