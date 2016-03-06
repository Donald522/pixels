#ifndef PIXELATE_EFFECT_H
#define PIXELATE_EFFECT_H

#include "effects/PostEffect.h"
#include "resource/ResourceIdentifiers.h"
#include "resource/ResourceHolder.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>

#include <array>


class PixelateEffect : public PostEffect {
public:

                        PixelateEffect( );

	virtual void		Apply( const sf::RenderTexture& input, sf::RenderTarget& output );
	void				SetPixelThreshold( float factor );

private:

	void				PrepareTextures( sf::Vector2u size );
	void				Pixelate( const sf::RenderTexture& input, sf::RenderTarget& output );

private:

	float				m_factor;
	ShaderHolder		m_shaders;
    sf::RenderTexture	m_pixelateTexture;
};

#endif // PIXELATE_EFFECT_H

