#include "node.hpp"

Node::Node(const std::string &name, char type)
{
    setName(name);
    setType(type);
    setParent(nullptr); // if no parent then point to parent
}

std::string Node::getName()
{
    return name;
}

char Node::getType()
{
    return type;
}

Node *Node::getParent()
{
    return parent;
}

std::vector<Node *> &Node::getChildren()
{
    return children;
}

Node *Node::getChild(const std::string &childName)
{
    for (Node *child : children)
    {
        if (child->getName() == childName)
            return child;
    }

    return nullptr;
}

void Node::setParent(Node *newParent)
{
    parent = newParent; // stores the address of the caller's parent variable
}

void Node::setType(char type)
{
    this->type = type;
}

void Node::setName(const std::string &name)
{
    this->name = name;
}

void Node::addChild(Node *newChild) // when this is called, it belongs to the domain of the caller object
{
    newChild->setParent(this);
    children.push_back(newChild); // this vector belongs to the current parent and we're adding the new child
}

void Node::addChild(const std::string &name, char type)
{
    Node *baby = new Node(name, type);
    addChild(baby);
}

bool Node::removeChild(const std::string &name)
{
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        if ((*it)->getName() == name)
        {
            Node *childToRemove = *it;    // Keep a pointer to the child to be removed
            children.erase(it);           // Remove the child from the vector
            deleteSubtree(childToRemove); // Delete the subtree after removing it from the vector
            return true;
        }
        else if ((*it)->removeChild(name))
        {
            return true;
        }
    }
    return false;
}

void Node::deleteSubtree(Node *node)
{
    if (node == nullptr)
        return; // Ensure we don't try to delete a null pointer

    while (!node->children.empty())
    {
        Node *child = node->children.back();
        node->children.pop_back();
        deleteSubtree(child);
    }
    delete node;
}
