#ifndef PARTICLE_NODE_H
#define PARTICLE_NODE_H

#include "nodes/SceneNode.h"
#include "effects/Particle.h"
#include "resource/ResourceHolder.h"
#include "resource/ResourceIdentifiers.h"

#include <SFML/Graphics/VertexArray.hpp>

#include <deque>


class ParticleNode : public SceneNode {
public:

								ParticleNode( Particle::Type_t type, const TextureHolder& textures );

	void						AddParticle( sf::Vector2f pos );

	Particle::Type_t			GetParticleType() const;
	virtual Category::Type_t	GetCategory( ) const;


private:

	virtual void				UpdateCurrent( sf::Time dt, CommandQueue& commands );
	virtual void				DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

	void						AddVertex( float worldX, float worldY, float texX, float texY, const sf::Color& color ) const;
	void						ComputeVerticies() const;

	std::deque<Particle>		m_particles;
	const sf::Texture&			m_texture;
	Particle::Type_t			m_particleType;

	mutable sf::VertexArray		m_vertexArray;
	mutable bool				m_needVerticiesUpdate;

};

#endif //PARTICLE_NODE_H
