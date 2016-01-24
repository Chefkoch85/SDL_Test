#pragma once

#include <fstream>
#include <map>
#include <vector>

namespace CKT
{
	namespace IO
	{

		class CIniFileIO
		{
		private:
			struct SEntry
			{
				int Line;
				bool Changed;
				std::string Key;
				std::string Val;
			};

		public:
			typedef std::map<std::string, SEntry> ENTRY_MAP;
			typedef std::map<std::string, ENTRY_MAP> CAPTION_MAP;

			typedef ENTRY_MAP::iterator ENTRY_IT;
			typedef CAPTION_MAP::iterator CAPTION_IT;

			typedef std::vector<std::string> STRING_VEC;

			typedef std::pair<std::string, std::string> STR_KEY_VAL_PAIR;
			typedef std::pair<std::string, ENTRY_MAP> CAPTION_ENTRY_PAIR;
			typedef std::pair<std::string, SEntry> ENTRY_VAL_PAIR;

		private:
			std::fstream m_FileStream;

			std::string m_FileName = "";

			bool m_FileIsOpen = false;
			bool m_DataChanged = false;

			STRING_VEC m_FileContent;
			CAPTION_MAP m_FileData;
			ENTRY_MAP m_EntryMap;


		private:
			int ReadFileToBuffer();
			int SplitLine(std::string line, STR_KEY_VAL_PAIR& keyValPair);
			void MakeEntry(STR_KEY_VAL_PAIR& keyValPair, int lineNum);
			void MakeCaptionEntry(std::string cap);

		public:
			CIniFileIO();
			~CIniFileIO();

			// General use
		public:
			int Open(std::string file);
			void Close();

			bool IsOpen() { return m_FileIsOpen; }

			void Clear();

			// for IniFileIO read
		public:
			int Read();

			ENTRY_MAP GetAllEntrys(std::string cap);

			std::string GetEntry(std::string cap, std::string ent);
			
			int GetEntryAsInt(std::string cap, std::string ent);
			float GetEntryAsFloat(std::string cap, std::string ent);
			bool GetEntryAsBool(std::string cap, std::string ent);


			// for IniFileIO write
		public:
			int Write();

			void ChangeEntry(std::string cap, std::string ent, std::string val);
			void ChangeEntry(std::string cap, std::string ent, int val);
			void ChangeEntry(std::string cap, std::string ent, float val);
			void ChangeEntry(std::string cap, std::string ent, bool val);

		};

	}

}
