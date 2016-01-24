#include "IniFileIO.h"

#include <string>
#include <sstream>

#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace CKT::IO;

int CKT::IO::CIniFileIO::ReadFileToBuffer()
{
	if (!m_FileIsOpen)
		return 1;

	std::string temp = "";
	while (!m_FileStream.eof())
	{
		char c = m_FileStream.get();

		temp.push_back(c);

		if(c == '\n' || m_FileStream.eof())
		{ 
			temp.pop_back();
			m_FileContent.push_back(temp);
			temp.clear();
		}

	}

	return 0;
}

int CKT::IO::CIniFileIO::SplitLine(std::string line, STR_KEY_VAL_PAIR & keyValPair)
{
	std::string temp = "";
	char lastChar = 0;
	int ret = 0;
	for (int i = 0; i < (int)line.length(); i++)
	{
		char c = line[i];
		temp.push_back(c);

		if (lastChar == ':' && c == '=')
		{
			temp.pop_back();
			temp.pop_back();

			keyValPair.first = temp;
			ret++;

			temp.clear();
		}
		else if (i == line.length() - 1)
		{
			if (temp[0] == '\"' && temp.back() == '\"')
				temp = temp.substr(1, temp.length() - 2);
			else
				return 0;

			keyValPair.second = temp;
			ret++;

			temp.clear();
		}
		else if (lastChar == '/' && c == '/')
		{
			temp.pop_back();
			temp.pop_back();

			while (temp.back() == ' ' || temp.back() == '\t')
			{
				temp.pop_back();
			}

			if (temp[0] == '\"' && temp.back() == '\"')
				temp = temp.substr(1, temp.length() - 2);
			else
				return 0;

			keyValPair.second = temp;
			ret++;

			temp.clear();

			break;
		}

		lastChar = c;
	}

	return ret;
}

void CKT::IO::CIniFileIO::MakeEntry(STR_KEY_VAL_PAIR & keyValPair, int lineNum)
{
	SEntry entry = { 0 };
	entry.Line = lineNum;
	entry.Changed = false;
	entry.Key = keyValPair.first;
	entry.Val = keyValPair.second;

	m_EntryMap.insert(ENTRY_VAL_PAIR(entry.Key, entry));
}

void CKT::IO::CIniFileIO::MakeCaptionEntry(std::string cap)
{
	m_FileData.insert(CAPTION_ENTRY_PAIR(cap, m_EntryMap));

	m_EntryMap.clear();
}

CIniFileIO::CIniFileIO()
{
}

CIniFileIO::~CIniFileIO()
{
}

int CKT::IO::CIniFileIO::Open(std::string file)
{
	m_FileName = file;

	m_FileStream.open(m_FileName.c_str(), std::ios::in);

	m_FileIsOpen = m_FileStream.is_open();

	if (!m_FileIsOpen)
		return 1;

	return 0;
}

void CKT::IO::CIniFileIO::Close()
{
	m_FileStream.close();

	m_FileIsOpen = false;
}

void CKT::IO::CIniFileIO::Clear()
{
	m_FileContent.clear();
	m_FileData.clear();

	this->Close();
}

int CKT::IO::CIniFileIO::Read()
{
	if (!m_FileIsOpen)
		return 1;

	ReadFileToBuffer();
	int lineNum = -1;
	int errors = 0;
	std::string caption = "";
	std::string lastCaption = "";
	bool first = true;
	bool correctEnd = false;
	for each (std::string line in m_FileContent)
	{
		lineNum++;

		if (line.empty() || 
			(line[0] == '/' && line[1] == '/'))
			continue;
		
		STR_KEY_VAL_PAIR splits;
		splits.first = splits.second = "";
		if (line[0] == '[' && line.back() == ']')
		{
			caption = line.substr(1, line.length() - 2);

			if (first)
			{
				first = false;
				lastCaption = caption;
			}
		}
		else if (SplitLine(line, splits) == 2)
		{
			if (!caption.empty() && !splits.first.empty() && !splits.second.empty())
			{
				MakeEntry(splits, lineNum);
			}
			else
			{
				errors++;
				continue;
			}
		}
		else
		{
			errors++;
			continue;
		}

		if (!(caption.compare(lastCaption) == 0))
		{
			MakeCaptionEntry(lastCaption);
			lastCaption = caption;
		}

		if (line.compare("[END]") == 0)
		{
			correctEnd = true;
			break;
		}

	}

	if (!correctEnd)
		errors++;

	return errors;
}

