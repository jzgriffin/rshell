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
/// \brief Contains the interface to the \ref rshell::DisjunctiveCommand class

#ifndef hpp_rshell_DisjunctiveCommand
#define hpp_rshell_DisjunctiveCommand

#include "Command.hpp"

namespace rshell {

/// \brief Command to be executed if the preceding command exited
/// unsuccessfully with a nonzero exit code
class DisjunctiveCommand : public Command
{
public:
    /// \brief Destructs the \ref DisjunctiveCommand instance
    virtual ~DisjunctiveCommand();

    /// \brief Determines whether the command should be executed after the
    /// given command in a composition
    /// \param command preceding command
    /// \param exitCode exit code of the preceding command
    /// \return \c true if \p exitCode is nonzero
    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const;
};

} // namespace rshell

#endif // hpp_rshell_DisjunctiveCommand
