
Game::Game() {
    // set the framerate limit in SFML (not needed in this example)1
    // window.setFramerateLimit(60);
}

void Game::restart() {

    // set the state to "Paused"
    state = State::Paused;

    // clear the manager from any existing entites
    manager.clear();

    // do game specific initialization
    initializeGame();
}

void Game::run() {
    while(true) {
        // clear the window with black
        //   not necessary in this example because we don't use SFML
        // window.clear(sf::Color::Black);

        // first handle the input, regardless of the state 
        //      (otherwise you could not get out of the pause state)
        handleInput();

        if(state == State::InProgress) {
            // update the manager, which means updating all the entities
            manager.update();

            // check things that are game specific
            gameLogic();

            // refresh the manager, i.e. remove entities which need to be deleted and such
            manager.refresh();

            // finally draw the entities
            manager.draw(/* window */);
        }

        // display the windows, needed in SFML
        // window.display();
    }
}