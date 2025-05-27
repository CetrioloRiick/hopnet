#include "binarize.hpp"
#include "../common/input.hpp"
#include "opencv2/core/mat.hpp"
#include <cxxopts.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <array>
#include <cctype>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[])
{
  try {
    hpn::BinarizeOptions options{hpn::getBinOpt(argc, argv)};

    std::ofstream fout(options.inputFolder.parent_path().parent_path()
                       / "binarized-images.txt");

    for (const auto& entry :
         std::filesystem::directory_iterator(options.inputFolder)) {
      if (hpn::isAcceptedImage(entry)) {
        cv::Mat image = cv::imread(entry.path(), cv::IMREAD_GRAYSCALE);
        if (image.empty()) {
          throw std::runtime_error("Error loading image: "
                                   + entry.path().string());
        }

        cv::Mat resized;
        cv::resize(image, resized, cv::Size(options.width, options.height));

        cv::Mat binary;
        cv::threshold(resized, binary, options.threshold, 255,
                      cv::THRESH_BINARY);

        std::transform(binary.begin<uchar>(), binary.end<uchar>(),
                       std::ostream_iterator<int>(fout, " "),
                       [](uchar val) { return val ? +1 : -1; });
        fout << '\n';
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
