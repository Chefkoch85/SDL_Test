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
			void AddControl(CGUIBase* item);
			void AddControl(CFocusableObj* item);
			void AddControl(CLabel* item, int count);
			void RemoveControl(CGUIBase* item);
			void RemoveControl(CFocusableObj* item);
			CGUIBase* GetControlByName(std::string name);

		public:
			CGuiContainer();
			~CGuiContainer();

			virtual int Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s = 1.0f);
			virtual int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s = 1.0f);
			virtual void Init(PRENDERER ren, SDL_Color col, float x, float y, float w, float h);

			virtual void CalculatePositions();

			virtual void Update(SDL_Event* e);
			virtual int Render() override;
		};

	}

}