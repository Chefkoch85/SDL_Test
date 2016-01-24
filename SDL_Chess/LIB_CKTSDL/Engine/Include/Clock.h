#pragma once

#include "MoveableObject.h"
#include "GfxObject.h"

namespace CKT
{
	namespace GUI
	{
		class CClock : public GFX::CGfxObject, public GAME::CMoveableObject
		{
		private:
			double m_Angle = 0.0;

			GFX::CGfxObject* m_Pointer = nullptr;
			GFX::CGfxObject* m_Pointer2 = nullptr;

			float m_SumTime = 0.0f;

			const float m_RefreshTime = 0.010f;

		public:
			DllExport CClock();
			DllExport ~CClock();

			DllExport double& Angle() { return m_Angle; }

			DllExport virtual int Init(PRENDERER ren, std::string fileBack, std::string filePointer, float x, float y, float s = 1.0f);

			DllExport int Update(float time) override;

			DllExport int Render() override;

		};

	}

}