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
/// \brief Contains the interface to the \ref rshell::ConjunctiveCommand class

#ifndef hpp_rshell_ConjunctiveCommand
#define hpp_rshell_ConjunctiveCommand

#include "Command.hpp"
#include <memory>

namespace rshell {

/// \brief Command to be executed if the preceding command exited successfully
/// with a zero exit code
class ConjunctiveCommand : public Command
{
public:
    std::unique_ptr<Command> primary; //!< Primary command to execute
    std::unique_ptr<Command> secondary; //!< Secondary command to execute

    /// \brief Destructs the \ref ConjunctiveCommand instance
    virtual ~ConjunctiveCommand();

    /// \brief Executes the command using the given executor
    /// \param executor executor to use for execution
    /// \return exit code of the command
    virtual int execute(Executor& executor) override;
};

} // namespace rshell

#endif // hpp_rshell_ConjunctiveCommand
