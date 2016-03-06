#ifndef ENTITY_H
#define ENTITY_H


#include "nodes/SceneNode.h"

class SceneGrid;

class Entity : public SceneNode
{
    //TODO: move friend out?
	friend class SceneGrid;

	public:

		explicit			Entity( SceneGrid* sceneGrid, int hitpoints );

		void				SetVelocity(sf::Vector2f velocity);
		void				SetVelocity(float vx, float vy);
		void				Accelerate(sf::Vector2f velocity);
		void				Accelerate(float vx, float vy);
		sf::Vector2f		GetVelocity() const;

		int					GetHitpoints() const;
		void				Repair(int points);
		void				Damage(int points);
		void				Destroy();
		virtual void		Remove( );
		virtual bool		IsDestroyed() const;


	protected:

		virtual void		UpdateCurrent(sf::Time dt, CommandQueue& commands);
		SceneGrid*			m_sceneGrid;

	private:

		sf::Vector2f		m_velocity;
		int					m_hitpoints;
};

#endif // ENTITY_H
