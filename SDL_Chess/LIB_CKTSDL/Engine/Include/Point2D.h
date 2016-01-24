#pragma once

#include "Common.h"

namespace CKT
{
	class CPoint2D
	{
	public:
		int X = 0;
		int Y = 0;

	public:
		DllExport CPoint2D();
		DllExport CPoint2D(int x, int y);
		DllExport ~CPoint2D();
	};

}
