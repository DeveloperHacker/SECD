#include "parser.h"

bool Parser::isNumber(const std::string &number)
{
    integer_t start_index;

    if (number.size() == 0) return false;
    start_index = (number[0] == '-') ? 1 : 0;
    for (auto i = start_index; i < (integer_t)number.size(); ++i)
        if (number[i] < '0' || number[i] > '9')
            return false;
    return true;
}

std::shared_ptr<Elem> Parser::StringtoInteger(const std::string &number)
{
    integer_t result = 0;
    short sign = (number[0] == '-') ? -1 : 1;

    for (const auto& digit : number)
    {
        if (digit == '-') continue;
        result = result * 10 + sign * (digit - '0');
    }

    return std::shared_ptr<Elem>(new Integer(result));
}

void Parser::parsing(const std::string &file_name)
{
    std::shared_ptr<Elem> ADD(new Instruction("ADD"));
    std::shared_ptr<Elem> MUL(new Instruction("MUL"));
    std::shared_ptr<Elem> SUB(new Instruction("SUB"));
    std::shared_ptr<Elem> DIV(new Instruction("DIV"));
    std::shared_ptr<Elem> REM(new Instruction("REM"));
    std::shared_ptr<Elem> EQ(new Instruction("EQ"));
    std::shared_ptr<Elem> LEQ(new Instruction("LEQ"));
    std::shared_ptr<Elem> SEL(new Instruction("SEL"));
    std::shared_ptr<Elem> LD(new Instruction("LD"));
    std::shared_ptr<Elem> LDC(new Instruction("LDC"));
    std::shared_ptr<Elem> LDF(new Instruction("LDF"));
    std::shared_ptr<Elem> CAR(new Instruction("CAR"));
    std::shared_ptr<Elem> CDR(new Instruction("CDR"));
    std::shared_ptr<Elem> CONS(new Instruction("CONS"));
    std::shared_ptr<Elem> NIL(new Instruction("NIL"));
    std::shared_ptr<Elem> DUM(new Instruction("DUM"));
    std::shared_ptr<Elem> AP(new Instruction("AP"));
    std::shared_ptr<Elem> RAP(new Instruction("RAP"));
    std::shared_ptr<Elem> RTN(new Instruction("RTN"));
    std::shared_ptr<Elem> STOP(new Instruction("STOP"));

    list_t temp;
    std::stack<list_t> stack_list;
    std::shared_ptr<list_t> list(new list_t);
    std::string token;
    uint64_t open_brackets = 0;
    std::ifstream source(file_name);
    bool comment = false;

    if (!source) throw Exception("Parsing", file_name + " Source file is not found.");
    while (!source.eof())
    {
        token.clear();
        source >> token;

        if (token == "") continue;

        if (token == "//")
        {
            std::getline(source, token);
            continue;
        }
        if (token == "/*")
        {
            comment = true;
            continue;
        }
        if (token == "*/")
        {
            comment = false;
            continue;
        }
        if (comment == true) continue;

        else if (token == "ADD") list->push_back(ADD);
        else if (token == "MUL") list->push_back(MUL);
        else if (token == "SUB") list->push_back(SUB);
        else if (token == "DIV") list->push_back(DIV);
        else if (token == "REM") list->push_back(REM);
        else if (token == "EQ") list->push_back(EQ);
        else if (token == "LEQ") list->push_back(LEQ);
        else if (token == "SEL") list->push_back(SEL);
        else if (token == "LD") list->push_back(LD);
        else if (token == "LDC") list->push_back(LDC);
        else if (token == "LDF") list->push_back(LDF);
        else if (token == "CAR") list->push_back(CAR);
        else if (token == "CDR") list->push_back(CDR);
        else if (token == "CONS") list->push_back(CONS);
        else if (token == "NIL") list->push_back(NIL);
        else if (token == "DUM") list->push_back(DUM);
        else if (token == "AP") list->push_back(AP);
        else if (token == "RAP") list->push_back(RAP);
        else if (token == "RTN") list->push_back(RTN);
        else if (token == "STOP") list->push_back(STOP);
        else if (isNumber(token)) list->push_back(StringtoInteger(token));
        else if (token == "Nil") list->push_back(std::shared_ptr<Elem>(new Nil()));
        else if (token == "T" || token == "F")
            list->push_back(std::shared_ptr<Elem>(new Bool(token == "T" ? true : false)));
        else if (token == "[")
        {
            ++open_brackets;
            stack_list.push(*list);
            list = std::shared_ptr<list_t>(new list_t);
        }
        else if (token == "]")
        {
            if (open_brackets == 0) throw Exception("Parsing", "Expected '[' before ']' token.");
            --open_brackets;
            temp = stack_list.top();
            stack_list.pop();
            switch (list->size())
            {
                case 0 : { temp.push_back(std::shared_ptr<Elem>(new Nil())); break; }
//                case 1 : { temp.push_back(list->front()); break; }
                default : { temp.push_back(std::shared_ptr<Elem>(new List(*list))); break; }
            }
            list = std::shared_ptr<list_t>(new list_t(temp));
        }
        else throw Exception("Parsing", " Token " + token + " is not recognized.");
    }
    if (open_brackets != 0) throw Exception("Parsing", "Expected ']' at end of input.");
    while (!list->empty())
    {
        machine.C->push(list->back());
        list->pop_back();
    }
}

const Machine & Parser::get_machine() const
{
    return machine;
}
