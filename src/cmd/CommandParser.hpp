#ifndef COMMANDPARSER_HPP
#define COMMANDPARSER_HPP

#include "Command.hpp"

std::string getUsageHelp();
Command parseCommand(const std::string str);

#endif