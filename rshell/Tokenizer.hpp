// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_Tokenizer
#define hpp_rshell_Tokenizer

#include "Token.hpp"
#include <iosfwd>
#include <vector>

namespace rshell {

class Tokenizer
{
public:
    explicit Tokenizer(std::istream& input);

    const std::vector<Token>& tokens() const noexcept { return _tokens; }
    bool inEscape() const noexcept { return _inEscape; }
    bool inQuote() const noexcept { return _inQuote; }
    bool isValid() const noexcept;

    const std::vector<Token>& apply();

private:
    std::istream& _input;
    std::vector<Token> _tokens;
    bool _inEscape{false};
    bool _inQuote{false};

    Token next();
    bool ignoreComment();
    bool nextSequence(Token& token);
    bool nextConjunction(Token& token);
    bool nextDisjunction(Token& token);
    bool nextWord(Token& token);
    bool nextDirectWord(Token& token);
    bool nextQuoteWord(Token& token);
};

} // namespace rshell

#endif // hpp_rshell_Tokenizer
