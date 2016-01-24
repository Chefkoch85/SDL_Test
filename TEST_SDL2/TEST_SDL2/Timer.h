#pragma once

#include "Common.h"

namespace CKT
{
	class CTimer
	{
	protected:
		bool m_IsStarted = false;
		bool m_IsStopped = true;
		bool m_IsPaused = false;

		Uint32 m_StartTicks = 0;
		Uint32 m_PausedTicks = 0;

	public:
		void Start();
		void Stop();
		void Pause();
		void Resume();

		bool IsStarted() { return m_IsStarted; }
		bool IsStopped() { return m_IsStopped; }
		bool IsPaused() { return m_IsPaused; }

		Uint32 GetTicks();

	public:
		CTimer();
		~CTimer();
	};

}
