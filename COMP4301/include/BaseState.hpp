#ifndef BASE_STATE_HPP
#define BASE_STATE_HPP
#include <SFML/Graphics.hpp>
class StateManager;

class BaseState 
{
public :
    BaseState(StateManager* l_stateManager) : m_stateManager(l_stateManager){}
    virtual ~BaseState(){}
    virtual void Oncreate() = 0;
    virtual void OnDestroy() = 0;
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    virtual void Update(const sf::Time& l_time) = 0;
    virtual void Draw() = 0;
	void SetTransparent(const bool& l_transparent){ m_transparent = l_transparent; }
	bool IsTransparent()const{ return m_transparent; }
	void SetTranscendent(const bool& l_transcendence){ m_transcendent = l_transcendence; }
	bool IsTranscendent()const{ return m_transcendent; }    
    StateManager* GetStateManager() {
        return m_stateManager;
    }
protected:
    StateManager* m_stateManager;
    bool m_transparent;
    bool m_transcendent;
};
#endif //BASE_STATE_HPP