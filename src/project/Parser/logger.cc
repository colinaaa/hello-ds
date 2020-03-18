#include <utility>

#include "Parser.hh"

void Project::Parser::log(std::string&& name, int childNumber) { logger.log(name, childNumber); }

void Project::Parser::log(std::string&& name, std::string&& value) { logger.log(name, value); }

void Project::Parser::log(std::string&& name) { log(std::forward<std::string>(name), 0); }
