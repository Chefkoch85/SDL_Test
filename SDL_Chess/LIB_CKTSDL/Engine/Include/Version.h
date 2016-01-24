#pragma once

#include "Common.h"
#include <string>

namespace CKT
{

	class CVersion
	{
	public:
		typedef unsigned char VERSION_NUM;

	private:
		VERSION_NUM m_Major = 0;
		VERSION_NUM m_Minor = 0;
		VERSION_NUM m_Revision = 0;
		VERSION_NUM m_Build = 0;

	public:
		DllExport CVersion();
		DllExport CVersion(VERSION_NUM major);
		DllExport CVersion(VERSION_NUM major, VERSION_NUM minor);
		DllExport CVersion(VERSION_NUM major, VERSION_NUM minor, VERSION_NUM revision);
		DllExport CVersion(VERSION_NUM major, VERSION_NUM minor, VERSION_NUM revision, VERSION_NUM build);

		DllExport CVersion(std::string version);

		DllExport ~CVersion();

		DllExport VERSION_NUM Major() const { return m_Major; }
		DllExport VERSION_NUM Minor() const { return m_Minor; }
		DllExport VERSION_NUM Revision() const { return m_Revision; }
		DllExport VERSION_NUM Build() const { return m_Build; }

		DllExport std::string ToString() const;
	};

}
