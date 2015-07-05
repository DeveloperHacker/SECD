#ifndef PARSER_H
#define PARSER_H

#include <machine.h>

class Parser
{
private:
    Machine machine;
public:
    Parser() = default;
    ~Parser() = default;

    static bool isNumber(const std::string &);
    static std::shared_ptr<Elem> StringtoInteger(const std::string &);
    void parsing(const std::string &);
    const Machine & get_machine() const;
};

#endif // PARSER_H