CKT::IO::CIniFileIO::ENTRY_MAP CKT::IO::CIniFileIO::GetAllEntrys(std::string cap)
{
	CAPTION_IT itCap = m_FileData.find(cap);
	if (itCap != m_FileData.end())
	{
		return itCap->second;
	}

	return ENTRY_MAP();
}

std::string CKT::IO::CIniFileIO::GetEntry(std::string cap, std::string ent)
{
	CAPTION_IT itCap = m_FileData.find(cap);
	if (itCap != m_FileData.end())
	{
		m_EntryMap.clear();
		m_EntryMap = itCap->second;
		ENTRY_IT itEntry = m_EntryMap.find(ent);
		if (itEntry != m_EntryMap.end())
		{
			return itEntry->second.Val;
		}
	}

	return std::string("");
}

int CKT::IO::CIniFileIO::GetEntryAsInt(std::string cap, std::string ent)
{
	std::string temp = GetEntry(cap, ent);
	if (temp != "")
	{
		return std::stoi(temp);
	}

	return 0;
}

float CKT::IO::CIniFileIO::GetEntryAsFloat(std::string cap, std::string ent)
{
	std::string temp = GetEntry(cap, ent);
	if (temp != "")
	{
		return std::stof(temp);
	}

	return 0.0f;
}

bool CKT::IO::CIniFileIO::GetEntryAsBool(std::string cap, std::string ent)
{
	std::string temp = GetEntry(cap, ent);
	if (temp != "")
	{
		bool res = false;
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		std::istringstream iss(temp);
		iss >> std::boolalpha >> res;
		return res;
	}

	return false;
}

int CKT::IO::CIniFileIO::Write()
{
	if (!m_DataChanged)
		return 0;

	m_FileStream.close();
	m_FileStream.open(m_FileName.c_str(), std::ios::out);
	if (!m_FileStream.is_open())
	{
		m_FileIsOpen = false;
		return 2;
	}

	for each (CAPTION_ENTRY_PAIR captionPair in m_FileData)
	{
		for each (ENTRY_VAL_PAIR entryPair in captionPair.second)
		{
			if (entryPair.second.Changed)
			{
				std::string temp = entryPair.second.Key + ":=\"" + entryPair.second.Val + "\"";
				m_FileContent[entryPair.second.Line] = temp;
			}
		}
	}

	for each(std::string line in m_FileContent)
	{
		m_FileStream.write(line.c_str(), line.length());
		m_FileStream.write("\n", 1);
	}

	return 0;
}

void CKT::IO::CIniFileIO::ChangeEntry(std::string cap, std::string ent, std::string val)
{
	CAPTION_IT itCap = m_FileData.find(cap);
	if (itCap != m_FileData.end())
	{
		m_EntryMap.clear();
		m_EntryMap = itCap->second;
		m_FileData.erase(itCap->first);

		ENTRY_IT itEntry = m_EntryMap.find(ent);
		if (itEntry != m_EntryMap.end())
		{
			itEntry->second.Val = val;
			itEntry->second.Changed = true;
			m_DataChanged = true;
		}

		if (itEntry->second.Changed)
		{
			m_FileData.insert(CAPTION_ENTRY_PAIR(cap, m_EntryMap));
		}
	}
}

void CKT::IO::CIniFileIO::ChangeEntry(std::string cap, std::string ent, int val)
{
	ChangeEntry(cap, ent, std::to_string(val));
}

void CKT::IO::CIniFileIO::ChangeEntry(std::string cap, std::string ent, float val)
{
	ChangeEntry(cap, ent, std::to_string(val));
}

void CKT::IO::CIniFileIO::ChangeEntry(std::string cap, std::string ent, bool val)
{
	std::string temp = val ? "TRUE" : "FALSE";
	ChangeEntry(cap, ent, temp);
}
