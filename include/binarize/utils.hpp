#ifndef BINARIZE_UTILS_HPP
#define BINARIZE_UTILS_HPP
#include <filesystem>

namespace hpn {
bool isAcceptedImage(const std::filesystem::directory_entry& entry);
} // namespace hpn

#endif