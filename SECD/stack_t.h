#ifndef STACK_T_H
#define STACK_T_H

#include <bool.h>
#include <integer.h>
#include <nil.h>
#include <instruction.h>
#include <list.h>
#include <closure.h>

#include <stack>

class stack_t : public std::stack<std::shared_ptr<Elem>>
{
public:
    void push_ptr(Elem *);
    std::shared_ptr<Elem> pop_ret()
    {
        auto result = top();
        pop();
        return result;
    }

    friend std::ostream & operator << (std::ostream &, stack_t &);
};

#endif // STACK_T_H
