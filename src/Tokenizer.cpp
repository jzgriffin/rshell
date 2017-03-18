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

#include "Tokenizer.hpp"
#include <istream>
#include <locale>
#include <map>
#include <stdexcept>

namespace {

/// \brief Converts an escaped character to its literal equivalent
/// \param c character to convert
/// \return literal equivalent of \p c
///
/// If the given character is not code for another character, it is its
/// own literal equivalent.
char unescape(char c)
{
    static std::map<char, char> codes{
        {'a', '\a'},
        {'e', 0x33},
        {'n', '\n'},
        {'r', '\r'},
        {'t', '\t'},
    };

    auto iter = codes.find(c);
    if (iter == std::end(codes)) {
        return c;
    }

    return iter->second;
}

}

namespace rshell {

Tokenizer::Tokenizer(std::istream& input)
    : _input(input)
{
}

bool Tokenizer::isValid() const noexcept
{
    return !(_inEscape || _inQuote || inScope());
}

const std::vector<Token>& Tokenizer::apply()
{
    // Continue tokenizing until the next token has no type, signalling
    // the end of tokenizable input

    auto token = next();
    while (token.type != Token::Type::None) {
        _tokens.push_back(std::move(token));
        token = next();
    }

    return _tokens;
}

Token Tokenizer::next()
{
    auto token = Token{Token::Type::None};

    // Ignore all white space and comments before the next token
    do {
        // Skip over white space between tokens
        if (!(_input >> std::ws)) {
            return token;
        }
    } while (ignoreComment());

    if (nextSequence(token)) {
        return token;
    }

    if (nextConjunction(token)) {
        return token;
    }

    if (nextDisjunction(token)) {
        return token;
    }

    if (nextInputRedirection(token)) {
        return token;
    }

    if (nextOutputRedirection(token)) {
        return token;
    }

    if (nextScope(token)) {
        return token;
    }

    if (nextWord(token)) {
        return token;
    }

    return token;
}

bool Tokenizer::ignoreComment()
{
    // Comments must start with a # symbol and continue until the next
    // line feed character

    if (_input.peek() != '#') {
        return false;
    }

    while (_input && _input.get() != '\n');

    return true;
}

bool Tokenizer::nextSequence(Token& token)
{
    // Sequence tokens consist of a single ; symbol

    if (_input.peek() != ';') {
        return false;
    }

    token.text += _input.get();
    token.type = Token::Type::Sequence;
    return true;
}

bool Tokenizer::nextConjunction(Token& token)
{
    // Conjunction tokens consists of two consecutive & symbols

    if (_input.peek() != '&') {
        return false;
    }

    token.text += _input.get();
    if (_input.peek() != '&') {
        throw std::runtime_error{"unexpected &"};
    }

    token.text += _input.get();
    token.type = Token::Type::Conjunction;
    return true;
}

bool Tokenizer::nextDisjunction(Token& token)
{
    // Disjunction tokens consist of two consecutive | symbols

    if (_input.peek() != '|') {
        return false;
    }

    token.text += _input.get();
    if (_input.peek() != '|') {
        // If there is a single pipe character, the delimiter is a pipe, not
        // a disjunction

        token.type = Token::Type::Pipe;
        return true;
    }

    token.text += _input.get();
    token.type = Token::Type::Disjunction;
    return true;
}

bool Tokenizer::nextInputRedirection(Token& token)
{
    // Input redirection tokens consist of a single < symbol

    if (_input.peek() != '<') {
        return false;
    }

    token.text += _input.get();
    token.type = Token::Type::InputRedirection;
    return true;
}

bool Tokenizer::nextOutputRedirection(Token& token)
{
    // Output redirection tokens consist of two consecutive > symbols

    if (_input.peek() != '>') {
        return false;
    }

    token.text += _input.get();
    if (_input.peek() != '>') {
        // If there is a single arrow character, the delimiter is an output
        // redirection, not an append redirection

        token.type = Token::Type::OutputRedirection;
        return true;
    }

    token.text += _input.get();
    token.type = Token::Type::AppendRedirection;
    return true;
}

bool Tokenizer::nextScope(Token& token)
{
    // Scope tokens are left and right parentheses

    switch (_input.peek()) {
        case '(': token.type = Token::Type::OpenScope; ++_scopeLevel; break;
        case ')': token.type = Token::Type::CloseScope; --_scopeLevel; break;
        default: return false;
    }

    token.text += _input.get();
    return true;
}

bool Tokenizer::nextWord(Token& token)
{
    // Word tokens consist of a mixture of one or more direct or quoted
    // words in sequence

    auto result = false;
    while (nextDirectWord(token) || nextQuoteWord(token)) {
        result = true;
    }

    return result;
}

bool Tokenizer::nextDirectWord(Token& token)
{
    auto loc = _input.getloc();
    auto isDirect = [&]()
    {
        // Determine whether the next character in the input is a direct
        // word symbol, meaning that it is not a quotation mark or, if
        // outside of a quote, a white space character or other special
        // punctuation mark

        auto c = _input.peek();
        if (c == EOF || c == '"') {
            return false;
        }

        if (!_inQuote) {
            if (std::isspace<char>(c, loc)) {
                return false;
            }

            if (c == '#' || c == ';' || c == '&' || c == '|' ||
                    c == '(' || c == ')' || c == '<' || c == '>') {
                return false;
            }
        }

        return true;
    };

    // Extract as many direct word symbols as possible
    auto count = 0;
    while (isDirect()) {
        auto c = _input.get();
        if (c == '\\') {
            // Process the escape sequence

            _inEscape = true;

            c = _input.get();
            if (c == EOF) {
                return false;
            }

            token.text += unescape(c);
            _inEscape = false;
        }
        else {
            token.text += c;
        }

        ++count;
    }

    // Empty sequences do not count as words
    if (count == 0) {
        return false;
    }

    token.type = Token::Type::Word;
    return true;
}

bool Tokenizer::nextQuoteWord(Token& token)
{
    // To tokenize a quoted word, simply extract the quotation marks and
    // read a direct word with the inQuote flag set

    if (_input.peek() != '"') {
        return false;
    }

    _inQuote = true;
    _input.get();

    nextDirectWord(token);

    if (_input.peek() != '"') {
        return false;
    }

    _inQuote = false;
    _input.get();

    token.type = Token::Type::Word;
    return true;
}

} // namespace rshell
