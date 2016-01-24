#pragma once

#include "FocusableObj.h"

#include <set>

namespace CKT
{
	namespace GUI
	{
		typedef std::set<CGUIBase*> GUI_DRAW_ELEM_SET;
		typedef std::set<CGUIBase*>::iterator GUI_DRAW_ELEM_IT;

		typedef std::set<CFocusableObj*> GUI_UPDATE_ELEM_SET;
		typedef std::set<CFocusableObj*>::iterator GUI_UPDATE_ELEM_IT;

		class CLabel;
		class CBtn;

		class CGuiContainer : public CGUIBase
		{
		protected:
			GUI_DRAW_ELEM_SET m_Content;
			GUI_UPDATE_ELEM_SET m_UpdateContent;

			bool m_KeyWasPressed = false;
			CBtn* m_SelectedItem = nullptr;

		public:
			DllExport void AddControl(CGUIBase* item);
			DllExport void AddControl(CFocusableObj* item);
			DllExport void AddControl(CLabel* item, int count);
			DllExport void RemoveControl(CGUIBase* item);
			DllExport void RemoveControl(CFocusableObj* item);
			DllExport CGUIBase* GetControlByName(std::string name);

		public:
			DllExport CGuiContainer();
			DllExport virtual ~CGuiContainer();

			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s = 1.0f);
			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s = 1.0f);
			DllExport virtual void Init(PRENDERER ren, SDL_Color col, float x, float y, float w, float h);

			DllExport virtual void CalculatePositions();

			DllExport virtual void Update(SDL_Event* e);
			DllExport virtual int Render() override;
		};

	}

}