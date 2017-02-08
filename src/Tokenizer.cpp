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
#include <cstdio>
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
    static std::map<char, char> codes;
    if (codes.empty()) {
        codes['a'] = '\a';
        codes['e'] = 0x33;
        codes['n'] = '\n';
        codes['r'] = '\r';
        codes['t'] = '\t';
    }

    std::map<char, char>::const_iterator iter = codes.find(c);
    if (iter == codes.end()) {
        return c;
    }

    return iter->second;
}

bool isDirect(char c, const std::locale& loc, bool inQuote)
{
    // Determine whether the next character in the input is a direct
    // word symbol, meaning that it is not a quotation mark or, if
    // outside of a quote, a white space character or other special
    // punctuation mark

    if (c == EOF || c == '"') {
        return false;
    }

    if (!inQuote) {
        if (std::isspace<char>(c, loc)) {
            return false;
        }

        if (c == '#' || c == ';' || c == '&' || c == '|') {
            return false;
        }
    }

    return true;
}

}

namespace rshell {

Tokenizer::Tokenizer(std::istream& input)
    : _input(input)
    , _inEscape(false)
    , _inQuote(false)
{
}

bool Tokenizer::isValid() const
{
    return !(_inEscape || _inQuote);
}

const std::vector<Token>& Tokenizer::apply()
{
    // Continue tokenizing until the next token has no type, signalling
    // the end of tokenizable input

    Token token = next();
    while (token.type != TokenNone) {
        _tokens.push_back(token);
        token = next();
    }

    return _tokens;
}

Token Tokenizer::next()
{
    Token token;
    token.type = TokenNone;

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
    token.type = TokenSequence;
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
        throw std::runtime_error("unexpected &");
    }

    token.text += _input.get();
    token.type = TokenConjunction;
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
        throw std::runtime_error("unexpected |");
    }

    token.text += _input.get();
    token.type = TokenDisjunction;
    return true;
}

bool Tokenizer::nextWord(Token& token)
{
    // Word tokens consist of a mixture of one or more direct or quoted
    // words in sequence

    bool result = false;
    while (nextDirectWord(token) || nextQuoteWord(token)) {
        result = true;
    }

    return result;
}

bool Tokenizer::nextDirectWord(Token& token)
{
    std::locale loc = _input.getloc();

    // Extract as many direct word symbols as possible
    std::size_t count = 0;
    while (isDirect(_input.peek(), loc, _inQuote)) {
        int c = _input.get();
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

    token.type = TokenWord;
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

    token.type = TokenWord;
    return true;
}

} // namespace rshell
