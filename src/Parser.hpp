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
/// \brief Contains the interface to the \ref rshell::Parser class

#ifndef hpp_rshell_Parser
#define hpp_rshell_Parser

#include "Command.hpp"
#include "Token.hpp"
#include <memory>
#include <stack>
#include <utility>
#include <vector>

namespace rshell {

// Forward declarations
class SequentialCommand;

/// \brief Accepts a sequence of tokens and transforms it into a composition
/// of one or more commands
class Parser
{
public:
    /// \brief Constructs a new instance of the \ref Parser class on the given
    /// sequence of tokens
    /// \param tokens sequence of tokens to parse
    explicit Parser(const std::vector<Token>& tokens);

    /// \brief Parses the token sequence according to command grammar
    /// \return parsed command on success, \c null on failure
    ///
    /// The parsing process is considered a failure if the token sequence is
    /// not well-formed.
    std::unique_ptr<Command> apply();

private:
    /// \brief Type of smart pointer for storing Command instances
    using CommandPtr = std::unique_ptr<Command>;

    /// \brief Type of pair used in the scope stack
    ///
    /// The first element is a pointer to the SequentialCommand representing
    /// the scope.  The second element is a pointer to the owning pointer for
    /// the SequentialCommand, which is used when popping the scope.
    using ScopePair = std::pair<SequentialCommand*, CommandPtr*>;

    const std::vector<Token>& _tokens; //!< Sequence of tokens to parse

    CommandPtr _root; //!< Root command for the parse
    CommandPtr* _current; //!< Pointer to the current owning command pointer
    bool _isRootSequence{false}; //!< Whether or not the root is sequential
    std::stack<ScopePair> _scopes; //!< Stack of current scopes

    /// \brief Parses a Token::Type::Word token
    /// \param token token to parse
    void parseWord(const Token& token);

    /// \brief Parses a Token::Type::Word token for an executable
    /// \param token token to parse
    /// \return whether the parse was accepted
    bool parseExecutableWord(const Token& token);

    /// \brief Parses a Token::Type::Word token for an input redirection
    /// \param token token to parse
    /// \return whether the parse was accepted
    bool parseInputRedirectionWord(const Token& token);

    /// \brief Parses a Token::Type::Word token for an output redirection
    /// \param token token to parse
    /// \return whether the parse was accepted
    bool parseOutputRedirectionWord(const Token& token);

    /// \brief Parses a Token::Type::Word token for an append redirection
    /// \param token token to parse
    /// \return whether the parse was accepted
    bool parseAppendRedirectionWord(const Token& token);

    /// \brief Parses a Token::Type::Sequence token
    /// \param token token to parse
    void parseSequence(const Token& token);

    /// \brief Parses a Token::Type::Conjunction token
    /// \param token token to parse
    void parseConjunction(const Token& token);

    /// \brief Parses a Token::Type::Disjunction token
    /// \param token token to parse
    void parseDisjunction(const Token& token);

    /// \brief Parses a Token::Type::Pipe token
    /// \param token token to parse
    void parsePipe(const Token& token);

    /// \brief Parses a Token::Type::InputRedirection token
    /// \param token token to parse
    void parseInputRedirection(const Token& token);

    /// \brief Parses a Token::Type::OutputRedirection token
    /// \param token token to parse
    void parseOutputRedirection(const Token& token);

    /// \brief Parses a Token::Type::AppendRedirection token
    /// \param token token to parse
    void parseAppendRedirection(const Token& token);

    /// \brief Parses a Token::Type::OpenScope token
    /// \param token token to parse
    void parseOpenScope(const Token& token);

    /// \brief Parses a Token::Type::CloseScope token
    /// \param token token to parse
    void parseCloseScope(const Token& token);
};

} // namespace rshell

#endif // hpp_rshell_Parser
