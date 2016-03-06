#include "nodes/TextNode.h"
#include "util/Utility.h"

#include <SFML/Graphics/RenderTarget.hpp>

    
TextNode::TextNode(const FontHolder& fonts, const std::string& text)
{
	m_text.setFont(fonts.Get(Fonts::Main));
	m_text.setCharacterSize(20);
	SetString(text);
}

void TextNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text, states);
}

void TextNode::SetString(const std::string& text)
{
	m_text.setString(text);
	CenterOrigin(m_text);
}
