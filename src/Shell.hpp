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

/// \file
/// \brief Contains the interface to the \ref rshell::Shell class

#ifndef hpp_rshell_Shell
#define hpp_rshell_Shell

#include "Command.hpp"
#include "Execution.hpp"
#include "Token.hpp"
#include <iosfwd>
#include <string>
#include <vector>

namespace rshell {

/// \brief Presents a user-friendly interface and provides the point of
/// interaction for accepting and executing user commands
class Shell
{
public:
    /// \brief Constructs a new instance of the \ref Shell class
    Shell();

    /// \brief Gets a value indicating whether or not the shell is interactive
    /// \return whether or not the shell is interactive
    bool isInteractive() const { return _isInteractive; }

    /// \brief Sets whether or not the shell is interactive
    /// \param isInteractive whether or not the shell is interactive
    void setInteractive(bool isInteractive);

    /// \brief Gets a reference to the command input stream
    /// \return reference to the command input stream
    std::istream& input() const { return *_input; }

    /// \brief Sets the command input stream
    /// \param input reference to the command input stream
    void setInput(std::istream& input);

    /// \brief Gets a value indicating whether or not the shell is running
    /// \return whether or not the shell is running
    /// \see exitCode
    bool isRunning() const { return _isRunning; }

    /// \brief Gets the exit code of the shell process
    /// \return exit code of the shell process
    /// \see isRunning
    int exitCode() const { return _exitCode; }

    /// \brief Processes a command
    ///
    /// Prompts for, reads, parses, and executes a command, which may be
    /// composite.
    void process();

    /// \brief Repeatedly processes commands as long as the shell is running
    /// \return exit code of the shell process
    /// \see isRunning
    /// \see exitCode
    /// \see process
    int run();

private:
    bool _isInteractive; //!< Whether or not the shell is interactive
    std::istream* _input; //!< Command input stream

    bool _isRunning; //!< Whether or not the shell is running
    int _exitCode; //!< Exit code of the shell process

    Execution _execution; //!< Execution strategy for executing commands
    std::string _commandPrompt; //!< Text for the command prompt

    /// \brief Builds the command prompt text
    /// \return command prompt text
    std::string buildCommandPrompt() const;

    /// \brief Prints the prompt to begin a command
    /// \see printContinuationPrompt
    void printCommandPrompt() const;

    /// \brief Prints the prompt to continue a multiline command
    /// \see printCommandPrompt
    void printContinuationPrompt() const;

    /// \brief Reads and tokenizes a command string from the standard input
    /// \return sequence of tokens
    /// \see printContinuationPrompt
    ///
    /// Prompts for multiline continuation as necessary.
    std::vector<Token> readCommand() const;

    /// \brief Prompts for, reads, and tokenizes a command string
    /// \return sequence of tokens
    /// \see printCommandPrompt
    /// \see readCommand
    std::vector<Token> promptCommand() const;

    /// \brief Prompts for, reads, tokenizes, and parses a command
    /// \return input command on success, \c null if the input process failed
    /// \see promptCommand
    Command* getCommand() const;

    /// \brief Executes the given command
    /// \param command command to execute
    /// \return exit code of the command
    ///
    /// Sets the \ref _isRunning member to \c false when an exit command is
    /// executed.
    int execute(const Command& command);
};

} // namespace rshell

#endif // hpp_rshell_Shell
