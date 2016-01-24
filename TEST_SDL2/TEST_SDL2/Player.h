#pragma once

#include "GfxObject.h"
#include "MoveableObject.h"
#include "Graphics.h"
#include "Shoot.h"

#include <vector>
#include <set>

namespace CKT
{
	namespace GAME
	{
		class CPlayer : public CKT::GFX::GfxObject, public CKT::GAME::CMoveableObject
		{
		public:
			struct PlayerVars
			{
				float ACC_SPEED;			// Velocity added if key is pressed
				float BRAKE_SPEED;		// Velocity substracted if key is released
				float MAX_SPEED;			// max Velocity speed
				float BOUNCE_STRENGTH;	// strength of the force for the bouncing effect if the player hit the wall [%]
				float ANIM_STEP_0;		// < this value = Center animation
				float ANIM_STEP_1;		// < this value and >= ANIM_STEP_0 = first animation step
				float ANIM_STEP_2;		// < this value and >= ANIM_STEP_0 = second animation step
												// have to be more then the MAX_SPEED

				int TIME_TO_SHOOT;		// time befor you can fire the next shoot
			};

		private:
			float m_VelX = 0;
			float m_VelY = 0;

			bool m_MoveLeft = false;
			bool m_MoveRight = false;
			bool m_Shoot = false;

			typedef std::set<CShoot*> SHOOT_SET;
			SHOOT_SET m_Shoots;

			bool m_HasShield = true;

			PlayerVars m_Vars;

			//const float ACC_SPEED = 0.6f;		// Velocity added if key is pressed
			//const float BRAKE_SPEED = 0.3f;		// Velocity substracted if key is released
			//const float MAX_SPEED = 0.3f;		// max Velocity speed
			//const float BOUNCE_STRENGTH = 0.5f;	// strength of the force for the bouncing effect if the player hit the wall [%]
			//const float ANIM_STEP_0 = 0.02f;	// < this value = Center animation
			//const float ANIM_STEP_1 = 0.17f;	// < this value and >= ANIM_STEP_0 = first animation step
			//const float ANIM_STEP_2 = 0.3f;		// < this value and >= ANIM_STEP_0 = second animation step
			//									// have to be more then the MAX_SPEED

			//const int TIME_TO_SHOOT = 300;		// time befor you can fire the next shoot

		private:
			void Fire();

		public:
			CPlayer();
			~CPlayer();

			float& VelX() { return m_VelX; }
			float& VelY() { return m_VelX; }

			void KeyLeft(bool down) { m_MoveLeft = down; }
			void KeyRight(bool down) { m_MoveRight = down; }
			void KeyShoot(bool shoot) { m_Shoot = shoot; }

			bool& HasShield() { return m_HasShield; }

			SHOOT_SET& GetShoots() { return m_Shoots; }
			void ResetPlayer();

			void PlayerData(PlayerVars vars);

		public:
			//int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s = 1.0f);

			virtual int Update(float time) override;
			virtual int Render() override;

		};

	}

}


