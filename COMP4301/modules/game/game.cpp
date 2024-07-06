#include "game.hpp"

Game::Game() 
    : m_window("Games", sf::Vector2u(1024, 768)), 
    m_StateManager(&m_context) {
    
    m_clock.restart();
    srand(time(nullptr));
    m_context.m_wind = &m_window;
    m_context.m_event_manager = m_window.GetEventManager();
    m_StateManager.RegisterState<StateMainMenu>(StateType::MainMenu);
    m_StateManager.RegisterState<StateGame>(StateType::Game);
    m_StateManager.SwitchTo(StateType::MainMenu);
}
//
Game::~Game() {}
//
sf::Time Game::GetElapsed() {
    return m_clock.getElapsedTime();
}
//
void Game::RestartClock() {
    m_elapsed = m_clock.restart();
}
//
Window* Game::GetWindow() {
    return &m_window;
}
//
void Game::Update() {
    m_window.Update();
    m_StateManager.Update(m_elapsed);
}
//
void Game::Render() {
    m_window.BeginDraw();
    //
    m_StateManager.Draw();
    m_window.EndDraw();
}
//
void Game::LateUpdate() {
    m_StateManager.ProcessRequirests();
    RestartClock();
    sf::sleep(sf::milliseconds(10));
}