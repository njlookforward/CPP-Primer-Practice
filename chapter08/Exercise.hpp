#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>

// exercise_8_1
std::istream &read(std::istream &is);
void process_fstream(std::ifstream &ifs);
void read(const std::string &file, std::vector<std::string> &svec);

// 个人通讯信息
struct PersonInfo {
    std::string _name;
    std::vector<std::string> _phones;   // phone number array
};

void MakeAddressList(std::istream &is, std::vector<PersonInfo> &people);

#endif  // EXERCISE_HPP