#pragma once

#include "..\LIB_CKTSDL_GUI_intern.h"
#include "GfxObject.h"

namespace CKT
{
	namespace GUI
	{
		enum EAncor
		{
			Unkown = 0x00,

			Top = 0x01,
			Bottom = 0x02,
			Left = 0x04,
			Right = 0x08,

			Center = 0x10,
			CenterX = 0x20,
			CenterY = 0x40,
		};

		typedef int AncorPoint;
		typedef unsigned int GUI_ID;

		class CGUIBase : public GFX::CGfxObject
		{
		private:
			static GUI_ID ID_COUNTER;

		protected:
			std::string m_GuiName = "";
			GUI_ID m_ID = 0;

			AncorPoint m_AncorPoint = EAncor::Top | EAncor::Left;

			SDL_Color m_BackgroundColor;

		public:
			DllExport AncorPoint& AncorPoint() { return m_AncorPoint; }

			DllExport std::string& Name() { return m_GuiName; }

			DllExport SDL_Color& BackgroundColor() { return m_BackgroundColor; }

		public:
			DllExport CGUIBase();
			DllExport ~CGUIBase();

			DllExport void SetContent(PTEXTURE tex, bool resize = false);

			DllExport GUI_ID ID() { return m_ID; }

			DllExport int Render() override;
		};

	}
}
