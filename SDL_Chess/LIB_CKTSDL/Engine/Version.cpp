#include "Include\Version.h"

using namespace CKT;

CVersion::CVersion()
{
	m_Major = m_Minor = m_Revision = m_Build = 0;
}


CVersion::CVersion(VERSION_NUM major)
{
	m_Major = major;
	m_Minor = m_Revision = m_Build = 0;
}

CKT::CVersion::CVersion(VERSION_NUM major, VERSION_NUM minor)
{
	m_Major = major;
	m_Minor = minor;
	m_Revision = m_Build = 0;
}

CKT::CVersion::CVersion(VERSION_NUM major, VERSION_NUM minor, VERSION_NUM revision)
{
	m_Major = major;
	m_Minor = minor;
	m_Revision = revision;
	m_Build = 0;
}

CKT::CVersion::CVersion(VERSION_NUM major, VERSION_NUM minor, VERSION_NUM revision, VERSION_NUM build)
{
	m_Major = major;
	m_Minor = minor;
	m_Revision = revision;
	m_Build = build;
}

CKT::CVersion::CVersion(std::string version)
{
	std::string temp = "";
	char curChar = 0, lastChar = 0;
	int numReady = 0;
	bool isLast = false;
	for (int i = 0; i < (int)version.length(); i++)
	{
		if (i == version.length() - 1)
			isLast = true;

		curChar = version[i];
		temp.push_back(curChar);

		if ((curChar == '.' && numReady == 0) || 
			(isLast && numReady == 0))
		{
			if (!isLast)
				temp.pop_back();

			m_Major = (VERSION_NUM)std::stoi(temp);
			numReady++;
			temp = "";
		}
		else if ((curChar == '.' && numReady == 1) || 
			(isLast && numReady == 1))
		{
			if (!isLast)
				temp.pop_back();

			m_Minor = (VERSION_NUM)std::stoi(temp);
			numReady++;
			temp = "";
		}
		else if ((curChar == '.' && numReady == 2) || 
			(isLast && numReady == 2))
		{
			if (!isLast)
				temp.pop_back();

			m_Revision = (VERSION_NUM)std::stoi(temp);
			numReady++;
			temp = "";
		}
		else if ((curChar == '.' && numReady == 3) || 
			(isLast && numReady == 3))
		{
			if (!isLast)
				temp.pop_back();

			m_Build = (VERSION_NUM)std::stoi(temp);
			numReady++;
			temp = "";
		}
	}
}

CVersion::~CVersion()
{
}

std::string CKT::CVersion::ToString() const
{
	std::string temp = "";
	temp += std::to_string(m_Major);
	temp += ".";
	temp += std::to_string(m_Minor);
	temp += ".";
	temp += std::to_string(m_Revision);
	temp += ".";
	temp += std::to_string(m_Build);

	return temp;
}
