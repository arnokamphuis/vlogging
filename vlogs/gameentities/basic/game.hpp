#ifndef __GAME_HPP__
#define __GAME_HPP__

template <typename T1, typename T2>
bool isIntersecting(const T1& mA, const T2& mB) noexcept
{
    return mA.right() >= mB.left() && mA.left() <= mB.right() &&
           mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

class Game {
protected:

    enum class State {
        Paused,
        GameOver,
        InProgress,
        Victory
    };

    // The render-window based on SFML, not needed in this example
    //sf::RenderWindow window{{wndWidth, wndHeight}, "<name of the game>"};

    // The game manager, handles the creation and deletion of game objects/entities
    //   Also responsible for deciding which entities to draw.
    Manager manager;

    // The state of the game. We start in game over, and restart the game at the beginning
    State state{State::GameOver};

    // Keeping track of the pause key....
    bool pausePressedLastFrame{false};

    virtual void handleInput() = 0;
    virtual void gameLogic() = 0;
    virtual void initializeGame() = 0;

public:

    virtual Game();
    void restart();
    void run();

};

#endif // __GAME_HPP__