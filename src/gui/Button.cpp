#include "gui/Button.h"
#include "util/Utility.h"
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Button::Button(State::Context_t context)
: m_callback()
, m_sprite(context.textures->Get(Textures::Buttons))
, m_text("", context.fonts->Get(Fonts::Main), 16)
, m_isToggle(false)
, m_sounds(*context.sound)
{
	ChangeTexture(Button::Normal);

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

	ChangeTexture(Button::Selected);
	m_sounds.Play(SoundEffect::Button);
}

void Button::Deselect()
{
	Component::Deselect();

	ChangeTexture(Button::Normal);
}

void Button::Activate()
{
	Component::Activate();

    // If we are toggle then we should show that the button is pressed and thus "toggled".
	if (m_isToggle)
		ChangeTexture(Button::Pressed);

	if (m_callback)
		m_callback();

    // If we are not a toggle then deactivate the button since we are just momentarily activated.
	if (!m_isToggle)
		Deactivate();

	m_sounds.Play(SoundEffect::Button);
}

void Button::Deactivate()
{
	Component::Deactivate();

	if (m_isToggle)
	{
        // Reset texture to right one depending on if we are selected or not.
		if (IsSelected())
			ChangeTexture(Button::Selected);
		else
			ChangeTexture(Button::Normal);
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

void Button::ChangeTexture(Button::Type_t type)
{
	sf::IntRect textureRect(0, 50 * type, 200, 50);
	m_sprite.setTextureRect(textureRect);
}


}
