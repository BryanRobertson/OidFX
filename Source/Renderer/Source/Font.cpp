//======================================================================================
//! @file         Font.cpp
//! @brief        Font class. Class that creates a texture from one of the system fonts
//!               and allows characters from the font to be drawn to the screen
//!               
//!				  
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


#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexData.h"
#include "Renderer/RenderState.h"
#include "Renderer/StateManager.h"
#include "Renderer/Font.h"
#include "Imaging/Image.h"
#include <windows.h>


using namespace Renderer;



//=========================================================================
//! @function    Font::Font
//! @brief       Construct a font
//!              
//! @param       renderer		[in] Reference to the renderer 
//! @param       fontName		[in] Name of the font
//! @param       fontSize		[in] Size of the font in points
//! @param		 fontWeight		[in] Member of the EFontWeight enumeration
//!									 indicating the weight of the font (i.e, bold, heavy, etc)
//! @param		 mipmapLevels	[in] Number of mip map levels
//! @param		 italic			[in] Specifies whether the font is italic or not
//! @param       quality		[in] Quality of the texture. Valid values consist of members
//!									 of the EFontQuality enumeration
//!              
//! @throw       Core::RuntimeError if the font could not be created
//=========================================================================
Font::Font ( IRenderer& renderer, const Char* fontName, UInt fontSize, UInt fontWeight, UInt mipmapLevels,
			  bool italic, UInt quality )
: Core::Resource(fontName), m_fontSize(fontSize), m_renderer(renderer), m_bufferSize(50), m_characterScale(1.0f)
{

	debug_assert ( fontName, "Null pointer passed as font filename!" );

	std::clog << __FUNCTION__ << ": Loading font " << fontName 
			  << ". Size: " << fontSize << std::endl;

	//Set the texture size to an appropriate level based on the font size
	//We need a texture big enough to hold the font, that isn't so big
	//that it wastes memory with empty space
	//
	//Memory shouldn't be a huge issue anyway, since we're going to 
	//store the font in a DXT compressed texture
	if ( (fontSize >= 60) 
		 && (m_renderer.GetDeviceProperty (CAP_TEXTURE_MAX_WIDTH) >= 2048)
		 && (m_renderer.GetDeviceProperty (CAP_TEXTURE_MAX_HEIGHT) >= 2048) )
	{
		m_textureSize = 2048;
	}
	else if ( fontSize >= 40 )
	{
		m_textureSize = 1024;
	}
	else if ( fontSize >= 10 )
	{
		m_textureSize = 512;
	}
	else 
	{
		m_textureSize = 256;
	}

	Initialise( fontWeight, mipmapLevels, italic, quality);
}
//End Font::Font



//=========================================================================
//! @function    Font::WriteText
//! @brief       Write text to the screen
//!              
//! @param       text		 [in] Text to write 
//! @param       x			 [in] x start position of the text
//! @param       y			 [in] y start position of the text
//! @param       drawCursor	 [in] Indicates whether a cursor will be drawn
//! @param       cursorIndex [in] Character index at which to draw the cursor
//!              
//=========================================================================
void Font::WriteText ( const Char* text, Float x, Float y, bool drawCursor, UInt cursorIndex )
{
	debug_assert ( text, "text is null!" );

	//Console variable that allows text drawing to be disabled
	static Core::ConsoleBool dbg_disabletext( "dbg_disabletext", false );

	if ( dbg_disabletext )
	{
		return;
	}
	
	UInt length = strlen(text);

	if ( drawCursor )
	{
		++length;
	}

	UInt charsToWrite = length;
	UInt currentIndex = 0;
	UInt maxBufferChars = m_bufferSize / 6;
	Float xPos = x; 
	Float yPos = y;
	
	while ( charsToWrite )
	{
		if ( charsToWrite > maxBufferChars )
		{
			ScopedVertexBufferLock lock = m_vertexStreamBinding.GetStream(0)->LockAll(LOCK_DISCARD);

			if ( !lock )
			{
				std::cerr << __FUNCTION__ ": Lock failed!" << std::endl;
				return;
			}

			FontVertex* vertexPointer = reinterpret_cast<FontVertex*>(lock.GetLockPointer());
			WriteStringToVertices ( text + currentIndex, maxBufferChars, x, xPos, yPos, drawCursor, cursorIndex, 
									vertexPointer );
			currentIndex += maxBufferChars;
			charsToWrite -= maxBufferChars;

			lock.Release();

			m_renderer.DrawPrimitive ( PRIM_TRIANGLELIST, 0, m_bufferSize ); 
		}
		else
		{
			ScopedVertexBufferLock lock = m_vertexStreamBinding.GetStream(0)->Lock ( 0, charsToWrite * 6, LOCK_DISCARD );

			if ( !lock )
			{
				std::cerr << __FUNCTION__ ": Lock failed!" << std::endl;
				return;
			}

			FontVertex* vertexPointer = reinterpret_cast<FontVertex*>(lock.GetLockPointer());
			WriteStringToVertices ( text + currentIndex, charsToWrite, x, xPos, yPos, drawCursor, 
									cursorIndex, vertexPointer );

			lock.Release();

			m_renderer.DrawPrimitive ( PRIM_TRIANGLELIST, 0, charsToWrite * 6 );
			charsToWrite = 0;
		}
	}
}
//End Font::WriteText



