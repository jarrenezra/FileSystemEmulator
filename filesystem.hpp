#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP
#include "node.hpp"

class FileSystem
{
private:
    Node *root;
    Node *currentDirectory;
    void addNode(Node*);
    Node *findNode(std::string);
    std::string address;
public:
    FileSystem();
    ~FileSystem();
    std::string pwd();
    std::string ls();
    std::string touch(std::string);
    std::string mkdir(std::string);
    std::string rm(std::string);
    std::string mv(std::string, std::string);
    std::string cd(std::string);
    void deleteNode(Node*);
};

#endif // FILESYSTEM_HPP