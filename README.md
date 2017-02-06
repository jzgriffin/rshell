# Introduction

rshell is an implementation of a simple command shell using POSIX system
calls and the composite and strategy patterns.  It is written according
to my own design specification as well as the assignment requirements
written by Mike Izbicki as used in the CS100 (Software Construction)
course by Brian Crites at the University of California, Riverside during
the winter 2017 quarter.

# Features

- Simple and extensible implementation
- Chained commands
  - Sequential commands (a; b)
  - Conjunctive commands (a && b)
  - Disjunctive commands (a || b)
- Robust command parser
  - Quoted strings
  - Escape sequences
  - Line continuation
  - Comments

# Known Issues

- Locked into initial working directory
- Unable to get or set environment variables

# Building

To build, execute `make` in the root repository directory.  This will
place the rshell executable in the `bin/` directory.  If you have
Doxygen installed, you may execute `make doc` to generate the code
documentation in the `doc/output/` directory.

## Requirements

- C++11 compiler
- GNU Make
- Doxygen (optional; only for `doc` target)

# Using

Once built, the `rshell` executable resides in the `bin/` directory and
may be invoked with `bin/rshell`.  Then it will accept and execute
commands using a traditional prompt interface.  To leave rshell and
return to your normal shell, execute the `exit` command.

# License

rshell is available under the terms of the ISC software license, the
full text of which is available in the LICENSE file.
