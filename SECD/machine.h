#ifndef MACHINE_H
#define MACHINE_H

#include <stack_t.h>

#include <functional>
#include <fstream>


//typedef std::stack<std::shared_ptr<Elem>> stack_t;

struct Dump
{
    std::shared_ptr<stack_t> S;
    std::shared_ptr<stack_t> E;
    std::shared_ptr<stack_t> C;
    Dump *D;
};

class Machine
{
private:
    std::shared_ptr<stack_t> S;
    std::shared_ptr<stack_t> E;
    Dump *D;
public:
    std::shared_ptr<stack_t> C;

public:
    Machine();
    ~Machine() = default;

    void toDump();
    void CtoDump();
    void get_out_dump();

    void operation(const std::function<integer_t (integer_t, integer_t)>);

    void ADD();
    void MUL();
    void SUB();
    void DIV();
    void REM();
    void EQ();
    void LEQ();
    void SEL();
    void LD();
    void LDC();
    void LDF();
    void CAR();
    void CDR();
    void CONS();
    void NIL();
    void DUM();
    void AP();
    void RAP();
    void RTN();
    void JOIN();

    std::shared_ptr<Elem>& STOP();

    Elem & execute(std::ostream &);


public:
    void print_S(std::ostream &);
    void print_E(std::ostream &);
    void print_C(std::ostream &);
};

#endif // MACHINE_H
