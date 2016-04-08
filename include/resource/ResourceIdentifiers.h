#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H


namespace sf
{
    class Texture;
    class Font;
    class Shader;
    class SoundBuffer;
}

namespace Textures
{
    enum ID_t
    {
	Entities,
	Space,
	Buttons,
	TitleScreen,
	Menu,
	LevelSelect,
	Particle,
	Explosion
    };
}

namespace Fonts
{
    enum ID_t
    {
	Main,
    };
}

namespace Music
{
    enum ID_t
    {
	MenuTheme,
	MissionTheme
    };
}

namespace SoundEffect
{
    enum ID_t
    {
        Gunfire,
        Explosion,
        Button
    };
}

namespace Shaders
{
    enum ID_t
    {
	BrightnessPass,
	DownSamplePass,
	GaussianBlurPass,
	AddPass,
	Pixelate
    };
}

template <typename Resource, typename Identifier>
class   ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID_t>         TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID_t>               FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID_t>           ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID_t>  SoundBufferHolder;

#endif // RESOURCEIDENTIFIERS_H
