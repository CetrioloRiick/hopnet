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

int main(int argc, char* argv[])
{
  try {
    // INIZIO INPUT
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

    std::cout << inputFolder.parent_path() << '\n';

    std::ofstream fout(inputFolder.parent_path() / "binarized-images.txt");

    for (const auto& entry : fs::directory_iterator(inputFolder)) {
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
