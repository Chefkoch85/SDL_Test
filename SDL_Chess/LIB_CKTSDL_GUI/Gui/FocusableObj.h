#pragma once

#include "GUIBase.h"
#include "GuiEventArgs.h"

namespace CKT
{
	namespace GUI
	{
		class CFocusableObj : public CGUIBase
		{
		public:
			typedef void(*GotFocus)(void * self, CFocusableObj& sender, CGuiEventArgs& args);
			typedef void(*LostFocus)(void * self, CFocusableObj& sender, CGuiEventArgs& args);

		protected:
			bool m_IsEnabled = true;

			bool m_IsSelected = false;
			bool m_WasSelected = false;

			bool m_GotFocus = false;
			bool m_LostFocus = false;

			bool m_NonVisual = false;

			GotFocus m_OnGotFocus = nullptr;
			LostFocus m_OnLostFocus = nullptr;

			CGuiEventArgs* m_EventArgs = nullptr;
			void * m_ObjForCallback = nullptr;

			SDL_Point m_FocusClipPoints[2];

		public:
			DllExport CFocusableObj();
			DllExport ~CFocusableObj();

			DllExport bool& IsSelected() { return m_IsSelected; }
			DllExport bool& IsEnabled() { return m_IsEnabled; }
			DllExport bool& IsNonVisual() { return m_NonVisual; }

			DllExport void SetClippingPoints(int x1, int y1, int x2, int y2);

			DllExport void SetEventGotFocus(GotFocus func, void* objForCallback) { m_OnGotFocus = func; m_ObjForCallback = objForCallback; }
			DllExport void SetEventLostFocus(LostFocus func, void* objForCallback) { m_OnLostFocus = func; m_ObjForCallback = objForCallback; }
			DllExport void SetFocusChanged(GotFocus gotFunc, LostFocus lostFunc, void* objForCallback);

			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s = 1.0f) override;

			DllExport virtual int Update(SDL_Event* e);
		};

	}

}