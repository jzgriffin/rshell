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
/// \brief Contains the interface to the \ref rshell::PosixExecutorPipeStream
/// class

#ifndef hpp_rshell_PosixExecutorPipeStream
#define hpp_rshell_PosixExecutorPipeStream

#include "ExecutorStream.hpp"

namespace rshell {

class PosixExecutorPipe;

/// \brief Implementation of the executor stream with POSIX system calls
class PosixExecutorPipeStream : public ExecutorStream
{
public:
    /// \brief Constructs a new instance of the \ref PosixExecutorPipeStream class
    /// on the given file descriptor in the given mode
    /// \param pipe pipe the stream exists within
    /// \param file reference to the file descriptor
    /// \param mode input/output mode of the stream
    explicit PosixExecutorPipeStream(PosixExecutorPipe& pipe, int& file,
            Mode mode);

    /// \brief Destructs the \ref PosixExecutorPipeStream instance
    virtual ~PosixExecutorPipeStream();

    /// \brief Activates the stream within the given executor
    /// \param executor executor to activate on
    virtual void activate(Executor& executor) override;

    /// \brief Closes the stream
    virtual void close() override;

protected:
    PosixExecutorPipe& _pipe; //!< Pipe the stream exists within
    int& _file; //!< Reference to the file descriptor
};

} // namespace rshell

#endif // hpp_rshell_PosixExecutorPipeStream
