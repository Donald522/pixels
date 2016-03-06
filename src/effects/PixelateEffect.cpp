#include "effects/PixelateEffect.h"


PixelateEffect::PixelateEffect()
: m_shaders()
, m_pixelateTexture()
, m_factor( 1 )
{
	m_shaders.Load( Shaders::Pixelate, "Data/Shaders/Fullpass.vert", "Data/Shaders/Pixelate.frag" );
}

void PixelateEffect::Apply( const sf::RenderTexture& input, sf::RenderTarget& output )
{
	PrepareTextures( input.getSize( ) );

	Pixelate( input, output );
}

void PixelateEffect::SetPixelThreshold( float factor )
{
	m_factor = factor;
}


void PixelateEffect::PrepareTextures( sf::Vector2u size )
{

	if ( m_pixelateTexture.getSize( ) != size )
	{
		m_pixelateTexture.create( size.x, size.y );
		m_pixelateTexture.setSmooth( true );
	}
}

void PixelateEffect::Pixelate( const sf::RenderTexture& input, sf::RenderTarget& output )
{
	sf::Shader& pixelate = m_shaders.Get( Shaders::Pixelate );

	pixelate.setParameter( "texture", input.getTexture( ) );
	pixelate.setParameter( "pixel_threshold", m_factor );

	ApplyShader( pixelate, output );
}

