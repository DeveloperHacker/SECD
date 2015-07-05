#include "stack_t.h"

std::ostream & operator << (std::ostream &out, stack_t &Stack)
{
    bool first_print = true;
    stack_t backup;

    out << "[ ";
    while (!Stack.empty())
    {
        if (first_print)
            first_print = false;
        else
            out << " , ";
        backup.push(Stack.top());
        out << *(Stack.top());
        Stack.pop();
    }
    out << " ]";

    while (!backup.empty())
    {
        Stack.push(backup.top());
        backup.pop();
    }

    return out;
}

void stack_t::push_ptr(Elem *elem)
{
    push(std::shared_ptr<Elem>(elem));
}
