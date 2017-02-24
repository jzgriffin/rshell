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
/// \brief Contains the interface to the \ref rshell::Tokenizer class

#ifndef hpp_rshell_Tokenizer
#define hpp_rshell_Tokenizer

#include "Token.hpp"
#include <iosfwd>
#include <vector>

namespace rshell {

/// \brief Accepts a stream and transforms it into a sequence of \ref Token
/// instances through lexical analysis
class Tokenizer
{
public:
    /// \brief Constructs a new instance of the \ref Tokenizer class on the
    /// given input stream
    /// \param input input stream to tokenize
    explicit Tokenizer(std::istream& input);

    /// \brief Gets a reference to the sequence of tokens
    /// \return reference to the sequence of tokens
    /// \see apply
    const std::vector<Token>& tokens() const noexcept { return _tokens; }

    /// \brief Gets a value indicating whether or not the tokenization
    /// terminated during an escape sequence
    /// \return whether or not the tokenization terminated during an escape
    /// sequence
    /// \see isValid
    bool inEscape() const noexcept { return _inEscape; }

    /// \brief Gets a value indicating whether or not the tokenization
    /// terminated during a quote sequence
    /// \return whether or not the tokenization terminated during a quote
    /// sequence
    /// \see isValid
    bool inQuote() const noexcept { return _inQuote; }

    /// \brief Gets a value indicating whether or not the tokenization
    /// terminated during a scope sequence
    /// \return whether or not the tokenization terminated during a scope
    /// sequence
    /// \see isValid
    bool inScope() const noexcept { return _scopeLevel > 0; }

    /// \brief Gets a value indicating whether or not the tokenization
    /// terminated normally
    /// \return whether or not the tokenization terminated normally
    /// \see inEscape
    /// \see inQuote
    /// \see inScope
    bool isValid() const noexcept;

    /// \brief Repeatedly tokenizes the input stream until its end is reached
    /// \return reference to the sequence of tokens
    /// \see tokens
    const std::vector<Token>& apply();

private:
    /// \brief Input stream to tokenize
    std::istream& _input;

    /// \brief Sequence of tokens
    std::vector<Token> _tokens;

    /// \brief Whether or not the tokenization terminated during an escape
    /// sequence
    bool _inEscape{false};

    /// \brief Whether or not the tokenization terminated during a quote
    /// sequence
    bool _inQuote{false};

    /// \brief Level of scope currently occupied
    int _scopeLevel{0};

    /// \brief Obtains the next token from the stream
    /// \return next token from the stream
    ///
    /// If there are no more tokens available, the returned \ref Token
    /// instance will have the \ref Token::Type::None classification.
    Token next();

    /// \brief Ignores a comment character and all subsequent characters for
    /// the remainder of the line
    /// \return whether or not a comment was ignored
    bool ignoreComment();

    /// \brief Tokenizes a sequential command delimiter
    /// \param token token to output into
    /// \return whether or not the tokenization succeeded
    bool nextSequence(Token& token);

    /// \brief Tokenizes a conjunctive command delimiter
    /// \param token token to output into
    /// \return whether or not the tokenization succeeded
    bool nextConjunction(Token& token);

    /// \brief Tokenizes a disjunctive command delimiter
    /// \param token token to output into
    /// \return whether or not the tokenization succeeded
    bool nextDisjunction(Token& token);

    /// \brief Tokenizes a scope character
    /// \param token token to output into
    /// \return whether or not the tokenization succeeded
    bool nextScope(Token& token);

    /// \brief Tokenizes a command word
    /// \param token token to output into
    /// \return whether or not the tokenization succeeded
    bool nextWord(Token& token);

    /// \brief Tokenizes a direct, unquoted command word
    /// \param token token to output into
    /// \return whether or not the tokenization succeeded
    ///
    /// The behavior of this method changes depending on the value of
    /// \ref _inQuote.  When inside of a quote, additional characters are
    /// accepted.
    bool nextDirectWord(Token& token);

    /// \brief Tokenizes a quoted command word
    /// \param token token to output into
    /// \return whether or not the tokenization succeeded
    bool nextQuoteWord(Token& token);
};

} // namespace rshell

#endif // hpp_rshell_Tokenizer
