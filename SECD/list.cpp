#include "list.h"

List::List(const List &elem)
{
    Elem * temp;


    if (this != &elem)
    {
//        if (elem.value.size() > 1)
//        {
            for(auto&& it : elem.value)
            {
                temp = it->clone();

                value.push_back(temp->get_ptr());
            }
//        }

//        throw Exception("List operator =", "FatalError");
    }
}

List::List(list_t value)
{
    Elem* temp;


    for(auto&& it : value)
    {
        temp = it->clone();
        this->value.push_back(temp->get_ptr());
    }
}


const List& List::operator = (const List &elem)
{
    Elem * temp;


    if (this != &elem)
    {
        this->value.clear();

//        if (elem.value.size() > 1)
//        {
            for(auto&& it : elem.value)
            {
                temp = it->clone();
                value.push_back(temp->get_ptr());
            }
//        }

//        throw Exception("List operator =", "FatalError");
    }

    return *this;
}

const List& List::operator = (list_t value)
{
    Elem * temp;


    this->value.clear();

    for(auto&& it : value)
    {
        temp = it->clone();
        this->value.push_back(temp->get_ptr());
    }

    return *this;
}


Elem* List::clone() const
{
    return new List(*this);
}

bool List::compare(Elem *orig) const
{
    auto elem = dynamic_cast<List*>(orig);
    list_t list;
    bool result = true;
    list_t::const_iterator it1;
    list_t::const_iterator it2;


    if (elem != nullptr)
    {
        list = elem->get_value();
        it1 = value.cbegin();
        it2 = list.cbegin();
        while ((it1 != value.cend()) && (it2 != list.cend()))
        {
            result = result && (**it1 == **it2);
            ++it1;
            ++it2;
        }

        return result;
    }
    return false;
}

std::shared_ptr<Elem> List::get_ptr() const
{
    std::shared_ptr<Elem> temp(new List(*this));
    return temp;
}

void List::print(std::ostream &out) const
{
    bool first_print = true;

    out << "[ ";
    for (const auto& elem : value)
    {
        if (first_print)
            first_print = false;
        else
            out << " , ";
        elem->print(out);
    }
    out << " ]";
}


list_t List::get_value() const
{
    return value;
}
