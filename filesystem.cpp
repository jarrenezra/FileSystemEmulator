#include "filesystem.hpp"

FileSystem::FileSystem()
{
    root = new Node("/root", 'd');
    currentDirectory = root; // current directory alternates depending on where it is currently
    address = root->getName();
}

FileSystem::~FileSystem()
{
    deleteNode(root);
}

void FileSystem::deleteNode(Node* node)
{
    if(node != nullptr)
    {
        std::vector<Node*> children = node->getChildren();
        for(Node* child : children)
        {
            deleteNode(child);
        }
        delete node;
    }
}

void FileSystem::addNode(Node *newNode)
{
    currentDirectory->addChild(newNode); // add a file or directory to root
}

Node *FileSystem::findNode(std::string name)
{
    std::vector<Node *> cd = currentDirectory->getChildren(); // get files and directories from current directory, traverse and return node that matches
    for (Node *item : cd)
    {
        if (item->getName() == name) // if item's name is equal to parameter name, return that Node* object.
            return item;
    }

    return nullptr; // Node not found
}

std::string FileSystem::pwd()
{
    return root->getName();
}

std::string FileSystem::ls()
{
    std::vector<Node *> cd = currentDirectory->getChildren(); // gets the children of the directory that currentDirectory is pointing at
    std::string formString = "\0";
    if (!cd.empty()) // if current directory is not empty, form the string
    {
        for (Node *item : cd)
        {
            formString += item->getType();
            formString += " ";
            formString += item->getName();
            formString += "\n";
        }
    } // if it's empty, just make it empty
    else
        formString = "";

    return formString;
}

std::string FileSystem::touch(std::string itemName)
{
    // std::cout << "hello\n";
    std::vector<Node *> cd = currentDirectory->getChildren();
    if (!cd.empty()) // if the directory is not empty
    {
        for (Node *item : cd) // check the directory for the itemName and see if there's already one.
        {
            if (item->getName() == itemName) // if the itemName exists whether it's a file or a directory print to console that that item already exists
            {
                return "Error: " + itemName + " exists"; // cd has that file already
            }
        }
    }
    // else, cd is empty or the itemName can't be found, do this:
    Node *newItem = new Node(itemName, 'f'); // f for file
    addNode(newItem);                        // add the item to the current directory
    return "file " + itemName + " created successfully";
}

std::string FileSystem::mkdir(std::string itemName)
{
    std::vector<Node *> cd = currentDirectory->getChildren();
    if (!cd.empty()) // if the directory is not empty
    {
        for (Node *item : cd) // check the directory for the itemName and see if there's already one.
        {
            if (item->getName() == itemName) // if the itemName exists whether it's a file or a directory print to console that that item already exists
            {
                return "Error: " + itemName + " exists"; // cd has that file already
            }
        }
    }
    // else, cd is empty or the itemName can't be found, do this:
    Node *newItem = new Node(itemName, 'd'); // d for directory
    addNode(newItem);                        // add the item to the current directory
    return "directory " + itemName + " created successfully";
}

std::string FileSystem::cd(std::string dirName) // cd for change directory
{
    std::vector<Node *> cd = currentDirectory->getChildren(); // Look at current directory
    bool movedInside = false;
    bool movedOutside = false;

    // move out of current directory:
    if (dirName == "..")
    {
        // move out of the directory
        if (currentDirectory->getParent() == nullptr) // if there's nothing to move out of
        {
            return "can't change to directory ..";
        }
        else
        {
            currentDirectory = currentDirectory->getParent();
            movedOutside = true;
        }
    }

    // change directory:
    for (Node *item : cd)
    {
        if (item->getType() == 'd' && item->getName() == dirName) // if this item is a directory and it matches the parameter, set this directory
        {
            currentDirectory = item; // point currentDirectory to current item inside cd
            movedInside = true;
        }
        else if (item->getType() == 'f' && item->getName() == dirName)
        {
            return dirName + ": is not a directory";
        }
    }
    if (movedInside)
    {
        address += "/";
        address += dirName;
        root->setName(address);
        return address;
    }
    if (movedOutside)
    {
        char delimiter = '/'; // when moving out, delete the path
        std::size_t pos = address.find_last_of(delimiter);
        if (pos != std::string::npos)
        { // Erase everything from the last delimiter to the end of the string
            address.erase(pos);
        }
        root->setName(address);
        return address;
    }
    return dirName + ": no such directory"; // traversed the entire vector and did not find the directory to change to
}

std::string FileSystem::mv(std::string currName, std::string newName)
{
    std::vector<Node *> cd = currentDirectory->getChildren(); // get all items in current directory

    // check current directory for a match of currName
    for (Node *item : cd)
    {
        if (currName == item->getName()) // item found
        {
            item->setName(newName);
            return "file/dir renamed successfully";
        }
    }
    // item is not found if it finishes the loop and the if statement did not execute.

    return "file not found";
}

std::string FileSystem::rm(std::string dataToRemove)
{
    bool success = currentDirectory->removeChild(dataToRemove);

    if(success)
        return dataToRemove + " removed successfully";
    //item is not found if it finishes the loop and the if statement did not execute.
    return "No such file or directory";
}
