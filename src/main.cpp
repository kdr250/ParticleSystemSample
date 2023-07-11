#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Particle Sample");
    window.setFramerateLimit(60);

    ParticleSystem particleSystem(window);

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
                    else
                    {
                        particleSystem.resetParticles();
                    }
            }
        }

        particleSystem.update();

        window.clear(sf::Color::Black);
        particleSystem.draw(window);
        window.display();
    }

    return 0;
}
