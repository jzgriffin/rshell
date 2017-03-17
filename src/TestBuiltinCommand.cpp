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

#include "TestBuiltinCommand.hpp"
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace {

/// \brief Modes of operation for the test command
enum class TestMode
{
    DoesExist, //!< Does the given path exist?
    IsFile, //!< Is the given path a file?
    IsDirectory, //!< is the given path a directory?
};

}

namespace rshell {

TestBuiltinCommand::~TestBuiltinCommand() = default;

int TestBuiltinCommand::execute(Executor& executor, WaitMode waitMode)
{
    // If we are using the symbolic form of the command, we expect the last
    // argument to be a matching bracket.  The absence of this bracket is
    // considered an error.  If the bracket is present, remove it so that we
    // can use the same code as for the command form
    auto args = arguments;
    if (program == "[") {
        if (args.back() != "]") {
            std::cerr << "rshell: [: must be terminated with ]\n";
            return 1;
        }

        args.pop_back();
    }

    if (args.empty()) {
        return report(false);
    }

    // Extract the test mode and path from the arguments.  If there is only
    // one argument, assume that we are in an existential test mode.
    // Otherwise, ensure that the mode is acceptable
    TestMode mode;
    std::string path;
    if (args.size() == 1) {
        mode = TestMode::DoesExist;
        path = args[0];
    }
    else {
        path = args[1];
        if (args[0] == "-e") {
            mode = TestMode::DoesExist;
        }
        else if (args[0] == "-f") {
            mode = TestMode::IsFile;
        }
        else if (args[0] == "-d") {
            mode = TestMode::IsDirectory;
        }
        else {
            std::cerr << "test: " << args[0] << ": mode flag expected\n";
            return 1;
        }
    }

    // Obtain the information about the file.  If stat fails, the entry does
    // not exist
    struct stat info;
    auto doesExist = stat(path.c_str(), &info) == 0;

    // Perform additional testing based on the mode
    switch (mode) {
        case TestMode::DoesExist:
            return report(doesExist);

        case TestMode::IsFile:
            return report(doesExist && S_ISREG(info.st_mode));

        case TestMode::IsDirectory:
            return report(doesExist && S_ISDIR(info.st_mode));
    }

    return report(false);
}

int TestBuiltinCommand::report(bool result)
{
    switch (result) {
        case true:
            std::cout << "(True)" << std::endl;
            return 0;

        case false:
            std::cout << "(False)" << std::endl;
            return 1;
    }
}

} // namespace rshell
