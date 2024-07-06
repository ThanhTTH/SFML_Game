#include "background.hpp"


Background::Background() {
    m_speed = 0.0f;
}
//
Background::~Background() {

}
// 
void Background::Initialize(std::string &textureName) {
    m_texture.loadFromFile(textureName);
    m_sprite.setTexture(m_texture);
}
//
void Background::Update(float& distance) {
    //
}