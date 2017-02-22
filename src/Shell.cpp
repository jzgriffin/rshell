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

#include "Shell.hpp"
#include "ExitException.hpp"
#include "Parser.hpp"
#include "PosixExecutor.hpp"
#include "Tokenizer.hpp"
#include "utility/make_unique.hpp"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <limits.h>
#include <unistd.h>

#if !defined(HOST_NAME_MAX) && defined(_POSIX_HOST_NAME_MAX)
#   define HOST_NAME_MAX _POSIX_HOST_NAME_MAX
#endif

#if !defined(LOGIN_NAME_MAX) && defined(_POSIX_LOGIN_NAME_MAX)
#   define LOGIN_NAME_MAX _POSIX_LOGIN_NAME_MAX
#endif

using utility::make_unique;

namespace rshell {

Shell::Shell()
    : _input{&std::cin}
    , _executor{make_unique<PosixExecutor>()}
    , _commandPrompt{buildCommandPrompt()}
{
}

void Shell::setInteractive(bool isInteractive)
{
    _isInteractive = isInteractive;
}

void Shell::setInput(std::istream& input)
{
    _input = &input;
}

void Shell::process()
{
    try {
        auto command = getCommand();
        if (command != nullptr) {
            execute(*command);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "rshell: error: " << e.what() << '\n';
    }
}

int Shell::run()
{
    _isRunning = true;

    while (*_input && _isRunning) {
        process();
    }

    return _exitCode;
}

std::string Shell::buildCommandPrompt() const
{
    // The intended format for the command prompt is "username@hostname$ ",
    // but will degrade gracefully if the calls to get the username or
    // hostname fail, leaving the appropriate part out of the prompt.  If both
    // calls fail, the prompt will simply be "$ ".

    std::ostringstream os;

    char username[LOGIN_NAME_MAX];
    if (getlogin_r(username, sizeof username) == 0) {
        os << username;
    }
    else {
        std::perror("rshell: warning: unable to get username");
    }

    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, sizeof hostname) == 0) {
        os << '@' << hostname;
    }
    else {
        std::perror("rshell: warning: unable to get hostname");
    }

    os << "$ ";

    return os.str();
}

void Shell::printCommandPrompt() const
{
    if (_isInteractive) {
        std::cout << _commandPrompt;
    }
}

void Shell::printContinuationPrompt() const
{
    if (_isInteractive) {
        std::cout << "> ";
    }
}

std::vector<Token> Shell::readCommand() const
{
    // This is where line continuation takes place.  This algorithm works
    // using two buffers: one for the overall command text and one for
    // the current line.  It reads a line, appends it to the text, then
    // attempts to tokenize the text.  If it tokenizes successfully, the
    // input process is done.  If tokenization fails in an escape or
    // quote sequence, the process is repeated

    std::vector<Token> tokens;
    std::string text;
    while (true) {
        std::string line;
        if (!std::getline(*_input, line)) {
            // If the end of the input stream is reached, the shell will exit
            return {};
        }

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

int Shell::execute(Command& command)
{
    try {
        return command.execute(*_executor);
    }
    catch (const ExitException& e) {
        // The exit command throws an integer when it is executed.  We
        // use this integer as the exit code for the shell process
        _isRunning = false;
        _exitCode = e.exitCode();
        return _exitCode;
    }
    catch (const std::exception& e) {
        std::cerr << "rshell: error: " << e.what() << '\n';
        return -1;
    }
}

} // namespace rshell
