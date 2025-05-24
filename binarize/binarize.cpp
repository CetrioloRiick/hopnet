#include "binarize.hpp"
#include "input.hpp"
#include "opencv2/core/mat.hpp"
#include <cxxopts.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;
namespace hpn {
cv::Mat scaleImage(const std::string& path)
{
  cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);
  cv::Mat resized;
  cv::resize(image, resized, cv::Size(10, 10));

  // cv::imshow("My Image", pippo);
  // cv::waitKey(0); // aspetta un tasto
  // std::cout << entry << '\n';
  // std::cout << "output/scaled" + entry << '\n';
  // std::cout << entry.path() << '\n';
  // cv::imwrite("output/scaled" + entry.path(), resized);
  return resized;
}
BinarizeOptions::BinarizeOptions(std::filesystem::path inp, int w, int h, int t)
    : inputFolder(inp)
    , width(w)
    , height(h)
    , threshold(t)
{
  if (!fs::exists(inputFolder) || !fs::is_directory(inputFolder)) {
    throw std::invalid_argument("inputFolder not valid");
  }
  if (width < 1) {
    throw std::invalid_argument("width must be greater than 1");
  }
  if (height < 1) {
    throw std::invalid_argument("height must be greater than 1");
  }
  if (threshold < 0 || threshold > 255) {
    throw std::invalid_argument("threshold must be between 0 and 255");
  }
}
} // namespace hpn
int main(int argc, char* argv[])
{
  try {
    hpn::BinarizeOptions opt{hpn::getOpt(argc, argv)};

    std::ofstream fout(opt.inputFolder.parent_path() / "binarized-images.txt");
    std::array<std::string, 7> acceptedExt = {".png",  ".jpg", ".jpeg", ".bmp",
                                              ".tiff", ".tif", ".webp"};

    for (const auto& entry : fs::directory_iterator(opt.inputFolder)) {
      if (entry.is_regular_file()
          && std::ranges::contains(acceptedExt,
                                   entry.path().extension().string())) {
        std::cout << entry.path().extension().string();
        std::string stem = entry.path().stem().string();

        cv::Mat image = hpn::scaleImage(entry.path());
        image         = image > opt.threshold;

        /*std::transform(image.begin<int>(), image.end<int>(),
                        std::ostream_iterator<int>(fout, " "),
                        [](int v) { return v ? +1 : -1; });*/

        for (int i = 0; i < image.rows; ++i) {
          for (int j = 0; j < image.cols; ++j) {
            int val = image.at<uchar>(i, j);
            fout << (val ? +1 : -1) << " ";
          }
        }
        fout << '\n';
      }
    }

  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
