#include <iostream>
#include <parser.h>


int main(int args, char *argv[])
{
    std::ofstream out_log;
    Parser parser;
    Machine machine;

    try
    {
        if (args < 2)
            throw Exception("Initialization", "Source file is not found");
        if (args > 2)
            out_log.open(argv[2]);

        parser.parsing(argv[1]);
        machine =  parser.get_machine();
        std::cout << machine.execute(out_log) << std::endl;
    }
    catch(Exception &exception)
    {
        std::cout << "Error: " << exception.name << ": " << exception.message << std::endl;
        out_log << "Error: " << exception.name << ": " << exception.message << std::endl;
        return 1;
    }

    return 0;
}
