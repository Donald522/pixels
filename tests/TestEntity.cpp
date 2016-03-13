#include <gtest/gtest.h>
#include "entity/Entity.h"
#include "entity/Creature.h"
#include "resource/ResourceHolder.h"

TEST(Entity, Hitpoints)
{
	Entity e1(nullptr, 100);

	ASSERT_EQ(100,		e1.GetHitpoints());
	ASSERT_EQ(false,	e1.IsDestroyed());

	e1.Damage(50);
	ASSERT_EQ(50,		e1.GetHitpoints());

	e1.Damage(50);
	ASSERT_EQ(0,		e1.GetHitpoints());
	ASSERT_EQ(true,		e1.IsDestroyed());

	e1.Damage(50);
	ASSERT_EQ(-50,		e1.GetHitpoints());
	ASSERT_EQ(true,		e1.IsDestroyed());

	e1.Repair(60);
	ASSERT_EQ(10,		e1.GetHitpoints());
	ASSERT_EQ(false,	e1.IsDestroyed());


	Entity e2(nullptr, std::numeric_limits<int>::max());

	ASSERT_EQ(std::numeric_limits<int>::max(),	e2.GetHitpoints());

	e2.Repair(1);
	ASSERT_EQ(true,								e2.IsDestroyed());
}


TEST(Entity, Velocity)
{
	Entity e(nullptr, 100);

	ASSERT_EQ(sf::Vector2f(0.0f, 0.0f), e.GetVelocity());

	e.SetVelocity(-1.0f, 1.0f);
	ASSERT_EQ(sf::Vector2f(-1.0f, 1.0f), e.GetVelocity());

	e.Accelerate(2.0f, 0.0f);
	ASSERT_EQ(sf::Vector2f(1.0f, 1.0f), e.GetVelocity());

	sf::Vector2f v(1.0f, -1.0f);

	e.SetVelocity(v);
	ASSERT_EQ(v, e.GetVelocity());

	e.Accelerate(-v);
	ASSERT_EQ(sf::Vector2f(0.0f, 0.0f), e.GetVelocity());

	e.Destroy();
	ASSERT_EQ(true,	e.IsDestroyed());
}

TEST(Creature, Base)
{



	//Creature c(nullptr, Creature::PlayerStarship, textures, fonts);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
