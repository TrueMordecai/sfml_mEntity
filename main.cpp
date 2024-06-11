#include "src/mEntity.hpp"
#include "SFML/Window.hpp"

int main()
{

    // Create the different animations
    mEntity bullet("sprite.png", {22, 187, 17, 29}, 120, 6, LEFT_TO_RIGHT, "walk");
    bullet.addAnimationLoop("idle", 3, 500, {21, 68, 16, 23});
    bullet.changeAnimationLoop("idle");


    bullet.getSprite().scale({5, 5});
    bullet.getSprite().move({100, 100});

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    
    
    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // Once setup, you can switch freely beetween the animation
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            bullet.changeAnimationLoop("walk");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            bullet.changeAnimationLoop("idle");

        // this functiun must be called before the display
        bullet.update();

        // Display the sprite to the window
        bullet.display(window);
        
        window.display();
        window.clear(sf::Color(207,99,99));
    }

    return 0;
}