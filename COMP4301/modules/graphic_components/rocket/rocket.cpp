#include "rocket.hpp"

Rocket::Rocket() {
    m_speed = 0.0f;
}
//
Rocket::~Rocket() {

}
//
void Rocket::Initialize(std::string &textureName) {
    m_texture.loadFromFile(textureName);
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}

void Rocket::Update(float& distance) {
    m_sprite.move(m_speed * distance, 0);
}