#include "opencv2/core/mat.hpp"
#include <cxxopts.hpp>
#include <opencv2/opencv.hpp>
#include <exception>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

cv::Mat scaleImage(const std::string& path)
{
  cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);
  cv::Mat resized;
  cv::resize(image, resized, cv::Size(1000, 1000));
  // cv::imshow("My Image", pippo);
  // cv::waitKey(0); // aspetta un tasto
  // std::cout << entry << '\n';
  // std::cout << "output/scaled" + entry << '\n';
  // std::cout << entry.path() << '\n';
  // cv::imwrite("output/scaled" + entry.path(), resized);
  return resized;
}

int main(int argc, char* argv[])
{
  try {
    //INIZIO INPUT
    cxxopts::Options options(
        "binarize", "Convert all images in a folder to binary format (-1, +1)");

    options.add_options()("i,input", "Input folder path",
                          cxxopts::value<std::string>())(
        "t,threshold", "Threshold for binarization",
        cxxopts::value<int>()->default_value("127"))("h,help", "Print help");

    auto result = options.parse(argc, argv);

    if (result.count("help") || !result.count("input")) {
      std::cout << options.help() << std::endl;
      return 0;
    }

    fs::path inputFolder = result["input"].as<std::string>();
    int threshold        = result["threshold"].as<int>();

    if (!fs::exists(inputFolder) || !fs::is_directory(inputFolder)) {
      std::cerr << "Error: invalid input folder path.\n";
      return 1;
    }
    //
    //
    //
    // FINE INPUT

    std::cout << threshold << '\n';
    fs::create_directory(inputFolder / "output");
    for (const auto& entry : fs::directory_iterator(inputFolder)) {
      if (entry.is_regular_file()) {
        cv::Mat image = scaleImage(entry.path());
        image         = image > threshold;
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
