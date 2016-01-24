#pragma once

#include "Common.h"
#include "Util.h"
#include <map>
#include <vector>

namespace CKT
{
	namespace GFX
	{
		typedef int TEX_ID;
		typedef std::map<std::string, PTEXTURE> MAP_FILETEX;
		typedef std::map<PTEXTURE, std::string> MAP_TEXFILE;
		typedef std::map<PTEXTURE, int> MAP_TEXCOUNT;

		class CTextureManager
		{
		private:
			static CTextureManager* m_Instance;
			MAP_FILETEX m_FileTexMap;
			MAP_TEXFILE m_TexFileMap;
			MAP_TEXCOUNT m_TexCounter;


			CTextureManager();

		public:
			DllExport static CTextureManager* Instance();

			DllExport ~CTextureManager();

			DllExport int GetTextureCount() { return m_FileTexMap.size(); }
			DllExport std::vector<std::string> GetTextureNames();

			DllExport PTEXTURE loadTexture(std::string file, PRENDERER ren);
			DllExport void releaseTexture(CKT::PTEXTURE pTex);

		};

	}

}
