// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_Token
#define hpp_rshell_Token

#include <string>

namespace rshell {

struct Token
{
    enum class Type
    {
        None,
        Word,
        Sequence,
        Conjunction,
        Disjunction,
    };

    Type type;
    std::string text;
};

} // namespace rshell

#endif // hpp_rshell_Token
