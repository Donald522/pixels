#ifndef EMITTER_NODE_H
#define EMITTER_NODE_H

#include "nodes/SceneNode.h"
#include "effects/Particle.h"
#include "nodes/ParticleNode.h"


// purely logical scene nodes that emit particles into particle systems
class EmitterNode : public SceneNode {
public:

	explicit			EmitterNode( Particle::Type_t type );

private:

	virtual void		UpdateCurrent( sf::Time dt, CommandQueue& commands );
	
	void				EmitParticle( sf::Time dt );
	
	sf::Time			m_accumulatedTime;
	Particle::Type_t	m_particleType;
	ParticleNode*		m_particleSystem;
};

#endif // EMITTER_NODE_H

