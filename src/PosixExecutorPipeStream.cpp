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

#include "PosixExecutorPipeStream.hpp"
#include "PosixExecutorPipe.hpp"
#include <unistd.h>

namespace rshell {

PosixExecutorPipeStream::PosixExecutorPipeStream(PosixExecutorPipe& pipe,
        int& file, Mode mode)
    : ExecutorStream{mode}
    , _pipe(pipe)
    , _file(file)
{
}

PosixExecutorPipeStream::~PosixExecutorPipeStream() = default;

void PosixExecutorPipeStream::activate(Executor& executor)
{
    // In input mode, the stream replaces the standard input; in output mode,
    // it replaces the standard output
    int slot = 0;
    switch (_mode) {
        case Mode::Input: slot = STDIN_FILENO; break;
        case Mode::Output: slot = STDOUT_FILENO; break;
    }

    ::dup2(_file, slot);
}

void PosixExecutorPipeStream::close()
{
    ::close(_file);
}

} // namespace rshell
