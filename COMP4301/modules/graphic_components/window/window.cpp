#include "window.hpp"


Window::Window(const std::string& window_name, const sf::Vector2u &window_sie) {
    Setup(window_name, window_sie);
}
//
Window::~Window() {
    Destroy();
}
//
void Window::BeginDraw() {
    m_window.clear(sf::Color::Blue);
}
//
void Window::EndDraw() {
    m_window.display();
}
//
void Window::Update() {
    sf::Event event;
    if (m_window.pollEvent(event)) {
        if (event.type == sf::Event::LostFocus) {
            m_isFocused = false;
            m_event_manager.SetFocus(false);
        } else if (event.type == sf::Event::GainedFocus) {
            m_isFocused = true;
            m_event_manager.SetFocus(true);
        }
        m_event_manager.HandleEvent(event);
    }
    m_event_manager.Update();
}
//
bool Window::isDone() {
    return m_isDone;
}
// 
sf::Vector2u Window::GetWindowSie() {
    return m_windowSize;
}
// 
void Window::Create() {
    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;
    m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y, 32), m_windowTitle, style);
    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(60);

}
// 
void Window::Setup(const std::string& window_name, const sf::Vector2u &window_sie){
    m_windowTitle = window_name;
    m_windowSize = window_sie;
    m_isDone = false;
    Create();
}
//
void Window::Destroy() {
    m_isDone = true;
    m_window.close();
}
// 
Window::Window() {
    std::string title = "Game";
    sf::Vector2u viewSite(1024, 768);
    Setup(title, viewSite);
}
//
sf::RenderWindow* Window::GetRenderWindow() {
    return &m_window;
}
//
EventManager* Window::GetEventManager() {
    return &m_event_manager;
}
//
void Window::Close(EventDetails* l_details) {
    m_isDone = true;
}