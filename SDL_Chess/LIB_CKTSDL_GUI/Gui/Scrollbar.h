#pragma once

#include "Btn.h"

#include "TimerOn.h"

namespace CKT
{
	namespace GUI
	{
		struct ScrollbarClip
		{
			SDL_Point btnNotSel;
			SDL_Point btnSel;
			SDL_Point btnPress;
		};
	

		class CScrollbar : public CFocusableObj
		{
		public:
			static const int STD_SCB_SIZE;

			typedef void(*ValueChanged)(void* self, CScrollbar& sender, CGuiEventArgs& args);

		protected:
			CBtn* m_btnPrev = nullptr;
			CBtn* m_btnNext = nullptr;
			CBtn* m_btnTrack = nullptr;

			float m_ScrollFactor = 1.0f;
			bool m_SnapToTicks = false;
			bool m_BtnWasPressed = false;

			bool m_CalcDataOk = false;
			float m_PixelRange = 0.0f;
			float m_ValueRange = 0.0f;
			float m_PixelStart = 0.0f;
			int m_Min = 0;
			int m_Max = 255;
			int m_Value = 0;
			int m_OldValue = 0;

			CTimerOn m_ScrollDelayTimer;
			int m_ScrollDelay = 250;

			ValueChanged m_OnValueChanged = nullptr;

		public:
			DllExport CScrollbar();
			DllExport virtual ~CScrollbar();

		public:
			DllExport int& Min() { m_CalcDataOk = false; return m_Min; }
			DllExport int& Max() { m_CalcDataOk = false; return m_Max; }

			DllExport virtual void SetBounds(float x, float y, float w = 0, float h = 0) = 0;

			DllExport bool& SnapToTicks() { return m_SnapToTicks; }
			DllExport int& ScrollDelay() { return m_ScrollDelay; }

		protected:
			DllExport virtual float& X() { return m_PosX; }
			DllExport virtual float& Y() { return m_PosY; }
			DllExport virtual float& Width() { return m_Width; }
			DllExport virtual float& Height() { return m_Height; }
			DllExport virtual void SetPos(float x, float y) { }

		public:
			DllExport float GetX() { return m_PosX; }
			DllExport float GetY() { return m_PosY; }
			DllExport float GetW() { return m_Width; }
			DllExport float GetH() { return m_Height; }

		public:
			DllExport void SetValueEvent(ValueChanged func, void* objForCallback) { m_OnValueChanged = func; m_ObjForCallback = objForCallback; }
			DllExport void SetValueFocusEvents(ValueChanged vFunc, GotFocus gFunc, LostFocus lFunc, void* objForCallback);

			DllExport void SetScrollFactor(float factor) { m_ScrollFactor = factor; }
			DllExport void SetBtnClippingPoints(ScrollbarClip prev, ScrollbarClip next, ScrollbarClip track);

			DllExport int GetValue() { return m_Value; }
			DllExport virtual void SetValue(int val) = 0;

		public:
			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float w, float h) = 0;
			DllExport virtual int Update(SDL_Event* e) = 0;
			DllExport virtual int Render() override;
		};

	}

}