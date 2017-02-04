// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#include "Execution.hpp"
#include <stdexcept>
#include <utility>

namespace rshell {

Execution::Execution(std::unique_ptr<Executor>&& executor)
    : _executor{std::move(executor)}
{
    if (_executor == nullptr) {
        throw std::runtime_error{"null executor in Execution"};
    }
}

int Execution::execute(const Command& command)
{
    int exitCode = 0;
    const Command* previous = nullptr;
    for (auto current = &command; current != nullptr;
            current = current->next.get()) {
        if (previous != nullptr
                && !current->shouldExecuteAfter(*previous, exitCode)) {
            continue;
        }

        if (current->program == "exit") {
            handleExit(*current); // Does not return
        }

        exitCode = _executor->execute(*current);
        previous = current;
    }

    return exitCode;
}

void Execution::handleExit(const Command& command)
{
    int exitCode = 0;
    if (!command.arguments.empty()) {
        try {
            exitCode = std::stoi(command.arguments[0]);
        }
        catch (...) {
        }
    }

    throw exitCode;
}

} // namespace rshell
