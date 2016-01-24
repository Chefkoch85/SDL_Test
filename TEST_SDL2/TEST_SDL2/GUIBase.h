#pragma once

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

		class CGUIBase : public GFX::GfxObject
		{
		private:
			static GUI_ID ID_COUNTER;

		protected:
			std::string m_GuiName = "";
			GUI_ID m_ID = 0;

			AncorPoint m_AncorPoint = EAncor::Top | EAncor::Left;

			SDL_Color m_BackgroundColor;

		public:
			AncorPoint& AncorPoint() { return m_AncorPoint; }

			std::string& Name() { return m_GuiName; }

			SDL_Color& BackgroundColor() { return m_BackgroundColor; }

		public:
			CGUIBase();
			~CGUIBase();

			void SetContent(PTEXTURE tex, bool resize = false);

			GUI_ID ID() { return m_ID; }

			int Render() override;
		};

	}
}
