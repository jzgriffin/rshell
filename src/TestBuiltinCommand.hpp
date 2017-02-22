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
/// \brief Contains the interface to the \ref rshell::TestBuiltinCommand class

#ifndef hpp_rshell_TestBuiltinCommand
#define hpp_rshell_TestBuiltinCommand

#include "ExecutableCommand.hpp"

namespace rshell {

/// \brief Represents an invocation of the test builtin command
///
/// The test command accepts the -e, -f, and -d flags followed by a file name.
class TestBuiltinCommand : public ExecutableCommand
{
public:
    /// \brief Destructs the \ref TestBuiltinCommand instance
    virtual ~TestBuiltinCommand();

    /// \brief Executes the command using the given executor
    /// \param executor executor to use for execution
    /// \return exit code of the command
    virtual int execute(Executor& executor) override;
};

} // namespace rshell

#endif // hpp_rshell_TestBuiltinCommand
