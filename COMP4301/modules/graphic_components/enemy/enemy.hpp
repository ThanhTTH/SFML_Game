#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "IDrawable.hpp"
class Enemy : public Idrawable
{
public:
    Enemy();
    ~Enemy();
    void Initialize(std::string &textureName) override;
    void Update(float& distance) override;
};

#endif //ENEMY_HPP