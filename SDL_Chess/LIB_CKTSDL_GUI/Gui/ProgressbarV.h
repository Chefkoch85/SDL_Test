#pragma once

#include "Progressbar.h"

namespace CKT
{
	namespace GUI
	{
		class CProgressbarV : public CProgressbar
		{
		public:
			DllExport CProgressbarV();
			DllExport ~CProgressbarV();

			DllExport int Render() override;
		};

	}

}

