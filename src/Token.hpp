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
/// \brief Contains the interface to the \ref rshell::Token structure

#ifndef hpp_rshell_Token
#define hpp_rshell_Token

#include <string>

namespace rshell {

/// \brief Types of tokens that may appear in a command string
enum TokenType
{
    TokenNone, //!< Represents the end of a token sequence
    TokenWord, //!< Space-delimited word or quoted grouping of words
    TokenSequence, //!< Sequential command delimiter
    TokenConjunction, //!< Conjunctive command delimiter
    TokenDisjunction //!< Disjunctive command delimiter
};

/// \brief Represents a lexical token within a command string
struct Token
{
    TokenType type; //!< Type classification
    std::string text; //!< Body text
};

} // namespace rshell

#endif // hpp_rshell_Token
