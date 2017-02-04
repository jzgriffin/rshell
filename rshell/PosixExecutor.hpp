// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_PosixExecutor
#define hpp_rshell_PosixExecutor

#include "Executor.hpp"

namespace rshell {

class PosixExecutor : public Executor
{
public:
    virtual ~PosixExecutor();

    virtual int execute(const Command& command) override;
};

} // namespace rshell

#endif // hpp_rshell_PosixExecutor
