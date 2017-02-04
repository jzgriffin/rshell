// Author:     Jeremiah Griffin
// Instructor: Brian Crites
// Course:     CS100
// Quarter:    Winter 2017
// Assignment: Assignment 2

#ifndef hpp_rshell_Execution
#define hpp_rshell_Execution

#include "Command.hpp"
#include "Executor.hpp"
#include <memory>

namespace rshell {

class Execution {
public:
    explicit Execution(std::unique_ptr<Executor>&& executor);

    const Executor& executor() const noexcept { return *_executor; }
    Executor& executor() noexcept { return *_executor; }

    int execute(const Command& command);

private:
    std::unique_ptr<Executor> _executor;

    void handleExit(const Command& command);
};

} // namespace rshell

#endif // hpp_rshell_Execution
