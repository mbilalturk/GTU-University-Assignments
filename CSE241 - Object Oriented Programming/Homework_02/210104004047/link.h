#ifndef LINK_H
#define LINK_H

#include <iostream>
#include <string>
#include <vector>
#include "file.h"
#include "os.h"

using namespace std;
using namespace program;

// Link class which inherited from OS
class Link : public OS {
    public:
        Link(Directory* dirPointer, string fileName) {
            name = fileName;
            pointerD = dirPointer;
            pointerF = nullptr;
        }

        Link(File* dirPointer, string fileName) {
            name = fileName;
            pointerD = nullptr;
            pointerF = dirPointer;
        }

        void ln(string sourceFile, string destinationFile) override { };

        Directory* getPointerD() { return pointerD; }
        File* getPointerF() {return pointerF; }
        string getName() { return name; }     

        void setName(string fileName);
        void setPointerD(Directory* newPointer);
        void setPointerF(File* newPointer);

        ~Link() = default;
    private:
        Directory* pointerD;
        File* pointerF;
        string name;
};

#endif
