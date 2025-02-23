#ifndef OS_H
#define OS_H

#include <string>

using std::string;
class Directory;


namespace program {
    // Class for prepare OS to be ready
    class Prepare {
        public:
            // Get command from the user 
            void getCommand(Directory& root) const;

            // Apply commands 
            void applyCommand(Directory& root, string command) const;

            // Reload the commands have been taken before
            void reload(Directory& root) const;

        private:
            // Save the command to a txt file
            void save(string command) const;

            // Check if the command is valid
            bool isValid(string command) const;
    };

    // Base class
    class OS {
        public:     
            OS() : depth(1) {};
            virtual void ls(bool recursive) { };
            virtual void lsRecursive(Directory* current, int index) { };
            virtual void mkdir(string fileName) { };
            virtual void rm(string fileName) { };
            virtual void cd(string fileName) { };
            virtual void cp(string source, string destination) { };
            virtual void cat(string fileName) const { };
            virtual void touch(string fileName)  { };
            virtual void ln(string sourceFile, string destinationFile) { };

            virtual string setPath(Directory* root, Directory* current) { return ""; };
            
            int getDepth() { return depth; }
            void setDepth(int newDepth) { depth = newDepth; }

            // Static variables to determine where the iterator is in
            static Directory* currentDirectory;
            static Directory* rootDirectory;

            virtual ~OS() = default; 
        protected:
            // Hold the time when directory or file is created 
            string createTime() const;

        private:
            // A variable that holds the distance from root
            int depth;                       
    };
}

#endif
