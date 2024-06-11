#include "mEntity.hpp"
#include <iostream> /// REMOVE !!

mEntityAnimation::mEntityAnimation(std::string name, int nbFrame, int64_t milli, sf::IntRect rect)
{
    _milliseconds = milli;
    _nbFrame = nbFrame;
    _name = name;
    _rect = rect;
}
mEntityAnimation::~mEntityAnimation() {}
std::string mEntityAnimation::name() {return (_name);}
sf::IntRect mEntityAnimation::rect() {return (_rect);}
int mEntityAnimation::nbFrame() {return (_nbFrame);}
int64_t mEntityAnimation::milliseconds() {return (_milliseconds);}

mEntity::mEntity(sf::String path, sf::IntRect rect, int64_t milliseconds, int nbFrame, direction_e dir/* = LEFT_TO_RIGHT*/, std::string namee /* = "DEFAULT"*/)
{
    _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(rect);
    _rect = rect;
    _clock.restart();
    _timingMilliseconds = milliseconds;
    _nbFrame = nbFrame;
    _dir = dir;
    _name = namee;
    if (namee != "DEFAULT" && namee != "") {
        mEntityAnimation toSave(namee, nbFrame, milliseconds, rect);
        _saved.push_back(toSave);
    }
    _checkedFrame = -1;
}

mEntity::mEntity(sf::Texture texture, sf::IntRect rect, int64_t milliseconds, int nbFrame, direction_e dir, std::string name)
{
    _texture = texture;
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(rect);
    _rect = rect;
    _clock.restart();
    _timingMilliseconds = milliseconds;
    _nbFrame = nbFrame;
    _dir = dir;
    _name = name;
    if (name != "DEFAULT" && name != "") {
        mEntityAnimation toSave(name, nbFrame, milliseconds, rect);
        _saved.push_back(toSave);
    }
    _checkedFrame = -1;
}

mEntity::mEntity(sf::Texture texture, sf::IntRect rect)
{
    _texture = texture;
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(rect);
    _rect = rect;
    _clock.restart();
    _timingMilliseconds = 100;
    _nbFrame = 1;
    _dir = LEFT_TO_RIGHT;
    _name = "";
    _checkedFrame = -1;
}

mEntity::mEntity(sf::String path, sf::IntRect rect)
{
    
    _texture.loadFromFile(path);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(rect);
    _texture.setRepeated(true);
    _rect = rect;
    _clock.restart();
    _timingMilliseconds = 100;
    _nbFrame = 1;
    _dir = LEFT_TO_RIGHT;
    _name = "";
    _checkedFrame = -1;
}


/// Problem : last frame is slightly longer.
int mEntity::update()
{
    sf::Time curTime = _clock.getElapsedTime();
    
    if (curTime.asMilliseconds() / _timingMilliseconds > _nbFrame - 1) {
        if (_queue.size() > 1) {
            this->changeAnimationLoop(_queue[0]);
            _queue.erase(_queue.begin());
            return (update());
        }
        _clock.restart();
        _checkedFrame = -1;
        return (_nbFrame);
    }
    if (_dir == LEFT_TO_RIGHT)
        _sprite.setTextureRect(sf::IntRect(_rect.width * (curTime.asMilliseconds() / _timingMilliseconds) + _rect.left, _rect.top, _rect.width, _rect.height));    
    else if (_dir == TOP_TO_BOTTOM)
        _sprite.setTextureRect(sf::IntRect(_rect.left, _rect.width * (curTime.asMilliseconds() / _timingMilliseconds) + _rect.top, _rect.width, _rect.height));    
    if (_checkedFrame != curTime.asMilliseconds() / _timingMilliseconds)
        _checkedFrame = -1;
    return (curTime.asMilliseconds() / _timingMilliseconds);
}

void mEntity::addAnimationLoop(std::string name, int nbFrame, int64_t milli, sf::IntRect rect)
{
    _saved.push_back(mEntityAnimation(name, nbFrame, milli, rect));
}

mEntity::~mEntity()
{}

void mEntity::changeAnimationLoop(sf::IntRect rect, int64_t milliseconds, int nbFrame, std::string name/* = "DEFAULT"*/)
{
    _rect = rect;
    _timingMilliseconds = milliseconds;
    _nbFrame = nbFrame;
    _name = name;
    if (name != "DEFAULT" && name != "")
        _saved.push_back(mEntityAnimation(name, nbFrame, milliseconds, rect));
    _clock.restart();
}

