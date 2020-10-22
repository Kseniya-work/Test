#pragma once

#include <machine/precompiled.h>

namespace machine
{

class Machine
{
    public:
        std::stringstream result;

    public:
        void make_convertation(std::istream& is);

        friend std::istream& operator >> (std::istream& is, 
                                          Machine& machine); 
        friend std::ostream& operator << (std::ostream& os, 
                                          const Machine& machine); 

    private:
        bool _ill_flag = false;

        std::map<std::string, char> _digit_map = {{" _ | ||_|", '0'},
                                                  {"     |  |", '1'},
                                                  {" _  _||_ ", '2'},
                                                  {" _  _| _|", '3'},
                                                  {"   |_|  |", '4'},
                                                  {" _ |_  _|", '5'},
                                                  {" _ |_ |_|", '6'},
                                                  {" _   |  |", '7'},
                                                  {" _ |_||_|", '8'},
                                                  {" _ |_| _|", '9'}};

    private:
        std::stringstream _get_number(std::string& up_line,
                                       std::string& mid_line,
                                       std::string& low_line);

        bool _is_valid(std::stringstream& number);
};

} // namespace machine

#include <machine/sources/machine.inl>

