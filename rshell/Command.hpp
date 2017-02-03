// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_Command
#define hpp_rshell_Command

#include <memory>
#include <string>
#include <vector>

namespace rshell {

class Command
{
public:
    std::string program;
    std::vector<std::string> arguments;
    std::unique_ptr<Command> next;

    virtual ~Command();

    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept = 0;
};

} // namespace rshell

#endif // hpp_rshell_Command
