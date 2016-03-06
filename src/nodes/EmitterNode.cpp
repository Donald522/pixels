#include "nodes/EmitterNode.h"
#include "system/CommandQueue.h"


EmitterNode::EmitterNode( Particle::Type_t type )
: SceneNode()
, m_accumulatedTime(sf::Time::Zero)
, m_particleType(type)
, m_particleSystem(nullptr)
{

}

void EmitterNode::UpdateCurrent( sf::Time dt, CommandQueue& commands )
{
	if ( m_particleSystem )
	{
		EmitParticle( dt );
	}
	else
	{
		// Find particle node with the same type as emitter node
		Command_t command;
		command.category = Category::ParticleSystem;
		auto findParticleType = [ this ]( ParticleNode& node, sf::Time )
		{
			if ( node.GetParticleType() == m_particleType )
				m_particleSystem = &node;
		};
		command.action = DerivedAction<ParticleNode>( findParticleType );

		commands.Push( command );
	}
}

void EmitterNode::EmitParticle( sf::Time dt )
{
	const float emissionRate = 50.0f;
	const sf::Time interval = sf::seconds( 1.0f ) / emissionRate;

	m_accumulatedTime += dt;

	while ( m_accumulatedTime > interval )
	{
		m_accumulatedTime -= interval;
		m_particleSystem->AddParticle( GetWorldPosition() );
	}
}
