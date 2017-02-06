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

#include "Parser.hpp"
#include "ConjunctiveCommand.hpp"
#include "DisjunctiveCommand.hpp"
#include "InitialCommand.hpp"
#include "SequentialCommand.hpp"
#include "utility/make_unique.hpp"
#include <stdexcept>

using utility::make_unique;

namespace rshell {

Parser::Parser(const std::vector<Token>& tokens)
    : _tokens(tokens)
{
}

std::unique_ptr<Command> Parser::apply()
{
    std::unique_ptr<Command> initial;
    Command* current = nullptr;
    for (auto&& token : _tokens) {
        // If the initial command has not yet been created, it must be
        // instantiated and made current
        if (initial == nullptr) {
            initial = make_unique<InitialCommand>();
            current = initial.get();
        }

        // If the current command does not yet have a program name, the
        // current token must be the name.  Otherwise, if the current token is
        // a word, it must be the next argument to the current command.
        // Otherwise, a new command should be instantiated and made current
        // according to the type of connective represented by the current
        // token
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
