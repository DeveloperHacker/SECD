#include "machine.h"

Machine::Machine()
{
    std::shared_ptr<stack_t> temp1(new stack_t);
    std::shared_ptr<stack_t> temp2(new stack_t);
    std::shared_ptr<stack_t> temp3(new stack_t);

    D = nullptr;

    S = temp1;
    E = temp2;
    C = temp3;
}


void Machine::toDump()
{
    Dump *temp_D = D;

    D = new Dump;
    D->D = temp_D;

    D->S = S;
    D->E = E;
    D->C = C;

    std::shared_ptr<stack_t> temp1(new stack_t);
    std::shared_ptr<stack_t> temp2(new stack_t);
    std::shared_ptr<stack_t> temp3(new stack_t);

    S = temp1;
    E = temp2;
    C = temp3;
}

void Machine::CtoDump()
{
    Dump *temp_D = D;

    D = new Dump;
    D->D = temp_D;

    D->C = C;

    std::shared_ptr<stack_t> temp(new stack_t);
    C = temp;
}

void Machine::get_out_dump()
{
    if (D == nullptr) throw Exception("get_out_dump", "DumpIsEmpty");

    S = D->S;
    E = D->E;
    C = D->C;

    D = D->D;
}

void Machine::operation(const std::function<integer_t (integer_t, integer_t)> oper)
{
    std::shared_ptr<Elem> A_orig;
    std::shared_ptr<Elem> B_orig;


    if (S->size() < 2) throw Exception("operation", "ArgumentsNotFound");

    A_orig = S->pop_ret();
    B_orig = S->pop_ret();

    auto A = dynamic_cast<Integer*>(&*A_orig);
    auto B = dynamic_cast<Integer*>(&*B_orig);

    if (A == nullptr || B == nullptr) throw Exception("operation", "InvalideArguments");
    S->push_ptr(new Integer(oper(A->get_value(), B->get_value())));
}

void Machine::ADD()
{
    operation([](integer_t a, integer_t b){ return a + b; });
}

void Machine::MUL()
{
    operation([](integer_t a, integer_t b){ return a * b; });
}

void Machine::SUB()
{
    operation([](integer_t a, integer_t b){ return a - b; });
}

void Machine::DIV()
{
    operation([](integer_t a, integer_t b){ return a / b; });
}

void Machine::REM()
{
    operation([](integer_t a, integer_t b){ return a % b; });
}

void Machine::EQ()
{
    std::shared_ptr<Elem> A;
    std::shared_ptr<Elem> B;


    if (S->size() < 2) throw Exception("EQ", "ArgumentsNotFound");

    A = S->pop_ret();
    B = S->pop_ret();

    S->push_ptr(new Bool(*A == *B));
}

void Machine::LEQ()
{
    std::shared_ptr<Elem> A_orig;
    std::shared_ptr<Elem> B_orig;


    if (S->size() < 2)
        throw Exception("LEQ", "ArgumentsNotFound");

    A_orig = S->pop_ret();
    B_orig = S->pop_ret();

    auto A_I = dynamic_cast<Integer*>(&*A_orig);
    auto B_I = dynamic_cast<Integer*>(&*B_orig);
    if (A_I != nullptr && B_I != nullptr)
        S->push_ptr(new Bool(A_I->get_value() <= B_I->get_value()));
    else
        throw Exception("LEQ", "InvalideArguments");
}

