#include <string>
#include "os.h"
#include "link.h"

using namespace std;

// Setters for name
void Link::setName(string fileName) { 
    name = fileName;
}

// Setters for pointer of directory
void Link::setPointerD(Directory* newPointer) {
    pointerD = newPointer; 
}

// Setters for pointer of file
void Link::setPointerF(File* newPointer) {
    pointerF = newPointer; 
}
