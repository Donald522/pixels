#ifndef CATEGORY_H
#define CATEGORY_H


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type_t
	{
		None				= 0,
		SceneAirLayer		= 1 << 0,
		PlayerAircraft		= 1 << 1,
		AlliedAircraft		= 1 << 2,
		EnemyAircraft		= 1 << 3,
		Pickup				= 1 << 4,
		AlliedProjectile	= 1 << 5,
		EnemyProjectile		= 1 << 6,

		ParticleSystem 		= 1 << 7,

		Creature			= PlayerAircraft | AlliedAircraft | EnemyAircraft,
		Projectile			= AlliedProjectile | EnemyProjectile,
	};
}

#endif // CATEGORY_H