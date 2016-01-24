#pragma once

#include "Common.h"

#include "GfxObject.h"
#include "MoveableObject.h"

#include <set>

namespace CKT
{
	namespace GAME
	{
		class CEnemy : public GFX::GfxObject, public CMoveableObject
		{
		private:
			static int ID_COUNTER;
			int m_ID = 0;

			int m_Life = 3;
			int m_OldLife = 3;

			std::set<GfxObject*> m_Explosions;

			bool m_IsActive = true;

			bool m_ShotLineFree = false;

		public:
			CEnemy();
			~CEnemy();

		public:
			bool IsActive() { return m_IsActive; }
			bool IsObstacle(CEnemy* other);

			void Shot();

		public:
			int& Life() { return m_Life; }
			bool& ShotAllowed() { return m_ShotLineFree; }

		public:
			virtual int Update(float time) override;
			virtual int Render() override;

		};

	}

}
