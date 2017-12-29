#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include <vector>
#include <map>

#include "entity.hpp"

class Manager {
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::map<std::size_t, std::vector<Entity*>> groupedEntities;

public:
    template <typename T, typename... TArgs>
    T& create(TArgs&&... mArgs);

    void refresh();

    void clear();

    template <typename T>
    auto& getAll();

    template <typename T, typename TFunc>
    void forEach(const TFunc& mFunc);

    void update();
    void draw(/*sf::RenderWindow& mTarget*/);
};

#endif //__MANAGER_HPP__