#pragma once

#include "MoveableObject.h"
#include "GfxObject.h"

namespace CKT
{
	namespace GUI
	{
		class CClock : public GFX::GfxObject, public GAME::CMoveableObject
		{
		private:
			double m_Angle = 0.0;

			GFX::GfxObject* m_Pointer = nullptr;
			GFX::GfxObject* m_Pointer2 = nullptr;

			float m_SumTime = 0.0f;

			const float m_RefreshTime = 0.010f;

		public:
			CClock();
			~CClock();

			double& Angle() { return m_Angle; }

			virtual int Init(PRENDERER ren, std::string fileBack, std::string filePointer, float x, float y, float s = 1.0f);

			int Update(float time) override;

			int Render() override;

		};

	}

}