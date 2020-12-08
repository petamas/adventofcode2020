#include "stl.h"
#include "aoc.h"

namespace day08 {

enum class InstructionType { NOP, ACC, JMP };

struct Instruction {
    InstructionType type;
    int param;
};

std::istream& operator>>(std::istream& is, Instruction& instruction) {
    static const std::map<std::string, InstructionType> lookup {
        {"nop", InstructionType::NOP},
        {"acc", InstructionType::ACC},
        {"jmp", InstructionType::JMP}
    };

    std::string name;
    if (is >> name >> instruction.param)
        instruction.type = lookup.at(name);
    return is;
}

class ProgramIterator;

using Program = std::vector<Instruction>;

struct State {
    int ip = 0;
    int acc = 0;

    bool execute(const Instruction& instruction) {
        switch (instruction.type) {
        case InstructionType::NOP:
            ip++;
            return true;
        case InstructionType::ACC:
            acc += instruction.param;
            ip++;
            return true;
        case InstructionType::JMP:
            ip += instruction.param;
            return true;
        }
        return false;
    }
};

class ProgramIterator : public boost::iterator_facade<ProgramIterator, const State, std::input_iterator_tag> {
public:
    ProgramIterator() = default;

    ProgramIterator(const Program& program) : program(&program) {}
private:
    friend class boost::iterator_core_access;

    void increment() {
        assert(program);
        state.execute((*program)[state.ip]);
        if (state.ip == program->size())
            program = nullptr;
    }

    bool equal(ProgramIterator const& other) const
    {
        if (program == nullptr && other.program == nullptr)
            return true;
        return program == other.program && state.ip == other.state.ip && state.acc == other.state.acc;
    }

    const State& dereference() const {
        return state;
    }

    const Program * program = nullptr;
    State state;
};

// first: value before stopping
// second: finished without infinite loop
std::pair<int, bool> run(const Program& program) {
    boost::iterator_range<ProgramIterator> rng(ProgramIterator(program), ProgramIterator{});
    std::set<int> visited;
    auto it = boost::find_if(rng, [&visited](const State& state) { return !visited.insert(state.ip).second; });
    return { it->acc, it == rng.end() };
}

int64_t solve(std::istream& is, Task task) {
    Program program;
    boost::copy(boost::istream_range<Instruction>(is), std::back_inserter(program));

    if (task == Task::FIRST)
    {
        auto rv = run(program);
        assert(!rv.second);
        return rv.first;
    } else {
        auto rng = boost::irange(program.size())
            | boost::adaptors::filtered([&program](size_t i) {
                return program[i].type == InstructionType::JMP || program[i].type == InstructionType::NOP;
            })
            | boost::adaptors::transformed([&program](size_t i) {
                Program copy(program);
                copy[i].type = program[i].type == InstructionType::JMP ? InstructionType::NOP : InstructionType::JMP;
                return run(copy);
            });
        
        return boost::find_if(rng, [](const auto& rv) { return rv.second; })->first;
    }
}

} // namespace day08
