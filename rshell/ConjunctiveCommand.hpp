// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_ConjunctiveCommand
#define hpp_rshell_ConjunctiveCommand

#include "Command.hpp"

namespace rshell {

class ConjunctiveCommand : public Command
{
public:
    virtual ~ConjunctiveCommand();

    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept override;
};

} // namespace rshell

#endif // hpp_rshell_ConjunctiveCommand
