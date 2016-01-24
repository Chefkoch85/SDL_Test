#pragma once

#include "GUIBase.h"

namespace CKT
{
	namespace GUI
	{
		enum BarOrientation
		{
			FromLeft = 0x01,
			FromRight = 0x02,
			FromTop = 0x04,
			FromBottom = 0x08,
			FromCenter = 0x10,
		};

		class CProgressbar : public CGUIBase
		{
		protected:
			int m_Min = 0;
			int m_Max = 100;
			int m_Value = 0;

			SDL_Color m_ColBack = { 128,128,128,255 };
			SDL_Color m_ColFront = { 0,0,128,255 };

			int m_DiffBackFront = 5;

			BarOrientation m_Orientation;

		public:
			DllExport CProgressbar();
			DllExport ~CProgressbar();

		public:
			DllExport int& Min() { return m_Min; }
			DllExport int& Max() { return m_Max; }
			DllExport int& Value() { return m_Value; }

			DllExport SDL_Color& ColorBack() { return m_ColBack; }
			DllExport SDL_Color& ColorFront() { return m_ColFront; }

			DllExport BarOrientation& Orientation() { return m_Orientation; }

			DllExport int& DistanceForeground() { return m_DiffBackFront; }

		public:

			DllExport int Init(PRENDERER ren, float x, float y, float w, float h);
			DllExport int Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s = 1.0) override;
			DllExport int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s = 1.0) override;

			DllExport int Render() override = 0;

		};

	}

}
