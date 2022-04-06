#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "mandelbrot.hpp"

const unsigned int H = 600;
const unsigned int W = 800;
  
int main()
{
    sf::RenderWindow window(sf::VideoMode(W, H), "SFML works!");
    window.setFramerateLimit(60);

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
        window.display();
    }

    deleteMandelbrotObj(mandelbrotObj);

    return 0;
}