#pragma once

#include "FocusableObj.h"
#include "MoveableObject.h"
#include "Label.h"
#include "BtnEventArgs.h"

//#include <functional>

namespace CKT
{
	class CGame;

	namespace GUI
	{
		class CBtn : public CFocusableObj
		{
		public:
			typedef void(*Click)(void* self, CBtn& sender, CBtnEventArgs& args);

			//typedef std::function<void(void*, CBtn&)> Click2;

		protected:
			bool m_IsPressed = false;
			bool m_IsPressedOld = false;
			bool m_IsDown = false, m_IsUp = false;
			bool m_ClickEventOnPress = false;

			Click m_OnClick = nullptr;
			CLabel* m_Content = nullptr;

			SDL_Point m_PressedClippingPoint[2];
			
		public:
			DllExport CBtn();
			DllExport ~CBtn();

			DllExport bool& IsPressed() { return m_IsPressed; }
			DllExport bool IsDown() {	return m_IsDown; }
			DllExport bool IsUp() { return m_IsUp; }

			DllExport void ClickEventOnPress(bool on) { m_ClickEventOnPress = on; }

			DllExport void SetClickEvent(Click func, void* objForCallback) { m_OnClick = func; m_ObjForCallback = objForCallback; }
			DllExport void SetClickFocusEvents(Click cFunc, GotFocus gFunc, LostFocus lFunc, void* objForCallback);

			DllExport void SetBtnClippingPoints(SDL_Point notSel, SDL_Point sel, SDL_Point pressed);

			DllExport void SetScale(float s) override;

			DllExport CLabel& Content();

			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s = 1.0f) override;

			// geerbt von CFocusableObj
			DllExport virtual int Update(SDL_Event* e) override;

			// geerbt von GfxObject
			DllExport virtual int Render() override;
		};

	}

}