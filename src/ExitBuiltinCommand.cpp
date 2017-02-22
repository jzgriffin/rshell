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

#include "ExitBuiltinCommand.hpp"
#include "Executor.hpp"
#include "ExitException.hpp"
#include <iostream>
#include <string>

namespace rshell {

ExitBuiltinCommand::~ExitBuiltinCommand() = default;

int ExitBuiltinCommand::execute(Executor& executor)
{
    int exitCode = 0;

    // The exit command accepts an optional argument that sets the exit
    // code of the shell
    if (!arguments.empty()) {
        try {
            exitCode = std::stoi(arguments.front());
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
