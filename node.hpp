#ifndef NODE_HPP
#define NODE_HPP
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Node
{

private:
    char type;        // data 1
    std::string name; // data 2
    std::vector<Node *> children;
    Node *parent; // point to child's parent
    void deleteSubtree(Node *node);

public:
    Node(const std::string&, char);
    Node() = default;
    void addChild(Node *);
    void addChild(const std::string&, char);
    bool removeChild(const std::string&);
    void setParent(Node *);
    void setType(char);
    void setName(const std::string&);
    Node *getChild(const std::string &);
    std::vector<Node *>& getChildren();
    Node *getParent();
    char getType();
    std::string getName();
};

#endif // NODE_HPP