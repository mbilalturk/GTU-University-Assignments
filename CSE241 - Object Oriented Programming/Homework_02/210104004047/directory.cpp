#include <iostream>
#include <fstream>
#include <filesystem>
#include <iterator>
#include "os.h"
#include "file.h"
#include "directory.h"

using namespace std;
using namespace filesystem;

// A function that lists the files and directories recursively with sub directories
void Directory::lsRecursive(Directory* current, int index) {
    if (current == nullptr)
        return;

    for (int i = 0; i < index; ++i)
        cout << "  ";
    cout << "D " << current->getName() << "             " << current->getTime() << endl;

    for (const auto& file : current->files) {
        for (int i = 0; i < index + 1; ++i)
            cout << "  ";
        cout << "F " << file.getName() << "       " << file.getTime() << "        " << file.getByte() << endl;
    }

    for (const auto& subdir : current->directories) {
        lsRecursive(subdir, index + 1);
    }
}

// A function that list the directories and files one by one, recursively or not
void Directory::ls(bool recursive) {
    if (recursive) {
        Directory* temp = currentDirectory;
        lsRecursive(temp, 0);
    } else {
        Directory* temp = currentDirectory;

        for(int i=0; i<getDepth(); ++i){
            cout << "D";
            for(int j =0; j<=i; ++j)
                cout << " .";

            if(temp != nullptr) {
                cout <<  "             " << temp->getTime() << endl;
                temp = temp->getParent();
            }
        }

        Directory* iterator = OS::currentDirectory;
        for(auto it : iterator->directories) {
            cout << "D " << it->getName() << "             " << it->getTime() << endl;
        }

        iterator = OS::currentDirectory;
        for(auto it : iterator->files) {
            cout << "F " << it.getName() << "       " << it.getTime() << "        " << it.getByte() << endl;
        }

        iterator = OS::currentDirectory;
        for(auto it : iterator->linkNames) {
            cout << "* " << it.getName() << endl;
        }
    }
}

// A function that is uses for change the current directory
void Directory::cd(string dirName) {
    int index = hasDir(dirName);
    Directory* iterator = OS::currentDirectory;

    if(index != SENTINEL_VALUE) {
        OS::currentDirectory = iterator->directories[index];
        setDepth(getDepth() + 1);
    }
    else {
        for(int i=0; i<iterator->linkNames.size(); ++i) {
            if(linkNames[i].getName() == dirName)
                index = i;
        }
        if(index != SENTINEL_VALUE) {
            Directory* temp = linkNames[index].getPointerD();
            if(temp != nullptr) {
                index = hasDir(temp->getName());
                OS::currentDirectory = iterator->directories[index];
                setDepth(getDepth() + 1);
            }
            else
                cout << dirName << " not found!\n";
        }
        else if(dirName == "..") {
            if(getDepth() > 1) {
                OS::currentDirectory = OS::currentDirectory->getParent();
                setDepth(getDepth() - 1);
            }
            else
                cout << "cd: cannot go back, already at root directory\n";
        }
        else if(dirName == ".") {
            OS::currentDirectory = OS::rootDirectory;
            setDepth(1);
        }
        else
            cout << dirName << " not found!\n";
    }
}

// A function that makes a directory and clear the os.txt then rewrite to it with a new directory
void Directory::mkdir(string dirName) {
    Directory* root = OS::rootDirectory;
    Directory* iterator = OS::currentDirectory;

    if(hasDir(dirName) == SENTINEL_VALUE) {
        iterator->directories.push_back(new Directory(dirName, iterator));
        emptyFile();
        saveFile(root, 0);
    }
    else {
        cout << "mkdir: cannot create directory '" + dirName + "': dir exists\n";
    }
}

