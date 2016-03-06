#ifndef SCENENODE_H
#define SCENENODE_H

#include "resource/Category.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <set>
#include <memory>
#include <utility>


struct  Command_t;
class   CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:

		typedef std::unique_ptr<SceneNode>			Ptr_t;
		typedef std::pair<SceneNode*, SceneNode*>	Pair_t;


		explicit					SceneNode(Category::Type_t category = Category::None);

		void						AttachChild(Ptr_t child);
		Ptr_t						DetachChild(const SceneNode& node);
		
		void						Update(sf::Time dt, CommandQueue& commands);

		sf::Vector2f				GetWorldPosition() const;
		sf::Transform				GetWorldTransform() const;

		void						OnCommand(const Command_t& command, sf::Time dt);
		virtual Category::Type_t	GetCategory( ) const;

		void						CheckSceneCollision(SceneNode& sceneGraph, std::set<Pair_t>& collisionPairs);
		void						CheckNodeCollision(SceneNode& node, std::set<Pair_t>& collisionPairs);
		void						RemoveWrecks();
		virtual sf::FloatRect		GetBoundingRect() const;
		virtual bool				IsMarkedForRemoval() const;
		virtual bool				IsDestroyed() const;

		void						SwitchDrawBoundingRect();
		void						SetDrawBoundingRect( bool IsDraw );

		size_t						GetChildCount( ) const;

	private:

		virtual void				UpdateCurrent(sf::Time dt, CommandQueue& commands);
		void						UpdateChildren(sf::Time dt, CommandQueue& commands);

		// override sfml draw(..)
		virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void				DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void						DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
		void						DrawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

	private:

        std::vector<Ptr_t>			m_children;
		SceneNode*					m_parent;
		Category::Type_t			m_defaultCategory;

		bool						m_IsDrawBoundingRect;
};

bool	NodeCollision(const SceneNode& lhs, const SceneNode& rhs);
float	NodeDistance(const SceneNode& lhs, const SceneNode& rhs);

#endif // SCENENODE_H
