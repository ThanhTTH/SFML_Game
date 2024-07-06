#include "sky.hpp"


Sky::Sky()  {
    m_speed = 0.0f;
}
//
Sky::~Sky() {

}
// 
void Sky::Initialize(std::string &textureName) {
    m_texture.loadFromFile(textureName);
    m_sprite.setTexture(m_texture);
}
//
void Sky::Update(float& distance) {
    // m_sprite.move(m_speed * distance, 0);
}