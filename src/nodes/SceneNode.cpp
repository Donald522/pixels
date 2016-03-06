#include "nodes/SceneNode.h"
#include "system/Command.h"
#include "util/Utility.h"
#include "log/Log.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>


SceneNode::SceneNode(Category::Type_t category)
: m_children()
, m_parent(nullptr)
, m_defaultCategory(category)
, m_IsDrawBoundingRect(true)
{

}

void SceneNode::AttachChild(Ptr_t child)
{
	child->m_parent = this;
	m_children.push_back(std::move(child));
}

SceneNode::Ptr_t SceneNode::DetachChild(const SceneNode& node)
{
	auto found = std::find_if(m_children.begin(), m_children.end(), [&] (Ptr_t& p) { return p.get() == &node; });
	assert(found != m_children.end());

	Ptr_t result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void SceneNode::Update(sf::Time dt, CommandQueue& commands)
{
	UpdateCurrent(dt, commands);
	UpdateChildren(dt, commands);
}

void SceneNode::UpdateCurrent(sf::Time, CommandQueue&)
{
	// 
}

void SceneNode::UpdateChildren(sf::Time dt, CommandQueue& commands)
{
	for ( Ptr_t& child : m_children )
		child->Update(dt, commands);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	DrawCurrent(target, states);
	DrawChildren(target, states);


	if ( m_IsDrawBoundingRect )	
		DrawBoundingRect(target, states);
}

void SceneNode::DrawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr_t& child : m_children)
		child->draw(target, states);
}

void SceneNode::DrawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = GetBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

size_t SceneNode::GetChildCount() const
{
	size_t count = m_children.size();
	for ( auto& child : m_children )
	{
		count += child->GetChildCount();
	}
	return count;
}

sf::Vector2f SceneNode::GetWorldPosition() const
{
	return GetWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::GetWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->m_parent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::OnCommand(const Command_t& command, sf::Time dt)
{
	// Command current node, if category matches
	if (command.category & GetCategory())
		command.action(*this, dt);

	// Command children
	for (Ptr_t& child : m_children)
		child->OnCommand(command, dt);
}

Category::Type_t SceneNode::GetCategory( ) const
{
	return m_defaultCategory;
}

void SceneNode::CheckSceneCollision(SceneNode& sceneGraph, std::set<Pair_t>& collisionPairs)
{
	CheckNodeCollision(sceneGraph, collisionPairs);

	for ( Ptr_t& child : sceneGraph.m_children )
		CheckSceneCollision(*child, collisionPairs);
}

void SceneNode::CheckNodeCollision(SceneNode& node, std::set<Pair_t>& collisionPairs)
{
	if (this != &node && NodeCollision(*this, node) && !IsDestroyed() && !node.IsDestroyed())
		collisionPairs.insert(std::minmax(this, &node));

	for (Ptr_t& child : m_children)
		child->CheckNodeCollision(node, collisionPairs);
}

void SceneNode::RemoveWrecks()
{
	// Remove all children which request so
	auto wreckfieldBegin = std::remove_if(m_children.begin(), m_children.end(), std::mem_fn(&SceneNode::IsMarkedForRemoval));
	m_children.erase(wreckfieldBegin, m_children.end());

	// Call function recursively for all remaining children
	std::for_each(m_children.begin(), m_children.end(), std::mem_fn(&SceneNode::RemoveWrecks));
}

sf::FloatRect SceneNode::GetBoundingRect() const
{
	return sf::FloatRect();
}

bool SceneNode::IsMarkedForRemoval() const
{
	return IsDestroyed();
}

bool SceneNode::IsDestroyed() const
{
	return false;
}

void SceneNode::SetDrawBoundingRect( bool IsDraw )
{
	m_IsDrawBoundingRect = IsDraw;
}

void SceneNode::SwitchDrawBoundingRect()
{
	SetDrawBoundingRect( !m_IsDrawBoundingRect );
}

bool NodeCollision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.GetBoundingRect().intersects(rhs.GetBoundingRect());
}

float NodeDistance(const SceneNode& lhs, const SceneNode& rhs)
{
	return VectorLength(lhs.GetWorldPosition() - rhs.GetWorldPosition());
}
