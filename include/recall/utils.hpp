#ifndef RECALL_UTILS_HPP
#define RECALL_UTILS_HPP
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace hpn {
void displayBinImage(const std::vector<int>& data, int w, int h);

sf::Vector2u windowScale(unsigned int width, unsigned int height);
}
#endif