//=========================================================================
//! @function    Font::WriteStringToVertices
//! @brief       Write a string to the vertex buffer
//!              
//!				 Handles spaces, tabs, newlines, etc
//!
//! @param       character   [in] Character to write
//! @param		 count		 [in] Number of characters to write
//! @param		 startX		 [in] Start X position
//! @param       x		     [in/out] X position, updated with the new position when writing has completed
//! @param       y		     [in/out] Y position, updated with the new position when writing has completed
//! @param		 drawCursor  [in] Indicates whether or not a cursor should be drawn
//! @param		 cursorIndex [in] Index at which cursor should be drawn
//! @param		 vertices	 [in/out] Pointer to vertices to be written. Pointer is advanced as characters are written
//=========================================================================
void Font::WriteStringToVertices ( const Char* text, UInt count, Float startX, Float& x, Float& y, bool drawCursor, UInt cursorIndex,
								  FontVertex*& vertices)
{

	Float xPos = x;
	Float yPos = y;

	for (  UInt i=0; i<count; ++i )
	{
		
		TexCoordRect& rect = m_texCoords[*text];

		switch ( *text )
		{
			case '\n':
				xPos = startX;
				yPos += (rect.bottom - rect.top) * m_textureSize * m_characterScale;

				//Write a space, to pad out the vertex buffer
				//When the buffer is drawn, it's assumed that the number of vertices 
				//is equal to the length of the text
				WriteCharToVertices( ' ', xPos, yPos, vertices );
				break;

			case '\0':
				x = xPos;
				y = yPos;
				return;

			default:
				WriteCharToVertices( *text, xPos, yPos, vertices );

				if ( drawCursor && (i==cursorIndex) )
				{
					WriteCharToVertices( '|', xPos - 0.5 * ((rect.right-rect.left) * m_textureSize * m_characterScale), yPos, vertices );
				}

			case ' ':
				xPos += (rect.right - rect.left) * m_textureSize * m_characterScale;
				break;

		}

		++text;
	}

	x = xPos;
	y = yPos;
}
//End Font::WriteStringToVertices



