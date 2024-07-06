#include "hero.hpp"

Hero::Hero() {
    m_gravity = 9.80f;
    jumpCount = 0;
    m_grounded = false;
}
//
Hero::~Hero() {

}
//
void Hero::Initialize(std::string &textureName) {
    //
    m_texture.loadFromFile(textureName);
    //Creat sprite and attach a Texture
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}
//
void Hero::Update(float& distance) {
    m_velocity -= m_speed * m_gravity * distance;
    m_position.y -= m_velocity * distance;
    m_sprite.setPosition(m_position);
    if (m_position.y >= 768 * 0.75) {
        m_position.y = 768 * 0.75;
        m_velocity = 0;
        m_grounded = true;
        jumpCount = 0;
    }
}
//
void Hero::Jump(float velocity) {
    if (jumpCount < 2) {
        jumpCount++;
        m_velocity = velocity;
        m_grounded = false;
    }
}
//
void Hero::Move(float distance) {
    if (GetDirection() == Direction::Right) {
        m_position.x += 100.0f * distance;
        m_sprite.move(100.0f * distance, 0);
        if (m_position.x >= 1024 - m_texture.getSize().x / 2) {
            m_position.x = 1024 - m_texture.getSize().x / 2;
        }
    } else {
        m_position.x -= 100.0f * distance;
        m_sprite.move(-100.0f * distance, 0);
        if (m_position.x  <= m_texture.getSize().x / 2)
        {
            m_position.x = m_texture.getSize().x / 2;
        }
    }
}
//
void Hero::SetDirection(Direction direction) {
    if (m_direction != direction) {
        m_direction = direction;
    }
}   
//
Direction Hero::GetDirection() {
    return m_direction;
}