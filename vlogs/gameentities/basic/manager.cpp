#include "manager.hpp"
#include <forward>
#include <memory>
#include <utility>
#include <typeinfo>

template <typename T, typename... TArgs>
T& Manager::create(TArgs&&... mArgs) {
    static_assert(std::is_base_of<Entity, T>::value,
        "`T` must be derived from `Entity`");

    auto uPtr(std::make_unique<T>(std::forward<TArgs>(mArgs)...));
    auto ptr(uPtr.get());
    groupedEntities[typeid(T).hash_code()].emplace_back(ptr);
    entities.emplace_back(std::move(uPtr));

    return *ptr;
}

void Manager::refresh() {
    for(auto& pair : groupedEntities) {
        auto& vector(pair.second);

        vector.erase(std::remove_if(std::begin(vector), std::end(vector),
                            [](auto mPtr) { return mPtr->destroyed; }),
            std::end(vector));
    }

    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                        [](const auto& mUPtr) { return mUPtr->destroyed; }),
        std::end(entities));
}

void Manager::clear() {
    groupedEntities.clear();
    entities.clear();
}

template <typename T>
auto& Manager::getAll() {
    return groupedEntities[typeid(T).hash_code()];
}

template <typename T, typename TFunc>
void Manager::forEach(const TFunc& mFunc) {
    for(auto ptr : getAll<T>()) mFunc(*reinterpret_cast<T*>(ptr));
}

void Manager::update() {
    for(auto& e : entities) e->update();
}

void Manager::draw(sf::RenderWindow& mTarget) {
    for(auto& e : entities) e->draw(mTarget);
}
