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

/// \brief Represents a lexical token within a command string
struct Token
{
    /// \brief Types of tokens that may appear in a command string
    enum class Type
    {
        None, //!< Represents the end of a token sequence
        Word, //!< Space-delimited word or quoted grouping of words
        Sequence, //!< Sequential command delimiter
        Conjunction, //!< Conjunctive command delimiter
        Disjunction, //!< Disjunctive command delimiter
    };

    Type type; //!< Type classification
    std::string text; //!< Body text
};

} // namespace rshell

#endif // hpp_rshell_Token
