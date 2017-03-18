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

#include "PosixExecutorAppendFileStream.hpp"
#include <cstdlib>
#include <stdexcept>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace rshell {

PosixExecutorAppendFileStream::PosixExecutorAppendFileStream(
        const std::string& path)
    : ExecutorStream{Mode::Output}
    , _file(::open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))
{
    if (_file == -1) {
        std::perror("rshell: unable to open output file");
        throw std::runtime_error{"unable to open output file"};
    }
}

PosixExecutorAppendFileStream::~PosixExecutorAppendFileStream()
{
    close();
}

void PosixExecutorAppendFileStream::activate(Executor& executor)
{
    ::dup2(_file, STDOUT_FILENO);
}

void PosixExecutorAppendFileStream::close()
{
    ::close(_file);
}

} // namespace rshell
