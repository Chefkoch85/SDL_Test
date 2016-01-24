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
			CBtn();
			~CBtn();

			bool& IsPressed() { return m_IsPressed; }
			bool IsDown() {	return m_IsDown; }
			bool IsUp() { return m_IsUp; }

			void ClickEventOnPress(bool on) { m_ClickEventOnPress = on; }

			void SetClickEvent(Click func, void* objForCallback) { m_OnClick = func; m_ObjForCallback = objForCallback; }
			void SetClickFocusEvents(Click cFunc, GotFocus gFunc, LostFocus lFunc, void* objForCallback);

			void SetBtnClippingPoints(SDL_Point notSel, SDL_Point sel, SDL_Point pressed);

			void SetScale(float s) override;

			CLabel& Content();

			virtual int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s = 1.0f) override;

			// geerbt von CFocusableObj
			virtual int Update(SDL_Event* e) override;

			// geerbt von GfxObject
			virtual int Render() override;
		};

	}

}