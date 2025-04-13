#ifndef COMMANDPARSER_HPP
#define COMMANDPARSER_HPP

#include "Command.hpp"

void printUsageHelp();
Command tryParseCommand(const std::string str);

#endif