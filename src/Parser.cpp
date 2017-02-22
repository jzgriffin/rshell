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
#include "ExecutableCommand.hpp"
#include "ExitBuiltinCommand.hpp"
#include "SequentialCommand.hpp"
#include "utility/make_unique.hpp"
#include <cassert>
#include <stdexcept>

#include <iostream>

using utility::make_unique;

namespace rshell {

Parser::Parser(const std::vector<Token>& tokens)
    : _tokens(tokens)
{
}

std::unique_ptr<Command> Parser::apply()
{
    _root.release();
    _current = &_root;
    _scope = nullptr;

    for (auto&& token : _tokens) {
        switch (token.type) {
            case Token::Type::Word: parseWord(token); break;
            case Token::Type::Sequence: parseSequence(token); break;
            case Token::Type::Conjunction: parseConjunction(token); break;
            case Token::Type::Disjunction: parseDisjunction(token); break;
            case Token::Type::None: break;
        }
    }

    return std::move(_root);
}

void Parser::parseWord(const Token& token)
{
    assert(token.type == Token::Type::Word);

    if (*_current == nullptr) {
        if (token.text == "exit") {
            *_current = make_unique<ExitBuiltinCommand>();
        }
        else {
            *_current = make_unique<ExecutableCommand>();
        }
    }

    auto executable = dynamic_cast<ExecutableCommand*>(_current->get());
    if (executable == nullptr) {
        throw std::runtime_error{"word in non-executable command"};
    }

    if (executable->program.empty()) {
        executable->program = token.text;
    }
    else {
        executable->arguments.push_back(token.text);
    }
}

void Parser::parseSequence(const Token& token)
{
    assert(token.type == Token::Type::Sequence);

    if (_scope == nullptr) {
        auto scope = make_unique<SequentialCommand>();
        if (_root != nullptr) {
            scope->sequence.push_back(std::move(_root));
        }

        _scope = scope.get();
        _root = std::move(scope);
    }

    _scope->sequence.push_back(nullptr);
    _current = &_scope->sequence.back();
}

void Parser::parseConjunction(const Token& token)
{
    assert(token.type == Token::Type::Conjunction);

    if (*_current == nullptr) {
        throw std::runtime_error{"conjunction must follow command"};
    }

    auto current = make_unique<ConjunctiveCommand>();
    auto connective = current.get();
    current->primary = std::move(*_current);
    *_current = std::move(current);
    _current = &connective->secondary;
}

void Parser::parseDisjunction(const Token& token)
{
    assert(token.type == Token::Type::Disjunction);

    if (*_current == nullptr) {
        throw std::runtime_error{"disjunction must follow command"};
    }

    auto current = make_unique<DisjunctiveCommand>();
    auto connective = current.get();
    current->primary = std::move(*_current);
    *_current = std::move(current);
    _current = &connective->secondary;
}

} // namespace rshell
