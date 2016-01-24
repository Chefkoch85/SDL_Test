#pragma once

#include "Progressbar.h"

namespace CKT
{
	namespace GUI
	{
		class CProgressbarH : public CProgressbar
		{
		public:
			DllExport CProgressbarH();
			DllExport ~CProgressbarH();

			DllExport int Render() override;
		};

	}

}
