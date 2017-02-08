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
#include <stdexcept>

namespace rshell {

Parser::Parser(const std::vector<Token>& tokens)
    : _tokens(tokens)
{
}

Command* Parser::apply()
{
    Command* initial = 0;
    Command* current = 0;
    for (std::vector<Token>::const_iterator token = _tokens.begin();
            token != _tokens.end(); ++token) {
        // If the initial command has not yet been created, it must be
        // instantiated and made current
        if (initial == 0) {
            initial = new InitialCommand();
            current = initial;
        }

        // If the current command does not yet have a program name, the
        // current token must be the name.  Otherwise, if the current token is
        // a word, it must be the next argument to the current command.
        // Otherwise, a new command should be instantiated and made current
        // according to the type of connective represented by the current
        // token
        if (current->program.empty()) {
            if (token->type != TokenWord) {
                delete initial;
                throw std::runtime_error("command must start with word");
            }

            current->program = token->text;
        }
        else if (token->type == TokenWord) {
            current->arguments.push_back(token->text);
        }
        else if (token->type == TokenSequence) {
            current->next = new SequentialCommand();
            current = current->next;
        }
        else if (token->type == TokenConjunction) {
            current->next = new ConjunctiveCommand();
            current = current->next;
        }
        else if (token->type == TokenDisjunction) {
            current->next = new DisjunctiveCommand();
            current = current->next;
        }
        else {
            delete initial;
            throw std::runtime_error("unexpected token");
        }
    }

    return initial;
}

} // namespace rshell
