#include "gui/Component.h"

namespace GUI
{

Component::Component()
: m_isSelected(false)
, m_isActive(false)
{
}

Component::~Component()
{
}

bool Component::IsSelected() const
{
	return m_isSelected;
}

void Component::Select()
{
	m_isSelected = true;
}

void Component::Deselect()
{
	m_isSelected = false;
}

bool Component::IsActive() const
{
	return m_isActive;
}

void Component::Activate()
{
	m_isActive = true;
}

void Component::Deactivate()
{
	m_isActive = false;
}

}