// A function that removes the file and directories if they are avilable to remove
void Directory::rm(string dirName) {
    Directory* root = OS::rootDirectory;
    Directory* iterator = OS::currentDirectory;

    int index = hasDir(dirName);

    if(index != SENTINEL_VALUE) {
        if(iterator->directories[index]->directories.size() == 0) {
            delete iterator->directories[index];
            iterator->directories.erase(iterator->directories.begin() + index);
            emptyFile();
            saveFile(root, 0);
        }
        else
            cout << "rm: cannot remove '" << dirName << "': Directory is not empty\n";
    }
    else {
        index = hasFile(dirName);
        if(index != SENTINEL_VALUE) {
            iterator->files.erase(iterator->files.begin() + index);
            emptyFile();
            saveFile(root, 0);
        }
        else
            cout << dirName << " not found!\n";
    } 
}

// Output content of the file
void Directory::cat(string fileName) const {
    if(hasDir(fileName) != SENTINEL_VALUE)
        cout << "cat: " << fileName << ": Is a directory\n";
    else if(hasFile(fileName) != SENTINEL_VALUE) {
        Directory* iterator = OS::currentDirectory;
        int index = hasFile(fileName);
        cout << files[index].getContent() << endl;
    }
        // readFile(fileName);
    else 
        cout << "cat: " << fileName << ": No such file or directory\n";
}

// Create a new file
void Directory::touch(string fileName) {
    Directory* iterator = OS::currentDirectory;
    File newFile = File(fileName);
    iterator->files.push_back(newFile);
}

// Link source file with destination file
void Directory::ln(string sourceFile, string destinationFile) {
    Directory* current = OS::currentDirectory;

    if(hasDir(sourceFile) != SENTINEL_VALUE) {
        Directory* sourceDir = current->directories[hasDir(sourceFile)];
        Link temp(sourceDir, destinationFile);
        current->linkNames.push_back(temp);
    }
    else if(hasFile(sourceFile) != SENTINEL_VALUE) {
        File sourceDir = current->files[hasFile(sourceFile)];
        Link temp(&sourceDir, destinationFile);
        current->linkNames.push_back(temp);
    }
    
}

// Copy file from the source to a destination with subdirectories
void Directory::cp(string sourceDirName, string destinationDirName) {          
    mkdir(destinationDirName);
    int indexS = hasDir(sourceDirName);
    int indexD = hasDir(destinationDirName);
    Directory* temp = OS::currentDirectory;
    Directory* sourceDir;
    Directory* destinationDir;

    if(indexS != SENTINEL_VALUE)
        sourceDir = temp->directories[indexS];
    
    if(indexD != SENTINEL_VALUE)
        destinationDir = temp->directories[indexD];
    
    recursiveCopy(sourceDir, destinationDir, 0);
}

// If any file in users OS will be copied, this function will be called
void Directory::cp(string sourceFilePath) {
    // get the desktop path
    string pathName = getenv("HOME");
    filesystem::path desktopPath = filesystem::path(pathName) / "Desktop";

    // add the users input which is path of the file that will be copied to full path
    filesystem::path fullPath = desktopPath / sourceFilePath;
    string fullPathS = fullPath.string();

    // Extract the file name so that file will be created with this name
    int indexOfLastSlash = fullPathS.find_last_of('/');
    string fileName = fullPathS.substr(indexOfLastSlash+1, fullPathS.size()-(indexOfLastSlash+1));

    filesystem::path fullPath1 = filesystem::path(fullPath);

    // Check if path is exist
    if(!exists(fullPath1)) {
        cerr << fullPath1.string() << " does not exist\n";
        return;
    }

    // Check if file is already exist
    if (hasFile(fileName) != SENTINEL_VALUE) {
        cerr << fileName << " already exists\n";
        return;
    }

    Directory* iterator = begin();
    touch(fileName);
    int index = hasFile(fileName);

    fstream in;
    in.open(fullPath);

    if(!in.is_open()) {
        cerr << "File could not open\n";
        return;
    }

    // Copy content of the file to a local file
    string text;
    while(getline(in,text)) 
        files[index].addContent(text);

    // update the byte
    files[index].setByte();

    in.close();
}

