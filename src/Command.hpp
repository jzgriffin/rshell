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
/// \brief Contains the interface to the \ref rshell::Command class

#ifndef hpp_rshell_Command
#define hpp_rshell_Command

#include <memory>
#include <string>
#include <vector>

namespace rshell {

/// \brief Serves as the abstract base class in the composite pattern of the
/// command structure
class Command
{
public:
    std::string program; //!< Name of the program
    std::vector<std::string> arguments; //!< Arguments for the program
    std::unique_ptr<Command> next; //!< Next command in the composition, if any

    /// \brief Destructs the \ref Command instance
    virtual ~Command();

    /// \brief Determines whether the command should be executed after the
    /// given command in a composition
    /// \param command preceding command
    /// \param exitCode exit code of the preceding command
    /// \return whether or not the command should be executed after \p command
    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept = 0;
};

} // namespace rshell

#endif // hpp_rshell_Command
