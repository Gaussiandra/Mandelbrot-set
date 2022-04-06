#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cassert>
#include "mandelbrot.hpp"

const unsigned int H = 600;
const unsigned int W = 800;
const unsigned int FPS_STRING_LEN = 50;
  
int main()
{
    sf::RenderWindow window(sf::VideoMode(W, H), "Mandelbrot set");
    window.setFramerateLimit(60);

    sf::Font font;
    assert(font.loadFromFile("Lato-Black.ttf"));
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);

    char fpsString[FPS_STRING_LEN] = {};
    float fps = 0;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime = sf::Time::Zero;

    sf::Texture texture;
    texture.create(W, H);
    sf::Sprite sprite(texture);

    mandelbrot_t *mandelbrotObj = initMandelbrotGen(W, H); 

    while (window.isOpen())
    { 
        sf::Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }   

        float upscaleFactor = 10;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            upscaleFactor = 100;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            mandelbrotObj->ROI_X -= mandelbrotObj->dx * upscaleFactor;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            mandelbrotObj->ROI_X += mandelbrotObj->dx * upscaleFactor;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            mandelbrotObj->ROI_Y += mandelbrotObj->dy * upscaleFactor;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            mandelbrotObj->ROI_Y -= mandelbrotObj->dy * upscaleFactor;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            mandelbrotObj->scale += 0.01 * upscaleFactor;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            mandelbrotObj->scale -= 0.01 * upscaleFactor;
        }
        
        calcMandelbrotSet(mandelbrotObj);

        texture.update(mandelbrotObj->data);

        window.clear();

        window.draw(sprite);

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        sprintf(fpsString, "fps = %.3f", fps);
        fpsText.setString(fpsString);
        previousTime = currentTime;
        window.draw(fpsText);

        window.display();
    }

    deleteMandelbrotObj(mandelbrotObj);

    return 0;
}