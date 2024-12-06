#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "filesystem.hpp"
#include <sstream>

class Terminal
{
private:
    FileSystem fs;
    std::string lineInput;
    std::string command;
    std::string arg1;
    std::string arg2;

public:
    Terminal() = default;
    void run()
    {
        do
        {
            command = "\0";
            arg1 = "\0";
            arg2 = "\0";
            std::cout << "$";
            std::getline(std::cin, lineInput);
            std::istringstream stream(lineInput);
            stream >> command >> arg1 >> arg2;
            if (command == "cd")
            {
                if (arg1.empty())
                {
                    std::cout << "Command " << command << " requires one argument\n";
                }
                else
                    std::cout << fs.cd(arg1) << "\n";
            }
            else if (command == "ls")
            {
                std::cout << fs.ls();
            }
            else if (command == "mv")
            {
                if (arg2.empty())
                {
                    std::cout << "Command " << command << " requires two arguments\n";
                }
                else
                    std::cout << fs.mv(arg1, arg2) << "\n";
            }
            else if (command == "rm")
            {
                if (arg1.empty())
                {
                    std::cout << "Command " << command << " requires one argument\n";
                }
                else
                    std::cout << fs.rm(arg1) << "\n";
            }
            else if (command == "mkdir")
            {
                if (arg1.empty())
                {
                    std::cout << "Command " << command << " requires one argument\n";
                }
                else
                    std::cout << fs.mkdir(arg1) << "\n";
            }
            else if (command == "touch")
            {
                if (arg1.empty())
                {
                    std::cout << "Command " << command << " requires one argument\n";
                }
                else
                    std::cout << fs.touch(arg1) << "\n";
            }
            else if (command == "pwd")
            {
                std::cout << fs.pwd() << "\n";
            }
            else if (command == "exit")
            {
                break;
            }
            else
            {
                std::cout << "Command '" << command << "' not found\n";
            }
            stream.clear();
            stream.str("");
        } while (true);
    }
};

#endif // TERMINAL_HPP