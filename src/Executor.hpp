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
/// \brief Contains the interface to the \ref rshell::Executor class

#ifndef hpp_rshell_Executor
#define hpp_rshell_Executor

#include "Command.hpp"

namespace rshell {

/// \brief Serves as the abstract base class in the strategy pattern of the
/// execution algorithm
class Executor
{
public:
    /// \brief Destructs the \ref Executor instance
    virtual ~Executor();

    /// \brief Executes the individual command given
    /// \param command command to execute
    /// \return exit code of the command
    virtual int execute(const Command& command) = 0;
};

} // namespace rshell

#endif // hpp_rshell_Executor
