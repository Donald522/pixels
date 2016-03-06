#include "gui/Button.h"
#include "util/Utility.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Button::Button(const FontHolder& fonts, const TextureHolder& textures)
: mCallback()
, mNormalTexture(textures.Get(Textures::ButtonNormal))
, mSelectedTexture(textures.Get(Textures::ButtonSelected))
, mPressedTexture(textures.Get(Textures::ButtonPressed))
, m_sprite()
, m_text("", fonts.Get(Fonts::Main), 16)
, mIsToggle(false)
{
	m_sprite.setTexture(mNormalTexture);

	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
	m_text.setString(text);
	CenterOrigin(m_text);
}

void Button::setToggle(bool flag)
{
	mIsToggle = flag;
}

bool Button::IsSelectable() const
{
    return true;
}

void Button::select()
{
	Component::select();

	m_sprite.setTexture(mSelectedTexture);
}

void Button::deselect()
{
	Component::deselect();

	m_sprite.setTexture(mNormalTexture);
}

void Button::activate()
{
	Component::activate();

    // If we are toggle then we should show that the button is pressed and thus "toggled".
	if (mIsToggle)
		m_sprite.setTexture(mPressedTexture);

	if (mCallback)
		mCallback();

    // If we are not a toggle then deactivate the button since we are just momentarily activated.
	if (!mIsToggle)
		deactivate();
}

void Button::deactivate()
{
	Component::deactivate();

	if (mIsToggle)
	{
        // Reset texture to right one depending on if we are selected or not.
		if (IsSelected())
			m_sprite.setTexture(mSelectedTexture);
		else
			m_sprite.setTexture(mNormalTexture);
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
