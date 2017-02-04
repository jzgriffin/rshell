// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_Executor
#define hpp_rshell_Executor

#include "Command.hpp"

namespace rshell {

class Executor
{
public:
    virtual ~Executor();

    virtual int execute(const Command& command) = 0;
};

} // namespace rshell

#endif // hpp_rshell_Executor
