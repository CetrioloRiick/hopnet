#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace hpn {
void displayImage(const std::vector<int>& data, unsigned int width, unsigned int height)
{
  if (data.size() != width * height) {
    std::cout << "data.size(): " << data.size() << '\n';
    throw std::invalid_argument("Vector size does not match width * height");
  }

  sf::RenderWindow window(sf::VideoMode(width, height), "Image Viewer");
  // Crea la finestra grafica

  sf::Image image;
  image.create(width, height, sf::Color::Black);
  // Crea immagine vuota tutta nera

  for (unsigned int y = 0; y < height; ++y) {
    for (unsigned int x = 0; x < width; ++x) {
      int value       = data[y * width + x];
      sf::Color color = (value == 1) ? sf::Color::White : sf::Color::Black;
      image.setPixel(x, y, color);
    }
  }
  // Trasformo il vettore in immagine

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
} // namespace hpn