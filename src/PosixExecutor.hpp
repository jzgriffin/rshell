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

namespace rshell {

/// \brief Implementation of the execution algorithm on top of POSIX system
/// calls
class PosixExecutor : public Executor
{
public:
    /// \brief Destructs the \ref PosixExecutor instance
    virtual ~PosixExecutor();

    /// \brief Creates a new pipe on the executor
    /// \return pointer to new pipe
    virtual std::unique_ptr<ExecutorPipe> createPipe();

    /// \brief Creates a new input file stream on the executor
    /// \param path path to open the stream on
    /// \return pointer to new stream
    virtual std::unique_ptr<ExecutorStream> createInputFileStream(
            const std::string& path);

    /// \brief Creates a new output file stream on the executor
    /// \param path path to open the stream on
    /// \return pointer to new stream
    virtual std::unique_ptr<ExecutorStream> createOutputFileStream(
            const std::string& path);

    /// \brief Creates a new append file stream on the executor
    /// \param path path to open the stream on
    /// \return pointer to new stream
    virtual std::unique_ptr<ExecutorStream> createAppendFileStream(
            const std::string& path);

    /// \brief Executes the individual command given
    /// \param command command to execute
    /// \param waitMode wait mode to use when executing
    /// \return exit code of the command
    virtual int execute(ExecutableCommand& command,
            WaitMode waitMode = WaitMode::Wait) override;
};

} // namespace rshell

#endif // hpp_rshell_PosixExecutor
