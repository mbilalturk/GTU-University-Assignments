#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <vector>
#include "os.h"

using namespace std;

// File class which inherited from OS
class File : public program::OS {
    public:
        File(string fileName) : name(fileName) { 
            createdTime = createTime();
            path = setPath(rootDirectory,currentDirectory);
            byte = "25345Bytes";
            updateByte("storage.txt");
        }

        void cat(string fileName) const override;

        string setPath(Directory* root, Directory* current) override;
        void addContent(string text);
        void setByte() {
            byte = to_string(sizeof(content)*1024);
            updateByte("storage.txt");
        }

        string getPath() const { return path; }
        string getName() const { return name; }
        string getTime() const { return createdTime; };
        string getByte() const { return byte; };
        string getContent() const { return content; }

        ~File() = default;
    private:
        void updateByte(string fileName);
        string content;
        string name;
        string path;
        string createdTime;
        string byte;
};

#endif
