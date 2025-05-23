#ifndef INPUT_HPP
#define INPUT_HPP
#include "binarize.hpp"
#include <cxxopts.hpp>

namespace hpn {
BinarizeOptions getOpt(int argc, char* argv[]);
}
#endif