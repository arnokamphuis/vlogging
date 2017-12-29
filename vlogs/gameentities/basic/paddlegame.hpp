#ifndef __PADDLEGAME_HPP__
#define __PADDLEGAME_HPP__

class PaddleGame : public Game {
protected:
    // Just some constants for the creation of the bricks
    //   This is specific game information, not general game architecture
    static constexpr int brkCountX{11}, brkCountY{4};
    static constexpr int brkStartColumn{1}, brkStartRow{2};
    static constexpr float brkSpacing{3.f}, brkOffsetX{22.f};

    // Let's also keep track of the remaning lives in the game class.
    int remainingLives{0};

    virtual void handleInput();
    virtual void gameLogic();
    virtual void initializeGame();
public:
};

#endif // __PADDLEGAME_HPP__