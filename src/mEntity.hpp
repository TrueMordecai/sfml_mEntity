// This belongs to mathias.blanchard01@gmail.com
// Notify me if you are using it, if your nice 


#ifndef mEntity_HPP_
#define mEntity_HPP_
#include "SFML/Graphics.hpp"
#include <memory>
#include <iostream>

enum direction_e {
    LEFT_TO_RIGHT = 0,
    TOP_TO_BOTTOM,
};

class mEntityAnimation {
    public:
        mEntityAnimation(std::string _name, int nbFrame, int64_t milli, sf::IntRect rect);
        ~mEntityAnimation();
        std::string name();
        int nbFrame();
        int64_t milliseconds();
        sf::IntRect rect();

    private:
        std::string _name;
        int _nbFrame;
        int64_t _milliseconds;
        sf::IntRect _rect;
};


class mEntity {
    public:
    // Create a mEntity from a path
    mEntity(sf::String path, sf::IntRect rect, int64_t milliseconds, int nbFrame, direction_e dir = LEFT_TO_RIGHT, std::string NAME = "");
    
    // Create a mEntity from a already loaded sf::Texture
    mEntity(sf::Texture texture, sf::IntRect rect, int64_t milliseconds, int nbFrame, direction_e dir = LEFT_TO_RIGHT, std::string NAME = "");

    // Create a small mEntity from a path, no animation.
    mEntity(sf::String path, sf::IntRect rect);
    
    // Create a small mEntity from a already loaded texture, no animation.
    mEntity(sf::Texture texture, sf::IntRect rect);

    /// Change animation loop, if name keep to default it doesn't save
    void changeAnimationLoop(sf::IntRect rect, int64_t milliseconds, int nbFrame, std::string name = "DEFAULT");
    
    /// Change animation loop to a pre register one
    void changeAnimationLoop(std::string name);
    
    /// Return the current frame
    int update();

    /// Add a loop to _saved
    void addAnimationLoop(std::string name, int nbFrame, int64_t milli, sf::IntRect rect);

    /// Display sprite on window
    void display(sf::RenderWindow &window);
    
    /// Check if point is in hitbox, don't handle rotation
    bool intersect(sf::Vector2f point);
    bool intersect(sf::Vector2i point);
    bool intersect(sf::Vector2u point);
    bool intersect(sf::IntRect rect);


    /// Add preregister animation in the wait list
    void addToQueue(std::string animation);

    /// Return hitbox, useful for debugging
    sf::IntRect getHitbox();
    
    /// Return reference to a sprite 
    sf::Sprite &getSprite();
    
    /// Return name of the playing animation
    std::string getName();
    
    /// Get number of frame
    int getNbFrame();

    /// Get Milliseconds
    int64_t getMilliseconds();

    /// Get clock
    sf::Clock getClock();

    /// GetTexture
    sf::Texture getTexture();

    /// Synchronize two animation
    void synchronize(mEntity toSynchronize);

    void setTimingMilliseconds(int64_t milli);
    bool isActualFrame(int _frame);

    void Destroy() { delete this; }
    ~mEntity();
private:
    std::vector<std::string> _queue;
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Clock _clock;
    direction_e _dir;
    int _checkedFrame;


    int64_t _timingMilliseconds;
    sf::IntRect _rect;
    int _nbFrame;
    std::string _name;
    std::vector<mEntityAnimation> _saved;
};


#endif /* !PARALLAX_HPP_ */