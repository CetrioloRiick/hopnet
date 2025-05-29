#include "common/input.hpp"
#include <filesystem>

namespace hpn {
int loadInt(const std::filesystem::path& path)
{
  std::ifstream is{path};
  if (!is.is_open()) {
    throw std::runtime_error("Cannot open input file: " + path.string());
  }

  std::string line;
  if (!std::getline(is, line)) {
    throw std::runtime_error("File is empty or unreadable: " + path.string());
  }

  std::istringstream iss(line);
  int result;
  if (!(iss >> result)) {
    throw std::runtime_error("No valid integer found in first line of file: "
                             + path.string());
  }

  return result;
}
} // namespace hpn
