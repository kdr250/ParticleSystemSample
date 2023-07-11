#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ParticleSystem
{
    struct Particle
    {
        sf::Vector2f velocity;
        int lifetime = 0;
        float speed  = 0.0;
    };

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Vector2u m_windowSize;
    float m_size = 8.0;

    void resetParticle(size_t index, bool first = false)
    {
        // give the particle an initial position
        float centerX = m_windowSize.x / 2;
        float centerY = m_windowSize.y / 2;

        m_vertices[4 * index + 0].position = sf::Vector2f(centerX, centerY);
        m_vertices[4 * index + 1].position = sf::Vector2f(centerX + m_size, centerY);
        m_vertices[4 * index + 2].position = sf::Vector2f(centerX + m_size, centerY + m_size);
        m_vertices[4 * index + 3].position = sf::Vector2f(centerX, centerY + m_size);

        // give the particle a color
        sf::Color color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);

        if (first)
        {
            color.a = 0;
        }

        m_vertices[4 * index + 0].color = color;
        m_vertices[4 * index + 1].color = color;
        m_vertices[4 * index + 2].color = color;
        m_vertices[4 * index + 3].color = color;

        // give the particle a velocity
        float randomX               = ((float)rand() / RAND_MAX) * 10.0 - 5.0;
        float randomY               = ((float)rand() / RAND_MAX) * 10.0 - 5.0;
        m_particles[index].velocity = sf::Vector2f(randomX, randomY);

        // give the particle a lifespan
        m_particles[index].lifetime = 30 + rand() % 60;
    }

public:
    ParticleSystem(const sf::RenderWindow& window)
    {
        m_windowSize = window.getSize();
        resetParticles();
    };

    void resetParticles(size_t count = 1024, float size = 8.0)
    {
        m_particles = std::vector<Particle>(count);
        m_vertices  = sf::VertexArray(sf::Quads, count * 4);
        m_size      = size;

        for (size_t p = 0; p < m_particles.size(); p++)
        {
            resetParticle(p, true);
        }
    }

    void update()
    {
        for (size_t i = 0; i < m_particles.size(); i++)
        {
            if (m_particles[i].lifetime <= 0)
            {
                resetParticle(i);
            }
            m_vertices[4 * i + 0].position += m_particles[i].velocity;
            m_vertices[4 * i + 1].position += m_particles[i].velocity;
            m_vertices[4 * i + 2].position += m_particles[i].velocity;
            m_vertices[4 * i + 3].position += m_particles[i].velocity;

            m_particles[i].lifetime--;
        }
    }

    void draw(sf::RenderWindow& window) const
    {
        window.draw(m_vertices);
    }
};
