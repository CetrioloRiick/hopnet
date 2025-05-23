#include "binarize.hpp"
#include "input.hpp"
#include "opencv2/core/mat.hpp"
#include <cxxopts.hpp>
#include <opencv2/opencv.hpp>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

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
BinarizeOptions::BinarizeOptions(std::filesystem::path inputFolder, int width,
                                 int height, int threshold)
    : inputFolder(inputFolder)
    , width(width)
    , height(height)
    , threshold(threshold)
{
  if (!fs::exists(inputFolder) || !fs::is_directory(inputFolder)) {
    throw std::invalid_argument("inputFolder not valid");
  }
  if (width < 1) {
    throw std::invalid_argument("width must be greater than 1");
  }if (height < 1) {
    throw std::invalid_argument("height must be greater than 1");
  }if(threshold<0 || threshold>255){
    throw std::invalid_argument("threshold must be between 0 and 255");
  }
}

int main(int argc, char* argv[])
{
  try {
    // INIZIO INPUT
    BinarizeOptions opt{getOpt(argc, argv)};

    int threshold;

    if (!fs::exists(opt.inputFolder) || !fs::is_directory(opt.inputFolder)) {
      std::cerr << "Error: invalid input folder path.\n";
      return 1;
    }
    //
    //
    //
    // FINE INPUT

    std::cout << opt.inputFolder.parent_path() << '\n';

    std::ofstream fout(opt.inputFolder.parent_path() / "binarized-images.txt");

    for (const auto& entry : fs::directory_iterator(opt.inputFolder)) {
      if (entry.is_regular_file()) {
        std::string stem = entry.path().stem().string();

        // cv::Mat img = cv::imread(entry.path().string(),
        // cv::IMREAD_GRAYSCALE);

        cv::Mat image = scaleImage(entry.path());
        image         = image > threshold;

        std::transform(image.begin<int>(), image.end<int>(),
                       std::ostream_iterator<int>(fout, " "),
                       [](int v) { return v ? +1 : -1; });
        /*for (int i = 0; i < image.rows; ++i) {
          for (int j = 0; j < image.cols; ++j) {
            int val = image.at<uchar>(i, j);
            fout << (val ? +1 : -1) << " ";
          }
        }*/
        fout << "\n";
        fout << "\n";
        fout << "\n";
        // cv::imshow("My Image", image);
        // cv::waitKey(0);
      }
    }

  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
} // namespace hpn