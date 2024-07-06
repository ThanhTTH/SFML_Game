#ifndef SKY_HPP
#define SKY_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "IDrawable.hpp"

class Sky : public Idrawable
{
public:
    Sky();
    ~Sky();
    void Initialize(std::string &textureName) override;
    void Update(float& distance) override;
};

#endif //SKY_HPP