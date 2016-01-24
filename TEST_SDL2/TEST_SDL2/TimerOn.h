#pragma once

#include "Timer.h"

namespace CKT
{
	class CTimerOn : public CTimer
	{
	protected:
		int m_TicksToFinish = 0;
		bool m_IsFinishedOnce = false;
		
	public:
		void Start(int ticks = -1);
		void Reset();
		bool IsFinish();
		bool IsFinishOnce();

	public:
		CTimerOn();
		~CTimerOn();
	};

}
