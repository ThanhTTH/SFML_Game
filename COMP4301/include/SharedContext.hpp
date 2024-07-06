#ifndef SHARED_CONTEXT_HPP
#define SHARED_CONTEXT_HPP
#include "event_manager.hpp"
#include "../modules/graphic_components/window/window.hpp"


struct SharedContext
{
    SharedContext() 
    :m_wind(nullptr),
    m_event_manager(nullptr){}
    Window* m_wind;
    EventManager* m_event_manager;
};

#endif //SHARED_CONTEXT_HPP
