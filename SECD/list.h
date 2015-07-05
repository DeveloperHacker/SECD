#ifndef LIST_H
#define LIST_H

#include <elem.h>
#include <list>

typedef std::list<std::shared_ptr<Elem>> list_t;
class List : public Elem
{
private:
    list_t value;

public:
    List() = default;
    List(const List &);
    List(list_t);
    ~List() = default;

    const List & operator = (const List &);
    const List & operator = (list_t);

    virtual Elem* clone() const;
    virtual bool compare(Elem*) const;
    virtual std::shared_ptr<Elem> get_ptr() const;
    virtual void print(std::ostream &) const;

    list_t get_value() const;
};

#endif // LIST_H