void Machine::LD()
{
    std::shared_ptr<Elem> nil(new Nil);
    std::shared_ptr<Elem> result = nil;
    stack_t stack;
    List *args = nullptr;
    Integer *arg1, *arg2;


    if (C->empty()) throw Exception("LD", "ArgumentsNotFound");

    arg1 = dynamic_cast<Integer*>(&*(C->top()));
    if (arg1 == nullptr)
    {
        args = dynamic_cast<List*>(&*(C->top()));
        if (args == nullptr) throw Exception("LD", "InvalideArguments");
        arg1 = dynamic_cast<Integer*>(&*(args->get_value().front()));
        if (arg1 == nullptr) throw Exception("LD", "InvalideArguments");
        arg2 = dynamic_cast<Integer*>(&*(args->get_value().back()));
        if (arg2 == nullptr) throw Exception("LD", "InvalideArguments");
    }


    if (arg1->get_value() < 1) throw Exception("LD", "InvalideArguments");
    for (auto i = 0; i < arg1->get_value(); ++i)
    {
        if (E->empty()) break;
        stack.push(E->pop_ret());
    }

    if (args != nullptr)
    {
        if (arg2->get_value() < 1) throw Exception("LD", "InvalideArguments");
        auto elem_ptr = dynamic_cast<List*>(stack.top()->clone());
        if (elem_ptr == nullptr)
        {
            if (arg2->get_value() == 1)
                result = stack.top();
        }
        else
        {
            auto elem = elem_ptr->get_value();

            for (auto i = 1; i < arg2->get_value(); ++i)
            {
                if (elem.empty()) break;
                elem.pop_front();
            }
            if (!elem.empty()) result = elem.front();
        }
    }
    else
        result = stack.top();

    while (!stack.empty())
        E->push(stack.pop_ret());
    S->push(result);
    C->pop();
}

void Machine::LDC()
{
    if (C->empty()) throw Exception("LDC", "ArgumentsNotFound");

    S->push(C->pop_ret());
}

void Machine::LDF() //Seted
{
    if (C->empty()) throw Exception("LDF", "ArgumentsNotFound");

    list_t enviroment_list;
    std::shared_ptr<Elem> enviroment;

    while (!E->empty())
        enviroment_list.push_back(E->pop_ret());

    if (enviroment_list.empty())
        enviroment = std::shared_ptr<Elem>(new Nil());
    else
        enviroment = std::shared_ptr<Elem>(new List(enviroment_list));

    for (auto it = enviroment_list.rbegin(); it != enviroment_list.rend(); ++it)
        E->push(*it);

    S->push_ptr(new Closure(*(C->pop_ret()), *enviroment));
}

void Machine::CAR()
{
    auto memory_cell = S->top();
    if (S->empty()) throw Exception("CAR", "ArgumentsNotFound");
    auto A = dynamic_cast<List*>(&*memory_cell);

    if (A != nullptr)
    {
        S->pop();
        S->push(A->get_value().front());
    }
}

void Machine::CDR() //Seted
{
    auto memory_cell = S->top();
    if (S->empty()) throw Exception("CDR", "ArgumentsNotFound");
    auto A = dynamic_cast<List*>(&*(S->pop_ret()));

    if (A == nullptr)
        this->NIL();
    else
    {
        auto elem = A->get_value();
        elem.pop_front();
        if (elem.empty())
            this->NIL();
        else
            S->push_ptr(new List(elem));
    }
}

void Machine::CONS()
{
    if(S->size() < 2) throw Exception("CONS", "ArgumentsNotFound");

    auto arg1_ptr = S->pop_ret();
    auto arg2_ptr = S->pop_ret();

    auto arg1 = dynamic_cast<List*>(&*arg1_ptr);
    auto arg2 = dynamic_cast<List*>(&*arg2_ptr);
    list_t list;

    if (arg1 == nullptr)
    {
        if (arg2 == nullptr)
        {
            list.push_front(arg2_ptr);
            list.push_front(arg1_ptr);
        }
        else
        {
            list = arg2->get_value();
            list.push_front(arg1_ptr);
        }
    }
    else
    {
        if (arg2 == nullptr)
        {
            list = arg1->get_value();
            list.push_back(arg2_ptr);
        }
        else
        {
            list_t temp;

            if (arg1->get_value().size() > arg2->get_value().size())
            {
                list = arg1->get_value();
                temp = arg2->get_value();
                while (!temp.empty())
                {
                    list.push_back(temp.front());
                    temp.pop_front();
                }
            }
            else
            {
                list = arg2->get_value();
                temp = arg1->get_value();
                while (!temp.empty())
                {
                    list.push_front(temp.back());
                    temp.pop_back();
                }
            }
        }
    }

    S->push_ptr(new List(list));
}

