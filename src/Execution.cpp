// rshell
// Copyright (c) Jeremiah Griffin <jgrif007@ucr.edu>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE NEGLIGENCE OR OTHER TORTIOUS ACTION,
// ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
// SOFTWARE.

#include "Execution.hpp"
#include "ExitException.hpp"
#include <iostream>
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

    // Loop over the command composition, starting with the first
    for (auto current = &command; current != nullptr;
            current = current->next.get()) {
        // If there was a previously executed command (ie, this is not
        // the first), do not execute if the command itself indicates
        // that it should not follow the previous command
        if (previous != nullptr
                && !current->shouldExecuteAfter(*previous, exitCode)) {
            continue;
        }

        // The "exit" command is a special case--handle it separately
        if (current->program == "exit") {
            handleExit(*current); // Does not return; throws
        }

        // Store the exit code of the command and make it the previosuly
        // executed command
        exitCode = _executor->execute(*current);
        previous = current;
    }

    return exitCode;
}

void Execution::handleExit(const Command& command)
{
    int exitCode = 0;

    // The exit command accepts an optional argument that sets the exit
    // code of the shell
    if (!command.arguments.empty()) {
        try {
            exitCode = std::stoi(command.arguments.front());
        }
        catch (...) {
            // std::stoi throws when conversion is impossible; we do not
            // care if this happens, as we will simply preserve the
            // default value of the exit code
            std::cerr << "rshell: warning: exit code must be an integer\n"
                << "rshell: warning: exiting with default code " << exitCode
                << '\n';
        }
    }

    // Throw the exit exception expected by the shell
    throw ExitException{exitCode};
}

} // namespace rshell
