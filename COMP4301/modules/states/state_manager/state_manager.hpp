#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP
#include <vector>
#include <unordered_map>
#include "state_mainmenu.hpp"
#include "state_game.hpp"
#include "SharedContext.hpp"
//
enum class StateType {
    MainMenu = 1,
    Game,
    Reversed
};
// State container
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;
// State Manager
class StateManager
{
public:
    StateManager(SharedContext* l_shared_context);
    ~StateManager();
    void Update(const sf::Time& l_time);
    void Draw();

    void ProcessRequirests();
    SharedContext* GetContext();
    bool HasState(const StateType& l_type);
    void SwitchTo(const StateType& l_type);
    void Remove(const StateType& l_type);
    template<class T>
    void RegisterState(const StateType& l_type) {
        m_stateFactory[l_type] = [this]() -> T* {
            return new T(this);
        };
    }
private:
    void CreateState(const StateType& l_type);
    void RemoveState(const StateType& l_type);
    // Data
    SharedContext * m_shared;
    StateContainer m_stateContainer;
    TypeContainer m_toRemove;
    StateFactory m_stateFactory;
};

#endif //STATE_MANAGER_HPP