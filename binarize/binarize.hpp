#ifndef BINARIZE_HPP
#define BINARIZE_HPP

#include "opencv2/core/mat.hpp"
#include <opencv2/opencv.hpp>
#include <filesystem>

namespace hpn {
bool isAcceptedImage(const std::filesystem::directory_entry& entry);
} // namespace hpn

#endif