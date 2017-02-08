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

#include "PosixExecutor.hpp"
#include "ArgVector.hpp"
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace rshell {

PosixExecutor::~PosixExecutor()
{
}

int PosixExecutor::execute(const Command& command)
{
    // Create an argv-style C array to pass to the system call
    ArgVector argv(command.program, command.arguments);

    // Fork the process.  If the fork is successful, there will be two
    // identical processes running at the same point on the next line of code.
    // One will possess a "pid" value of zero, indicating that it is the
    // forked child process.  The other will possess a positive "pid" value,
    // indicating that it is the parent process and the pid is of the child.
    // If the "pid" value is negative, no fork occurred
    pid_t pid = fork();
    if (pid == 0) {
        // Invoke the exit system call, replacing the current process image
        // with the given executable
        execvp(argv[0], argv);

        // Under normal conditions, exec does not return.  However, if an
        // error occurred, it will return, leaving us in the forked child
        // process, which was not replaced for some reason (likely due to a
        // missing executable).  We must report on the error and exit the
        // child process
        std::perror("rshell: exec failed");
        std::exit(1);
    }
    else if (pid > 0) {
        // Wait for the forked child process to exit.  If the return value
        // of the waitpid system call is negative, an error occurred while
        // waiting
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            std::perror("rshell: wait failed");
            throw std::runtime_error("error while waiting");
        }

        // If the child process exited, as it should, return its exit code
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }

        // If the child process did not exit, something went horribly wrong
        throw std::runtime_error("abnormal process termination");
    }
    else {
        std::perror("rshell: fork failed");
        throw std::runtime_error("unable to fork");
    }
}

} // namespace rshell
