#include "effects/BloomEffect.h"


BloomEffect::BloomEffect()
: m_shaders()
, m_brightnessTexture()
, m_firstPassTextures()
, m_secondPassTextures()
{
	m_shaders.Load( Shaders::BrightnessPass,	"Data/Shaders/Fullpass.vert", "Data/Shaders/Brightness.frag" );
	m_shaders.Load( Shaders::DownSamplePass,	"Data/Shaders/Fullpass.vert", "Data/Shaders/DownSample.frag" );
	m_shaders.Load( Shaders::GaussianBlurPass,	"Data/Shaders/Fullpass.vert", "Data/Shaders/GuassianBlur.frag" );
	m_shaders.Load( Shaders::AddPass,			"Data/Shaders/Fullpass.vert", "Data/Shaders/Add.frag" );
}

void BloomEffect::Apply( const sf::RenderTexture& input, sf::RenderTarget& output )
{
	PrepareTextures( input.getSize() );


	//sf::Shader& brightness = m_shaders.Get( Shaders::BrightnessPass );
	//brightness.setParameter( "source", input.getTexture( ) );
	//ApplyShader( brightness, output );

	FilterBright( input, m_brightnessTexture );

	Downsample( m_brightnessTexture, m_firstPassTextures[0] );
	BlurMultipass( m_firstPassTextures );

	Downsample( m_firstPassTextures[0], m_secondPassTextures[0] );
	BlurMultipass( m_secondPassTextures );

	Add( m_firstPassTextures[0], m_secondPassTextures[0], m_firstPassTextures[1] );
	m_firstPassTextures[1].display();
	Add( input, m_firstPassTextures[1], output );
}


void BloomEffect::PrepareTextures( sf::Vector2u size )
{
	if ( m_brightnessTexture.getSize( ) != size )
	{
		m_brightnessTexture.create( size.x, size.y );
		m_brightnessTexture.setSmooth( true );

		m_firstPassTextures[0].create( size.x / 2, size.y / 2 );
		m_firstPassTextures[0].setSmooth( true );
		m_firstPassTextures[1].create( size.x / 2, size.y / 2 );
		m_firstPassTextures[1].setSmooth( true );

		m_secondPassTextures[0].create( size.x / 4, size.y / 4 );
		m_secondPassTextures[0].setSmooth( true );
		m_secondPassTextures[1].create( size.x / 4, size.y / 4 );
		m_secondPassTextures[1].setSmooth( true );
	}
}


void BloomEffect::FilterBright( const sf::RenderTexture& input, sf::RenderTexture& output )
{
	sf::Shader& brightness = m_shaders.Get( Shaders::BrightnessPass );
	brightness.setParameter( "source", input.getTexture() );
	ApplyShader( brightness, output );
	output.display();
}

void BloomEffect::BlurMultipass( RenderTextureArray_t& renderTextures )
{
	sf::Vector2u textureSize = renderTextures[0].getSize( );

	for ( std::size_t count = 0; count < 2; ++count )
	{
		Blur( renderTextures[0], renderTextures[1], sf::Vector2f( 0.f, 1.f / textureSize.y ) );
		Blur( renderTextures[1], renderTextures[0], sf::Vector2f( 1.f / textureSize.x, 0.f ) );
	}
}

void BloomEffect::Blur( const sf::RenderTexture& input, sf::RenderTexture& output, sf::Vector2f offsetFactor )
{
	sf::Shader& gaussianBlur = m_shaders.Get( Shaders::GaussianBlurPass );

	gaussianBlur.setParameter( "source", input.getTexture( ) );
	gaussianBlur.setParameter( "offsetFactor", offsetFactor );
	ApplyShader( gaussianBlur, output );
	output.display( );
}

void BloomEffect::Downsample( const sf::RenderTexture& input, sf::RenderTexture& output )
{
	sf::Shader& downSampler = m_shaders.Get( Shaders::DownSamplePass );

	downSampler.setParameter( "source", input.getTexture( ) );
	downSampler.setParameter( "sourceSize", sf::Vector2f( input.getSize( ) ) );
	ApplyShader( downSampler, output );
	output.display( );
}

void BloomEffect::Add( const sf::RenderTexture& source, const sf::RenderTexture& bloom, sf::RenderTarget& output )
{
	sf::Shader& adder = m_shaders.Get( Shaders::AddPass );

	adder.setParameter( "source", source.getTexture( ) );
	adder.setParameter( "bloom", bloom.getTexture( ) );
	ApplyShader( adder, output );

}
