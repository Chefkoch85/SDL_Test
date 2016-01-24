#pragma once

#include "GuiContainer.h"
#include "Scrollbar.h"
#include "Util.h"

namespace CKT
{
	namespace GUI
	{
		enum EScrollbarUse
		{
			NEVER		= 0x00,
			ALLWAYS		= 0x01,
			AS_NEEDED	= 0x02,
		};

		class CGuiScrollableContainer : public CGuiContainer
		{
		protected:
			SDL_Rect m_ContainerBounds = { 0 };
			SDL_Rect m_CurentClip = { 0 };
			SDL_Rect m_OldClip = { 0 };

			bool m_ScrollbarsInitOK = false;
			CScrollbar* m_scbBottom = nullptr;
			CScrollbar* m_scbRight = nullptr;
			EScrollbarUse m_UseScbRight = EScrollbarUse::AS_NEEDED;
			EScrollbarUse m_UseScbBottom = EScrollbarUse::AS_NEEDED;

			GUI_DRAW_ELEM_SET m_ElementsToDraw;
			GUI_UPDATE_ELEM_SET m_ElementsToUpdate;

			int m_ScrollFactor = 1;

		protected:
			static void onValueCallback(void * pThis, CKT::GUI::CScrollbar & sender, GUI::CGuiEventArgs& args);
			void onValue(GUI::CScrollbar & sender, GUI::CGuiEventArgs& args);

		public:
			CGuiScrollableContainer();
			~CGuiScrollableContainer();

			int& ScrollFactor() { return m_ScrollFactor; }

			void ScrollbarUse(EScrollbarUse use, eOriantation witch);
			int InitScrollbars(PRENDERER ren, std::string fileHor, std::string fileVer, float w, float h, int xTiles, int yTiles);

			virtual void CalculatePositions() override;

			virtual void Init(PRENDERER ren, SDL_Color col, float x, float y, float w, float h) override;

			virtual void Update(SDL_Event* e) override;

			virtual int Render() override;
		};

	}

}
