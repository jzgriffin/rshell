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
#include <iostream>
#include <stdexcept>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace {

/// \brief Determines whether the given path is to an existing file
/// \param path path to evaluate
/// \return \c true of \p path is a file and exists
bool isPathFile(const std::string& path)
{
    struct stat info;
    return stat(path.c_str(), &info) == 0 && S_ISREG(info.st_mode);
}

}

namespace rshell {

PosixExecutor::~PosixExecutor() = default;

int PosixExecutor::execute(ExecutableCommand& command)
{
    // Attempt to locate the program to run.  If this process fails, bail out
    // before forking because exec will fail.
    auto program = searchPath(command.program);
    if (!isPathFile(program)) {
        std::cerr << "rshell: command not found: " << command.program << '\n';
        return 1;
    }

    // Create an argv-style C array to pass to the system call
    ArgVector argv{searchPath(command.program), command.arguments};

    // Fork the process.  If the fork is successful, there will be two
    // identical processes running at the same point on the next line of code.
    // One will possess a "pid" value of zero, indicating that it is the
    // forked child process.  The other will possess a positive "pid" value,
    // indicating that it is the parent process and the pid is of the child.
    // If the "pid" value is negative, no fork occurred
    auto pid = fork();
    if (pid == 0) {
        // Invoke the exit system call, replacing the current process image
        // with the given executable
        execv(argv[0], argv);

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
            throw std::runtime_error{"error while waiting"};
        }

        // If the child process exited, as it should, return its exit code
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }

        // If the child process did not exit, something went horribly wrong
        throw std::runtime_error{"abnormal process termination"};
    }
    else {
        std::perror("rshell: fork failed");
        throw std::runtime_error{"unable to fork"};
    }
}

std::vector<std::string> PosixExecutor::searchPaths() const
{
    static constexpr char delimiter = ':';

    // Retrieve the value of PATH from the environment, then begin tokenizing
    // it by its delimiting character.  Each element goes into the paths
    // vector
    std::vector<std::string> paths;
    std::string var = getenv("PATH");
    auto next = var.find(delimiter);
    decltype(next) prev = 0;
    while (next != std::string::npos) {
        paths.push_back(var.substr(prev, next - prev));
        prev = next + 1;
        next = var.find(delimiter, prev);
    }

    // The above tokenization loop may stop with more data after the final
    // delimiter; add the remainder to the paths vector
    paths.push_back(var.substr(prev));

    return paths;
}

std::string PosixExecutor::searchPath(const std::string& program) const
{
    static constexpr char delimiter = '/';

    // If the program has a slash in it, we assume that it is complete and
    // do not process it further
    if (program.find(delimiter) != std::string::npos) {
        return program;
    }

    // Try to locate the program in each path in succession
    for (auto&& path : searchPaths()) {
        // Ensure that the path item ends with a delimiter
        auto attempt = path;
        if (attempt.back() != delimiter) {
            attempt.push_back(delimiter);
        }

        attempt += program;

        // If the program exists as a file, stop early
        if (isPathFile(attempt)) {
            return attempt;
        }
    }

    return {};
}

} // namespace rshell
