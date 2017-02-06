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
/// \brief Contains the interface to the \ref rshell::ArgVector class

#ifndef hpp_rshell_ArgVector
#define hpp_rshell_ArgVector

#include <string>
#include <vector>

namespace rshell {

/// \brief Utility for converting a program and argument vector to a C-style
/// null-terminated argv array
///
/// This class takes ownership of the string data.  Thus, the C array is
/// valid as long as its ArgVector exists.
class ArgVector
{
public:
    /// \brief Constructs a new instance of the \ref ArgVector class with the
    /// given program string and argument strings
    /// \param program program string
    /// \param arguments argument strings
    ArgVector(std::string program, std::vector<std::string> arguments);

    /// \brief Gets a pointer to a string in the argv array
    /// \param i index of string
    /// \return pointer to argument string
    const char* operator[](std::size_t i) const noexcept { return _argv[i]; }

    /// \brief Gets a pointer to a string in the argv array
    /// \param i index of string
    /// \return pointer to argument string
    char* operator[](std::size_t i) noexcept { return _argv[i]; }

    /// \brief Gets the pointer to the argv array
    /// \return pointer to argv array
    operator const char* const*() const noexcept { return argv(); }

    /// \brief Gets the pointer to the argv array
    /// \return pointer to argv array
    operator char* const*() noexcept { return argv(); }

    /// \brief Gets a reference to the program string
    /// \return reference to the program string
    const std::string& program() const noexcept { return _program; }

    /// \brief Gets a reference to the argument strings
    /// \return reference to the argument strings
    const std::vector<std::string>& arguments() const noexcept
    { return _arguments; }

    /// \brief Gets the pointer to the argv array
    /// \return pointer to argv array
    const char* const* argv() const noexcept { return _argv.data(); }

    /// \brief Gets the pointer to the argv array
    /// \return pointer to argv array
    char* const* argv() noexcept { return _argv.data(); }

    /// \brief Updates the argument vector with the given program string and
    /// argument strings
    /// \param program program string
    /// \param arguments argument strings
    void update(std::string program, std::vector<std::string> arguments);

private:
    std::string _program; //!< Program string
    std::vector<std::string> _arguments; //!< Argument strings
    std::vector<char*> _argv; //!< Argument vector

    /// \brief Updates the argument vector with the internal program string
    /// and argument strings
    void update();
};

} // namespace rshell

#endif // hpp_rshell_ArgVector
