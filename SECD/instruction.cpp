#include "instruction.h"


Instruction::Instruction(const Instruction& elem)
{
    this->name = elem.name;
}

Instruction::Instruction(instruction_t name)
{
    this->name = name;
}


const Instruction& Instruction::operator =(const Instruction &elem)
{
    this->name = elem.name;

    return *this;
}

const Instruction& Instruction::operator =(instruction_t name)
{
    this->name = name;
    return *this;
}


Elem* Instruction::clone() const
{
    return new Instruction(*this);
}

bool Instruction::compare(Elem* orig) const
{
    auto elem = dynamic_cast<Instruction*>(orig);

    if (elem != nullptr && elem->get_value() == this->name)
        return true;
    return false;
}

std::shared_ptr<Elem> Instruction::get_ptr() const
{
    std::shared_ptr<Elem> temp(new Instruction(*this));
    return temp;
}

void Instruction::print(std::ostream &out) const
{
    out << name;
}


instruction_t Instruction::get_value() const
{
    return name;
}
