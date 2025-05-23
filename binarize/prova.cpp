#include <opencv2/opencv.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_folder>\n";
    return 1;
  }

  fs::path inputFolder = argv[1];
  if (!fs::exists(inputFolder) || !fs::is_directory(inputFolder)) {
    std::cerr << "Error: invalid folder path.\n";
    return 1;
  }

  const int threshold = 127; // soglia per binarizzazione

  std::cout << inputFolder << "\n";
  std::cout << inputFolder.parent_path() << "\n";
  for (const auto& entry : fs::directory_iterator(inputFolder)) {
    if (!entry.is_regular_file())
      continue;

    std::string filename = entry.path().filename().string();
    std::string stem     = entry.path().stem().string();

    cv::Mat img = cv::imread(entry.path().string(), cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
      std::cerr << "Warning: could not read " << filename << "\n";
      continue;
    }

    fs::path outputFolder = inputFolder.parent_path() / "poppo";

    std::ofstream fout(outputFolder / (stem + ".txt"));

    img = img > threshold; // binarizzazione

    for (int i = 0; i < img.rows; ++i) {
      for (int j = 0; j < img.cols; ++j) {
        int val = img.at<uchar>(i, j);
        fout << (val ? +1 : -1) << " ";
      }
    }
    fout << "\n";
    std::cout << "Processed: " << filename << "\n";
  }

  return 0;
}
