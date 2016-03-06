#ifndef LABEL_H
#define LABEL_H

#include "gui/Component.h"
#include "resource/ResourceIdentifiers.h"
#include "resource/ResourceHolder.h"

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

	class Label : public Component {
	public:

        typedef std::shared_ptr<Label> Ptr;

                            Label( const std::string& text, const FontHolder& fonts );

		virtual bool		IsSelectable() const;
		void				SetText( const std::string& text );
		virtual void		HandleEvent( const sf::Event& event );

	private:

		void				draw( sf::RenderTarget& target, sf::RenderStates states ) const;

		sf::Text			m_text;
	};
}

#endif // LABEL_H
