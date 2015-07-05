#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <elem.h>
#include <string>

typedef std::string instruction_t;
class Instruction : public Elem
{
private:
    instruction_t name;

public:
    Instruction() = default;
    Instruction(instruction_t);
    Instruction(const Instruction &);
    ~Instruction() = default;

    const Instruction & operator =(const Instruction &);
    const Instruction & operator =(instruction_t);

    virtual Elem* clone() const;
    virtual bool compare(Elem*) const;
    virtual std::shared_ptr<Elem> get_ptr() const;
    virtual void print(std::ostream &) const;

    instruction_t get_value() const;
};

#endif // INSTRUCTION_H
