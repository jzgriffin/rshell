// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_Shell
#define hpp_rshell_Shell

#include "Command.hpp"
#include "Execution.hpp"
#include "Token.hpp"
#include <memory>
#include <string>
#include <vector>

namespace rshell {

class Shell
{
public:
    Shell();

    bool isRunning() const noexcept { return _isRunning; }
    int exitCode() const noexcept { return _exitCode; }

    void process();
    int run();

private:
    bool _isRunning{false};
    int _exitCode{0};
    Execution _execution;

    void printCommandPrompt() const;
    void printContinuationPrompt() const;
    std::vector<Token> readCommand() const;
    std::vector<Token> promptCommand() const;
    std::unique_ptr<Command> getCommand() const;

    int execute(const Command& command);
};

} // namespace rshell

#endif // hpp_rshell_Shell