void mEntity::changeAnimationLoop(std::string name)
{
    if (name == _name)
        return;
    for (auto &i : _saved) {
        if (i.name() == name && _name != name) {
            _rect = i.rect();
            _timingMilliseconds = i.milliseconds();
            _nbFrame = i.nbFrame();
            _name = i.name();
            _clock.restart();
            _sprite.setTextureRect(_rect);
        }
    }
}

void mEntity::display(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

bool mEntity::intersect(sf::Vector2f p)
{
    sf::IntRect r = this->getHitbox();
    if (p.x >= r.left && p.x <= r.left + r.width) {
        if (p.y >= r.top && p.y <= r.top + r.height) {
            return (true);
        }
    }
    return (false);
}

bool mEntity::intersect(sf::Vector2i p)
{
    sf::IntRect r = this->getHitbox();

    if (p.x >= r.left && p.x <= r.left + r.width) {
        if (p.y >= r.top && p.y <= r.top + r.height) {
            return (true);
        }
    }
    return (false);
}

bool mEntity::intersect(sf::Vector2u p)
{
    sf::IntRect r = this->getHitbox();

    if (r.left < 0 || r.top < 0 || r.width < 0 || r.height < 0)
        return (false); // Shouldn't be negative for better comparison.
    if (p.x >= (unsigned int)r.left && p.x <= (unsigned int)r.left + (unsigned int)r.width) {
        if (p.y >= (unsigned int)r.top && p.y <= (unsigned int)r.top + (unsigned int)r.height) {
            return (true);
        }
    }
    return (false);
}

bool mEntity::intersect(sf::IntRect rect)
{
    if (this->intersect(sf::Vector2i{rect.left, rect.top}))
        return true;
    if (this->intersect(sf::Vector2i{rect.left + rect.width, rect.height}))
        return true;
    if (this->intersect(sf::Vector2i{rect.width, rect.top + rect.height}))
        return true;
    if (this->intersect(sf::Vector2i{rect.left + rect.width, rect.top + rect.height}))
        return true;
    return (false);
}

void mEntity::addToQueue(std::string s)
{
    _queue.push_back(s);
}

sf::IntRect mEntity::getHitbox()
{
    sf::IntRect result;
    sf::Vector2f sc = _sprite.getScale();
    sf::IntRect rect = this->_rect;
    sf::Vector2f pos = _sprite.getPosition();
    sf::Vector2f origin = _sprite.getOrigin();
    
    if (sc.x == 0)
        sc.x = 1;
    if (sc.y == 0)
        sc.y = 1;
    if (sc.y < 0) {
        result.height = rect.height * std::abs(sc.y);
        result.top = pos.y - (origin.y * sc.y) - rect.height * std::abs(sc.y);
    } else {
        result.height = rect.height * std::abs(sc.y);
        result.top = pos.y - (origin.y * sc.y);
    }
    if (sc.x < 0) {
        result.width = rect.width * std::abs(sc.x);
        result.left = pos.x - (origin.x * sc.x) - rect.width * std::abs(sc.x);
    } else {
        result.width = rect.width * std::abs(sc.x);
        result.left = pos.x - (origin.x * sc.x);
    }
    return (result);
}

sf::Sprite& mEntity::getSprite()
{
    return _sprite;
}

std::string mEntity::getName()
{
    return (_name);
}

int mEntity::getNbFrame()
{
    return (_nbFrame);
}

int64_t mEntity::getMilliseconds()
{
    return _timingMilliseconds;
}

sf::Clock mEntity::getClock()
{
    return _clock;
}

sf::Texture mEntity::getTexture()
{
    return _texture;
}

void mEntity::synchronize(mEntity toSynchronizeWith)
{
    this->_clock = toSynchronizeWith.getClock();
}

bool mEntity::isActualFrame(int frame)
{
    if (_checkedFrame != -1)
        return false;
    int i = update();
    if (frame == i) {
        _checkedFrame = i;
        return true;
    }
    return false;
}

void mEntity::setTimingMilliseconds(int64_t milli)
{
    _timingMilliseconds = milli;
}