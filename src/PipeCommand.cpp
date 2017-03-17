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

#include "PipeCommand.hpp"
#include "Executor.hpp"
#include "ExecutorPipe.hpp"
#include <stdexcept>
#include <utility>
#include <vector>

namespace {

using namespace rshell;

// RAII for creating sets of pipes to connect commands
// TODO: Refactor into a class with encapsulation in its own file
struct ExecutorPipeSet
{
    using PipeContainer = std::vector<std::unique_ptr<ExecutorPipe>> ;

    Executor& executor;
    PipeContainer pipes;

    ExecutorPipeSet(Executor& executor, std::size_t count)
        : executor(executor)
        , pipes(count)
    {
        // Create the set of pipes for connecting commands
        // While doing this, insert each pipe into the executor stream set
        for (auto&& pipe : pipes) {
            pipe = executor.createPipe();
            executor.streamSet().insert(*pipe);
        }
    }

    ~ExecutorPipeSet()
    {
        // Upon destruction, erase all pipes from the executor stream set
        for (auto&& pipe : pipes) {
            executor.streamSet().erase(*pipe);
        }
    }

    void activate(PipeContainer::iterator pipe)
    {
        // If the pipe is the first, unset the input stream.  Otherwise, make
        // the previous pipe the input stream
        executor.setInputStream(pipe != std::begin(pipes) ?
                &(*std::prev(pipe))->inputStream() : nullptr);

        // If the pipe is the last, unset the output stream.  Otherwise, make
        // it the output stream
        executor.setOutputStream(pipe != std::end(pipes) ?
                &(*pipe)->outputStream() : nullptr);
    }
};

}

namespace rshell {

PipeCommand::~PipeCommand() = default;

int PipeCommand::execute(Executor& executor, WaitMode waitMode)
{
    if (primary == nullptr || secondary == nullptr) {
        throw std::runtime_error{"incomplete PipeCommand"};
    }

    // Flatten the pipe structure to a linear list
    std::vector<Command*> commands;
    auto pipeCommand = this;
    while (pipeCommand != nullptr) {
        commands.push_back(pipeCommand->primary.get());

        auto previous = pipeCommand;
        pipeCommand = dynamic_cast<PipeCommand*>(
                pipeCommand->secondary.get());
        if (pipeCommand == nullptr) {
            commands.push_back(previous->secondary.get());
        }
    }

    // Create the set of pipes to connect commands, then execute the commands
    // in the order they are given, activating the appropriate pair of pipes
    // at each stage.  Execute the first n-1 commands in continue mode and the
    // last command in wait mode so that all commands are executing
    // concurrently and the pipe command returns when the last command
    // terminates
    ExecutorPipeSet pipeSet(executor, commands.size() - 1);
    auto pipe = std::begin(pipeSet.pipes);
    for (auto&& command : commands) {
        pipeSet.activate(pipe++);

        if (command == commands.back()) {
            return command->execute(executor, WaitMode::Wait);
        }

        command->execute(executor, WaitMode::Continue);
    }

    return 0;
}

} // namespace rshell
