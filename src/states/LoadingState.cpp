//#include "LoadingState.h"
//#include "ResourceHolder.h"
//
//#include "Utility.h"
//#include <SFML\Graphics\RenderWindow.hpp>
//
//LoadingState::LoadingState( StateStack& stack, Context_t context )
//: State( stack, context )
//{
//	m_loadingText.setFont( context.fonts->Get( Fonts::Main ) );
//	m_loadingText.setString( "Loading Resources" );
//	centerOrigin( m_loadingText );
//	m_loadingText.setPosition( context.window->getSize( ).x / 2u, context.window->getSize( ).y /2u + 50 );
//
//	m_progressBarBackground.setFillColor( sf::Color::White );
//	m_progressBarBackground.setSize( sf::Vector2f( context.window->getSize( ).x - 20,10 ) );
//	m_progressBarBackground.setPosition( 10, m_loadingText.getPosition( ).y +40 );
//
//	m_progressBar.setFillColor( sf::Color( 100, 100, 100 ) );
//	m_progressBar.setSize( sf::Vector2f( 200, 10 ) );
//	m_progressBar.setPosition( 10, m_loadingText.getPosition( ).y + 40 );
//	SetCompletion( 0.f );
//
//	m_loadingTask.Execute( );
//}
//
//void LoadingState::Draw( )
//{
//
//}
//
//bool LoadingState::Update( sf::Time dt )
//{
//	if ( m_loadingTask.IsFinished() )
//	{
//		RequestStackPop();
//		RequestStackPush( States::Game );
//	}
//	else
//	{
//		SetCompletion( m_loadingTask.GetCompletion() );
//	}
//	return true;
//}
//
//bool LoadingState::HandleEvent( const sf::Event& event )
//{
//
//}
//
//void LoadingState::SetCompletion( float completion )
//{
//	if ( completion > 1.0f )
//		completion = 1.0f;
//
//	m_progressBar.setSize( sf::Vector2f( m_progressBarBackground.getSize().x * completion, m_progressBar.getSize().y ) );
//}