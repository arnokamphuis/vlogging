#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

class Entity {
public:
    bool destroyed{false};

    virtual ~Entity() {}
    virtual void update() {}
    virtual void draw(/*sf::RenderWindow& mTarget*/) {}
};

#endif // __ENTITY_HPP__