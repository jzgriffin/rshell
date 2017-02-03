// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_SequentialCommand
#define hpp_rshell_SequentialCommand

#include "Command.hpp"

namespace rshell {

class SequentialCommand : public Command
{
public:
    virtual ~SequentialCommand();

    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept override;
};

} // namespace rshell

#endif // hpp_rshell_SequentialCommand
