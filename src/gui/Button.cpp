#include "gui/Button.h"
#include "util/Utility.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Button::Button(const FontHolder& fonts, const TextureHolder& textures)
: m_callback()
, m_normalTexture(textures.Get(Textures::ButtonNormal))
, m_selectedTexture(textures.Get(Textures::ButtonSelected))
, m_pressedTexture(textures.Get(Textures::ButtonPressed))
, m_sprite()
, m_text("", fonts.Get(Fonts::Main), 16)
, m_isToggle(false)
{
	m_sprite.setTexture(m_normalTexture);

	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::SetCallback(Callback callback)
{
	m_callback = std::move(callback);
}

void Button::SetText(const std::string& text)
{
	m_text.setString(text);
	CenterOrigin(m_text);
}

void Button::SetToggle(bool flag)
{
	m_isToggle = flag;
}

bool Button::IsSelectable() const
{
    return true;
}

void Button::Select()
{
	Component::Select();

	m_sprite.setTexture(m_selectedTexture);
}

void Button::Deselect()
{
	Component::Deselect();

	m_sprite.setTexture(m_normalTexture);
}

void Button::Activate()
{
	Component::Activate();

    // If we are toggle then we should show that the button is pressed and thus "toggled".
	if (m_isToggle)
		m_sprite.setTexture(m_pressedTexture);

	if (m_callback)
		m_callback();

    // If we are not a toggle then deactivate the button since we are just momentarily activated.
	if (!m_isToggle)
		Deactivate();
}

void Button::Deactivate()
{
	Component::Deactivate();

	if (m_isToggle)
	{
        // Reset texture to right one depending on if we are selected or not.
		if (IsSelected())
			m_sprite.setTexture(m_selectedTexture);
		else
			m_sprite.setTexture(m_normalTexture);
	}
}

void Button::HandleEvent(const sf::Event&)
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
	target.draw(m_text, states);
}

}