//=========================================================================
//! @function    Font::WriteCharToVertices
//! @brief       Write a character to the vertex buffer
//!              
//! @param       character [in] Character to write
//! @param       x		   [in] X position
//! @param       y		   [in] Y position
//! @param		 vertices  [in/out]	Array of vertices to write into. Pointer is advanced as vertices are written
//=========================================================================
void Font::WriteCharToVertices ( Char character, Float x, Float y, Font::FontVertex*& vertex )
{
	TexCoordRect& rect = m_texCoords[character];

	Float width = ((rect.right - rect.left) * static_cast<Float>(m_textureSize)) * m_characterScale; 
	Float height = ((rect.bottom - rect.top) * static_cast<Float>(m_textureSize)) * m_characterScale;

	vertex->position[0] = x;
	vertex->position[1] = y - height;
	vertex->position[2] = 1.0f;
	vertex->colour = 0xFFFFFFFF;
	vertex->texCoord0[0] = rect.left;
	vertex->texCoord0[1] = rect.top;
	++vertex;

	vertex->position[0] = x;
	vertex->position[1] = y;
	vertex->position[2] = 1.0f;
	vertex->colour = 0xFFFFFFFF;
	vertex->texCoord0[0] = rect.left;
	vertex->texCoord0[1] = rect.bottom;
	++vertex;

	vertex->position[0] = x + width;
	vertex->position[1] = y - height;
	vertex->position[2] = 1.0f;
	vertex->colour = 0xFFFFFFFF;
	vertex->texCoord0[0] = rect.right;
	vertex->texCoord0[1] = rect.top;
	++vertex;

	vertex->position[0] = x + width;
	vertex->position[1] = y - height;
	vertex->position[2] = 1.0f;
	vertex->colour = 0xFFFFFFFF;
	vertex->texCoord0[0] = rect.right;
	vertex->texCoord0[1] = rect.top;
	++vertex;

	vertex->position[0] = x;
	vertex->position[1] = y;
	vertex->position[2] = 1.0f;
	vertex->colour = 0xFFFFFFFF;
	vertex->texCoord0[0] = rect.left;
	vertex->texCoord0[1] = rect.bottom;
	++vertex;

	vertex->position[0] = x + width;
	vertex->position[1] = y;
	vertex->position[2] = 1.0f;
	vertex->colour = 0xFFFFFFFF;
	vertex->texCoord0[0] = rect.right;
	vertex->texCoord0[1] = rect.bottom;
	++vertex;

}
//End Font::WriteToVertices



//=========================================================================
//! @function    Font::SetupRenderState
//! @brief       Set up the render state for rendering the font
//!              
//!              
//=========================================================================
void Font::SetupRenderState ( StateManager& stateManager )
{

	stateManager.ActivateVertexStreamBinding ( m_vertexStreamBinding );
	stateManager.ActivateVertexDeclaration ( m_vertexDeclaration );
	stateManager.ActivateRenderState ( *m_renderState );

}
//End Font::SetupRenderState



//=========================================================================
//! @function    Font::RenderDebugDisplay
//! @brief       Render a debug display of the font texture
//=========================================================================
void Font::RenderDebugDisplay ()
{
	ScopedVertexBufferLock lock = m_vertexStreamBinding.GetStream(0)->Lock( 0, 4*sizeof(FontVertex), LOCK_DISCARD );

	if ( !lock )
		return;

	FontVertex* vertex = static_cast<FontVertex*>(lock.GetLockPointer());

	Float halfWidth  = static_cast<Float>(m_renderer.ScreenWidth())  / 2;
	Float halfHeight = static_cast<Float>(m_renderer.ScreenHeight()) / 2;
	Float logoWidth  = halfHeight;
	Float logoHeight = halfHeight;

	vertex->position[0] = halfWidth - logoWidth;
	vertex->position[1] = halfHeight - logoWidth;
	vertex->position[2] = 1.0f;
	vertex->colour = 0xFFFFFFFF;
	vertex->texCoord0[0] = 0.0f;
	vertex->texCoord0[1] = 0.0f;
	++vertex;
	
	vertex->position[0] = halfWidth - logoWidth;
	vertex->position[1] = halfHeight + logoWidth;
	vertex->position[2] = 1.0f;
	vertex->colour = 0xFFFFFFFF;
	vertex->texCoord0[0] = 0.0f;
	vertex->texCoord0[1] = 1.0f;
	++vertex;
	
	vertex->position[0] = halfWidth + logoWidth;
	vertex->position[1] = halfHeight - logoWidth;
	vertex->position[2] = 1.0f;
	vertex->colour = 0xFFFFFFFF;
	vertex->texCoord0[0] = 1.0f;
	vertex->texCoord0[1] = 0.0f;
	++vertex;
	
	vertex->position[0] = halfWidth + logoWidth;
	vertex->position[1] = halfHeight + logoWidth;
	vertex->position[2] = 1.0f;
	vertex->colour = 0xFFFFFFFF;
	vertex->texCoord0[0] = 1.0f;
	vertex->texCoord0[1] = 1.0f;

	lock.Release();

	//m_renderer.SetColour ( STATE_DIFFUSEMATERIALCOLOUR, Renderer::Colour4f ( (UInt)0, 0, 0 ) ); 
	//m_renderer.DrawPrimitive ( PRIM_TRIANGLESTRIP, 0, 4 ); 
	//m_renderer.SetColour ( STATE_DIFFUSEMATERIALCOLOUR, Renderer::Colour4f ( (UInt)255, 255, 255 ) );
	m_renderer.DrawPrimitive ( PRIM_TRIANGLESTRIP, 0, 4 );
}
//End Font::RenderDebugDisplay



