#pragma once

#include "Timer.h"

namespace CKT
{
	class CTimerOn : public CTimer
	{
	protected:
		Uint32 m_TicksToFinish = 0;
		bool m_IsFinishedOnce = false;
		
	public:
		DllExport void Start(int ticks = -1);
		DllExport void Reset();
		DllExport bool IsFinish();
		DllExport bool IsFinishOnce();

	public:
		DllExport CTimerOn();
		DllExport ~CTimerOn();
	};

}