void Machine::NIL()
{
    S->push_ptr(new Nil());
}

void Machine::DUM()
{
    E->push_ptr(new Nil());
}

void Machine::AP()
{
    if (S->empty()) throw Exception("AP", "ArgumentsNotFound");

    List *enviroment;
    List *body;
    list_t list;
    std::shared_ptr<Elem> args_ptr;
    auto closure_ptr = S->pop_ret();
    auto closure = dynamic_cast<Closure*>(&*closure_ptr);
    if (closure == nullptr) throw Exception("AP", "InvalideArguments");

    if (S->empty())
        args_ptr = std::shared_ptr<Elem>(new Nil());
    else
        args_ptr = S->pop_ret();

    toDump();

    body = dynamic_cast<List*>(&(closure->get_body()));
    if (body == nullptr)
        C->push_ptr(closure->get_body().clone());
    else
    {
        list = body->get_value();
        while(!list.empty())
        {
            C->push(list.back());
            list.pop_back();
        }
    }
    enviroment = dynamic_cast<List*>(&(closure->get_enviroment()));
    if (enviroment == nullptr)
        E->push_ptr(closure->get_enviroment().clone());
    else
    {
        list = enviroment->get_value();
        while(!list.empty())
        {
            E->push(list.back());
            list.pop_back();
        }
    }

    E->push(args_ptr);
}

void Machine::RAP()
{
    if (S->empty()) throw Exception("RAP", "ArgumentsNotFound");

    List *enviroment;
    List *body;
    list_t list;
    std::shared_ptr<Elem> args_ptr;
    auto closure_ptr = S->pop_ret();
    auto closure = dynamic_cast<Closure*>(&*closure_ptr);
    if (closure == nullptr) throw Exception("RAP", "InvalideArguments");

    if (S->empty())
        args_ptr = std::shared_ptr<Elem>(new Nil());
    else
        args_ptr = S->pop_ret();

    toDump();

    body = dynamic_cast<List*>(&(closure->get_body()));
    if (body == nullptr) C->push_ptr(closure->get_body().clone());
    else
    {
        list = body->get_value();
        while(!list.empty())
        {
            C->push(list.back());
            list.pop_back();
        }
    }
    S->push_ptr(closure->get_enviroment().clone());
    CDR();
    enviroment = dynamic_cast<List*>(&*(S->top()));
    if (enviroment == nullptr)
        E->push_ptr(&*(S->top()));
    else
    {
        list = enviroment->get_value();
        while(!list.empty())
        {
            E->push(list.back());
            list.pop_back();
        }
    }
    S->pop();
    E->push(args_ptr);
}

void Machine::RTN()
{
    std::shared_ptr<Elem> result;

    if (S->empty())
        result = nullptr;
    else
        result = S->pop_ret();

    get_out_dump();

    if (result != nullptr) S->push(result);
}

void Machine::SEL()
{
    if (S->empty()) throw Exception("SEL", "ArgumentsNotFound");

    std::shared_ptr<Elem> value = S->pop_ret();
    auto basis = dynamic_cast<Bool*>(&*value);

    if (basis == nullptr) throw Exception("SEL", "InvalideArguments");
    if (C->size() < 2) throw Exception("SEL", "ArgumentsNotFound");

    std::shared_ptr<Elem> body_then = C->pop_ret();
    std::shared_ptr<Elem> body_else = C->pop_ret();

    std::shared_ptr<Elem> body_ptr;
    if (basis->get_value() == true)
        body_ptr = body_then;
    else
        body_ptr = body_else;

    auto body = dynamic_cast<List*>(&*body_ptr);
    auto body_nil = dynamic_cast<Nil*>(&*body_ptr);
    if (body == nullptr && body_nil == nullptr) Exception("SEL", "FatalError");

    CtoDump();
    C->push_ptr(new Instruction("JOIN"));
    if (body != nullptr)
    {
        auto list = body->get_value();
        while (!list.empty())
        {
            C->push(list.back());
            list.pop_back();
        }
    }
}

