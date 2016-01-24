#pragma once

#include "Progressbar.h"

namespace CKT
{
	namespace GUI
	{
		class CProgressbarH : public CProgressbar
		{
		public:
			CProgressbarH();
			~CProgressbarH();

			int Render() override;
		};

	}

}
