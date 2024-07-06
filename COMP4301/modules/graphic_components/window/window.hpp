#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "IDrawable.hpp"
#include "event_manager.hpp"

class Window
{
public:
    Window(const std::string& window_name, const sf::Vector2u &window_sie);
    Window();
    ~Window();
    void BeginDraw();
    void EndDraw();
    void Update();
    bool isDone();
    void Close(EventDetails* l_details = nullptr);
    sf::Vector2u GetWindowSie();
    sf::RenderWindow* GetRenderWindow();
    EventManager* GetEventManager();
private:
    void Create();
    void Setup(const std::string& window_name, const sf::Vector2u &window_sie);
    void Destroy();
    std::string m_windowTitle;
    sf::RenderWindow m_window;
    EventManager m_event_manager;
    sf::Vector2u m_windowSize;
    bool m_isDone;
    bool m_isFullscreen;
	bool m_isFocused;
};


#endif //WINDOW_HPP 