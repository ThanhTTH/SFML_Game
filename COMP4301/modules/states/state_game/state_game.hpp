#ifndef STATE_GAME_HPP
#define STATE_GAME_HPP
#include <vector>
#include "utilitis.hpp"
#include "BaseState.hpp"
#include "background.hpp"
#include "sky.hpp"
#include "enemy.hpp"
#include "rocket.hpp"
#include "hero.hpp"
#include "state_manager.hpp"
#include "event_manager.hpp"

class StateGame : public BaseState 
{
public:
    StateGame(StateManager* l_stateManager);
    ~StateGame();
    void Oncreate() override;
    void OnDestroy();
    void Activate();
    void Deactivate();
    void Update(const sf::Time& l_time);
    void Draw();
    void MouseClick(EventDetails* l_event_details);
    void KeyLeftPress(EventDetails* l_event_details);
    void KeyRightPress(EventDetails* l_event_details);
    void KeyUpPress(EventDetails* l_event_details);
    void KeyLeftUp(EventDetails* l_event_details);
    void KeyRightUp(EventDetails* l_event_details);
    void KeyEXIT(EventDetails* l_event_details);
private:
    bool CollisionChecking(const sf::Sprite &object, const sf::Sprite &distance);
    void EnemyGender();
    void RocketGender();
    std::vector<Enemy*> m_enemies;
    std::vector<Rocket*> m_rockets;
    Hero m_hero;
    Background m_background;
    Sky m_sky;
    float m_currentTime;
    float m_prevTime;
    bool m_moving_state;
    bool m_isStop;
    sf::Font m_font;
	sf::Text m_text;
    std::uint32_t m_score;
    std::string m_working_direction;
};

#endif //STATE_GAME_HPP