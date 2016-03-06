#ifndef CONTAINER_H
#define CONTAINER_H

#include "Component.h"

#include <vector>
#include <memory>


namespace GUI
{

    class Container : public Component
    {
        public:

            typedef std::shared_ptr<Container> Ptr;

                                Container();

            void				Pack(Component::Ptr component);
            virtual bool		IsSelectable() const;
            virtual void		HandleEvent(const sf::Event& event);

        private:

            virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

            bool				HasSelection() const;
            void				Select(std::size_t index);
            void				SelectNext();
            void				SelectPrevious();


        private:
            std::vector<Component::Ptr>		m_children;
            int								m_selectedChild;

    };

}

#endif // CONTAINER_H
