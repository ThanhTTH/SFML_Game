#include "event_manager.hpp"
#include "utilitis.hpp"

EventManager::EventManager() : m_currentState(StateType(0)), m_hasFocus(true) {
    LoadBindings();
}
//
EventManager::~EventManager() {
    for (auto &itr : m_bindings) {
        delete itr.second;
    }
}
//
bool EventManager::AddBinding(Binding* l_binding) {
    if (m_bindings.find(l_binding->m_name) != m_bindings.end()) {
        return false;
    }
    return m_bindings.emplace(l_binding->m_name, l_binding).second;
}
//
bool EventManager::RemoveBinding(std::string l_name) {
    auto itr = m_bindings.find(l_name);
    if (itr == m_bindings.end()) {
        return false;
    }
    delete itr->second;
    m_bindings.erase(itr);
    return true;
}
//
void EventManager::SetCurrentState(StateType l_state) {
    m_currentState = l_state;
}
//
void EventManager::SetFocus(const bool& l_focus) {
    m_hasFocus = l_focus;
}
//
void EventManager::LoadBindings() {
    std::string delimiter = ":";
    std::string assets_path = Utilitis::GetWorkingDirectory() + "Assets/key_config/";
    std::fstream binding_file;
    binding_file.open(assets_path + "keys.cfg");
    if (!binding_file.is_open()) {
        std::cout << "Fale to load binding file" <<std::endl;
    }
    std::string lines;
    while (std::getline(binding_file, lines)) {
        std::stringstream key_stream(lines);
        std::string callback_name;
        key_stream >> callback_name;
        Binding* bind = new Binding(callback_name);
        while (!key_stream.eof()) {
            std::string key_value;
            key_stream >> key_value;
            int start = 0;
            int end = key_value.find(delimiter);
            if (end == std::string::npos) {
                break;
            }
            EventType event_type = EventType(std::stoi(key_value.substr(start, end - start)));
            int code = std::stoi(key_value.substr(end + delimiter.length(), key_value.find(delimiter, end + delimiter.length())));
            EventInfo event_info;
            event_info.m_code = code;
            bind->BindEvent(event_type, event_info);
        }
        //
        if (!AddBinding(bind)) {
            delete bind;
        }
        bind = nullptr;
    }
    binding_file.close();
}
//
void EventManager::HandleEvent(sf::Event& l_event) {
    for(auto &bind_itr : m_bindings) {
        Binding* bind = bind_itr.second;
        for(auto &event_itr : bind->m_events) {
            EventType sfEvent = (EventType)l_event.type;
            
            if (event_itr.first != sfEvent) {
                continue;
            }
            // 
            if (event_itr.first == EventType::KeyDown || event_itr.first == EventType::KeyUp) {
                if (event_itr.second.m_code == l_event.key.code) {
                    bind->m_details.m_keyCode = event_itr.second.m_code;
                    (bind->m_count++);
                    break;
                }
            } else if (sfEvent == EventType::MButtonDown || sfEvent == EventType::MButtonUp) {
                if (event_itr.second.m_code == l_event.mouseButton.button) {
                    bind->m_details.m_mouse.x = l_event.mouseButton.x;
                    bind->m_details.m_mouse.y = l_event.mouseButton.y;
                    bind->m_details.m_keyCode = event_itr.second.m_code;
                    (bind->m_count++);
                    break;
                }
                
            } else {
                if (sfEvent == EventType::MouseWheel) {
                    bind->m_details.m_mouseWheelDelta = l_event.mouseWheel.delta;
                } else if (sfEvent == EventType::WindowResized) {
                    bind->m_details.m_size.x = l_event.size.width;
                    bind->m_details.m_size.y = l_event.size.height;
                } else if (sfEvent == EventType::TextEntered) {
                    bind->m_details.m_textEntered = l_event.text.unicode;
                }
                (bind->m_count++);
            }
        }
    }
}
//
void EventManager::Update() {
    for(auto &bind_itr : m_bindings) {
        Binding* bind = bind_itr.second;
        for (auto &event_itr : bind->m_events) {
            switch (event_itr.first) {
            case EventType::Keyboard :
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(event_itr.second.m_code))) {
                    bind->m_details.m_keyCode = event_itr.second.m_code;
                    ++(bind->m_count);
                }
                break;
            case EventType::Mouse :
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button(event_itr.second.m_code))) {
                    bind->m_details.m_keyCode = event_itr.second.m_code;
                    ++(bind->m_count);
                }
                break;
            case EventType::Joystick:    
            default:
                break;
            }
        }
        //
        if (bind->m_events.size() == bind->m_count) {
            auto state_callback = m_callbacks.find(m_currentState);
            // State Callback
            if (state_callback != m_callbacks.end()) {
                auto call_itr = state_callback->second.find(bind->m_name);
                if (call_itr != state_callback->second.end()) {
                    call_itr->second(&bind->m_details);
                }
            }
        }
        bind->m_count = 0;
        bind->m_details.Clear();
    }
}