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
/// \brief Contains the interface to the \ref rshell::ExecutorStream class

#ifndef hpp_rshell_ExecutorStream
#define hpp_rshell_ExecutorStream

namespace rshell {

// Forward declarations
class Executor;

/// \brief Abstract base class for individual input/output streams within
/// executors
class ExecutorStream
{
public:
    /// \brief Possible input/output modes for streams
    enum class Mode
    {
        Input, //!< Stream will replace the standard input
        Output, //!< Stream will replace the standard output
    };

    /// \brief Destructs the \ref ExecutorStream instance
    virtual ~ExecutorStream();

    /// \brief Gets the input/output mode of the stream
    /// \return input/output mode
    Mode mode() const noexcept { return _mode; }

    /// \brief Activates the stream within the given executor
    /// \param executor executor to activate on
    virtual void activate(Executor& executor) = 0;

    /// \brief Closes the stream
    virtual void close() = 0;

protected:
    Mode _mode; //!< Input/output mode of the stream

    /// \brief Constructs a new instance of the \ref ExecutorStream class with
    /// the given mode
    /// \param mode input/output mode of the stream
    explicit ExecutorStream(Mode mode);
};

} // namespace rshell

#endif // hpp_rshell_ExecutorStream
