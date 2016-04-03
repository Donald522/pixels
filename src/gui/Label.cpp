#include "gui/Label.h"
#include "util/Utility.h"

#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

	Label::Label( const std::string& text, const FontHolder& fonts )
		: m_text( text, fonts.Get( Fonts::Main ), 16 )
	{
	}

	bool Label::IsSelectable() const
	{
		return false;
	}

	void Label::HandleEvent( const sf::Event& )
	{
	}

	void Label::draw( sf::RenderTarget& target, sf::RenderStates states ) const
	{
		states.transform *= getTransform();
		target.draw( m_text, states );
	}

	void Label::SetText( const std::string& text )
	{
		m_text.setString( text );
	}
}
