#include<stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
class FileManager {
public:
        void showCurrentDirectory() {
        char cwd[256];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            std::cout << "Current Directory: " << cwd << std::endl ;
        } else {
            std::cerr << "Error getting current directory!" << std::endl ;
        }
    }
};
void listFiles() {
        DIR *dir;
        struct dirent *entry;

        if ((dir = opendir(".")) != nullptr) {
            while ((entry = readdir(dir)) != nullptr) {
                std::cout << entry->d_name << std::endl;
            }
            closedir(dir);
        } else {
            std::cerr << "Error opening directory!" << std::endl;
        }
    }

void createDirectory(const std::string& dirName) {
    if (mkdir(dirName.c_str()) == 0){
        std::cout << "Directory created: " << dirName << std::endl ;
    } else {
        std::cerr << "Failed to create directory!" << std::endl ;
    }
}


void copyFile(const std::string& source, const std::string& destination) {
    std::ifstream src(source.c_str(), std::ios::binary);
    std::ofstream dest(destination.c_str(), std::ios::binary);

    dest << src.rdbuf();

    src.close();
    dest.close();

    std::cout << "File copied successfully from " << source << " to " << destination << std::endl;
}

void moveFile(const std::string& source, const std::string& destination) {
    if (std::rename(source.c_str(), destination.c_str()) == 0) {
        std::cout << "File moved successfully from " << source << " to " << destination << std::endl;
    } else {
        std::cerr << "Error moving file!" << std::endl;
    }
}

int main()  {
    FileManager fileManager;
    std::string input;
    while (true) {
        std::cout << "Enter a command (ls, mkdir, cp, mv, cd, exit): ";
        std::cin >> input;

        if (input == "ls") {
            listFiles();
        } else if (input == "mkdir") {
            std::string dirName;
            std::cout << "Enter directory name: ";
            std::cin >> dirName;
            createDirectory(dirName);
        } else if (input == "cp") {
            std::string source, destination;
            std::cout << "Enter source file path: ";
            std::cin >> source;
            std::cout << "Enter destination file path: ";
            std::cin >> destination;
            copyFile(source, destination);
        } else if (input == "mv") {
            std::string source, destination;
            std::cout << "Enter source file path: ";
            std::cin >> source;
            std::cout << "Enter destination file path: ";
            std::cin >> destination;
            moveFile(source, destination);
        } else if (input == "cd") {
            std::string dirPath;
            std::cout << "Enter directory path: ";
            std::cin >> dirPath;
            if (chdir(dirPath.c_str()) == 0) {
                fileManager.showCurrentDirectory();
            } else
             {
                std::cerr << "Directory doesn't exist!" << std::endl;
            }
        } else if (input == "exit") {
            break;
        } else {
            std::cerr << "Invalid command!" << std::endl;
        }
    }

    return 0;
 }

      

