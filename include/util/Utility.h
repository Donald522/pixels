#ifndef UTILITY_H
#define UTILITY_H
#include "animation/Animation.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <sstream>


namespace sf
{
	class Sprite;
	class Text;
}

// std::to_string doesn't work on MinGW
template <typename T>
std::string		ToString(const T& value);

// Convert enumerators to strings
std::string		ToString(sf::Keyboard::Key key);

// Call SetOrigin() with the center of the object
void			CenterOrigin(sf::Sprite& sprite);
void			CenterOrigin(sf::Text& text);
void			CenterOrigin( Animation& animation );

float			ToDegree(float radian);
float			ToRadian(float degree);

int				RandomInt(int exclusiveMax);

float			VectorLength(sf::Vector2f vector);
sf::Vector2f	VectorUnit(sf::Vector2f vector);


#include "Utility.inl"

#endif // UTILITY_H
