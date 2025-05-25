#include "recall.hpp"
#include "../common/input.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
  try {
    hpn::RecallOptions options{hpn::getRecallOpt(argc, argv)};

    
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}