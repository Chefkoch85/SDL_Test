#pragma once

#include "Common.h"
#include "GfxObject.h"

namespace CKT
{
	namespace GAME
	{
		class CBackground : public GFX::GfxObject
		{
		private:

			int m_TilesX;
			int m_TilesY;

		public:
			CBackground();
			~CBackground();

			virtual int Init(PRENDERER ren, std::string file, int scrWidth, int scrHeight, float s = 1.0f);

			virtual int Render() override;

		};

	}

}
