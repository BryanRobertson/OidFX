//======================================================================================
//! @file         EffectViewerApplication.h
//! @brief        Class encapsulating the effect viewer application
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 09 June 2005
//! @copyright    Bryan Robertson 2005
//
//				  This file is part of OidFX Engine.
//
//  			  OidFX Engine is free software; you can redistribute it and/or modify
//  			  it under the terms of the GNU General Public License as published by
//  			  the Free Software Foundation; either version 2 of the License, or
//  			  (at your option) any later version.
//
//  			  OidFX Engine is distributed in the hope that it will be useful,
//  			  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  			  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  			  GNU General Public License for more details.
//
//  			  You should have received a copy of the GNU General Public License
//  			  along with OidFX Engine; if not, write to the Free Software
//  			  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================

#ifndef EFFECTVIEWER_EFFECTVIEWERAPPLICATION_H
#define EFFECTVIEWER_EFFECTVIEWERAPPLICATION_H


#include "OidFX/GameApplication.h"
#include "Renderer/Font.h"
#include "EffectViewer/EffectDisplayer.h"


//namespace EffectViewer
namespace EffectViewer
{


	//!@class	EffectViewerApplication
	//!@brief	Class encapsulating the effect viewer application
	class EffectViewerApplication : public OidFX::GameApplication
	{
		public:

			EffectViewerApplication();

			void PostInitialise();
			void InitialiseScene();
			void UpdateScene(Float timeElapsed);

			void Render();

		private:

			Renderer::HFont			m_font;

			boost::shared_ptr<EffectDisplayer> m_effectDisplayer;
	};
	//End EffectViewer


};
//end namespace EffectViewer


#endif
//#ifndef EFFECTVIEWERAPPLICATION_H
