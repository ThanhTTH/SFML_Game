#ifndef ROCKET_HPP
#define ROCKET_HPP
#include <string>
#include <SFML/Graphics.hpp>
#include "IDrawable.hpp"

class Rocket : public Idrawable
{
public:
    Rocket();
    ~Rocket();
    void Initialize(std::string& textureName);
    void Update(float& distance);
};

#endif //ROCKET_HPP