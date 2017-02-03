// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#include "Tokenizer.hpp"
#include <istream>
#include <locale>
#include <map>
#include <stdexcept>

namespace {

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
    return !(_inEscape || _inQuote);
}

const std::vector<Token>& Tokenizer::apply()
{
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
    if (!(_input >> std::ws)) {
        return token;
    }

    ignoreComment();

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
    if (_input.peek() != '#') {
        return false;
    }

    while (_input && _input.get() != '\n');

    return true;
}

bool Tokenizer::nextSequence(Token& token)
{
    if (_input.peek() != ';') {
        return false;
    }

    token.text += _input.get();
    token.type = Token::Type::Sequence;
    return true;
}

bool Tokenizer::nextConjunction(Token& token)
{
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
    if (_input.peek() != '|') {
        return false;
    }

    token.text += _input.get();
    if (_input.peek() != '|') {
        throw std::runtime_error{"unexpected |"};
    }

    token.text += _input.get();
    token.type = Token::Type::Disjunction;
    return true;
}

bool Tokenizer::nextWord(Token& token)
{
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
        auto c = _input.peek();
        if (c == EOF || c == '"') {
            return false;
        }

        if (!_inQuote) {
            if (std::isspace<char>(c, loc)) {
                return false;
            }

            if (c == '#' || c == ';' || c == '&' || c == '|') {
                return false;
            }
        }

        return true;
    };

    auto count = 0;
    while (isDirect()) {
        auto c = _input.get();
        if (c == '\\') {
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

    if (count == 0) {
        return false;
    }

    token.type = Token::Type::Word;
    return true;
}

bool Tokenizer::nextQuoteWord(Token& token)
{
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
