#include <string>
#include "state_mainmenu.hpp"
#include "state_manager.hpp"
#include "utilitis.hpp"

StateMainMenu::StateMainMenu(StateManager* l_stateManager) 
    : BaseState(l_stateManager) {

}
//
StateMainMenu::~StateMainMenu(){

}
//
void StateMainMenu::Oncreate() {
    SetTransparent(true);
    std::string font_path = Utilitis::GetWorkingDirectory() + "Assets/fonts/arial.ttf";
    std::string background_path = Utilitis::GetWorkingDirectory() + "Assets/graphics/background.png";
    m_background.Initialize(background_path);
    m_font.loadFromFile(font_path);
    m_text.setFont(m_font);
    m_text.setString(sf::String("MAIN MENU"));
    m_text.setCharacterSize(18);
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_text.setPosition(512, 100);
    //
    m_button_size = sf::Vector2f(300.0f, 32.0f);
    m_button_pos = sf::Vector2f(512, 200);
    m_button_padding = 4; //4px
    //
    std::array<std::string, 2> str;
    str[0] = "PLAY";
    str[1] = "EXIT";
    
    for(int i = 0; i < str.size(); i++) {
        //Config Rects
        sf::Vector2f buttonPosition(m_button_pos.x, m_button_pos.y + (i* (m_button_size.y + m_button_padding)));
        m_rects[i].setSize(m_button_size);
        m_rects[i].setFillColor(sf::Color::Red);
        //Set position
        m_rects[i].setOrigin(m_button_size.x / 2.0f, m_button_size.y / 2.0f);
        m_rects[i].setPosition(buttonPosition);
        
        //Config labels
        m_labels[i].setFont(m_font);
        m_labels[i].setString(sf::String(str[i]));
        m_labels[i].setCharacterSize(12);
        
        //Rect labels
        sf::FloatRect label_rect = m_labels[i].getLocalBounds();
        m_labels[i].setOrigin(label_rect.left + label_rect.width / 2.0f, label_rect.top + label_rect.height / 2.0f);
        m_labels[i].setPosition(buttonPosition);
    }
    EventManager* event_manager = m_stateManager->GetContext()->m_event_manager;
    event_manager->AddCallback(StateType::MainMenu, "Mouse_Left", &StateMainMenu::MouseClick, this);
}
//
void StateMainMenu::OnDestroy() {
    EventManager* event_manager = m_stateManager->GetContext()->m_event_manager;
    event_manager->RemoveCallback(StateType::MainMenu, "Mouse_Left");
}
//
void StateMainMenu::Activate() {
    if (m_stateManager->HasState(StateType::Game) &&
        m_labels[0].getString() == "PLAY") {
        m_labels[0].setString(sf::String("RESUME"));
        sf::FloatRect rect = m_labels[0].getLocalBounds();
        m_labels[0].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    }
}
//
void StateMainMenu::Draw() {
    sf::RenderWindow* window = m_stateManager->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_background.getSprite());
    for(int i = 0; i < m_rects.size(); i++) {
        window->draw(m_rects[i]);
        window->draw(m_labels[i]);
    }
}
//
void StateMainMenu::MouseClick(EventDetails* l_event_details) {
    sf::Vector2i mouse_pos = l_event_details->m_mouse;
    float hafl_x = m_button_size.x / 2.0f;
    float hafl_y = m_button_size.y / 2.0f;
    for(int i = 0; i < m_rects.size(); i++) {
        if ((mouse_pos.x >= m_rects[i].getPosition().x - hafl_x) &&
            (mouse_pos.x <= m_rects[i].getPosition().x + hafl_x) &&
            (mouse_pos.y >= m_rects[i].getPosition().y - hafl_y) &&
            (mouse_pos.y <= m_rects[i].getPosition().y + hafl_y)) {
            if (i == 0) {
                m_stateManager->SwitchTo(StateType::Game);
            } else if (i == 1) {
                m_stateManager->GetContext()->m_wind->Close();
            }
        }
    }
}
//
void StateMainMenu::Update(const sf::Time& l_time) {}
void StateMainMenu::Deactivate() {}