//=========================================================================
//! @function    Font::Initialise
//! @brief       Do all initialisation of the font.
//!				 Uses private member functions to do all the hard work
//!              
//! @param		 fontWeight	  [in] 
//! @param       mipmapLevels [in]
//! @param       italic		  [in]
//! @param       quality	  [in]
//!              
//! @throw       Core::RuntimeError if the texture could not be created
//=========================================================================
void Font::Initialise ( UInt fontWeight, UInt mipmapLevels, bool italic, UInt quality )
{

	HDC		hDC = CreateCompatibleDC( 0 );  //Handle to the device context used in creating the texture
	HFONT	font = 0;						//Handle to system font
	HFONT	oldFont = 0;					//hDC's previous font, used for cleanup
	Imaging::Image image( m_textureSize, m_textureSize, 0, Imaging::PXFMT_A8R8G8B8 ); //Image to store the font

	if ( !hDC )
	{
		throw Core::RuntimeError ( "Couldn't create device context!", GetLastError(), __FILE__, __FUNCTION__, __LINE__ );
	}

	//Set the text colour to white
	if ( SetTextColor ( hDC, RGB(255,255,255) ) == CLR_INVALID )
	{
		throw Core::RuntimeError ( "Couldn't set text colour!", GetLastError(), __FILE__, __FUNCTION__, __LINE__);
	}

	//Set the background colour and foreground colour for the DC
	if ( !SetBkColor( hDC, RGB(0, 0, 0) ) )
	{
		throw Core::RuntimeError ( "Couldn't set text background colour!", GetLastError(), __FILE__, __FUNCTION__, __LINE__);
	}

	//Align the text to the top of the rectangle
	if ( SetTextAlign( hDC, TA_TOP ) == GDI_ERROR )
	{
		throw Core::RuntimeError ( "Couldn't set text alignment!", GetLastError(), __FILE__, __FUNCTION__, __LINE__);
	}

	//Set the mapping mode
	// MM_TEXT - Each logical unit is converted to 1 device pixel. Positive x is to the right; positive y is down. 
	if ( !SetMapMode( hDC, MM_TEXT) )
	{
		throw Core::RuntimeError ( "Couldn't set mapping mode!", GetLastError(), __FILE__, __FUNCTION__, __LINE__);
	}


	try
	{
		CreateFont		   ( hDC, font, fontWeight, italic, quality, oldFont );
		CreateFontBitmap   ( hDC, image );
		CreateFontTexture  ( image, mipmapLevels );
		CreateVertexBuffer ( );
		InitialiseRenderState ( );
	}
	catch (...)
	{
		CleanUp ( hDC, font, oldFont );
		throw;
	}

	CleanUp(hDC, font, oldFont);

}
//End Font::Initialise



