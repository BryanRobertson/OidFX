//======================================================================================
//! @file         Font.h
//! @brief        Font class. 
//! @author       Bryan Robertson
//! @date         Tuesday, 21 June 2005
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

#ifndef RENDERER_RENDERERFONT_H
#define RENDERER_RENDERERFONT_H

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include "Core/Handle.h"
#include "Core/Resource.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexStreamBinding.h"
#include "Renderer/VertexDeclaration.h"


//=========================================================================
// Forward declaration
//=========================================================================

namespace Renderer
{
	class IRenderer;
	class RenderState;
	class StateManager;
};

namespace Imaging
{
	class Image;
};



//namespace Renderer
namespace Renderer
{

    //=========================================================================
    // Types
    //=========================================================================
	enum EFontQuality
	{
		FONTQUALITY_DEFAULT = 0,
		FONTQUALITY_ANTIALIASED
	};

	enum EFontWeight
	{
		FONTWEIGHT_DEFAULT = FW_DONTCARE,
		FONTWEIGHT_BOLD = FW_BOLD,
		FONTWEIGHT_HEAVY = FW_HEAVY
	};


	//!@class	Font
	//!@brief	A font is a class that stores one of the system fonts as a texture	
	//!			and permits text to be rendered
	//!
	class Font : public Core::Resource
	{
		public:

			Font ( IRenderer& renderer, const Char* fontName, UInt fontSize, UInt fontWeight, UInt mipmapLevels,
					bool italic, UInt quality  );

			//Initialisation
			void Initialise( UInt fontWeight, UInt mipmapLevels, bool italic, UInt quality );

			//Write text
			void WriteText ( const Char* text, Float x, Float y, bool drawCursor = false, UInt cursorIndex = 0 );

			//Rendering
			void SetupRenderState ( StateManager& stateManager );
			void RenderDebugDisplay();
			
			//Core::Resource
			void Unload() {}
			
		private:

			//Private types
			struct TexCoordRect
			{
				Float top;
				Float bottom;
				Float left;
				Float right;
			};

			struct FontVertex
			{	
				Float	position[3];
				UInt32  colour;
				Float	texCoord0[2];
			};

			typedef std::vector<TexCoordRect> TexCoordStore;

			//Private methods

			//Initialisation methods
			void CreateFont( HDC hDC, HFONT& font, UInt fontWeight, bool italic, UInt quality, HFONT& oldFont );
			
			void CreateFontBitmap ( HDC hDC, Imaging::Image& image );

			void WriteTextIntoBitmap ( HDC hDC, Imaging::Image& image, Byte* bitmapData );
			
			void CreateFontTexture ( const Imaging::Image& image, UInt mipmapLevels  );
			
			void CreateVertexBuffer ( );

			void InitialiseRenderState ( );

			void CleanUp ( HDC hDC, HFONT font, HFONT oldFont );

			//Write a character to the vertex buffer
			void WriteStringToVertices ( const Char* character, UInt count, Float startX, Float& x, Float& y, 
											bool drawCursor, UInt cursorIndex, FontVertex*& vertices );
			void WriteCharToVertices ( Char character, Float x, Float y, FontVertex*& vertices );

			//Private data
			IRenderer&					  m_renderer;
			HTexture					  m_texture;
			VertexStreamBinding			  m_vertexStreamBinding;
			HVertexDeclaration			  m_vertexDeclaration;
			TexCoordStore				  m_texCoords;
			boost::shared_ptr<RenderState> m_renderState;
			UInt						  m_textureSize;
			UInt						  m_fontSize;
			UInt						  m_bufferSize;
			Float						  m_characterScale;

			UInt						  m_lastIndexUsed;
	};
	//End class Font


    //=========================================================================
    // Type definitions
    //=========================================================================
	typedef Core::Handle<Font> HFont;


};
//end namespace Renderer



#endif//#ifndef RENDERERFONT_H

