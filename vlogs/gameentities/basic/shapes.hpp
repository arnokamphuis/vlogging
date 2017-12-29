#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__

struct Rectangle
{
    sf::RectangleShape shape;

    float x() const noexcept { return shape.getPosition().x; }
    float y() const noexcept { return shape.getPosition().y; }
    float width() const noexcept { return shape.getSize().x; }
    float height() const noexcept { return shape.getSize().y; }
    float left() const noexcept { return x() - width() / 2.f; }
    float right() const noexcept { return x() + width() / 2.f; }
    float top() const noexcept { return y() - height() / 2.f; }
    float bottom() const noexcept { return y() + height() / 2.f; }
};

struct Circle
{
    sf::CircleShape shape;

    float x() const noexcept { return shape.getPosition().x; }
    float y() const noexcept { return shape.getPosition().y; }
    float radius() const noexcept { return shape.getRadius(); }
    float left() const noexcept { return x() - radius(); }
    float right() const noexcept { return x() + radius(); }
    float top() const noexcept { return y() - radius(); }
    float bottom() const noexcept { return y() + radius(); }
};

#endif // __SHAPES_HPP__