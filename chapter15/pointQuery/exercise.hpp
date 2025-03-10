#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

inline void checkInputArg(int argc, int req)
{
    if(argc != req)
        throw std::runtime_error("input arguments invalid.");
}

inline void openInputFile(std::ifstream &ifs, const std::string &dir)
{
    ifs.open(dir);
    if(!ifs)
    {
        std::cerr << "Sorry, cannot open " << dir << std::endl;
        std::exit(-1);
    }
}

#endif