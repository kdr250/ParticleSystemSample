#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720),
                            "Particle Sample",
                            sf::Style::Titlebar | sf::Style::Close);

    sf::VertexArray triangle(sf::Triangles, 3);

    float centerX = window.getSize().x / 2.0;
    float centerY = window.getSize().y / 2.0;

    triangle[0].position = sf::Vector2f(centerX, centerY);
    triangle[1].position = sf::Vector2f(centerX + 100.0f, centerY);
    triangle[2].position = sf::Vector2f(centerX + 100.0f, centerY + 100.0f);

    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
            }
        }

        window.clear();
        window.draw(triangle);
        window.display();
    }

    return 0;
}
