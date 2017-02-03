// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#include "Parser.hpp"
#include "ConjunctiveCommand.hpp"
#include "DisjunctiveCommand.hpp"
#include "InitialCommand.hpp"
#include "SequentialCommand.hpp"
#include "utility/make_unique.hpp"
#include <stdexcept>

namespace rshell {

using utility::make_unique;

Parser::Parser(const std::vector<Token>& tokens)
    : _tokens(tokens)
{
}

std::unique_ptr<Command> Parser::apply()
{
    std::unique_ptr<Command> initial;
    Command* current = nullptr;

    for (auto&& token : _tokens) {
        if (initial == nullptr) {
            initial = make_unique<InitialCommand>();
            current = initial.get();
        }

        if (current->program.empty()) {
            if (token.type != Token::Type::Word) {
                throw std::runtime_error{"command must start with word"};
            }

            current->program = token.text;
        }
        else if (token.type == Token::Type::Word) {
            current->arguments.push_back(token.text);
        }
        else if (token.type == Token::Type::Sequence) {
            current->next = make_unique<SequentialCommand>();
            current = current->next.get();
        }
        else if (token.type == Token::Type::Conjunction) {
            current->next = make_unique<ConjunctiveCommand>();
            current = current->next.get();
        }
        else if (token.type == Token::Type::Disjunction) {
            current->next = make_unique<DisjunctiveCommand>();
            current = current->next.get();
        }
        else {
            throw std::runtime_error{"unexpected token"};
        }
    }

    return initial;
}

} // namespace rshell
