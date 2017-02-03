// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_InitialCommand
#define hpp_rshell_InitialCommand

#include "Command.hpp"

namespace rshell {

class InitialCommand : public Command
{
public:
    virtual ~InitialCommand();

    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept override;
};

} // namespace rshell

#endif // hpp_rshell_InitialCommand
