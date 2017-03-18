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
/// \brief Contains the interface to the
/// \ref rshell::PosixExecutorAppendFileStream class

#ifndef hpp_rshell_PosixExecutorAppendFileStream
#define hpp_rshell_PosixExecutorAppendFileStream

#include "ExecutorStream.hpp"
#include <string>

namespace rshell {

/// \brief Executor stream for appending to a file with POSIX system calls
class PosixExecutorAppendFileStream : public ExecutorStream
{
public:
    /// \brief Constructs a new instance of the
    /// \ref PosixExecutorAppendFileStream class on the given path
    /// \param path path to the file to write
    explicit PosixExecutorAppendFileStream(const std::string& path);

    /// \brief Destructs the \ref PosixExecutorAppendFileStream instance
    virtual ~PosixExecutorAppendFileStream();

    /// \brief Activates the stream within the given executor
    /// \param executor executor to activate on
    virtual void activate(Executor& executor) override;

    /// \brief Closes the stream
    virtual void close() override;

protected:
    int _file; //!< File descriptor
};

} // namespace rshell

#endif // hpp_rshell_PosixExecutorAppendFileStream
