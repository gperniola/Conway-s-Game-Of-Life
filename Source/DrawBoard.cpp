#include "DrawBoard.h"

Drawboard::Drawboard(Config config)
:   CONFIG  (config)
{
    m_pixels.reserve(config.simWidth * config.simHeight * 4);
    makeGrid();
}

void Drawboard::addQuad(unsigned x, unsigned y, sf::Color& colour)
{
    sf::Vertex topLeft;
    sf::Vertex topRight;
    sf::Vertex bottomLeft;
    sf::Vertex bottomRight;

    float pixelX = x * CONFIG.quadSize;
    float pixelY = y * CONFIG.quadSize;

    topLeft     .position = {pixelX,                    pixelY};
    topRight    .position = {pixelX + CONFIG.quadSize,  pixelY};
    bottomLeft  .position = {pixelX,                    pixelY + CONFIG.quadSize};
    bottomRight .position = {pixelX + CONFIG.quadSize,  pixelY + CONFIG.quadSize};

    topLeft     .color = colour;
    topRight    .color = colour;
    bottomLeft  .color = colour;
    bottomRight .color = colour;

    m_pixels.push_back(topLeft);
    m_pixels.push_back(bottomLeft);
    m_pixels.push_back(bottomRight);
    m_pixels.push_back(topRight);
}

void Drawboard::setQuadColour(unsigned x, unsigned y, sf::Color& colour)
{
    auto index = getQuadIndex(x, y);

    for (int i = 0; i < 4; i++)
    {
        m_pixels[index + i].color = colour;
    }
}

void Drawboard::draw(sf::RenderWindow& window, bool drawGrid)
{
    window.draw(m_pixels.data(), m_pixels.size(), sf::Quads);
    if (drawGrid)
    {
        window.draw(m_grid.data(), m_grid.size(), sf::Lines);
    }
}


void Drawboard::makeGrid()
{
    for (unsigned x = 0; x < CONFIG.simWidth; x++)
    {
        sf::Vertex top;
        sf::Vertex bottom;

        float pX = x * CONFIG.quadSize;
        float pY = CONFIG.simHeight * CONFIG.quadSize;

        top     .position = {pX, 0};
        bottom  .position = {pX, pY};

        m_grid.push_back(top);
        m_grid.push_back(bottom);
    }

    for (unsigned y = 0; y < CONFIG.simHeight; y++)
    {
        sf::Vertex left;
        sf::Vertex right;

        float pX = CONFIG.simWidth * CONFIG.quadSize;
        float pY = y * CONFIG.quadSize;

        left    .position = {0,  pY};
        right   .position = {pX, pY};

        m_grid.push_back(left);
        m_grid.push_back(right);
    }
}

unsigned Drawboard::getQuadIndex(unsigned x, unsigned y)
{
    return (y * CONFIG.simWidth + x) * 4;
}

