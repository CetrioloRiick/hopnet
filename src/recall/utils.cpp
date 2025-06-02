#include "recall/utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace hpn {
void displayBinImage(const std::vector<int>& data, int w, int h)
{
  unsigned int width{static_cast<unsigned int>(w)};
  unsigned int height{static_cast<unsigned int>(h)};

  if (data.size() != width * height) {
    std::cout << "data.size(): " << data.size() << '\n';
    throw std::invalid_argument("Vector size does not match width * height");
  }

  sf::RenderWindow window(sf::VideoMode(width, height), "Image Viewer");
  window.setSize(windowScale(width, height));
  sf::Image image;
  image.create(width, height, sf::Color::Black);

  for (unsigned int y = 0; y < height; ++y) {
    for (unsigned int x = 0; x < width; ++x) {
      int value       = data[y * width + x];
      sf::Color color = (value == 1) ? sf::Color::White : sf::Color::Black;
      image.setPixel(x, y, color);
    }
  }

  sf::Texture texture;
  texture.loadFromImage(image);
  sf::Sprite sprite(texture);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    window.draw(sprite);
    window.display();
  }
}

sf::Vector2u windowScale(unsigned int width, unsigned int height)
{
  constexpr unsigned int windowWidth  = 500;
  constexpr unsigned int windowHeight = 500;

  unsigned int scaleX = windowWidth / width;
  unsigned int scaleY = windowHeight / height;
  auto scale          = std::min(scaleX, scaleY);

  return {width * scale, height * scale};
}
} // namespace hpn