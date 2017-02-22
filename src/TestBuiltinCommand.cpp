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

namespace rshell {

TestBuiltinCommand::~TestBuiltinCommand() = default;

int TestBuiltinCommand::execute(Executor& executor)
{
    if (program == "[") {
        if (arguments.size() != 3 || arguments[2] != "]") {
            std::cout << "Usage: [ -<e|f|d> <path> ]\n";
            return 1;
        }
    }
    else if (arguments.size() != 2) {
        std::cout << "Usage: test -<e|f|d> <path>\n";
        return 1;
    }

    struct stat info;
    if (stat(arguments[1].c_str(), &info) != 0) {
        std::cout << "(False)\n";
        return 1;
    }

    auto result = true;
    if (arguments[0] == "-e") {
    }
    else if (arguments[0] == "-f") {
        if (!S_ISREG(info.st_mode)) {
            result = false;
        }
    }
    else if (arguments[0] == "-d") {
        if (!S_ISDIR(info.st_mode)) {
            result = false;
        }
    }
    else {
        std::cerr << "test: flag must be one of -e|-f|-d\n";
        return 1;
    }

    if (result) {
        std::cout << "(True)\n";
        return 0;
    }

    std::cout << "(False)\n";
    return 1;
}

} // namespace rshell
