// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#include "InitialCommand.hpp"

namespace rshell {

InitialCommand::~InitialCommand() = default;

bool InitialCommand::shouldExecuteAfter(const Command& command,
        int exitCode) const noexcept
{
    return false;
}

} // namespace rshell
