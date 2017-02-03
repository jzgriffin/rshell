// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#include "DisjunctiveCommand.hpp"

namespace rshell {

DisjunctiveCommand::~DisjunctiveCommand() = default;

bool DisjunctiveCommand::shouldExecuteAfter(const Command& command,
        int exitCode) const noexcept
{
    return exitCode != 0;
}

} // namespace rshell
