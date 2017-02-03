// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#include "SequentialCommand.hpp"

namespace rshell {

SequentialCommand::~SequentialCommand() = default;

bool SequentialCommand::shouldExecuteAfter(const Command& command,
        int exitCode) const noexcept
{
    return true;
}

} // namespace rshell
