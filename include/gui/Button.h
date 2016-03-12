
#ifndef BUTTON_H
#define BUTTON_H

#include "gui/Component.h"
#include "resource/ResourceIdentifiers.h"
#include "states/State.h"
#include "music/SoundPlayer.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


namespace GUI
{

class Button : public Component
{
    public:

        typedef std::shared_ptr<Button>		Ptr;
        typedef std::function<void()>		Callback;

        enum Type_t
        {
            Normal,
            Selected,
            Pressed,
            ButtonCount
        };

                                Button(State::Context_t context);

        void					SetCallback(Callback callback);
        void					SetText(const std::string& text);
        void					SetToggle(bool flag);

        virtual bool			IsSelectable() const;
        virtual void			Select();
        virtual void			Deselect();

        virtual void			Activate();
        virtual void			Deactivate();

        virtual void			HandleEvent(const sf::Event& event);

    private:

        virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void                    ChangeTexture(Button::Type_t type);

    private:

        Callback				m_callback;
        sf::Sprite				m_sprite;
        sf::Text				m_text;
        bool					m_isToggle;

        SoundPlayer&            m_sounds;
};

}

#endif // BUTTON_H
