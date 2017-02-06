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
/// \brief Contains the interface to the \ref rshell::ExitException class

#ifndef hpp_rshell_ExitException
#define hpp_rshell_ExitException

namespace rshell {

/// \brief Exception thrown when the exit command is executed
class ExitException
{
public:
    /// \brief Constructs a new instance of the \ref ExitException class with
    /// the given exit code
    /// \param exitCode exit code for the shell process
    explicit ExitException(int exitCode = 0);

    /// \brief Gets the exit code for the shell process
    /// \return exit code for the shell process
    int exitCode() const noexcept { return _exitCode; }

private:
    int _exitCode; //!< Exit code for the shell process
};

} // namespace rshell

#endif // hpp_rshell_ExitException
