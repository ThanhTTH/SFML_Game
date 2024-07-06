#ifndef IDRAW_ABLE_HPP
#define IDRAW_ABLE_HPP
#include <SFML/Graphics.hpp>
#include <string>

class Idrawable 
{
public :
    virtual void Initialize(std::string &textureName) = 0;
    virtual void Update(float& distance) = 0;
    virtual ~Idrawable() {};
    
    sf::Sprite getSprite() {
        return m_sprite;
    }
    
    void setSprite(sf::Sprite &l_sprite) {
        m_sprite = l_sprite;
    }
    //
    sf::Vector2f getPosition() {
        return m_position;
    }
    void setPosition(sf::Vector2f &l_position){
        m_position = l_position;
        m_sprite.setPosition(m_position);
    }
    //
    void setSpeed(float &l_speed) {
        m_speed = l_speed;
    }
    //
    float getSpeed() {
        return m_speed;
    }
    sf::Texture getTexture() {
        return m_texture;
    }
protected :
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    float m_speed;
};


#endif //IDRAW_ABLE_HPP