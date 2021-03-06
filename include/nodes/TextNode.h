#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "resource/ResourceHolder.h"
#include "resource/ResourceIdentifiers.h"
#include "nodes/SceneNode.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>


class TextNode : public SceneNode
{
	public:

		explicit			TextNode(const FontHolder& fonts, const std::string& text);

		void				SetString(const std::string& text);

	private:

		virtual void		DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Text			m_text;
};

#endif // TEXTNODE_H
