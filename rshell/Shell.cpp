// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#include "Shell.hpp"
#include "Parser.hpp"
#include "PosixExecutor.hpp"
#include "Tokenizer.hpp"
#include "utility/make_unique.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

using utility::make_unique;

namespace rshell {

Shell::Shell()
    : _execution{make_unique<PosixExecutor>()}
{
}

void Shell::process()
{
    auto command = getCommand();
    if (command != nullptr) {
        execute(*command);
    }
}

int Shell::run()
{
    _isRunning = true;

    while (_isRunning) {
        process();
    }

    return _exitCode;
}

void Shell::printCommandPrompt() const
{
    std::cout << "$ ";
}

void Shell::printContinuationPrompt() const
{
    std::cout << "> ";
}

std::vector<Token> Shell::readCommand() const
{
    std::vector<Token> tokens;
    std::string text;
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        text += line;

        std::istringstream is{text};
        Tokenizer tokenizer{is};
        tokenizer.apply();

        if (tokenizer.isValid()) {
            tokens = tokenizer.tokens();
            break;
        }

        printContinuationPrompt();
        if (tokenizer.inEscape()) {
            text.pop_back(); // Remove backslash
        }
        else if (tokenizer.inQuote()) {
            text += '\n';
        }
    }

    return tokens;
}

std::vector<Token> Shell::promptCommand() const
{
    printCommandPrompt();
    return readCommand();
}

std::unique_ptr<Command> Shell::getCommand() const
{
    auto tokens = promptCommand();
    if (tokens.empty()) {
        return nullptr;
    }

    return Parser{tokens}.apply();
}

int Shell::execute(const Command& command)
{
    try {
        return _execution.execute(command);
    }
    catch (int e) {
        _isRunning = false;
        _exitCode = e;
        return _exitCode;
    }
    catch (const std::exception& e) {
        std::cerr << "rshell: error: " << e.what() << '\n';
    }
}

} // namespace rshell
