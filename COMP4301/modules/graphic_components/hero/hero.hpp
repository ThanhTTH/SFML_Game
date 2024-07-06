#ifndef HERO_HPP
#define HERO_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "IDrawable.hpp"

enum class Direction: std::uint8_t {
    Left = 0,
    Right,
};

class Hero : public Idrawable
{
private:
    /* data */
    int jumpCount;
    float m_velocity;
    float m_gravity ;
    bool m_grounded;
    Direction m_direction;
public:
    Hero();
    ~Hero();
    void Initialize(std::string &textureName) override;
    void Update(float& distance);
    void Jump(float velocity);
    void Move(float distance);
    void SetDirection(Direction direction);
    Direction GetDirection();
};
#endif //HERO_HPP