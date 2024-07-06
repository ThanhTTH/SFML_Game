#ifndef STATE_MAIN_MENU_HPP
#define STATE_MAIN_MENU_HPP
#include <array>
#include "BaseState.hpp"
#include "event_manager.hpp"
#include "background.hpp"

class StateMainMenu : public BaseState
{
public: 
    StateMainMenu(StateManager* l_stateManager);
    ~StateMainMenu();
    void Oncreate() override;
    void OnDestroy();
    void Activate();
    void Deactivate();
    void Update(const sf::Time& l_time);
    void Draw();
    void MouseClick(EventDetails* l_event_details);
private:
    sf::Font m_font;
    sf::Text m_text;
    sf::Vector2f m_button_size;
    sf::Vector2f m_button_pos;
    unsigned int m_button_padding;
    Background m_background;
    std::array<sf::RectangleShape, 2> m_rects;
    std::array<sf::Text, 2> m_labels;
};

#endif //STATE_MAIN_MENU_HPP