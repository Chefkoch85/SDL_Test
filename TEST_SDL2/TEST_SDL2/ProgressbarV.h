#pragma once

#include "Progressbar.h"

namespace CKT
{
	namespace GUI
	{
		class CProgressbarV : public CProgressbar
		{
		public:
			CProgressbarV();
			~CProgressbarV();

			int Render() override;
		};

	}

}

