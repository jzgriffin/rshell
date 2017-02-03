// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_Parser
#define hpp_rshell_Parser

#include "Command.hpp"
#include "Token.hpp"
#include <memory>

namespace rshell {

class Parser
{
public:
    explicit Parser(const std::vector<Token>& tokens);

    std::unique_ptr<Command> apply();

private:
    const std::vector<Token>& _tokens;
};

} // namespace rshell

#endif // hpp_rshell_Parser
