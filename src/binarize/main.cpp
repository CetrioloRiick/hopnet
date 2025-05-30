#include "binarize/input.hpp"
#include "binarize/utils.hpp"
#include "opencv2/core/mat.hpp"
#include <cxxopts.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
  try {
    hpn::BinarizeOptions options{hpn::getBinOpt(argc, argv)};
    auto outputPath{options.inputFolder.parent_path()};

    std::ofstream fout(outputPath / "binarized-images.txt");

    //  Possible other implementation with the for
    /* for (const auto& entry : std::filesystem::directory_iterator(options.inputFolder))
     * {*/
    std::ranges::for_each(
        std::filesystem::directory_iterator(options.inputFolder),
        [&](const auto& entry) {
          if (hpn::isAcceptedImage(entry)) {
            cv::Mat image = cv::imread(entry.path(), cv::IMREAD_GRAYSCALE);
            if (image.empty()) {
              throw std::runtime_error("Error loading image: " + entry.path().string());
            }
            cv::resize(image, image, cv::Size(options.width, options.height));
            // cv::imshow("test", image);
            // cv::waitKey(0);
            cv::threshold(image, image, options.threshold, 255, cv::THRESH_BINARY);

            if (options.show) {
              cv::imwrite(options.inputFolder.parent_path()
                              / ("binarized-" + entry.path().filename().string()),
                          image);
            }

            // Not usable because image is not necessarily contiguous in memory
            /*std::transform(image.begin<uchar>(), image.end<uchar>(),
                           std::ostream_iterator<int>(fout, " "),
                           [](uchar val) { return val ? +1 : -1; });*/
            for (int i{0}; i < image.rows; ++i) {
              for (int j{0}; j < image.cols; ++j) {
                fout << (image.at<uchar>(i, j) ? +1 : -1) << " ";
              }
            }
            fout << '\n';
          }
        }

    );
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return 1;
  }
}
