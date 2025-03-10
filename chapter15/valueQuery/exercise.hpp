#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstddef>

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

class Threshold {
public:
    Threshold(std::size_t lb, std::size_t rb): _lb(lb), _rb(rb) {}

    bool operator() (std::size_t sz) const {
        return sz < _lb || sz > _rb;
    }

private:
    std::size_t _lb;
    std::size_t _rb;
};

#endif