// A function used for copying directories with subdirectories
void Directory::recursiveCopy(Directory* sourceDir, Directory* destinationDir, int index) {
    // Copy files
    for(const auto& file : sourceDir->files) {
        destinationDir->files.push_back(File(file.getName()));
    }

    // Copy directories with subdirectories
    for(const auto& subdir : sourceDir->directories) {
        string subDirName = subdir->getName();
        Directory* newSubDir = new Directory(subDirName, destinationDir);
        destinationDir->directories.push_back(newSubDir);
        recursiveCopy(subdir, newSubDir, index + 1);
    }
}

// Set the path from root to current
string Directory::setPath(Directory* root, Directory* current) {
    string dirPath = "/";
    Directory* tempC = current;

    while (tempC != root) {
        dirPath = "/" + tempC->getName() + dirPath;
        tempC = tempC->getParent();
    }

    return dirPath;
}

//  Check if directory exist, if it exist return index, otherwise -1
int Directory::hasDir(string dirName) const {
    Directory* iterator = OS::currentDirectory;
    for(int i=0; i<iterator->directories.size(); ++i) {
        if(iterator->directories[i]->getName() == dirName)
            return i;
    }
    return SENTINEL_VALUE;
}

//  Check if file exist, if it exist return index, otherwise -1
int Directory::hasFile(string fileName) const {
    Directory* iterator = OS::currentDirectory;
    for(int i=0; i<iterator->files.size(); ++i) {
        if(iterator->files[i].getName() == fileName)
            return i;
    }
    return SENTINEL_VALUE;
}

// Read file to print to the screen if is needed
void Directory::readFile(string fileName) const {
    fstream in;
    in.open(fileName);

    if(!in.is_open()) {
        cerr << "File could not open\n";
        return;
    }

    string text;
    while(getline(in,text)) 
        cout << text << endl;

    in.close();
}

// A function that saves the directories and files in os.txt
// It is actually operating system
void Directory::saveFile(Directory* current, int index) const {
    ofstream out("os.txt", ios::app);

    if(!out.is_open()) {
        cerr << "File could not open\n";
        return;
    }

    if (current == nullptr)
        return;

    for (int i = 0; i < index; ++i)
        out << "  ";
    out << "D " << current->getName() << endl;

    for (const auto& file : current->files) {
        for (int i = 0; i < index + 1; ++i)
            out << "  ";
        out << "F " << file.getName() << "        " << file.getByte() << endl;
    }

    for (const auto& subdir : current->directories) {
        saveFile(subdir, index + 1);
    }

    out.close();
}

// Empty the file
void Directory::emptyFile() const {
    ofstream out("os.txt");

    if(!out.is_open()) {
        cerr << "File could not open\n";
        return;
    }

    out.close();
}

// A function that updates the byte in storage.txt
void Directory::updateByte(string fileName) {
    fstream in(fileName, ios::in);

    if (!in.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    string line;
    int freeSpace = 0;
    int usedSpace = 0;

    while (getline(in, line)) {
        string key;
        int value;
        int colonIndex = line.find(':');

        if (colonIndex != string::npos) {
            key = line.substr(0, colonIndex);
            value = stoi(line.substr(colonIndex + 1));

            if (key == "FreeSpace") {
                freeSpace = value - 1024;
            } else if (key == "UsedSpace") {
                usedSpace = value + 1024;
            }
        }
    }

    in.close();

    fstream out(fileName, ios::out);

    if (!out.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    out << "FreeSpace: " << freeSpace << endl;
    out << "UsedSpace: " << usedSpace << endl;

    out.close();
}

// Return parent
Directory* Directory::getParent() const {
    return parent;
}

// Iterators
Directory* Directory::begin() {
    auto begin = OS::currentDirectory;
    return begin;
}

Directory* Directory::end() {
    if(!this->directories.empty()) {
        return directories[directories.size()-1] + 1;
    }
    return nullptr;
}

// Destructor
Directory::~Directory() {
    for (auto subdir : directories) {
        delete subdir;
    }
}