//=========================================================================
//! @function    Font::CreateFont
//! @brief       Create the system font object
//!              
//! @param       hDC		[in] Device context
//! @param       font		[out] Handle to font
//! @param		 fontWeight [in]  Weight of the font (i.e, default, bold, heavy)
//! @param       italic		[in] Whether the font is italic or not
//! @param       quality	[in] Quality of the font
//! @param		 oldFont	[out] Font that was previously selected into the device context
//!              
//! @throw       Core::RuntimeError if failed
//=========================================================================
void Font::CreateFont ( HDC hDC, HFONT& font, UInt fontWeight, bool italic, UInt quality, HFONT& oldFont )
{

	DWORD fontQuality = 0;

	if ( quality == FONTQUALITY_DEFAULT )
	{
		fontQuality = DEFAULT_QUALITY;
	}
	else
	{
		fontQuality = ANTIALIASED_QUALITY;
	}

	//Increase the font size a bit on systems that don't use large fonts
	//Also, decrease the boldness
	//
	//This is a bit of a hack, but I want the fonts to look the same
	//on both
	if ( GetDeviceCaps(hDC, LOGPIXELSY) == 96 )
	{
		m_fontSize += (m_fontSize/3);
	}

	//Change the font size and font scale appropriately depending on the
	//size of the font.
	//Smaller fonts look better if you render the text at a higher resolution and just scale down
	if ( m_fontSize < 10 )
	{
		m_characterScale = static_cast<Float>(m_fontSize) / 10.0f;
		m_fontSize = 10;
	}

	if ( m_fontSize > 35 )
	{
		m_characterScale = static_cast<Float>(m_fontSize) / 35.0f;
		m_fontSize = 35;
	}

	//Convert the font size in points to pixels
	m_fontSize = MulDiv ( m_fontSize, static_cast<Int>(GetDeviceCaps(hDC, LOGPIXELSY)), 72 );



	font = ::CreateFont ( m_fontSize,		//Height
						  0,				//Width
						  0,				//Angle of escapement
						  0,				//Orientation
						  fontWeight,		//Font weight
						  italic,			//Italic?
						  0,				//Underline
						  0,				//Strikethrough
						  DEFAULT_CHARSET,  //Character set
						  OUT_DEFAULT_PRECIS, //Precision
						  CLIP_DEFAULT_PRECIS, //Clipping precision
						  fontQuality,		//Quality
						  VARIABLE_PITCH,	//Pitch
						  Name().c_str()
						  );

	if ( !font )
	{
		throw Core::RuntimeError ( "Error, couldn't create font!", GetLastError(), __FILE__, __FUNCTION__, __LINE__ );
	}

	//Select the font into the device context, and store the old font in oldFont
	oldFont = static_cast<HFONT>(SelectObject( hDC, font ) ); 
	
	if ( (oldFont == 0) || (oldFont == HGDI_ERROR) )
	{
		throw Core::RuntimeError ( "Error, couldn't select font into hDC", GetLastError(), __FILE__, __FUNCTION__, __LINE__ );
	}
}
//End Font::CreateFont



//=========================================================================
//! @function    Font::CreateFontBitmap
//! @brief       Create the bitmap for the font, and store it in an image
//!				 Also creates 
//!              
//! @param       hDC			[in] Handle to the device context with which the
//!									 bitmap will be used
//! @param       image			[out] Image that will store the contents of the bitmap 
//!              
//! @return      
//! @throw       
//=========================================================================
void Font::CreateFontBitmap ( HDC hDC, Imaging::Image& image )
{

	HBITMAP		bitmap = 0;
	HBITMAP		oldBitmap = 0;
	Byte*		bitmapData = 0;
	BITMAPINFO	info;

	//Clear out the info structure
	ZeroMemory ( &info.bmiHeader, sizeof(info.bmiHeader) );
	
	//Setup the info structure
	info.bmiHeader.biSize = sizeof(info.bmiHeader);
	info.bmiHeader.biWidth =  static_cast<Int>(m_textureSize);
	info.bmiHeader.biHeight = -static_cast<Int>(m_textureSize); //Negative height puts the origin at the top
																//rather than the bottom
	
	info.bmiHeader.biPlanes = 1;								//Must be set to 1
	info.bmiHeader.biBitCount = 32;
	info.bmiHeader.biCompression = BI_RGB;						//No compression

	//Create the bitmap
	bitmap = CreateDIBSection(  hDC,			//Device context
							   &info,			//Pointer to info
							   DIB_RGB_COLORS,	//RGB info
							   reinterpret_cast<void**>(&bitmapData), //Pointer to bitmap data
							   0,				//Unused
							   0				//Unused
							   );

	if ( bitmap == 0 )
	{
		throw Core::RuntimeError ( "Could not create bitmap!", GetLastError(), __FILE__, __FUNCTION__, __LINE__);
	}

	//Select the bitmap into the device context
	oldBitmap = reinterpret_cast<HBITMAP>( SelectObject(hDC, bitmap) );

	if ( (oldBitmap == 0) || (oldBitmap == HGDI_ERROR) )
	{
		throw Core::RuntimeError ( "Error, couldn't select bitmap into hDC", GetLastError(), __FILE__, __FUNCTION__, __LINE__ );
	}

	try
	{
		//Write the text into the bitmap
		WriteTextIntoBitmap( hDC, image, bitmapData );
	}
	catch ( ... )
	{
		//Clean up
		SelectObject( hDC, oldBitmap );
		DeleteObject ( reinterpret_cast<HGDIOBJ>( bitmap ) ); 
		throw;
	}

	SelectObject( hDC, oldBitmap );
	DeleteObject ( reinterpret_cast<HGDIOBJ>( bitmap ) );

}
//End Font::CreateFontBitmap



