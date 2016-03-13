#include <gtest/gtest.h>
#include "resource/ResourceHolder.h"
#include "resource/ResourceIdentifiers.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Shader.hpp>

TEST(Resource, LoadGet)
{
    TextureHolder th;
	th.Load(Textures::Buttons, "Data/Textures/Buttons.png");
	ASSERT_EQ(true,  th.Get(Textures::Buttons).getSize() != sf::Vector2u(0, 0));

	FontHolder fh;
	fh.Load(Fonts::Main, "Data/Sansation.ttf");

	SoundBufferHolder sbh;
	sbh.Load(SoundEffect::Button, "Data/Sounds/Button.wav");
	sbh.Get(SoundEffect::Button);

	ShaderHolder sh;
	sh.Load( Shaders::AddPass,	"Data/Shaders/Fullpass.vert", "Data/Shaders/Add.frag" );
	sh.Get(Shaders::AddPass);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
