#pragma once

#include "FocusableObj.h"
#include "Label.h"
#include "Btn.h"
#include <TimerOn.h>

#include <vector>

namespace CKT
{
	namespace GUI
	{

		class CMenuItem : public CFocusableObj
		{
		public:
			typedef void(*Click)(void* self, CMenuItem& sender, CBtnEventArgs& args);
			typedef std::vector<CMenuItem*> MENUITEM_LIST;
			static const int DIFF_TEXT = 4;

		protected:
			CLabel* m_Header = nullptr;
			
			MENUITEM_LIST m_Content;
			CTimerOn m_Timer;
			SDL_Color m_OriginalColor;
			
			eMenuPosition m_MenuPosition = TOP;

			bool m_IsOpen = false;
			bool m_IsTopItem = false;
			bool m_IsLeafItem = true;
			bool m_IsInUse = false;
			bool m_IsSeperator = false;

			Click m_OnClick = nullptr;
			bool m_IsPressed = false, m_WasPressed = false, m_IsDown = false, m_IsUp = false;

		public:
			DllExport CMenuItem();
			DllExport virtual ~CMenuItem();

		public:
			DllExport int Init(PRENDERER ren, const std::string& msg, float x, float y, SDL_Color colText, SDL_Color colBack, GFX::FONT_ID id);
			DllExport int Init(PRENDERER ren, const std::string& msg, float x, float y, SDL_Color colBack, GFX::FONT_ID id);

		public:
			DllExport void Add(CMenuItem* item, bool arrow = false);
			DllExport void Add(CGUIBase* sep);

			DllExport void SetClickEvent(Click func, void* objForCallback) { m_OnClick = func; m_ObjForCallback = objForCallback; }

		public:
			DllExport MENUITEM_LIST& Content() { return m_Content; }

			DllExport eMenuPosition& MenuPosition() { return m_MenuPosition; }

			DllExport bool& TopItem() { return m_IsTopItem; }
			DllExport bool& IsOpen() { return m_IsOpen; }

			DllExport bool IsPressed() { return m_IsPressed; }
			DllExport bool IsDown() { return m_IsDown; }
			DllExport bool IsUp() { return m_IsUp; }

			DllExport bool IsInUse() { return m_IsInUse; }
			DllExport bool IsInUse(CMenuItem* item);

			DllExport bool IsSeperator() { return m_IsSeperator; }

		public:
			DllExport void SetX(float x);
			DllExport void SetY(float y);

		public:
			DllExport int Update(SDL_Event* e) override;
			DllExport int UpdateChilds(SDL_Event* e);
			DllExport int Render() override;
		};

	}

}
