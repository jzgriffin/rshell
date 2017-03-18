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

#include "OutputRedirectionCommand.hpp"
#include "Executor.hpp"
#include "ExecutorStream.hpp"
#include <stdexcept>

namespace rshell {

OutputRedirectionCommand::~OutputRedirectionCommand() = default;

int OutputRedirectionCommand::execute(Executor& executor, WaitMode waitMode)
{
    if (primary == nullptr || path.empty()) {
        throw std::runtime_error{"incomplete OutputRedirectionCommand"};
    }

    // Create the output file stream
    auto stream = executor.createOutputFileStream(path);
    executor.streamSet().insert(*stream.get());

    // Make the stream the output stream for the executor and execute the
    // command
    executor.setOutputStream(stream.get());
    auto exitCode = primary->execute(executor, waitMode);
    executor.setOutputStream(nullptr);

    executor.streamSet().erase(*stream.get());
    return exitCode;
}

} // namespace rshell
