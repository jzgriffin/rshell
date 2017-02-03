class Shell
{
public:
    bool isRunning() const noexcept;

    int process();
    int run();

private:
    bool _isRunning{false};
    Execution _execution;

    void printCommandPrompt();
    void printContinuationPrompt();
    std::string readCommand();
    std::string promptCommand();

    int execute(const std::string& string);
};

struct Token
{
    enum class Type
    {
        None,
        Word,
        Sequence,
        Conjunction,
        Disjunction,
    };

    Type type;
    std::string text;
};

class Tokenizer
{
public:
    explicit Tokenizer(std::istream& input);

    const std::vector<Token>& tokens() const noexcept;
    bool inEscape() const noexcept;
    bool inQuote() const noexcept;
    bool isValid() const noexcept;

    const std::vector<Token>& apply();

private:
    std::istream& _input;
    std::vector<Token> _tokens;
    bool _inEscape;
    bool _inQuote;

    Token next();
};

class Parser
{
public:
    explicit Parser(const std::vector<Token>& tokens);

    std::unique_ptr<Command> apply();

private:
    const std::vector<Token>& _tokens;
};

class Execution
{
public:
    explicit Execution(std::unique_ptr<Executor>&& executor);

    const Executor& executor() const noexcept;
    Executor& executor() noexcept;

    int execute(const Command& command);

private:
    std::unique_ptr<Executor> _executor;
};

class Executor
{
public:
    virtual ~PosixExecutor();

    virtual int execute(const Command& command) = 0;
};

class PosixExecutor : public Executor
{
public:
    virtual ~PosixExecutor();

    virtual int execute(const Command& command) override;
};

class Command
{
public:
    std::string program;
    std::vector<std::string> arguments;
    std::unique_ptr<Command> next;

    virtual ~Command();

    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept = 0;
};

class InitialCommand : public Command
{
public:
    virtual ~InitialCommand();

    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept override;
};

class SequentialCommand : public Command
{
public:
    virtual ~SequentialCommand();

    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept override;
};

class ConjunctiveCommand : public Command
{
public:
    virtual ~ConjunctiveCommand();

    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept override;
};

class DisjunctiveCommand : public Command
{
public:
    virtual ~DisjunctiveCommand();

    virtual bool shouldExecuteAfter(const Command& command,
            int exitCode) const noexcept override;
};
