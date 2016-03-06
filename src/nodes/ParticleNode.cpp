#include "nodes/ParticleNode.h"
#include "resource/DataTables.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace
{
	const std::vector<ParticleData> Table = InitializeParticleData();
}

ParticleNode::ParticleNode( Particle::Type_t type, const TextureHolder& textures )
: SceneNode()
, m_particles()
, m_texture( textures.Get( Textures::Particle ) )
, m_particleType( type )
, m_vertexArray(sf::Quads)
, m_needVerticiesUpdate(true)
{

}

void ParticleNode::AddParticle( sf::Vector2f pos )
{
	Particle particle;
	particle.color = Table[m_particleType].color;
	particle.lifetime = Table[m_particleType].lifetime;
	particle.position = pos;

	m_particles.push_back( particle );
}

Particle::Type_t ParticleNode::GetParticleType() const
{
	return m_particleType;
}

Category::Type_t ParticleNode::GetCategory() const
{
	return Category::ParticleSystem;
}

void ParticleNode::UpdateCurrent( sf::Time dt, CommandQueue& commands )
{
	// remove expired
	while ( !m_particles.empty() && m_particles.front().lifetime <= sf::Time::Zero )
		m_particles.pop_front();

	for ( Particle& p : m_particles )
	{
		p.lifetime -= dt;
	}

	m_needVerticiesUpdate = true;
}

void ParticleNode::DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{
	if ( m_needVerticiesUpdate )
	{
		ComputeVerticies();
		m_needVerticiesUpdate = false;
	}

	states.texture = &m_texture;
	target.draw( m_vertexArray, states );
}


void ParticleNode::AddVertex( float worldX, float worldY, float texX, float texY, const sf::Color& color ) const
{
	sf::Vertex vertex;

	vertex.position = sf::Vector2f( worldX, worldY );
	vertex.texCoords = sf::Vector2f( texX, texY );
	vertex.color = color;


	m_vertexArray.append( vertex );
}

void ParticleNode::ComputeVerticies() const
{
	sf::Vector2f size( m_texture.getSize() );
	sf::Vector2f halfSize = size / 2.0f;

	m_vertexArray.clear( );
	for ( const Particle& p : m_particles )
	{
		sf::Vector2f pos	= p.position;
		sf::Color color		= p.color;

		float ratio = p.lifetime.asSeconds() / Table[m_particleType].lifetime.asSeconds();
		color.a = static_cast< sf::Uint32 >( 255 * std::max( ratio, 0.0f ) );

		AddVertex( pos.x - halfSize.x, pos.y - halfSize.y, 0.0f, 0.0f, color );
		AddVertex( pos.x + halfSize.x, pos.y - halfSize.y, size.x, 0.0f, color );
		AddVertex( pos.x + halfSize.x, pos.y + halfSize.y, size.x, size.y, color );
		AddVertex( pos.x - halfSize.x, pos.y + halfSize.y, 0.0f, size.y, color );
	}
}
