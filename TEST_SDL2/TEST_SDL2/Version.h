#pragma once

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
		CVersion();
		CVersion(VERSION_NUM major);
		CVersion(VERSION_NUM major, VERSION_NUM minor);
		CVersion(VERSION_NUM major, VERSION_NUM minor, VERSION_NUM revision);
		CVersion(VERSION_NUM major, VERSION_NUM minor, VERSION_NUM revision, VERSION_NUM build);

		CVersion(std::string version);

		~CVersion();

		VERSION_NUM Major() const { return m_Major; }
		VERSION_NUM Minor() const { return m_Minor; }
		VERSION_NUM Revision() const { return m_Revision; }
		VERSION_NUM Build() const { return m_Build; }

		std::string ToString() const;
	};

}