//=========================================================================
//! @function    Font::WriteTextIntoBitmap
//! @brief       Write text into the bitmap and set up the texture coordinates
//!              
//! @param       hDC	[in]	
//! @param       image	[out]
//!              
//! @throw       Core::RuntimeError if the operation failed
//=========================================================================
void Font::WriteTextIntoBitmap ( HDC hDC, Imaging::Image& image, Byte* bitmapData )
{
	BOOL	result = 0;
	SIZE	charExtent;
	TexCoordRect rect;
	UInt   xPos = 0;
	UInt   yPos = 0;

	//Copy all the characters into the font texture
	for ( UChar currentChar = 0; currentChar < 255; ++currentChar )
	{
		result = GetTextExtentPoint32 ( hDC, reinterpret_cast<LPCTSTR>(&currentChar),
										1, &charExtent );
		if ( result == FALSE )
		{
			throw Core::RuntimeError ( "Error, couldn't get character extent!", GetLastError(), __FILE__, 
										__FUNCTION__, __LINE__ );
		}

		if ( xPos + charExtent.cx + 1 > m_textureSize )
		{
			xPos = 0;
			yPos += charExtent.cy + 5;
		}

		//Set up the texture coordinate rect
		rect.left = static_cast<Float>(xPos) / static_cast<Float>(m_textureSize);
		rect.right = static_cast<Float>(xPos + charExtent.cx) / static_cast<Float>(m_textureSize);
		rect.top = static_cast<Float>(yPos) / static_cast<Float>(m_textureSize);
		rect.bottom = static_cast<Float>(yPos + charExtent.cy) / static_cast<Float>(m_textureSize);
		m_texCoords.push_back(rect);

		//Draw the text
		result = ExtTextOut( hDC,				// handle to DC
							 xPos,				// x-coordinate of reference point
							 yPos,				// y-coordinate of reference point
							 ETO_OPAQUE,		// text-output options (fill with background colour before the text)
							 0,					// optional dimensions
							 reinterpret_cast<LPCSTR>(&currentChar),	// string
							 1,					// number of characters in string
							 0					// array of spacing values
							);

		if ( !result )
		{
			throw Core::RuntimeError ( "Couldn't draw text!", GetLastError(), __FILE__, __FUNCTION__, __LINE__ );
		}

		xPos += charExtent.cx + 10;

	}

	UChar* imageData = image.GetBufferPointer();

	for ( UInt i=0; i < (m_textureSize * m_textureSize * 4); i+=4 )
	{
		//std::clog << i << std::endl;
		*(imageData+i) 
			= *(bitmapData + i);
		*(imageData+i+1) 
			= *(bitmapData + i);
		*(imageData+i+2) 
			= *(bitmapData + i);
		*(imageData+i+3) 
			= *(bitmapData + i);
	
	}

}
//End Font::WriteTextIntoBitmap



