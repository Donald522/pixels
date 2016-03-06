#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H


namespace sf
{
	class Texture;
	class Font;
	class Shader;
}

namespace Textures
{
	enum ID_t
	{
		Entities,
		Space,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed,
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
	enum ID_t  {
		MenuTheme,
		MissionTheme
	};
}

namespace Shaders
{
	enum ID {
		BrightnessPass,
		DownSamplePass,
		GaussianBlurPass,
		AddPass,

		Pixelate
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID_t>		TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID_t>			FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>			ShaderHolder;

#endif // RESOURCEIDENTIFIERS_H
