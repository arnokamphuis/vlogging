#include "paddlegame.hpp"

void PaddleGame::solvePaddleBallCollision(const Paddle& mPaddle, Ball& mBall) noexcept {
    if(!isIntersecting(mPaddle, mBall)) return;

    mBall.velocity.y = -Ball::defVelocity;
    mBall.velocity.x =
        mBall.x() < mPaddle.x() ? -Ball::defVelocity : Ball::defVelocity;
}

void PaddleGame::solveBrickBallCollision(Brick& mBrick, Ball& mBall) noexcept {
    if(!isIntersecting(mBrick, mBall)) return;

    // Instead of immediately destroying the brick upon collision,
    // we decrease and check its required hits first.
    --mBrick.requiredHits;
    if(mBrick.requiredHits <= 0) mBrick.destroyed = true;

    float overlapLeft{mBall.right() - mBrick.left()};
    float overlapRight{mBrick.right() - mBall.left()};
    float overlapTop{mBall.bottom() - mBrick.top()};
    float overlapBottom{mBrick.bottom() - mBall.top()};

    bool ballFromLeft(std::abs(overlapLeft) < std::abs(overlapRight));
    bool ballFromTop(std::abs(overlapTop) < std::abs(overlapBottom));

    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

    if(std::abs(minOverlapX) < std::abs(minOverlapY))
        mBall.velocity.x =
            ballFromLeft ? -Ball::defVelocity : Ball::defVelocity;
    else
        mBall.velocity.y = ballFromTop ? -Ball::defVelocity : Ball::defVelocity;
}

void PaddleGame::handleInput() {
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) break;

    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
    //     if(!pausePressedLastFrame) {
    //         if(state == State::Paused)
    //             state = State::InProgress;
    //         else if(state == State::InProgress)
    //             state = State::Paused;
    //     }
    //     pausePressedLastFrame = true;
    // } else
    //     pausePressedLastFrame = false;

    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) restart();    
}

void PaddleGame::gameLogic() {
    // If there are no more balls on the screen, spawn a
    // new one and remove a life.
    if(manager.getAll<Ball>().empty()) {
        manager.create<Ball>(wndWidth / 2.f, wndHeight / 2.f);

        --remainingLives;
    }

    // If there are no more bricks on the screen,
    // the player won!
    if(manager.getAll<Brick>().empty()) state = State::Victory;

    // If the player has no more remaining lives,
    // it's game over!
    if(remainingLives <= 0) state = State::GameOver;

    manager.forEach<Ball>([this](auto& mBall) {
            manager.forEach<Brick>([&mBall](auto& mBrick) {
                    solveBrickBallCollision(mBrick, mBall);
                });
            manager.forEach<Paddle>([&mBall](auto& mPaddle) {
                    solvePaddleBallCollision(mPaddle, mBall);
                });
        });    
}

void PaddleGame::initializeGame() {
    // Let's remember to reset the remaining lives.
    remainingLives = 3;

    for(int iX{0}; iX < brkCountX; ++iX)
        for(int iY{0}; iY < brkCountY; ++iY) {
            float x{(iX + brkStartColumn) * (Brick::defWidth + brkSpacing)};
            float y{(iY + brkStartRow) * (Brick::defHeight + brkSpacing)};

            auto& brick(manager.create<Brick>(brkOffsetX + x, y));

            // Let's set the required hits for the bricks.
            brick.requiredHits = 1 + ((iX * iY) % 3);
        }

    manager.create<Ball>(wndWidth / 2.f, wndHeight / 2.f);
    manager.create<Paddle>(wndWidth / 2, wndHeight - 50);
}