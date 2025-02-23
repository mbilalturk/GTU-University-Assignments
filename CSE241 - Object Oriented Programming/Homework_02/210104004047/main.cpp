#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "os.h"
#include "directory.h"

using namespace std;
using namespace program;

int main() {
    Directory root(".");
    Prepare prepare;
    OS::rootDirectory = &root;
    OS::currentDirectory = &root;

    cout << "myShell\n";
    prepare.reload(root);
    prepare.getCommand(root);
    
    cout << "Program terminated!\n";
    return 0;
}
