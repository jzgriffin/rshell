// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#include "PosixExecutor.hpp"
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace {

std::unique_ptr<char[]> toCString(const std::string& string)
{
    auto size = string.size() + 1;
    auto cString = std::unique_ptr<char[]>(new char[size]);
    std::memcpy(cString.get(), string.c_str(), size);
    return cString;
}

std::vector<std::unique_ptr<char[]>> toCStrings(
        const std::vector<std::string>& strings)
{
    std::vector<std::unique_ptr<char[]>> cStrings;
    for (auto&& string : strings) {
        cStrings.push_back(toCString(string));
    }

    return cStrings;
}

std::vector<std::unique_ptr<char[]>> toArgv(const std::string& program,
        const std::vector<std::string>& args)
{
    auto argv = toCStrings(args);
    argv.insert(std::begin(argv), toCString(program));
    argv.push_back(nullptr);
    return argv;
}

}

namespace rshell {

PosixExecutor::~PosixExecutor() = default;

int PosixExecutor::execute(const Command& command)
{
    auto argvOwner = toArgv(command.program, command.arguments);
    std::vector<char*> argv;
    for (auto&& arg : argvOwner) {
        argv.push_back(arg.get());
    }

    auto pid = fork();
    if (pid == 0) {
        execvp(argv[0], argv.data());

        // exec only returns in error
        std::cerr << "rshell: error: unable to execute "
            << command.program << '\n';
        exit(1);
    }
    else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }

        throw std::runtime_error{"abnormal process termination"};
    }
    else {
        throw std::runtime_error{"unable to fork"};
    }
}

} // namespace rshell
