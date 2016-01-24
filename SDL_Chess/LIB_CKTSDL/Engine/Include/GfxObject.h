#pragma once

#include "Common.h"
#include "Util.h"
#include "ObjectBase.h"

#include "TextureManager.h"

namespace CKT
{
	namespace GFX
	{

		class CGfxObject : public CObjectBase
		{
		protected:
			
			PRENDERER m_pRenderer = nullptr;

			// current pos on screen
			float m_PosX = 0;
			float m_PosY = 0;

			// designed pos on screen (original)
			float m_DesignX = 0;
			float m_DesignY = 0;

			// size of the whole texture
			int m_TexWidth = 0;
			int m_TexHeight = 0;

			// size of one frame in the texture
			int m_AnimWidth = 0;
			int m_AnimHeight = 0;

			// size of the gfx object inclusive scaling
			float m_Width = 0;
			float m_Height = 0;
			
			// the original given size
			float m_DesignWidth = 0;
			float m_DesignHeight = 0;

			float m_ScaleX = 1.0f;
			float m_ScaleY = 1.0f;

			double m_Angle = 0.0;
			SDL_Point m_RotationCenter = { 0 };
			SDL_RendererFlip m_Flipping = SDL_RendererFlip::SDL_FLIP_NONE;

			PTEXTURE m_Texture = nullptr;
			
			int m_AlphaMod = 255;
			SDL_BlendMode m_BlendMode = SDL_BlendMode::SDL_BLENDMODE_BLEND;

			Uint32 m_lastTime = 0;
			int m_AnimStep = 0;
			int m_AnimStepX = 0;
			int m_AnimStepY = 0;
			int m_AnimTimesToPlay = -1;
			bool m_AnimActiv = false;

			int m_OffsetClipX = 0;
			int m_OffsetClipY = 0;
			SDL_Rect m_rClip = { 0 };

			bool m_IsVisible = true;
			bool m_UseRotate = false;

			DllExport virtual void _SetScale(float sx, float sy);

		public:
			DllExport virtual float& X() { return m_PosX; }
			DllExport virtual float& Y() { return m_PosY; }
			DllExport virtual void SetPos(float x, float y) { m_PosX = x; m_PosY = y; }
			
			//float& Scale() { return m_Scale; }
			DllExport virtual void SetScale(float s);
			DllExport virtual void SetScale(float sx, float sy);
			DllExport virtual void SetScaleX(float sx);
			DllExport virtual void SetScaleY(float sy);
			DllExport float GetScaleX() { return m_ScaleX; }
			DllExport float GetScaleY() { return m_ScaleY; }

			DllExport int& OffsetClipX() { return m_OffsetClipX; }
			DllExport int& OffsetClipY() { return m_OffsetClipY; }
			DllExport SDL_Rect& Clip() { return m_rClip; }

			DllExport bool& Visibility() { return m_IsVisible; }
			DllExport bool& UseRotate() { return m_UseRotate; }

			DllExport double& Angle() { return m_Angle; }
			DllExport SDL_RendererFlip& Flip() { return m_Flipping; }
			DllExport SDL_Point& Center() { return m_RotationCenter; }

			DllExport virtual float& Width() { return m_Width; }
			DllExport virtual float& Height() { return m_Height; }
			
			DllExport float GetDesignX() { return m_DesignX; }
			DllExport float GetDesignY() { return m_DesignY; }
			DllExport float GetDesignWidth() { return m_DesignWidth; }
			DllExport float GetDesignHeight() { return m_DesignHeight; }

			DllExport PTEXTURE Texture() { return m_Texture; }

			DllExport int& AlphaMod() { return m_AlphaMod; }
			DllExport SDL_BlendMode BlendMode() { return m_BlendMode; }

		public:

			DllExport CGfxObject();
			DllExport virtual ~CGfxObject();

			DllExport virtual int Init(PRENDERER ren, PTEXTURE tex, float x, float y, float s = 1.0f);
			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, float s = 1.0f);
			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s = 1.0f);
			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s = 1.0f);
			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, SDL_Rect clip, float s = 1.0f);

			DllExport virtual int Render();

			DllExport virtual void ResetAnimation();
			DllExport virtual int PlayAnimation(int beginn, int end, int speed, bool loop = true);
			DllExport virtual int PlayAnimation(int beginn, int end, int speed, int timesPlay);
		};

	}

}
