#include <elem.h>


bool operator ==(Elem& a, Elem& b)
{
    return a.compare(&b);
}

std::ostream & operator << (std::ostream &out, const Elem &elem)
{
    elem.print(out);

    return out;
}
