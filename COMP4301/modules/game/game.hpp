#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"
#include "event_manager.hpp"
#include "state_manager.hpp"
#include "SharedContext.hpp"
#include <iostream>

class Game 
{

public:
    Game();
    ~Game();
    void Update();
    void Render();
    void LateUpdate();
    sf::Time GetElapsed();
    Window* GetWindow();
private:
    SharedContext m_context;
    Window m_window;
    StateManager m_StateManager;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    void RestartClock();
};

#endif //GAME_HPP