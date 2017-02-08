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

/// \file
/// \brief Contains the interface to the \ref rshell::Execution class

#ifndef hpp_rshell_Execution
#define hpp_rshell_Execution

#include "Command.hpp"
#include "Executor.hpp"

namespace rshell {

/// \brief Represents the algorithm for executing commands in the strategy
/// pattern
class Execution {
public:
    /// \brief Constructs a new instance of the \ref Execution class with the
    /// given executor
    /// \param executor executor to apply to commands
    ///
    /// The Execution takes ownership of \p executor.
    explicit Execution(Executor* executor);

    /// \brief Destructs the \ref Execution instance.
    ~Execution();

    /// \brief Gets a reference to the executor to apply to commands
    /// \return reference to the executor to apply to commands
    const Executor& executor() const { return *_executor; }

    /// \brief Gets a reference to the executor to apply to commands
    /// \return reference to the executor to apply to commands
    Executor& executor() { return *_executor; }

    /// \brief Executes the given command structure
    /// \param command initial command to execute
    /// \return exit code of the last command executed
    ///
    /// If at any point a command with the program name "exit" is tried for
    /// execution, an integer is thrown with the value of the intended exit
    /// code for the shell process.  This must be caught by the caller and
    /// preferably used to terminate the shell.
    int execute(const Command& command);

private:
    Executor* _executor; //!< Executor to apply to commands

    /// \brief Handles the exit command
    /// \param command command representing the exit
    ///
    /// The exit command accepts one optional argument: the integral exit code
    /// to exit the shell with.  If this argument is omitted, the exit code
    /// will be zero.
    void handleExit(const Command& command);
};

} // namespace rshell

#endif // hpp_rshell_Execution