void Machine::JOIN()
{
    if (D == nullptr) throw Exception("JOIN", "DumpIsEmpty");

    C = D->C;
    D = D->D;
}

std::shared_ptr<Elem>& Machine::STOP()
{
    return S->top();
}

Elem & Machine::execute(std::ostream &out)
{
    Instruction *command;
    std::shared_ptr<Elem> command_ptr;

    Elem *ADD(new Instruction("ADD"));
    Elem *MUL(new Instruction("MUL"));
    Elem *SUB(new Instruction("SUB"));
    Elem *DIV(new Instruction("DIV"));
    Elem *REM(new Instruction("REM"));
    Elem *EQ(new Instruction("EQ"));
    Elem *LEQ(new Instruction("LEQ"));
    Elem *SEL(new Instruction("SEL"));
    Elem *LD(new Instruction("LD"));
    Elem *LDC(new Instruction("LDC"));
    Elem *LDF(new Instruction("LDF"));
    Elem *CAR(new Instruction("CAR"));
    Elem *CDR(new Instruction("CDR"));
    Elem *CONS(new Instruction("CONS"));
    Elem *NIL(new Instruction("NIL"));
    Elem *DUM(new Instruction("DUM"));
    Elem *AP(new Instruction("AP"));
    Elem *RAP(new Instruction("RAP"));
    Elem *RTN(new Instruction("RTN"));
    Elem *JOIN(new Instruction("JOIN"));
    Elem *STOP(new Instruction("STOP"));

    while (!C->empty())
    {
        if (out != 0x0)
        {
            print_S(out);
            print_E(out);
            print_C(out);
            out << std::endl;
        }

        command_ptr = C->pop_ret();
        command = dynamic_cast<Instruction*>(&*command_ptr);
        if (command == nullptr) throw Exception("Execute", "FatalError");

        if (*command == *ADD)       this->ADD();
        else if (*command == *MUL)  this->MUL();
        else if (*command == *SUB)  this->SUB();
        else if (*command == *DIV)  this->DIV();
        else if (*command == *REM)  this->REM();
        else if (*command == *EQ)   this->EQ();
        else if (*command == *LEQ)  this->LEQ();
        else if (*command == *SEL)  this->SEL();
        else if (*command == *LD)   this->LD();
        else if (*command == *LDC)  this->LDC();
        else if (*command == *LDF)  this->LDF();
        else if (*command == *CAR)  this->CAR();
        else if (*command == *CDR)  this->CDR();
        else if (*command == *CONS) this->CONS();
        else if (*command == *NIL)  this->NIL();
        else if (*command == *DUM)  this->DUM();
        else if (*command == *AP)   this->AP();
        else if (*command == *RAP)  this->RAP();
        else if (*command == *RTN)  this->RTN();
        else if (*command == *JOIN)  this->JOIN();
        else if (*command == *STOP) { return (*(this->STOP()));}
        else throw Exception("Execute", "Expected 'instruction' but greeted constant.");
    }

    throw Exception("Execute", "FatalError");
}

void Machine::print_S(std::ostream &out)
{
    out << "S = ";
    out << *S;
    out << std::endl;
}

void Machine::print_E(std::ostream &out)
{
    out << "E = ";
    out << *E;
    out << std::endl;
}

void Machine::print_C(std::ostream &out)
{
    out << "C = ";
    out << *C;
    out << std::endl;
}
