#ifndef DIRECTORY_H
#define DIRECToRY_H

#include <vector>
#include <string>
#include <iterator>
#include "os.h"
#include "file.h"
#include "link.h"

using std::string;
using std::vector;
using namespace program;

// Directory class which inherited from OS
class Directory : public OS {
    public:
        Directory(string fileName, Directory* newParent = nullptr) : name(fileName), parent(newParent) { 
            createdTime = createTime();
            path = setPath(rootDirectory, currentDirectory);
            updateByte("storage.txt");
        }
        string getName() const { return name; }
        string getTime() const { return createdTime; }
        string getPath() const { return path; }
        Directory* getParent() const;
        
        void ls(bool recursive) override;
        void lsRecursive(Directory* current, int index) override;
        void mkdir(string dirName) override;
        void cd(string dirName) override;
        void rm(string dirName) override;
        void cp(string sourceDir, string destinationDir) override;
        void cp(string sourceDir);
        void cat(string fileName) const override;
        void touch(string fileName) override;
        void ln(string sourceFile, string destinationFile) override;

        string setPath(Directory* root, Directory* current) override;
        void setName(string fileName) { name = fileName; }

        // Iterators
        Directory* begin();
        Directory* end();

        ~Directory();
    private:
        const int SENTINEL_VALUE = -1; 

        // Read file to print to the screen if is needed
        void readFile(string fileName) const; 

        //  Check if directory exist, if it exist return index, otherwise -1
        int hasDir(string fileName) const;

         //  Check if file exist, if it exist return index, otherwise -1
        int hasFile(string fileName) const;

        // A function used for copying directories with subdirectories
        void recursiveCopy(Directory* sourceDir, Directory* destinationDir, int i); 

        // A function that updates the byte in storage.txt
        void updateByte(string fileName);  

        // A function that saves the directories and files in os.txt
        // It is actually os
        void saveFile(Directory* current, int index) const;

        // Empty the file
        void emptyFile() const;

        string name;
        string createdTime;
        string path;
        Directory* parent;
        vector<Directory*> directories; 
        vector<File> files;
        vector<Link> linkNames;
};

#endif
