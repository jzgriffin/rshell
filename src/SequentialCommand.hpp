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
/// \brief Contains the interface to the \ref rshell::SequentialCommand class

#ifndef hpp_rshell_SequentialCommand
#define hpp_rshell_SequentialCommand

#include "Command.hpp"

namespace rshell {

/// \brief Command to be executed unconditionally within a command composition
class SequentialCommand : public Command
{
public:
    /// \brief Destructs the \ref SequentialCommand instance
    virtual ~SequentialCommand();

    /// \brief Determines whether the command should be executed after the
    /// given command in a composition
    /// \param command preceding command
    /// \param exitCode exit code of the preceding command
    /// \return \c true
    ///
    /// Always returns true, as a sequential command is always executed.
    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept override;
};

} // namespace rshell

#endif // hpp_rshell_SequentialCommand
