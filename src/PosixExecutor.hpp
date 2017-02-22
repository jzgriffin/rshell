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
/// \brief Contains the interface to the \ref rshell::PosixExecutor class

#ifndef hpp_rshell_PosixExecutor
#define hpp_rshell_PosixExecutor

#include "Executor.hpp"
#include <string>
#include <vector>

namespace rshell {

/// \brief Implementation of the execution algorithm on top of POSIX system
/// calls
class PosixExecutor : public Executor
{
public:
    /// \brief Destructs the \ref PosixExecutor instance
    virtual ~PosixExecutor();

    /// \brief Executes the individual command given
    /// \param command command to execute
    /// \return exit code of the command
    virtual int execute(ExecutableCommand& command) override;

private:
    /// \brief Gets the list of paths to search for executables
    /// \return list of paths
    /// \see searchPath
    ///
    /// Obtained from the colon-delimited PATH environment variable.
    std::vector<std::string> searchPaths() const;

    /// \brief Searches for the first matching executable in the path
    /// \param program name of the program to search for
    /// \return path to the program to execute on success or an empty string
    /// on failure
    /// \see searchPaths
    ///
    /// If the \p program has a slash in it, it is treated as complete and
    /// no paths will be searched.
    std::string searchPath(const std::string& program) const;
};

} // namespace rshell

#endif // hpp_rshell_PosixExecutor
