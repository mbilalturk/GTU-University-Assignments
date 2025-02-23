#include <string>
#include <fstream>
#include "os.h"
#include "file.h"
#include "directory.h"
 
using namespace std;

// Set the path from root to current
string File::setPath(Directory* root, Directory* current) {
    string dirPath = "/";
    Directory* tempC = current;

    while (tempC != root) {
        dirPath = "/" + tempC->getName() + dirPath;
        tempC = tempC->getParent();
    }

    return dirPath;
}

// A function that extends the content of file
void File::addContent(string text) {
    content += text;
}

// A function that updates the byte in storage.txt
void File::updateByte(string fileName) {
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
                freeSpace = value - stoi(getByte());
            } else if (key == "UsedSpace") {
                usedSpace = value + stoi(getByte());
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

// Output content of the file
void File::cat(string fileName) const {
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
