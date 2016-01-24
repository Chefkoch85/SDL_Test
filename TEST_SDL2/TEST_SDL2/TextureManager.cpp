#include "TextureManager.h"

#include "Graphics.h"

#include "Cleanup.h"

CKT::GFX::CTextureManager* CKT::GFX::CTextureManager::m_Instance = nullptr;

CKT::GFX::CTextureManager::CTextureManager()
{
}


CKT::GFX::CTextureManager * CKT::GFX::CTextureManager::Instance()
{
	if(m_Instance)
		return m_Instance;

	m_Instance = new CTextureManager();
	return m_Instance;
}

CKT::GFX::CTextureManager::~CTextureManager()
{
	delete m_Instance;
}

std::vector<std::string> CKT::GFX::CTextureManager::GetTextureNames()
{
	std::vector<std::string> temp;

	for each(std::pair<std::string, PTEXTURE> pair in m_FileTexMap)
	{
		temp.push_back(pair.first);
	}

	return temp;
}

CKT::PTEXTURE CKT::GFX::CTextureManager::loadTexture(std::string file, PRENDERER ren)
{
	MAP_FILETEX::iterator it = m_FileTexMap.find(file);
	if (it != m_FileTexMap.end())
	{
		MAP_TEXFILE::iterator itTex = m_TexFileMap.find(it->second);
		if (itTex != m_TexFileMap.end())
		{
			m_TexCounter[itTex->first]++;
			return itTex->first;
		}
	}

	PTEXTURE pTex = CKT::GFX::loadTexture(file, ren);

	m_FileTexMap.insert(std::pair<std::string, PTEXTURE>(file, pTex));
	m_TexFileMap.insert(std::pair<PTEXTURE, std::string>(pTex, file));
	m_TexCounter.insert(std::pair<PTEXTURE, int>(pTex, 1));

	return pTex;
}

void CKT::GFX::CTextureManager::releaseTexture(CKT::PTEXTURE pTex)
{
	MAP_TEXCOUNT::iterator itCount = m_TexCounter.find(pTex);
	if (itCount != m_TexCounter.end())
		m_TexCounter[pTex]--;
	else
		return;

	MAP_TEXFILE::iterator itTex = m_TexFileMap.find(pTex);
	std::cout << itTex->second << " : " << m_TexCounter[pTex] << std::endl;
	
	//TODO: search error texture is deleted to early (visible after sec play)
	if (m_TexCounter[pTex] <= 0)
	{
		MAP_TEXFILE::iterator itTex = m_TexFileMap.find(pTex);
		std::string fileToDelete = "";
		if (itTex != m_TexFileMap.end())
		{
			fileToDelete = itTex->second;

			cleanup(itTex->first);
			//SDL_DestroyTexture(itTex->first);
			m_TexCounter.erase(itTex->first);
			m_TexFileMap.erase(pTex);
		}

		if (fileToDelete != "")
		{
			MAP_FILETEX::iterator it = m_FileTexMap.find(fileToDelete);
			if (it != m_FileTexMap.end())
			{
				m_FileTexMap.erase(it->first);
			}
		}
	}
	
}

