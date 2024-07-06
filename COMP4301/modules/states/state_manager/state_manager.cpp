#include "state_manager.hpp"

StateManager::StateManager(SharedContext* l_shared_context) 
:m_shared(l_shared_context){
    RegisterState<StateMainMenu>(StateType::MainMenu);
    RegisterState<StateGame>(StateType::Game);
}
//
StateManager::~StateManager() {
    for(auto &itr : m_stateContainer){
        itr.second->OnDestroy();
        delete itr.second;
    }
}
//
void StateManager::Update(const sf::Time& l_time) {
    //
    if (m_stateContainer.empty()) {
        return ;
    }
    //
    if (m_stateContainer.back().second->IsTransparent() && 
        m_stateContainer.size() > 1 ) {
        auto itr = m_stateContainer.end();
        while (itr != m_stateContainer.begin()) {
            if (itr != m_stateContainer.end()) {
                if (!itr->second->IsTransparent()) {
                    break;
                }
            }
            --itr;
        }
        for(; itr != m_stateContainer.end(); ++itr) {
            itr->second->Update(l_time);
        }
        
    } else {
        m_stateContainer.back().second->Update(l_time);
    }

}
//
void StateManager::Draw() {
    //TODO : Draw each available state
    if (m_stateContainer.empty()) {
        return;
    }
    if (m_stateContainer.back().second->IsTransparent() && m_stateContainer.size() > 1) {
        auto itr = m_stateContainer.end();
        while (itr != m_stateContainer.begin()) {
            if (itr != m_stateContainer.end()) {
                if (!itr->second->IsTransparent()) {
                    break;
                }
            }
            --itr;
        }
        for (; itr != m_stateContainer.end(); ++itr) {
            itr->second->Draw();
        }
    } else {
        m_stateContainer.back().second->Draw();
    }
}
//
SharedContext* StateManager::GetContext() { 
    return m_shared;
}
//
bool StateManager::HasState(const StateType& l_type) {
    for(auto itr = m_stateContainer.begin(); itr != m_stateContainer.end(); ++itr) {
        if(itr->first == l_type) {
            auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), l_type);
            if (removed == m_toRemove.end()) {
                return true;
            }
            return false;
        }
    }
    return false;
}
//
void StateManager::ProcessRequirests() {
    while (m_toRemove.begin() != m_toRemove.end()) {
        RemoveState(*m_toRemove.begin());
        m_toRemove.erase(m_toRemove.begin());
    }
}
//
void StateManager::SwitchTo(const StateType& l_type) {
    m_shared->m_event_manager->SetCurrentState(l_type);
    for(auto itr = m_stateContainer.begin(); itr != m_stateContainer.end(); ++itr ) {
        if (itr->first == l_type) {
            m_stateContainer.back().second->Deactivate();
            StateType tmp_type = itr->first;
            BaseState* tmp_state = itr->second;
            m_stateContainer.erase(itr);
            m_stateContainer.emplace_back(tmp_type, tmp_state);
            tmp_state->Activate();
            return;
        }
    }
    //Deactive current state
    if (!m_stateContainer.empty()) {
        m_stateContainer.back().second->Deactivate();
    }
    // Create new State if state which switch to not available 
    CreateState(l_type);
    m_stateContainer.back().second->Activate();
}
//
void StateManager::Remove(const StateType& l_type) {
    m_toRemove.push_back(l_type);
}
//
void StateManager::CreateState(const StateType& l_type) {
    auto new_state = m_stateFactory.find(l_type);
    if(new_state == m_stateFactory.end()) {
        return;
    }
    BaseState* state = new_state->second();
    m_stateContainer.emplace_back(l_type, state);
    state->Oncreate();
}
//
void StateManager::RemoveState(const StateType& l_type) {
    for(auto itr = m_stateContainer.begin(); itr != m_stateContainer.end(); ++itr) {
        if (itr->first == l_type) {
            itr->second->OnDestroy();
            delete itr->second;
            m_stateContainer.erase(itr);
            return;
        }
    }   
}