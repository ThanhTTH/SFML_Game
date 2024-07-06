#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "IDrawable.hpp"

class Background : public Idrawable
{
public:
    Background();
    ~Background();
    void Initialize(std::string &textureName) override;
    void Update(float& distance) override;
};

#endif //BACKGROUND_HPP