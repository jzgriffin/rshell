// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_DisjunctiveCommand
#define hpp_rshell_DisjunctiveCommand

#include "Command.hpp"

namespace rshell {

class DisjunctiveCommand : public Command
{
public:
    virtual ~DisjunctiveCommand();

    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept override;
};

} // namespace rshell

#endif // hpp_rshell_DisjunctiveCommand