//=========================================================================
//! @function    Font::CreateFontTexture
//! @brief       Create the font texture
//!              
//! @param       image			[in]	
//! @param       mipmapLevels	[in]
//!              
//! @throw       Core::RuntimeError if the operation succeeded
//=========================================================================
void Font::CreateFontTexture ( const Imaging::Image& image, UInt mipmapLevels )
{
	
	//Create a DXT compressed texture to hold the image
	m_texture = m_renderer.CreateTexture (  TEXTURE_2D,				//Type 
											m_textureSize,			//Width 
											m_textureSize,			//Height 
											Imaging::PXFMT_DXT5,	//Format
											0,						//Quality 
											TEXUSAGE_AUTOGENERATE_MIPMAPS,						//Usage
											0						//Flags
										);
	
	if ( !m_texture->SetFromImage( image ) )
	{
		throw Core::RuntimeError ( "Error, couldn't set texture from image!", 0, __FILE__, __FUNCTION__, __LINE__ );
	}

}
//End Font::CreateFontTexture



//=========================================================================
//! @function    Font::CreateVertexBuffer
//! @brief       Create the vertex buffer to hold the text
//!				 
//!              
//! @throw       Core::RuntimeError if failed
//=========================================================================
void Font::CreateVertexBuffer ()
{

	VertexDeclarationDescriptor descriptor;

	descriptor.AddElement ( 0, 0, DECLTYPE_FLOAT3,  DECLUSAGE_POSITION, 0 );
	descriptor.AddElement ( 0, 12, DECLTYPE_COLOUR, DECLUSAGE_DIFFUSE, 0  );
	descriptor.AddElement ( 0, 16, DECLTYPE_FLOAT2, DECLUSAGE_TEXCOORD, 0 );

	m_vertexDeclaration = m_renderer.AcquireVertexDeclaration ( descriptor );

	HVertexBuffer buffer = m_renderer.CreateVertexBuffer( sizeof(FontVertex), m_bufferSize, USAGE_DYNAMICWRITEONLY );
	m_vertexStreamBinding.SetStream ( buffer, 0 );

}
//End Font::CreateVertexBuffer



//=========================================================================
//! @function    Font::InitialiseRenderState
//! @brief       Create the render state object, and initialise its settings
//!              
//!              
//=========================================================================
void Font::InitialiseRenderState ( )
{
	m_renderState = boost::shared_ptr<RenderState>(new RenderState());
		
	TextureUnit texUnit;

	texUnit.SetHandle ( m_texture );
	texUnit.SetMinFilter ( TEXFILTER_LINEAR );
	texUnit.SetMagFilter ( TEXFILTER_LINEAR );
	texUnit.SetMipFilter ( TEXFILTER_POINT );

	if ( m_fontSize > 20 )
	{
		m_renderState->SetAlphaReference ( 0.5 );
	}
	else
	{
		m_renderState->SetAlphaReference ( 0.5 );
	}

	m_renderState->SetAlphaFunc ( CMP_GREATER ); 
	m_renderState->AddTextureUnit( texUnit );
	m_renderState->SetCullMode ( CULL_NONE );
	m_renderState->SetBlending ( true );

	m_renderState->SetSceneBlend ( BLEND_SRCALPHA, BLEND_INVSRCALPHA );
	m_renderState->SetAlphaTest ( true );

}
//End Font::InitialiseRenderState



//=========================================================================
//! @function    Font::CleanUp
//! @brief       Do all required cleanup
//!              
//! @param       hDC	 [in] Device context
//! @param       font	 [in] Current font for the device context
//! @param       oldFont [in] Old font for the device context
//!              
//! @throw       
//=========================================================================
void Font::CleanUp ( HDC hDC, HFONT font, HFONT oldFont )
{

	SelectObject ( hDC, reinterpret_cast<HGDIOBJ>(oldFont) );
	DeleteObject ( reinterpret_cast<HGDIOBJ>(font) );
	DeleteDC ( hDC );

}
//End Font::CleanUp