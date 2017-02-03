// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#include "ConjunctiveCommand.hpp"

namespace rshell {

ConjunctiveCommand::~ConjunctiveCommand() = default;

bool ConjunctiveCommand::shouldExecuteAfter(const Command& command,
        int exitCode) const noexcept
{
    return exitCode == 0;
}

} // namespace rshell
