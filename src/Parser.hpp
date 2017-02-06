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
/// \brief Contains the interface to the \ref rshell::Parser class

#ifndef hpp_rshell_Parser
#define hpp_rshell_Parser

#include "Command.hpp"
#include "Token.hpp"
#include <memory>

namespace rshell {

/// \brief Accepts a sequence of tokens and transforms it into a composition
/// of one or more commands
class Parser
{
public:
    /// \brief Constructs a new instance of the \ref Parser class on the given
    /// sequence of tokens
    /// \param tokens sequence of tokens to parse
    explicit Parser(const std::vector<Token>& tokens);

    /// \brief Parses the token sequence according to command grammar
    /// \return parsed command on success, \c null on failure
    ///
    /// The parsing process is considered a failure if the token sequence is
    /// not well-formed.
    std::unique_ptr<Command> apply();

private:
    const std::vector<Token>& _tokens; //!< Sequence of tokens to parse
};

} // namespace rshell

#endif // hpp_rshell_Parser
