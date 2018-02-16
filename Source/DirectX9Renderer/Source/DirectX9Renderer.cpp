//======================================================================================
//! @file         DirectX9Renderer.cpp
//! @brief        DirectXRenderer class
//!               
//!				  IRenderer implementation for DirectX 9 
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 01 June 2005
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
#include "Math/Vector3D.h"
#include "Math/Matrix4x4.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererConstantToString.h"
#include "Renderer/VertexBufferCreator.h"
#include "Renderer/IndexBufferCreator.h"
#include "Renderer/VertexBufferManager.h"
#include "Renderer/IndexBufferManager.h"
#include "Renderer/VertexDeclarationCreator.h"
#include "Renderer/VertexDeclaration.h"
#include "Renderer/TextureManager.h"
#include "Renderer/TextureCreator.h"
#include "Renderer/VertexDeclarationManager.h"
#include "Renderer/VertexDeclarationCreator.h"
#include "DirectX9Renderer/ErrorCodes.h"
#include "DirectX9Renderer/Formats.h"
#include "DirectX9Renderer/DirectX9Renderer.h"
#include "DirectX9Renderer/DirectXRendererCreator.h"
#include "DirectX9Renderer/DirectXVertexBufferCreator.h"
#include "DirectX9Renderer/DirectXIndexBufferCreator.h"
#include "DirectX9Renderer/DirectXVertexDeclaration.h"
#include "DirectX9Renderer/DirectXVertexDeclarationCreator.h"
#include "DirectX9Renderer/DeviceCapabilities.h"
#include "DirectX9Renderer/ConversionFunctions.h"
#include "DirectX9Renderer/DirectXTextureCreator.h"
#include <string>


using namespace DirectX9Renderer;



//=========================================================================
//! @function    DirectXRenderer::DirectXRenderer
//! @brief       DirectXRenderer Constructor
//!              
//!              Creates the Direct3D object, so that it can be queried
//! 
//! @throw       RendererError
//=========================================================================
DirectXRenderer::DirectXRenderer()
: IRenderer(), m_name("DirectX9"), m_deviceType (D3DDEVTYPE_HAL), m_adapter(D3DADAPTER_DEFAULT),
  m_minModeWidth(800), m_minModeHeight(600), m_stencilClearValue(0.0f), m_depthClearValue(1.0f),
  m_worldViewOutOfDate(true), m_viewProjOutOfDate(true), m_screenWidth(0), m_screenHeight(0),
  m_trisPerFrame(0)
{

	//Get the value of the console variables ren_minModeWidth, and ren_minModeHeight
	//
	//These will be used to set the minimum display resolution that the renderer allows
	Core::ConsoleUInt ren_minModeWidth ( "ren_minmodewidth", m_minModeWidth );
	Core::ConsoleUInt ren_minModeHeight ( "ren_minmodeheight", m_minModeHeight );
	m_minModeWidth = ren_minModeWidth;
	m_minModeHeight = ren_minModeHeight;

	//Clear out the device capabilities structure
	ZeroMemory(&m_deviceCaps, sizeof(m_deviceCaps) );

	//Get the value of the console variable "debug_userefdevice"
	//giving it a default value of false, if no such variable has been registered at the console
	Core::ConsoleBool dbg_dxr_refdevice("dbg_dxr_refdevice", false );

	//If the variable has been registered, and it is true, then use the reference device
	if ( dbg_dxr_refdevice )
	{
		std::clog << "Using reference device" << std::endl;
		m_deviceType = D3DDEVTYPE_REF;
	}
	else
	{
		std::clog << "Using hardware device" << std::endl;
	}

	//Create the texture creator
	m_textureCreator = boost::shared_ptr<Renderer::ITextureCreator>(new DirectXTextureCreator(*this) );

	//Create the texture manager
	m_textureManager = boost::shared_ptr<Renderer::TextureManager>(new Renderer::TextureManager(*m_textureCreator) );

	//Create the vertex buffer creator
	m_vertexBufferCreator = boost::shared_ptr<Renderer::IVertexBufferCreator>(new DirectXVertexBufferCreator(*this) );

	//Create the vertex buffer manager
	m_vertexBufferManager = boost::shared_ptr<Renderer::VertexBufferManager>(new Renderer::VertexBufferManager(*m_vertexBufferCreator));

	//Create the index buffer creator
	m_indexBufferCreator = boost::shared_ptr<Renderer::IIndexBufferCreator>(new DirectXIndexBufferCreator(*this) );

	//Create the index buffer manager
	m_indexBufferManager = boost::shared_ptr<Renderer::IndexBufferManager>(new Renderer::IndexBufferManager(*m_indexBufferCreator));

	//Create the vertex declaration creator
	m_declarationCreator = boost::shared_ptr<Renderer::IVertexDeclarationCreator>( new DirectXVertexDeclarationCreator(*this) );

	//Create the vertex declaration manager
	m_vertexDeclarationManager = boost::shared_ptr<Renderer::VertexDeclarationManager>
												( new Renderer::VertexDeclarationManager(*m_declarationCreator) );

	std::clog << "DirectX9 Renderer object created" << std::endl;
	CreateD3D();
}
//End DirectXRenderer::DirectXRenderer



//=========================================================================
//! @function    DirectXRenderer::GetDisplayModeList
//! @brief       Populate and return a list of display modes the renderer supports
//!              
//! @return      A list of display modes supported by the renderer
//! @throw       
//=========================================================================
const Renderer::DisplayModeList& DirectXRenderer::GetDisplayModeList() const
{
	return m_displayModes;
}
//End DirectXRenderer::GetDisplayModeList



//=========================================================================
//! @function    DirectXRenderer::Initialise
//! @brief       Fully initialise the renderer
//!
//!				 After this call has completed, the renderer will be ready
//!				 to begin displaying graphics
//!              
//! @throw       RendererError
//=========================================================================
void DirectXRenderer::Initialise()
{
	Core::ConsoleUInt init_bpp("init_bpp", 32 );
	Core::ConsoleUInt init_mode( "init_mode", 0 );
	Core::ConsoleBool init_fullscreen ( "init_fullscreen", false );

	std::clog << "Initialising renderer with display mode: " << init_mode << std::endl;

	const Renderer::DisplayMode& mode(GetDisplayModeList().GetMode(init_mode, init_bpp));

	m_screenWidth = mode.Width();
	m_screenHeight = mode.Height();

	std::clog << "   " << mode.Description() 
				<< "\n   " << init_bpp << " bit\n"; 
	
	if ( init_fullscreen )
	{
		std::clog << "   " << "Full screen\n" << std::endl;
	}
	else
	{
		std::clog << "   " << "Windowed\n" << std::endl;
	}

	CreateRenderWindow();
	CreateDevice();


	//Call BeginScene, EndScene, and Present
	//to stop the screen from showing random data in the first frame
	m_device->BeginScene();
	Clear( Renderer::COLOUR_BUFFER );
	m_device->EndScene();
	m_device->Present(0, 0, 0, 0);

	m_device->SetRenderState ( D3DRS_COLORVERTEX, TRUE );
}
//End DirectXRenderer::Initialise



//=========================================================================
//! @function    DirectXRenderer::ShutDown
//! @brief       Shuts down the renderer
//!              
//!              
//! @throw       RendererError
//=========================================================================
void DirectXRenderer::ShutDown()
{

}
//End DirectXRenderer::ShutDown



//=========================================================================
//! @function    DirectXRenderer::AcquireTexture
//! @brief       Get a handle to a texture.
//!
//!				 If the texture is already loaded, then a handle to the texture
//!				 is returned. The texture must be of the same type, or the acquire will
//!				 fail, and a RuntimeError will be thrown
//!
//!				 If the texture could not be found in the internal texture store,
//!				 then the texture will be loaded from disk. If the texture could not be loaded
//!				 then a RuntimeError will be thrown, otherwise a handle to the new resource
//!				 will be returned.
//!              
//! @param       type	  [in] Type of the texture TEXTURE_1D, TEXTURE_2D, or TEXTURE_CUBEMAP
//! @param       fileName [in] File name of the texture
//! @param       quality  [in] Quality option for the texture. Unused, and reserved for future use.
//!							   Set to 0.
//! @param		 usage	  [in] Usage options for the texture. Combation of the flags from the ETextureUsage enumeration
//! @param		 flag	  [in] Flags for the texture. Unused and reserved for future use.
//!							   Set to 0.
//!              
//! @return      A handle to the texture
//! @throw		 Core::RuntimeError
//=========================================================================
Renderer::HTexture DirectXRenderer::AcquireTexture ( Renderer::ETextureType type, const Char* fileName, 
													  UInt quality, UInt usage, UInt flags )
{
	return m_textureManager->AcquireTexture( type, fileName, quality, usage, flags );
}
//End DirectXRenderer::AcquireTexture



//=========================================================================
//! @function    DirectXRenderer::CreateTexture
//! @brief       Create a texture.
//!
//!				 If the texture could not be created then a RuntimeError will be thrown,
//!				 otherwise a handle to the new resource will be returned.
//!              
//! @param       type	  [in] Type of the texture TEXTURE_1D, TEXTURE_2D, or TEXTURE_CUBEMAP
//! @param       width	  [in] Width of the texture
//! @param		 height	  [in] Height of the texture
//! @param		 format	  [in] Format of the texture
//! @param       quality  [in] Quality option for the texture. Unused, and reserved for future use.
//!							   Set to 0.
//! @param		 usage	  [in] Usage options for the texture. Combination of flags from the ETextureUsage enumeration
//! @param		 flag	  [in] Flags for the texture. Unused and reserved for future use.
//!							   Set to 0.
//!              
//! @return      A handle to the texture
//! @throw		 Core::RuntimeError if the texture could not be created
//=========================================================================
Renderer::HTexture DirectXRenderer::CreateTexture ( Renderer::ETextureType type, UInt width, UInt height, 
												   Imaging::PixelFormat format, UInt quality, UInt usage, UInt flags )
{
	return m_textureManager->CreateTexture( type, width, height, format, quality, usage, flags );
}
//End DirectXRenderer::CreateTexture


//=========================================================================
//! @function    DirectXRenderer::CreateVertexBuffer
//! @brief       Create a vertex buffer
//!              
//! @param       vertexSize  [in] Size of a vertex in the vertex buffer
//! @param       vertexCount [in] Number of vertices in the buffer	
//! @param       usage		 [in] Usage options for the buffer
//!              
//! @return      A handle to the new buffer, or a null handle if the create
//!				 operation failed
//=========================================================================
Renderer::HVertexBuffer DirectXRenderer::CreateVertexBuffer ( size_t vertexSize, 
																size_t vertexCount, 
																Renderer::EUsage usage )
{
	return m_vertexBufferManager->CreateVertexBuffer( vertexSize, vertexCount, usage );
}
//End DirectXRenderer::CreateVertexBuffer



//=========================================================================
//! @function    DirectXRenderer::CreateIndexBuffer
//! @brief       Create an index buffer
//!              
//! @param       indexSize	[in] Size of a single index in the buffer @see Renderer::EIndexSize
//! @param       indexCount [in] Number of vertices in the buffer
//! @param       usage		[in] Usage flags for the index buffer
//!              
//! @return      A handle to the new buffer, or a null handle if the create
//!				 operation failed
//=========================================================================
Renderer::HIndexBuffer DirectXRenderer::CreateIndexBuffer ( Renderer::EIndexSize indexSize,
														    size_t indexCount,
															Renderer::EUsage usage )
{
	return m_indexBufferManager->CreateIndexBuffer( indexSize, indexCount, usage );
}
//End DirectXRenderer::CreateIndexBuffer


//=========================================================================
//! @function    DirectXRenderer::AcquireVertexDeclaration
//! @brief       Get a handle to a vertex declaraiton
//!                     
//!				 If a vertex declaration with a format matching the descriptor
//!				 already exists, then a handle to the existing descriptor will be returned
//!				 Otherwise, a handle to a new declaration will be returned
//!              
//! @param       descriptor [in]
//!              
//! @return      A handle to a vertex declaration
//! @throw       Core::RuntimeError
//=========================================================================
Renderer::HVertexDeclaration DirectXRenderer::AcquireVertexDeclaration( Renderer::VertexDeclarationDescriptor& descriptor )
{
	return m_vertexDeclarationManager->AcquireVertexDeclaration( descriptor );
}
//End DirectXRenderer::AcquireVertexDeclaration



//=========================================================================
//! @function    DirectXRenderer::BeginFrame
//! @brief       Does any setup necessary to begin the rendering of a new frame
//!              
//!              
//=========================================================================
void DirectXRenderer::BeginFrame()
{
	HRESULT result = 0;

	#ifdef PRINT_TRISPERFRAME
		m_trisPerFrame = 0;
	#endif

	//First we call Present. Obviously this will fail the first time, but in
	//the general case it's better to call present here. For maximum parallelism 
	//between the graphics hardware and the CPU, it's best to leave as long
	//a time frame as possible between calling EndScene and calling Present
	result = m_device->Present(0, 0, 0, 0);

	if ( FAILED(result) )
	{
		std::cerr << "Error! m_device->Present failed! Error code: " << D3DErrorCodeToString(result) << std::endl;
	}
	
	result = m_device->BeginScene();

	if ( FAILED(result) )
	{
		std::cerr << "Error! m_device->BeginScene failed! Error code: " << D3DErrorCodeToString(result) << std::endl;
	}
}
//End DirectXRenderer::BeginFrame 



//=========================================================================
//! @function    DirectXRenderer::EndFrame
//! @brief       Ends the current frame, and displays it
//!              
//!              
//! @return      
//! @throw       
//=========================================================================
void DirectXRenderer::EndFrame()
{
	HRESULT result = 0;

	//End the scene
	result = m_device->EndScene();

	if ( FAILED(result) )
	{
		std::cerr << "Error! m_device->EndScene failed! Error code: " << D3DErrorCodeToString(result) << std::endl;
	}

	#ifdef PRINT_TRISPERFRAME
		std::cout << m_trisPerFrame << " triangles rendered this frame" << std::endl;
	#endif
}
//End DirectXRenderer::EndFrame 



//=========================================================================
//! @function    DirectXRenderer::Clear
//! @brief       Clear the buffers specified by buffer flags
//!              
//! @param       bufferFlags [in] Set of flags specifying which buffers to clear
//!								  Possible flag values are
//!								  ColourBuffer,
//!								  DepthBuffer,
//!								  StencilBuffer
//!              
//! @return      
//! @throw       
//=========================================================================
void DirectXRenderer::Clear ( UInt bufferFlags )
{
	DWORD flags = 0;

	if ( bufferFlags & Renderer::COLOUR_BUFFER  )
	{
		flags |= D3DCLEAR_TARGET;
	}

	if ( bufferFlags & Renderer::DEPTH_BUFFER )
	{
		flags |= D3DCLEAR_ZBUFFER;
	}

	if ( bufferFlags & Renderer::STENCIL_BUFFER )
	{
		flags |= D3DCLEAR_STENCIL;
	}

	if ( FAILED(m_device->Clear ( 0, 0, flags, m_backgroundColour, m_depthClearValue, m_stencilClearValue )))
	{
		std::cerr << __FUNCTION__ ": Error, m_device->Clear failed!" << std::endl;
	}
}
//End DirectXRenderer::Clear



//=========================================================================
//! @function    DirectXRenderer::DrawPrimitive
//! @brief       Renders a series of non-indexed primitives from the current
//!				 vertex streams
//!              
//! @param       type		 [in] Primitive type
//! @param       startIndex  [in] First index to be rendered
//! @param       vertexCount [in] Number of vertices to be rendered
//=========================================================================
void DirectXRenderer::DrawPrimitive( Renderer::EPrimType type, size_t startIndex, size_t vertexCount )
{
	UInt primitiveCount = 0;

	//Calculate the primitive count from the primitive type
	switch ( type )
	{
		case Renderer::PRIM_POINTLIST:
			primitiveCount = vertexCount;
			break;

		case Renderer::PRIM_LINELIST:
			primitiveCount = (vertexCount / 2);
			break;

		case Renderer::PRIM_LINESTRIP:
			primitiveCount = vertexCount - 1;
			break;

		case Renderer::PRIM_TRIANGLELIST:
			primitiveCount = (vertexCount / 3);

			#ifdef PRINT_TRISPERFRAME
				m_trisPerFrame += primitiveCount;
			#endif

			break;

		case Renderer::PRIM_TRIANGLESTRIP:
			primitiveCount = (vertexCount - 2);

			#ifdef PRINT_TRISPERFRAME
				m_trisPerFrame += primitiveCount;
			#endif

			break;

		case Renderer::PRIM_TRIANGLEFAN:
			primitiveCount = (vertexCount - 2);

			#ifdef PRINT_TRISPERFRAME
				m_trisPerFrame += primitiveCount;
			#endif

			break;

		default:
			debug_assert ( false, "Invalid primitive type!" );
	}

	//Do the drawing
	HRESULT result = m_device->DrawPrimitive( ConvertPrimTypeToD3D(type), //Primitive type
												startIndex,				  //First vertex to render
												primitiveCount			  //Number of vertices to render
												);

	if ( SUCCEEDED(result) )
	{
		return;
	}
	else
	{
		std::cerr << __FUNCTION__ ":Error, DrawPrimitive failed! Called with: "
			<< "type: " << Renderer::PrimTypeToString( type ) 
			<< " startIndex: " << static_cast<UInt>(startIndex) 
			<< " vertexCount: " << static_cast<UInt>(vertexCount) << "\n"
			<< "Primitive count = " << primitiveCount << ". Error Code " << D3DErrorCodeToString(result) << std::endl;
	}
}
//End DirectXRenderer::DrawPrimitive



//=========================================================================
//! @function    DirectXRenderer::DrawIndexedPrimitive
//! @brief       Renders a series of indexed primitives from the current
//!				 vertex streams
//!              
//! @param       type				[in] Primitive type to render
//! @param       baseVertexIndex	[in] Offset from the start of the buffer to the first index
//! @param       startIndex			[in] First index to render
//! @param       vertexCount		[in] Number of vertices to be rendered
//=========================================================================
void DirectXRenderer::DrawIndexedPrimitive ( Renderer::EPrimType type, 
											size_t baseVertexIndex, 
											size_t startIndex, 
											size_t vertexCount )
{
	UInt primitiveCount = 0;

	//Calculate the primitive count from the primitive type
	switch ( type )
	{
		case Renderer::PRIM_POINTLIST:
			primitiveCount = vertexCount;
			break;

		case Renderer::PRIM_LINELIST:
			primitiveCount = (vertexCount / 2);
			break;

		case Renderer::PRIM_LINESTRIP:
			primitiveCount = vertexCount - 1;
			break;

		case Renderer::PRIM_TRIANGLELIST:
			primitiveCount = (vertexCount / 3);

			#ifdef PRINT_TRISPERFRAME
				m_trisPerFrame += primitiveCount;
			#endif

			break;

		case Renderer::PRIM_TRIANGLESTRIP:
			primitiveCount = (vertexCount - 2);

			#ifdef PRINT_TRISPERFRAME
				m_trisPerFrame += primitiveCount;
			#endif

			break;

		case Renderer::PRIM_TRIANGLEFAN:
			primitiveCount = (vertexCount - 2);

			#ifdef PRINT_TRISPERFRAME
				m_trisPerFrame += primitiveCount;
			#endif

			break;

		default:
			debug_assert ( false, "Invalid primitive type!" );
	}

	HRESULT result = m_device->DrawIndexedPrimitive( ConvertPrimTypeToD3D(type), //Primitive type
													 baseVertexIndex,			  //Base vertex index
													 0,							  //Minimum index
													 vertexCount,				  //Vertex count
													 startIndex,				  //First vertex to render
													 primitiveCount				  //Number of vertices to render
													);

	if ( SUCCEEDED(result) )
	{
		return;
	}
	else
	{
		std::cerr << __FUNCTION__ ":Error, DrawPrimitive failed! Called with: "
			<< "type: " << Renderer::PrimTypeToString ( type ) 
			<< " baseVertexIndex: " << baseVertexIndex
			<< " vertexCount: " << vertexCount
			<< " startIndex: " << startIndex
			<< " primitiveCount " << primitiveCount
			<< "\nErrorCode: " << D3DErrorCodeToString(result) << std::endl;
	}


}
//End DirectXRenderer::DrawIndexedPrimitive



//=========================================================================
//! @function    DirectXRenderer::DrawIndexedPrimitive
//! @brief       Renders a series of indexed primitives from the current
//!				 vertex streams
//!
//!				 This version accepts a maxVertexIndex parameter, so that
//!				 more indices can be rendered, than there are vertices in the
//!				 currently bound buffers
//!
//!				 Might amalgamate this method with the other one...
//!              
//! @param       type				[in] Primitive type to render
//! @param       baseVertexIndex	[in] Offset from the start of the buffer to the first index
//! @param		 maxVertexIndex		[in] The highest vertex index that can be rendered
//! @param       startIndex			[in] First index to render
//! @param       vertexCount		[in] Number of vertices to be rendered
//=========================================================================
void DirectXRenderer::DrawIndexedPrimitive ( Renderer::EPrimType type, 
											size_t baseVertexIndex,
											size_t maxVertexIndex,
											size_t startIndex, 
											size_t vertexCount )
{
	UInt primitiveCount = 0;

	//Calculate the primitive count from the primitive type
	switch ( type )
	{
		case Renderer::PRIM_POINTLIST:
			primitiveCount = vertexCount;
			break;

		case Renderer::PRIM_LINELIST:
			primitiveCount = (vertexCount / 2);
			break;

		case Renderer::PRIM_LINESTRIP:
			primitiveCount = vertexCount - 1;
			break;

		case Renderer::PRIM_TRIANGLELIST:
			primitiveCount = (vertexCount / 3);

			#ifdef PRINT_TRISPERFRAME
				m_trisPerFrame += primitiveCount;
			#endif

			break;

		case Renderer::PRIM_TRIANGLESTRIP:
			primitiveCount = (vertexCount - 2);

			#ifdef PRINT_TRISPERFRAME
				m_trisPerFrame += primitiveCount;
			#endif

			break;

		case Renderer::PRIM_TRIANGLEFAN:
			primitiveCount = (vertexCount - 2);

			#ifdef PRINT_TRISPERFRAME
				m_trisPerFrame += primitiveCount;
			#endif

			break;

		default:
			debug_assert ( false, "Invalid primitive type!" );
	}

	HRESULT result = m_device->DrawIndexedPrimitive( ConvertPrimTypeToD3D(type), //Primitive type
													 baseVertexIndex,			  //Base vertex index
													 0,							  //Minimum index
													 maxVertexIndex,			  //Vertex count
													 startIndex,				  //First vertex to render
													 primitiveCount				  //Number of primitives to render
													);

	if ( SUCCEEDED(result) )
	{
		return;
	}
	else
	{
		std::cerr << __FUNCTION__ ":Error, DrawPrimitive failed! Called with: "
			<< "type: " << Renderer::PrimTypeToString ( type ) 
			<< " baseVertexIndex: " << baseVertexIndex
			<< " vertexCount: " << vertexCount
			<< " startIndex: " << startIndex
			<< " primitiveCount " << primitiveCount
			<< "\nErrorCode: " << D3DErrorCodeToString(result) << std::endl;
	}


}
//End DirectXRenderer::DrawIndexedPrimitive



//=========================================================================
//! @function    DirectXRenderer::SetClearColour
//! @brief       Sets the colour value used to clear the colour buffer
//!              
//! @param       colour [in] New colour value for the buffer
//!              
//=========================================================================
bool DirectXRenderer::SetClearColour( const Renderer::Colour4f& colour )
{
	m_backgroundColourAsColour4 = colour;
	m_backgroundColour = D3DCOLOR_COLORVALUE ( colour.Red(), colour.Green(), colour.Blue(), colour.Alpha() );

	return true;
}
//End DirectXRenderer::SetClearColour



//=========================================================================
//! @function    DirectXRenderer::SetTextureAddressingMode
//! @brief       Set the texture addressing mode for a texture stage.
//!
//!				 The texture addressing mode defines how textures behave when
//!				 the texture coordinates go beyond the range 0.0 - 1.0
//!              
//! @param       stageID [in] Texture stage to set the addressing mode for
//! @param       type	 [in] Member of the ETextureAddressModeType enumeration,
//!							  indicating which coordinate to set the address mode for, U, V, or W
//!							  Valid values are: TEX_ADDRESS_U, TEX_ADDRESS_V, TEX_ADDRESS_W
//!								
//! @param       mode	 [in] Texture addressing mode to set
//!							  TEXADDRESS_WRAP 		 : Repeat the texture				
//!						      TEXADDRESS_CLAMP		 : Repeat the edge pixels
//!							  TEXADDRESS_BORDER		 : Fill the pixels with the border colour
//!							  TEXADDRESS_MIRROR		 : Repeat the texture, but reversed
//!							  TEXADDRESS_MIRRORONCE  : Mirrors around zero, but clamps the texture
//!													   coordinate after mirroring once
//!
//! @return		true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetTextureAddressingMode ( Renderer::ETextureStageID stageID, 
												 Renderer::ETextureAddressModeType type, 
												 Renderer::ETextureAddressingMode mode )
{
	D3DSAMPLERSTATETYPE samplerType;
	
	switch ( type )
	{
		case Renderer::TEX_ADDRESS_U:
			samplerType = D3DSAMP_ADDRESSU;
			break;

		case Renderer::TEX_ADDRESS_V:
			samplerType = D3DSAMP_ADDRESSV;
			break;

		case Renderer::TEX_ADDRESS_W:
			samplerType = D3DSAMP_ADDRESSW;
			break;
	}

	D3DTEXTUREADDRESS address = ConvertTextureAddressingModeToD3D(mode);
	
	HRESULT result = m_device->SetSamplerState ( static_cast<DWORD>(stageID), samplerType, static_cast<DWORD>(address) );


	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error setting texture addressing mode for ";

		switch( type )
		{
			case Renderer::TEX_ADDRESS_U:
				std::cerr << "TEX_ADDRESS_U";
				break;

			case Renderer::TEX_ADDRESS_V:
				std::cerr << "TEX_ADDRESS_V";
				break;

			case Renderer::TEX_ADDRESS_W:
				std::cerr << "TEX_ADDRESS_W";
				break;			
		}

		std::cerr << " to " << Renderer::TextureAddressingModeToString( mode )
				  << "! Error code " << D3DErrorCodeToString(result) << std::endl;

		return false;
	}
}
//End DirectXRenderer::SetTextureAddressingMode



//=========================================================================
//! @function    DirectXRenderer::SetTextureCoordGeneration
//! @brief       Turn on texture coordinate generation for the specified
//!				 texture stage
//!              
//! @param       stageID			  [in] Texture stage 
//! @param		 textureCoordinateSet [in] Texture coordinate set to turn on
//!										   generation for. Must be less than TEXCOORDSET_COUNT
//! @param       mode				  [in] Texture coordinate generation mode to use
//!										   TEXGEN_NONE				  : No texture coordinate generation
//!										   TEXGEN_SPHEREMAP			  : Calculates coordinates for sphere mapping
//!										   TEXGEN_EYESPACE_REFLECTION : Calculates the eyespace reflection vector
//!										   TEXGEN_EYESPACE_NORMAL	  : Calculates the eyespace normal vector
//!              
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetTextureCoordGeneration ( Renderer::ETextureStageID stageID, 
												  UInt textureCoordinateSet, 
												  Renderer::ETextureCoordGen mode )
{
	debug_assert ( textureCoordinateSet < Renderer::TEXCOORDSET_COUNT, "Invalid texture coordinate set!" );

	DWORD dxMode = 0;

	switch ( mode )
	{
		case Renderer::TEXGEN_NONE:
			dxMode = D3DTSS_TCI_PASSTHRU;
			break;

		case Renderer::TEXGEN_SPHEREMAP:
			dxMode = D3DTSS_TCI_SPHEREMAP;
			break;

		case Renderer::TEXGEN_EYESPACE_REFLECTION:
			dxMode = D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR;
			break;

		case Renderer::TEXGEN_EYESPACE_NORMAL:
			dxMode = D3DTSS_TCI_CAMERASPACENORMAL;
			break;

		default:
			debug_assert(false, "Invalid texgen mode!");
	}

	HRESULT result = m_device->SetTextureStageState ( stageID, D3DTSS_TEXCOORDINDEX, textureCoordinateSet | dxMode );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ << ": Failed to set texture coordinate state! For stage " << stageID
				  << ". Texcoord index = " << textureCoordinateSet << ", mode = ";

		switch ( mode )
		{
			case Renderer::TEXGEN_NONE:
				std::cerr << "TEXGEN_NONE";
				break;

			case Renderer::TEXGEN_SPHEREMAP:
				std::cerr << "TEXGEN_SPHEREMAP";
				break;

			case Renderer::TEXGEN_EYESPACE_REFLECTION:
				std::cerr << "TEXGEN_EYESPACE_REFLECTION";
				break;

			case Renderer::TEXGEN_EYESPACE_NORMAL:
				std::cerr << "TEXGEN_EYESPACE_NORMAL";
				break;

			default:
				debug_assert(false, "Invalid texgen mode!");
		}

		std::cerr << ". Error code " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}
}		
//End DirectXRenderer::SetTextureCoordGeneration




//=========================================================================
//! @function    DirectXRenderer::SetTextureFilter
//! @brief       Set the texture filter for a texture stage
//!              
//! @param       stageID [in] Texture stage to set the filter for
//! @param		 type	 [in] Type of filter to set
//!							  TEXFILTER_MIN: Minification filter
//!							  TEXFILTER_MAG: Magnification filter
//!							  TEXFILTER_MIP: Mip filter
//!
//! @param		 filter  [in] Filter to set
//!							  TEXFILTER_POINT		: Gets the nearest point						  
//!							  TEXFILTER_LINEAR		: Linear filtering
//!							  TEXFILTER_ANISOTROPIC : Anisotropic filtering
//!              
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetTextureFilter ( Renderer::ETextureStageID stageID, 
										 Renderer::ETextureFilterType type, 
										 Renderer::ETextureFilter filter )
{
	
	//Convert the type to Direct3D
	D3DSAMPLERSTATETYPE samplerType;
	switch ( type )
	{
		case Renderer::TEXFILTER_MIN:
			samplerType = D3DSAMP_MINFILTER;
			break;

		case Renderer::TEXFILTER_MAG:
			samplerType = D3DSAMP_MAGFILTER;
			break;

		case Renderer::TEXFILTER_MIP:
			samplerType = D3DSAMP_MIPFILTER;
			break;
	}

	//Convert the filter to Direct3D
	D3DTEXTUREFILTERTYPE filterType;
	switch ( filter )
	{
		case Renderer::TEXFILTER_POINT:
			filterType = D3DTEXF_POINT;
			break;

		case Renderer::TEXFILTER_LINEAR:
			filterType = D3DTEXF_LINEAR;
			break;

		case Renderer::TEXFILTER_ANISOTROPIC:
			filterType = D3DTEXF_ANISOTROPIC;
			break;
	}

	HRESULT result = m_device->SetSamplerState ( static_cast<DWORD>(stageID), samplerType, filterType );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error setting texture filter for stage " << stageID
				  << "! Type = ";

		switch ( type )
		{
			case Renderer::TEXFILTER_MIN:
				std::cerr << "TEXFILTER_MIN";
				break;

			case Renderer::TEXFILTER_MAG:
				std::cerr << "TEXFILTER_MAG";
				break;

			case Renderer::TEXFILTER_MIP:
				std::cerr << "TEXFILTER_MIP";
				break;
		}

		std::cerr << ", filter = ";

		switch ( filter )
		{
			case Renderer::TEXFILTER_POINT:
				std::cerr << "TEXFILTER_POINT";
				break;

			case Renderer::TEXFILTER_LINEAR:
				std::cerr << "TEXFILTER_LINEAR";
				break;

			case Renderer::TEXFILTER_ANISOTROPIC:
				std::cerr << "TEXFILTER_ANISOTROPIC";
				break;
		}

		std::cerr << ". Error code " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return false;
}
//End DirectXRenderer::SetTextureFilter



//=========================================================================
//! @function    DirectXRenderer::SetTextureBorderColour
//! @brief       Set the border colour used when texture coordinates go beyond the range
//!				 0.0 - 1.0. The texture addressing mode must be set appropriately for this to happen
//!				 
//!
//! @param       stageID [in] Texture stage to set the border colour for
//! @param		 colour	 [in] Colour to set
//!
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetTextureBorderColour ( Renderer::ETextureStageID stageID, const Renderer::Colour4f& colour )
{
	HRESULT result = m_device->SetSamplerState( static_cast<DWORD>(stageID), D3DSAMP_BORDERCOLOR, colour );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error, couldn't set border colour for stage " << stageID
				  << " to " << colour << ". Error code " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return false;
}
//End DirectXRenderer::SetTextureBorderColour



//=========================================================================
//! @function    DirectXRenderer::SetTextureParameter
//! @brief       Set a parameter for one of the texture stages
//!
//! @param       stageID [in] Texture stage to set the texture parameter for
//! @param		 type	 [in] Parameter to set
//!
//!
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetTextureParameter ( Renderer::ETextureStageID stageID, Renderer::ETextureParamType type, UInt value )
{

	HRESULT result = 0;
	
	switch ( type )
	{
		case Renderer::TEXPARAM_MIPMAP_LOD_BIAS:
			result = m_device->SetSamplerState ( static_cast<DWORD>(stageID), D3DSAMP_MIPMAPLODBIAS, value );
			break;

		case Renderer::TEXPARAM_MAX_ANISOTROPY:
			result = m_device->SetSamplerState ( static_cast<DWORD>(stageID), D3DSAMP_MAXANISOTROPY, value ); 
			break;
	}

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error, couldn't set texture parameter ";

		switch ( type )
		{
			case Renderer::TEXPARAM_MIPMAP_LOD_BIAS:
				std::cerr << "TEXPARAM_MIPMAP_LOD_BIAS";
				break;
			case Renderer::TEXPARAM_MAX_ANISOTROPY:
				std::cerr << "TEXPARAM_MAX_ANISOTROPY";
				break;
		}

		std::cerr << " to " << value << ": Error code " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return false;
}
//End DirectXRenderer::SetTextureParameter



//=========================================================================
//! @function    DirectXRenderer::SetBlendOp
//! @brief       Set the blending operation used on the source and destination
//!				 blend operands. @see Renderer::EBlendOp
//!              
//! @param       op [in] Blending operation to use
//!              
//! @return      true if the blending operation could be set, false otherwise
//=========================================================================
bool DirectXRenderer::SetBlendOp ( Renderer::EBlendOp op )
{
	HRESULT result = m_device->SetRenderState ( D3DRS_BLENDOP, ConvertBlendOpToD3D(op) );
	
	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Failed setting blend op to " << Renderer::BlendOpToString(op)
				  << "! Error code " << D3DErrorCodeToString(result) << std::endl;
	}
}
//End DirectXRenderer::SetBlendOp



//=========================================================================
//! @function    DirectXRenderer::SetBlendFunc
//! @brief       Set the blending function
//!              
//! @param       src [in] Source blend mode
//! @param       dst [in] Destination blend mode
//!              
//! @return      true if the blend mode could be set, false otherwise
//=========================================================================
bool DirectXRenderer::SetBlendFunc ( Renderer::EBlendMode src, Renderer::EBlendMode dst )
{
	
	HRESULT result = m_device->SetRenderState ( D3DRS_SRCBLEND, ConvertBlendModeToD3D(src) );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ ": Failed setting source blend mode to " << Renderer::BlendModeToString(src)
				  << "! Error Code: " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	result = m_device->SetRenderState ( D3DRS_DESTBLEND, ConvertBlendModeToD3D(dst) );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ ": Failed setting destination blend mode to " << Renderer::BlendModeToString(dst)
				  << "! Error Code: " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return true;
}
//End DirectXRenderer::SetBlendFunc



//=========================================================================
//! @function    DirectXRenderer::SetDepthFunc
//! @brief       Set the comparison function used for depth testing
//!              
//! @param       cmp [in] Comparison function to use
//!              
//! @return      true if successful, false if failed
//=========================================================================
bool DirectXRenderer::SetDepthFunc ( Renderer::ECmpFunc cmp )
{
	
	HRESULT result = m_device->SetRenderState( D3DRS_ZFUNC, ConvertCmpFuncToD3D(cmp) );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Failed setting depth func to " << Renderer::CmpFuncToString(cmp)
				  << "! Error Code: " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

}
//End DirectXRenderer::SetDepthFunc



//=========================================================================
//! @function    DirectXRenderer::SetAlphaFunc
//! @brief       Set the comparison function used for alpha testing
//!              
//! @param       cmp [in] Comparison function to use
//!              
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetAlphaFunc ( Renderer::ECmpFunc cmp )
{
	HRESULT result = m_device->SetRenderState( D3DRS_ALPHAFUNC, ConvertCmpFuncToD3D(cmp) );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Failed setting alpha func to " << Renderer::CmpFuncToString(cmp)
				  << "! Error Code: " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}
}
//End DirectXRenderer::SetAlphaFunc



//=========================================================================
//! @function    DirectXRenderer::SetStencilFunc
//! @brief       Set the comparison function used for stencil testing
//!              
//! @param       cmp  [in] Comparison function to use
//!              
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetStencilFunc ( Renderer::ECmpFunc cmp )
{
	HRESULT result = m_device->SetRenderState( D3DRS_STENCILFUNC, ConvertCmpFuncToD3D(cmp) );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Failed setting stencil func to " << Renderer::CmpFuncToString(cmp)
				  << "! Error Code: " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}
}
//End DirectXRenderer::SetStencilFunc




//=========================================================================
//! @function    DirectXRenderer::SetStencilOp
//! @brief       Set the stencil operation for a specific operation type
//!              
//! @param       type [in]  Operation type
//!							STENCILOP_FAIL : Operation for when the stencil test fails 	
//!							STENCILOP_ZFAIL: Operation for when the stencil test passes, but the depth test fails
//!							STENCILOP_PASS : Operation for when the stencil test passes	
//!
//! @param       op   [in] @see Renderer::EStencilOp
//!              
//! @return      true if the operation was set successfully, false otherwise
//=========================================================================
bool DirectXRenderer::SetStencilOp ( Renderer::EStencilOpType type, Renderer::EStencilOp op )
{
	HRESULT result = 0;

	switch ( type )
	{
		case Renderer::STENCILOP_FAIL:
			result = m_device->SetRenderState ( D3DRS_STENCILFAIL, ConvertStencilOpToD3D(op) );
			break;
		
		case Renderer::STENCILOP_ZFAIL:
			result = m_device->SetRenderState ( D3DRS_STENCILZFAIL, ConvertStencilOpToD3D(op) );
			break;

		case Renderer::STENCILOP_PASS:
			result = m_device->SetRenderState ( D3DRS_STENCILPASS, ConvertStencilOpToD3D(op) );
			break;
	}

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Failed to set stencil op to " << Renderer::StencilOpToString(op)
				  << "! Error Code: " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return false;
}
//End DirectXRenderer::SetStencilOp



//=========================================================================
//! @function    DirectXRenderer::SetStencilFuncCCW
//! @brief       Set the comparison function used for the counter clockwise side stencil testing
//!				 Requires two sided stenciling to be enabled              
//!
//! @param       cmp  [in] Comparison function to use
//!              
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetStencilFuncCCW ( Renderer::ECmpFunc cmp )
{
	HRESULT result = m_device->SetRenderState( D3DRS_CCW_STENCILFUNC, ConvertCmpFuncToD3D(cmp) );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Failed setting counterclockwise stencil func to " << Renderer::CmpFuncToString(cmp)
				  << "! Error Code: " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}
}
//End DirectXRenderer::SetStencilFuncCCW



//=========================================================================
//! @function    DirectXRenderer::SetStencilOpCCW
//! @brief       Set the stencil operation for a specific operation type
//!				 Same as SetStencilOp, but for the counterclockwise equivilient
//!				 requires two sided stencilling to be enabled
//!              
//! @param       type [in]  Operation type
//!							STENCILOP_FAIL : Operation for when the stencil test fails 	
//!							STENCILOP_ZFAIL: Operation for when the stencil test passes, but the depth test fails
//!							STENCILOP_PASS : Operation for when the stencil test passes	
//!
//! @param       op   [in] @see Renderer::EStencilOp
//!              
//! @return      true if the operation was set successfully, false otherwise
//=========================================================================
bool DirectXRenderer::SetStencilOpCCW ( Renderer::EStencilOpType type, Renderer::EStencilOp op )
{
	HRESULT result = 0;

	switch ( type )
	{
		case Renderer::STENCILOP_FAIL:
			result = m_device->SetRenderState ( D3DRS_CCW_STENCILFAIL, ConvertStencilOpToD3D(op) );
			break;
		
		case Renderer::STENCILOP_ZFAIL:
			result = m_device->SetRenderState ( D3DRS_CCW_STENCILZFAIL, ConvertStencilOpToD3D(op) );
			break;

		case Renderer::STENCILOP_PASS:
			result = m_device->SetRenderState ( D3DRS_CCW_STENCILPASS, ConvertStencilOpToD3D(op) );
			break;
	}

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Failed to set counterclockwise stencil op to " << Renderer::StencilOpToString(op)
				  << "! Error Code: " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return false;
}
//End DirectXRenderer::SetStencilOpCCW




//=========================================================================
//! @function    DirectXRenderer::SetFogMode
//! @brief       Set the fog mode for the specified fog type
//!				 fog blending must be enabled for this to have any effect
//!              
//! @param       type [in] Type of fog to set the mode for
//!							FOGTYPE_TABLE  :  Table fog (pixel)
//!							FOGTYPE_VERTEX :  Vertex fog
//!
//! @param       mode [in] Fog mode to set
//!							FOGMODE_NONE	: No fog	
//!							FOGMODE_EXP		: The fog effect intensifies exponentially	
//!							FOGMODE_EXP2	: The fog effect intensifies exponentially with the square of the distance	
//!							FOGMODE_LINEAR	: The fog effect intensifies linearly between the start and end points	
//!
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetFogMode ( Renderer::EFogType type, Renderer::EFogMode mode )
{
	
	D3DRENDERSTATETYPE state = (type == Renderer::FOGTYPE_TABLE) ? D3DRS_FOGTABLEMODE : D3DRS_FOGVERTEXMODE;
	HRESULT result = m_device->SetRenderState ( state, ConvertFogModeToD3D(mode) );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Failed to set " ;

		if (type == Renderer::FOGTYPE_TABLE)
		{
			std::cerr << "table";
		}
		else
		{
			std::cerr << "vertex"; 
		}
		
		std::cerr << " fog mode to " << Renderer::FogModeToString(mode)
				  << "! Error Code: " << D3DErrorCodeToString(result) << std::endl;
		
		return false;
	}

	return false;
}
//End DirectXRenderer::SetFogMode




//=========================================================================
//! @function    DirectXRenderer::SetShadeMode
//! @brief       Set the triangle shading mode
//!              
//! @param       mode [in] Mode to set the shading mode to
//!						   SHADE_FLAT : The colour and specular component
//!										of the first vertex are used for the whole triangle
//!						   SHADE_GOURAUD : The colour and specular component is interpolated
//!										   over the triangle
//!              
//! @return      true if the mode could be set, false otherwise
//=========================================================================
bool DirectXRenderer::SetShadeMode ( Renderer::EShadeMode mode )
{

	HRESULT result = 0;

	switch ( mode )
	{
		case Renderer::SHADE_FLAT:
			result = m_device->SetRenderState(  D3DRS_SHADEMODE, D3DSHADE_FLAT );
			break;

		case Renderer::SHADE_GOURAUD:
			result = m_device->SetRenderState ( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
			break;
	}

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error setting shade mode to ";

		switch ( mode )
		{
			case Renderer::SHADE_FLAT:
				std::cerr << "SHADE_FLAT";
				break;
			
			case Renderer::SHADE_GOURAUD:
				std::cerr << "SHADE_FLAT";
				break;
		}

		std::cerr << " error code " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return false;
}
//End DirectXRenderer::SetShadeMode




//=========================================================================
//! @function    DirectXRenderer::SetCullingMode
//! @brief       Set the culling order of vertices
//!              
//! @param       mode [in] New culling mode
//!						   CULL_NONE			 :	Disables culling 
//!						   CULL_CLOCKWISE		 :  Clockwise triangles are culled
//!						   CULL_COUNTERCLOCKWISE :  Counter clockwise triangles are culled
//!
//! @return		 true if succeeded, false if the mode could not be set      
//! @throw       
//=========================================================================
bool DirectXRenderer::SetCullingMode ( Renderer::ECullMode mode )
{
	HRESULT result = 0;

	switch ( mode )
	{
		case Renderer::CULL_NONE:
			result = m_device->SetRenderState ( D3DRS_CULLMODE, D3DCULL_NONE );
			break;

		case Renderer::CULL_CLOCKWISE:
			result = m_device->SetRenderState ( D3DRS_CULLMODE, D3DCULL_CW );
			break;

		case Renderer::CULL_COUNTERCLOCKWISE:
			result = m_device->SetRenderState ( D3DRS_CULLMODE, D3DCULL_CCW );
			break;
	}

    if ( SUCCEEDED(mode) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Failed to set culling mode to ";

		switch ( mode )
		{
			case Renderer::CULL_NONE:
				std::cerr << "CULL_NONE";			
				break;

			case Renderer::CULL_CLOCKWISE:
				std::cerr << "CULL_CLOCKWISE";
				break;

			case Renderer::CULL_COUNTERCLOCKWISE:
				std::cerr << "CULL_COUNTERCLOCKWISE";
				break;
		}

		std::cerr << "! Error code " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return false;
}
//End DirectXRenderer::SetCullingMode




//=========================================================================
//! @function    DirectXRenderer::SetFillMode
//! @brief       Set the fill mode
//!              
//! @param       mode [in] New fill mode
//!						   FILL_POINT	  : Draw objects as points
//!						   FILL_WIREFRAME : Draw objects in wireframe
//!						   FILL_SOLID	  : Draw objects as solid
//!              
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetFillMode ( Renderer::EFillMode mode )
{
	HRESULT result = 0;

	switch ( mode )
	{
		case Renderer::FILL_POINT:
			result = m_device->SetRenderState ( D3DRS_FILLMODE, D3DFILL_POINT );
			break;

		case Renderer::FILL_WIREFRAME:
			result = m_device->SetRenderState ( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
			break;

		case Renderer::FILL_SOLID:
			result = m_device->SetRenderState ( D3DRS_FILLMODE, D3DFILL_SOLID );
			break;
	}

    if ( SUCCEEDED(mode) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Failed to set fill mode to ";

		switch ( mode )
		{
			case Renderer::FILL_POINT:
				std::cerr << "FILL_POINT";			
				break;

			case Renderer::FILL_WIREFRAME:
				std::cerr << "FILL_WIREFRAME";
				break;

			case Renderer::FILL_SOLID:
				std::cerr << "FILL_SOLID";
				break;
		}

		std::cerr << "! Error code " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return false;
}
//End DirectXRenderer::SetFillMode



//=========================================================================
//! @function    DirectXRenderer::GetClearColour
//! @brief       Return the value used to clear the colour buffer
//!              
//!              
//! @return      The value currently being used to clear the colour buffer
//=========================================================================
const Renderer::Colour4f& DirectXRenderer::GetClearColour() const
{
	return m_backgroundColourAsColour4;
}
//End DirectXRenderer::GetClearColour



//=========================================================================
//! @function    DirectXRenderer::Bind (HTexture, ETextureStageID)
//! @brief       Bind a texture to a texture stage
//!       
//!				 If a null texture handle is passed, then the texture stage
//!				 will be deactivated
//!
//! @param       texture [in] Handle to the texture to be bound
//! @param       stageID [in] Texture stage to bind the texture to
//!
//!              
//! @return      true if successful
//!				 false if failed
//=========================================================================
bool DirectXRenderer::Bind ( Renderer::HTexture& texture, Renderer::ETextureStageID stageID )
{
	if ( texture.IsNull() )
	{
		//
		m_device->SetTexture ( static_cast<DWORD>(stageID), 0 );
		
		//Set the currently bound texture for the texture stage
		m_textures[stageID] = Core::NullHandle();
	}
	else
	{

		if ( texture->Bind(stageID) )
		{			
			//Set up the texture coordinates, based on the texture type
			//TODO: Disable this when vertex shaders are enabled

			switch ( texture->Type() )
			{
				case Renderer::TEXTURE_1D:
					m_device->SetTextureStageState ( static_cast<DWORD>(stageID), D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT1);
					break;

				case Renderer::TEXTURE_2D:
					m_device->SetTextureStageState ( static_cast<DWORD>(stageID), D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
					break;

				case Renderer::TEXTURE_CUBEMAP:
					m_device->SetTextureStageState ( static_cast<DWORD>(stageID), D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT3);
					break;

				default:
					debug_assert ( false, "Invalid texture type!" );
					break;
			}

			//Set the currently bound texture for the texture stage
			m_textures[stageID] = texture;

			return true;
		}
		else
		{
			std::cerr << __FUNCTION__ ": Error, couldn't bind texture " << texture->Name() 
					<< " to stage " << static_cast<UInt>(stageID) << std::endl;
			
			//Set the currently bound texture for the texture stage
			m_textures[stageID] = Core::NullHandle();
			return false;
		}
	}

	return false;
}
//End DirectXRenderer::Bind (HTexture, ETextureStageID)



//=========================================================================
//! @function    DirectXRenderer::Bind (HVertexBuffer, UInt)
//! @brief       Bind a vertex buffer to a stream index
//!              
//! @param       buffer		 [in] Handle to the vertex buffer to be bound
//! @param       streamIndex [in] Stream index for the buffer to be bound to
//!
//!              
//! @return      true if successful
//!				 false if failed
//=========================================================================
bool DirectXRenderer::Bind ( Renderer::HVertexBuffer& buffer, UInt streamIndex )
{
	if ( buffer.IsNull() )
	{
		m_device->SetStreamSource ( streamIndex, 0, 0, 0 );
		return true;
	}

	return buffer->Bind(streamIndex);
}
//End DirectXRenderer::Bind



//=========================================================================
//! @function    DirectXRenderer::Bind(HIndexBuffer)
//! @brief       Bind an index buffer as the renderer's current index source
//!              
//! @param       buffer		 [in] Handle to the index buffer to be bound
//!
//!            
//! @return      true if successful
//!				 false if failed
//=========================================================================
bool DirectXRenderer::Bind ( Renderer::HIndexBuffer& buffer )
{
	if ( buffer.IsNull() )
	{
		m_device->SetIndices ( 0 );
		return true;
	}

	return buffer->Bind();
}
//End DirectXRenderer::Bind



//=========================================================================
//! @function    DirectXRenderer::Bind(VertexDeclaration&)
//! @brief       Bind a vertex declaration as the renderer's vertex declaration
//!              
//! @param       decl [in] Vertex declaration to use
//!              
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::Bind ( Renderer::HVertexDeclaration& decl )
{
	return decl->Bind();
}
//End DirectXRenderer::Bind



//=========================================================================
//! @function    DirectXRenderer::SetRenderState
//! @brief       Set a boolean render state on or off
//!              
//! @param       stateID [in] ID of the render state to set
//! @param       value	 [in] New ID for the render state
//!              
//! @return      true if the state could be set, false otherwise
//=========================================================================
bool DirectXRenderer::SetRenderState ( Renderer::EBoolStateID stateID, bool value )
{
	//Set initial value of dxValue
	DWORD dxValue = value ? TRUE : FALSE;
	HRESULT result = 0;

	switch ( stateID )
	{
		case Renderer::STATE_COLOURWRITE:
			dxValue = value ? D3DCOLORWRITEENABLE_ALPHA | D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_BLUE  | D3DCOLORWRITEENABLE_GREEN 
							: 0;

			result = m_device->SetRenderState ( D3DRS_COLORWRITEENABLE, dxValue );
			break;

		case Renderer::STATE_DEPTHTEST:
			dxValue = value ? D3DZB_TRUE : D3DZB_FALSE;
			
			result = m_device->SetRenderState ( D3DRS_ZENABLE, dxValue );
			break;

		case Renderer::STATE_DEPTHWRITE:
			result = m_device->SetRenderState ( D3DRS_ZWRITEENABLE, dxValue );
			break;

		case Renderer::STATE_ALPHATEST:
			result = m_device->SetRenderState ( D3DRS_ALPHATESTENABLE, dxValue);
			break;

		case Renderer::STATE_BLENDING:
			result = m_device->SetRenderState ( D3DRS_ALPHABLENDENABLE, dxValue);
			break;

		case Renderer::STATE_FOGBLENDING:
			result = m_device->SetRenderState ( D3DRS_FOGENABLE, dxValue );
			break;

		case Renderer::STATE_SPECULAR:
			result = m_device->SetRenderState ( D3DRS_SPECULARENABLE, dxValue );
			break;

		case Renderer::STATE_STENCIL:
			result = m_device->SetRenderState ( D3DRS_STENCILENABLE, dxValue );
			break;

		case Renderer::STATE_RANGEFOG:
			result = m_device->SetRenderState ( D3DRS_RANGEFOGENABLE, dxValue );
			break;

		case Renderer::STATE_CLIPPING:
			result = m_device->SetRenderState ( D3DRS_CLIPPING, dxValue );
			break;

		case Renderer::STATE_LIGHTING:
			result = m_device->SetRenderState ( D3DRS_LIGHTING, dxValue );
			break;

		case Renderer::STATE_VERTEXCOLOURS:
			result = m_device->SetRenderState ( D3DRS_COLORVERTEX, dxValue );
			break;

		case Renderer::STATE_NORMALISENORMALS:
			result = m_device->SetRenderState ( D3DRS_NORMALIZENORMALS, dxValue );
			break;

		case Renderer::STATE_POINTSPRITE:
			result = m_device->SetRenderState ( D3DRS_POINTSPRITEENABLE, dxValue );
			break;

		case Renderer::STATE_POINTSCALE:
			result = m_device->SetRenderState ( D3DRS_POINTSCALEENABLE, dxValue );
			break;

		case Renderer::STATE_SCISSORTEST:
			result = m_device->SetRenderState ( D3DRS_SCISSORTESTENABLE, dxValue );
			break;

		case Renderer::STATE_TWOSIDEDSTENCIL:
			result = m_device->SetRenderState ( D3DRS_TWOSIDEDSTENCILMODE, dxValue );
			break;

		case Renderer::STATE_SEPERATE_ALPHABLEND:
			result = m_device->SetRenderState (  D3DRS_SEPARATEALPHABLENDENABLE, dxValue );
			break;

		case Renderer::STATE_INDEXED_VERTEX_BLEND:
			result = m_device->SetRenderState ( D3DRS_INDEXEDVERTEXBLENDENABLE, dxValue ); 
			break;

		default:
			std::cerr << __FUNCTION__ ": Invalid state ID!" << std::endl;
			return false;
	}

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error, couldn't set state " << Renderer::BoolStateIDToString(stateID) 
				  << ". Error code " << D3DErrorCodeToString(result) << std::endl;
		
		return false;
	}
}
//End DirectXRenderer::SetRenderState



//=========================================================================
//! @function    DirectXRenderer::SetRenderState
//! @brief       Set a UInt render state
//!              
//! @param       stateID [in] ID of the render state to set
//! @param       value	 [in] New value for the render state
//!              
//! @return      true if the state could be set, false otherwise
//=========================================================================
bool DirectXRenderer::SetRenderState ( Renderer::EUIntStateID stateID, UInt value )
{
	HRESULT result = 0;

	switch ( stateID )
	{
		case Renderer::STATE_STENCILREFERENCE:
			m_device->SetRenderState ( D3DRS_STENCILREF, value );
			break;

		case Renderer::STATE_STENCILMASK:
			m_device->SetRenderState( D3DRS_STENCILMASK, value );
			break;

		case Renderer::STATE_STENCILWRITEMASK:
			m_device->SetRenderState ( D3DRS_STENCILWRITEMASK, value );
			break;

		default:
			std::cerr << __FUNCTION__ ": Invalid state ID!" << std::endl;
			return false;
	}

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error, couldn't set state " << Renderer::UIntStateIDToString(stateID) 
				  << ". Error code " << D3DErrorCodeToString(result) << std::endl;
		
		return false;
	}
}
//End DirectXRenderer::SetRenderState



//=========================================================================
//! @function    DirectXRenderer::SetRenderState
//! @brief       Set a Float render state
//!              
//! @param       stateID [in] ID of the render state to set
//! @param       value	 [in] New value for the render state	
//!              
//! @return      true if the state could be set, false otherwise
//=========================================================================
bool DirectXRenderer::SetRenderState ( Renderer::EFloatStateID stateID, Float value )
{
	HRESULT result = 0;

	switch ( stateID )
	{
		case Renderer::STATE_ALPHAREFERENCE:
			{
				//Direct3D stores the reference value in the lowest 8 bits
				//of a DWORD
				DWORD referenceValue = static_cast<UInt>(value * 255.0f);
				referenceValue &= 0xFF;

                result = m_device->SetRenderState( D3DRS_ALPHAREF, referenceValue );
			}
			break;
				
		case Renderer::STATE_FOGSTART:
			result = m_device->SetRenderState( D3DRS_FOGSTART, *reinterpret_cast<DWORD*>(&value) );
			break;
						
		case Renderer::STATE_FOGEND:
			result = m_device->SetRenderState( D3DRS_FOGEND, *reinterpret_cast<DWORD*>(&value) );
			break;
						
		case Renderer::STATE_FOGDENSITY:
			result = m_device->SetRenderState( D3DRS_FOGDENSITY, *reinterpret_cast<DWORD*>(&value) );
			break;
					
		case Renderer::STATE_DEPTHBIASVALUE:
			result = m_device->SetRenderState( D3DRS_DEPTHBIAS, *reinterpret_cast<DWORD*>(&value) );
			break;
				
		case Renderer::STATE_SLOPESCALEDEPTHBIASVALUE:
			result = m_device->SetRenderState( D3DRS_SLOPESCALEDEPTHBIAS, *reinterpret_cast<DWORD*>(&value) );
			break;
		
		case Renderer::STATE_POINTSIZE:
			result = m_device->SetRenderState( D3DRS_POINTSIZE, *reinterpret_cast<DWORD*>(&value) );
			break;
					
		case Renderer::STATE_POINTSIZEMIN:
			result = m_device->SetRenderState( D3DRS_POINTSIZE_MIN, *reinterpret_cast<DWORD*>(&value) );
			break;
					
		case Renderer::STATE_POINTSIZEMAX:
			result = m_device->SetRenderState( D3DRS_POINTSIZE_MAX, *reinterpret_cast<DWORD*>(&value) );
			break;
					
		case Renderer::STATE_POINTSCALE_A:
			result = m_device->SetRenderState( D3DRS_POINTSCALE_A, *reinterpret_cast<DWORD*>(&value) );
			break;
					
		case Renderer::STATE_POINTSCALE_B:
			result = m_device->SetRenderState( D3DRS_POINTSCALE_B, *reinterpret_cast<DWORD*>(&value) );
			break;
					
		case Renderer::STATE_POINTSCALE_C:
			result = m_device->SetRenderState( D3DRS_POINTSCALE_C, *reinterpret_cast<DWORD*>(&value) );
			break;
					
		default:
			std::cerr << __FUNCTION__ ": Invalid state ID!" << std::endl;
			return false;
	}

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error, couldn't set state " << Renderer::FloatStateIDToString(stateID) 
				  << ". Error code " << D3DErrorCodeToString(result) << std::endl;
		
		return false;
	}
}
//End DirectXRenderer::SetRenderState



//=========================================================================
//! @function    DirectXRenderer::SetTextureStageState
//! @brief       Set a texture stage state
//!              
//! @param		 stageID [in] Texture stage to set the state for
//! @param       stateID [in] ID of the state to set
//! @param       value	 [in] New value for the state
//!              
//! @return      true if the state could be set, false otherwise
//=========================================================================
bool DirectXRenderer::SetTextureStageState ( Renderer::ETextureStageID stageID, Renderer::ETextureStageStateID stateID, UInt value )
{
	HRESULT result = 0;

	switch ( stateID )
	{
		case Renderer::TEXSTAGE_ALPHAOP:
		case Renderer::TEXSTAGE_COLOUROP:
			{
				D3DTEXTUREOP op = ConvertTextureOpToD3D ( static_cast<Renderer::ETextureOp>(value) );
				result = m_device->SetTextureStageState ( static_cast<DWORD>(stageID), 
														  ConvertTextureStageStateTypeToD3D(stateID), 
														  op ); 
			}
			break;

		case Renderer::TEXSTAGE_ALPHAARG0:
		case Renderer::TEXSTAGE_ALPHAARG1:
		case Renderer::TEXSTAGE_ALPHAARG2:
		case Renderer::TEXSTAGE_COLOURARG0:
		case Renderer::TEXSTAGE_COLOURARG1:
		case Renderer::TEXSTAGE_COLOURARG2:
		case Renderer::TEXSTAGE_RESULTARG:
			{
				DWORD arg = ConvertTextureArgumentToD3D ( static_cast<Renderer::ETextureArgument>(value) );
				result = m_device->SetTextureStageState ( static_cast<DWORD>(stageID), 
														  ConvertTextureStageStateTypeToD3D(stateID), 
														  arg ); 
			}
			break;

		case Renderer::TEXSTAGE_TEXCOORDINDEX:
			result = m_device->SetTextureStageState ( static_cast<DWORD>(stageID), 
													  ConvertTextureStageStateTypeToD3D(stateID), 
													  value ); 
			break;
	}

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error, couldn't set texture stage state state " << Renderer::TextureStageStateIDToString(stateID) 
				  << ". Error code " << D3DErrorCodeToString(result) << std::endl;
		
		return false;
	}

}
//End DirectXRenderer::SetTextureStageState




//=========================================================================
//! @function    DirectXRenderer::SetTextureStageConstantColour
//! @brief       Set the constant colour for the texture stage, if supported
//!              
//! @param       stageID [in] Zero based index of the texture stage 
//! @param       value	 [in] Colour value to set the texture stage constant to
//!              
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetTextureStageConstantColour ( Renderer::ETextureStageID stageID, const Renderer::Colour4f& value )
{
	HRESULT result = m_device->SetTextureStageState ( stageID, D3DTSS_CONSTANT, value );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Couldn't set constant colour! Error code " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}

	return false;
}


//=========================================================================
//! @function    DirectXRenderer::SetColour
//! @brief       Set a colour render state value
//!              
//! @param       stateID [in]
//! @param       value	 [in]
//!              
//! @return      
//! @throw       
//=========================================================================
bool DirectXRenderer::SetColour ( Renderer::EColourStateID stateID, const Renderer::Colour4f& value )
{
	HRESULT result = 0;

	switch ( stateID )
	{
		case Renderer::STATE_FOGCOLOUR:
			result = m_device->SetRenderState( D3DRS_FOGCOLOR, value );
			break;
				
		case Renderer::STATE_TEXTUREFACTORCOLOUR:
			result = m_device->SetRenderState( D3DRS_TEXTUREFACTOR, value );
			break;

		case Renderer::STATE_AMBIENTLIGHTCOLOUR:
			result = m_device->SetRenderState( D3DRS_AMBIENT, value );
			break;
	
		case Renderer::STATE_BLENDFACTORCOLOUR:
			result = m_device->SetRenderState( D3DRS_BLENDFACTOR, value );
			break;
				
		default:
			debug_assert ( false, "Invalid state ID" );
	}


	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ << ": Failed to set ";

		switch ( stateID )
		{
			case Renderer::STATE_FOGCOLOUR:
				std::cerr << "fog colour";
				break;
					
			case Renderer::STATE_TEXTUREFACTORCOLOUR:
				std::cerr << "texture factor colour";
				break;

			case Renderer::STATE_AMBIENTLIGHTCOLOUR:
				std::cerr << "ambient light colour";
				break;
		
			case Renderer::STATE_BLENDFACTORCOLOUR:
				std::cerr << "blend factor colour";
				break;
		}

		std::cerr << ". Error code " << D3DErrorCodeToString(result) << std::endl;
	}


	return false;
}
//End DirectXRenderer::SetColour




//=========================================================================
//! @function    DirectXRenderer::SetMaterialColourSource
//! @brief       Set the material colour source for one of the colour modes
//!				 (ambient, diffuse, specular, or emissive)
//!				 The material colour source determines whether the colour
//!				 is taken from the vertex colours, or from the material
//!              
//! @param       sourceType [in]	STATE_DIFFUSE_MATERIAL_SOURCE,
//!									STATE_AMBIENT_MATERIAL_SOURCE,
//!									STATE_SPECULAR_MATERIAL_SOURCE or
//!									STATE_EMISSIVE_MATERIAL_SOURCE
//!
//! @param       source		[in]	MATERIALSOURCE_MATERIALCOLOUR - Get the colour from the material colour
//!									MATERIALSOURCE_DIFFUSECOLOUR  - Get the colour from the vertex diffuse colour
//!              
//! @return      true if succeeded, false if failed
//=========================================================================
bool DirectXRenderer::SetMaterialColourSource ( Renderer::EMaterialSourceType sourceType, Renderer::EMaterialSource source )
{
	D3DRENDERSTATETYPE state;

	switch (sourceType)
	{
		case Renderer::STATE_AMBIENT_MATERIAL_SOURCE:
			state = D3DRS_AMBIENTMATERIALSOURCE;
			break;

		case Renderer::STATE_DIFFUSE_MATERIAL_SOURCE:
			state = D3DRS_DIFFUSEMATERIALSOURCE;
			break;

		case Renderer::STATE_SPECULAR_MATERIAL_SOURCE:
			state = D3DRS_SPECULARMATERIALSOURCE;
			break;

		case Renderer::STATE_EMISSIVE_MATERIAL_SOURCE:
			state = D3DRS_EMISSIVEMATERIALSOURCE;
			break;

		default:
			debug_assert(false, "Invalid material source!");
	}

	DWORD matSource = 0;

	switch ( source )
	{
		case Renderer::MATERIALSOURCE_MATERIALCOLOUR:
			matSource = D3DMCS_MATERIAL;
			break;

		case Renderer::MATERIALSOURCE_DIFFUSECOLOUR:
			matSource = D3DMCS_COLOR1;
			break;

		default:
			debug_assert(false, "Invalid material colour source!");
	}

	HRESULT result = m_device->SetRenderState ( state, source );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ << ": Error, couldn't set material source ";

		switch (sourceType)
		{
			case Renderer::STATE_AMBIENT_MATERIAL_SOURCE:
				std::cerr << "STATE_AMBIENT_MATERIAL_SOURCE";
				break;

			case Renderer::STATE_DIFFUSE_MATERIAL_SOURCE:
				std::cerr << "STATE_DIFFUSE_MATERIAL_SOURCE";
				break;

			case Renderer::STATE_SPECULAR_MATERIAL_SOURCE:
				std::cerr << "STATE_SPECULAR_MATERIAL_SOURCE";
				break;

			case Renderer::STATE_EMISSIVE_MATERIAL_SOURCE:
				std::cerr << "STATE_EMISSIVE_MATERIAL_SOURCE";
				break;

			default:
				std::cerr << "(Invalid value)";
		}

		std::cerr << " to ";

		switch ( source )
		{
			case Renderer::MATERIALSOURCE_MATERIALCOLOUR:
				std::cerr << "MATERIALSOURCE_MATERIALCOLOUR";
				break;

			case Renderer::MATERIALSOURCE_DIFFUSECOLOUR:
				std::cerr << "MATERIALSOURCE_DIFFUSECOLOUR";
				break;

			default:
				std::cerr << "(Invalid value)";
		}

		std::cerr << "! Error code " << D3DErrorCodeToString(result) << std::endl;
		return false;
	}
}
//End DirectXRenderer::SetMaterialColourSource




//=========================================================================
//! @function    DirectXRenderer::SetMaterial
//! @brief       Set the material
//!              
//! @param       material [in] Material to set
//!              
//! @return      true if succeded, false if failed
//=========================================================================
bool DirectXRenderer::SetMaterial ( const Renderer::Material& material )
{
	D3DMATERIAL9 dxMaterial;

	dxMaterial.Ambient.r = material.GetAmbient().Red();
	dxMaterial.Ambient.g = material.GetAmbient().Green();
	dxMaterial.Ambient.b = material.GetAmbient().Blue();
	dxMaterial.Ambient.a = material.GetAmbient().Alpha();

	dxMaterial.Diffuse.r = material.GetDiffuse().Red();
	dxMaterial.Diffuse.g = material.GetDiffuse().Green();
	dxMaterial.Diffuse.b = material.GetDiffuse().Blue();
	dxMaterial.Diffuse.a = material.GetDiffuse().Alpha();

	dxMaterial.Emissive.r = material.GetEmissive().Red();
	dxMaterial.Emissive.g = material.GetEmissive().Green();
	dxMaterial.Emissive.b = material.GetEmissive().Blue();
	dxMaterial.Emissive.a = material.GetEmissive().Alpha();

	dxMaterial.Specular.r = material.GetSpecular().Red();
	dxMaterial.Specular.g = material.GetSpecular().Green();
	dxMaterial.Specular.b = material.GetSpecular().Blue();
	dxMaterial.Specular.a =	material.GetSpecular().Alpha();

	dxMaterial.Power = material.GetShininess();

	HRESULT result = m_device->SetMaterial ( &dxMaterial );

	if ( SUCCEEDED(result) )
	{
		return true;
	}
	else
	{
		std::cerr << __FUNCTION__ << ": Error setting material. Error code " << D3DErrorCodeToString(result) << std::endl;
	}
}
//End DirectXRenderer::SetMaterial



//=========================================================================
//! @function    DirectXRenderer::SetMatrix
//! @brief       Set one of the renderer's matrices
//!              
//!				 Sets one of the renderer's transformation matrices
//!
//! @param       type [in]	Identifier of matrix to set
//!						MAT_WORLD		: Set the world matrix
//!						MAT_VIEW		: Set the view matrix
//!						MAT_PROJECTION : Set the projection matrix
//!						MAT_TEXTURE0 - 
//!						MAT_TEXTUREN : The texture matrix for the specified texture stage
//!								
//!
//!
//! @param       mat  [in]	Matrix to set the renderer's internal matrix to
//!              
//=========================================================================
void DirectXRenderer::SetMatrix ( Renderer::EMatrixType type, const Math::Matrix4x4& mat )
{
	D3DXMATRIX dxMatrix;
	HRESULT result = 0;

	switch ( type )
	{
		case Renderer::MAT_WORLD:
			m_worldTransform = mat;
			SetD3DMatrixFromMatrix4x4 ( m_worldTransform, dxMatrix );
			result = m_device->SetTransform ( D3DTS_WORLD, &dxMatrix );
			
			//Flag the world view matrix as being out of date, so that it
			//will be regenerated next time it is requested
			m_worldViewOutOfDate = true;
			break;

		case Renderer::MAT_VIEW:
			m_viewTransform = mat;
			SetD3DMatrixFromMatrix4x4 ( m_viewTransform, dxMatrix );
			result = m_device->SetTransform ( D3DTS_VIEW, &dxMatrix );
			
			//Flag the world view matrix as being out of date, so that it
			//will be regenerated the next time it is requested
			m_worldViewOutOfDate = true;

			//Flag the view projection matrix as being out of date, so that
			//it gets regenerated the next time it's requested
			m_viewProjOutOfDate = true;
			break;

		case Renderer::MAT_PROJECTION:
			m_projectionTransform = mat;
			SetD3DMatrixFromMatrix4x4 ( m_projectionTransform, dxMatrix );
			result = m_device->SetTransform ( D3DTS_PROJECTION, &dxMatrix );

			//Flag the view projection matrix as being out of date, so that
			//it gets regenerated the next time it is requested
			m_viewProjOutOfDate = true;
			break;

		case Renderer::MAT_TEXTURE0:
			m_textureTransform[0] = mat;
			if ( m_textures[0] )
			{
				SetD3DTextureMatrixFromMatrix4x4 ( m_textureTransform[0], dxMatrix, m_textures[0]->Type() );
			}
			else
			{
				SetD3DMatrixFromMatrix4x4 ( m_textureTransform[0], dxMatrix );
			}
			result = m_device->SetTransform ( D3DTS_TEXTURE0, &dxMatrix );
			break;

		case Renderer::MAT_TEXTURE1:
			m_textureTransform[1] = mat;
			if ( m_textures[1] )
			{
				SetD3DTextureMatrixFromMatrix4x4 ( m_textureTransform[1], dxMatrix, m_textures[1]->Type() );
			}
			else
			{
				SetD3DMatrixFromMatrix4x4 ( m_textureTransform[1], dxMatrix );
			}
			result = m_device->SetTransform ( D3DTS_TEXTURE1, &dxMatrix );
			break;

		case Renderer::MAT_TEXTURE2:
			m_textureTransform[2] = mat;
			if ( m_textures[2] )
			{
				SetD3DTextureMatrixFromMatrix4x4 ( m_textureTransform[2], dxMatrix, m_textures[2]->Type() );
			}
			else
			{
				SetD3DMatrixFromMatrix4x4 ( m_textureTransform[2], dxMatrix );
			}
			result = m_device->SetTransform ( D3DTS_TEXTURE2, &dxMatrix );
			break;
	
		case Renderer::MAT_TEXTURE3:
			m_textureTransform[3] = mat;
			if ( m_textures[3] )
			{
				SetD3DTextureMatrixFromMatrix4x4 ( m_textureTransform[3], dxMatrix, m_textures[3]->Type() );
			}
			else
			{
				SetD3DMatrixFromMatrix4x4 ( m_textureTransform[3], dxMatrix );
			}
			result = m_device->SetTransform ( D3DTS_TEXTURE3, &dxMatrix );
			break;

		case Renderer::MAT_TEXTURE4:
			m_textureTransform[4] = mat;
			if ( m_textures[4] )
			{
				SetD3DTextureMatrixFromMatrix4x4 ( m_textureTransform[4], dxMatrix, m_textures[4]->Type() );
			}
			else
			{
				SetD3DMatrixFromMatrix4x4 ( m_textureTransform[4], dxMatrix );
			}
			result = m_device->SetTransform ( D3DTS_TEXTURE4, &dxMatrix );
			break;

		case Renderer::MAT_TEXTURE5:
			m_textureTransform[5] = mat;
			if ( m_textures[5] )
			{
				SetD3DTextureMatrixFromMatrix4x4 ( m_textureTransform[5], dxMatrix, m_textures[5]->Type() );
			}
			else
			{
				SetD3DMatrixFromMatrix4x4 ( m_textureTransform[5], dxMatrix );
			}
			result = m_device->SetTransform ( D3DTS_TEXTURE5, &dxMatrix );
			break;

		case Renderer::MAT_TEXTURE6:
			m_textureTransform[6] = mat;
			if ( m_textures[6] )
			{
				SetD3DTextureMatrixFromMatrix4x4 ( m_textureTransform[6], dxMatrix, m_textures[6]->Type() );
			}
			else
			{
				SetD3DMatrixFromMatrix4x4 ( m_textureTransform[6], dxMatrix );
			}
			SetD3DMatrixFromMatrix4x4 ( m_textureTransform[6], dxMatrix );
			result = m_device->SetTransform ( D3DTS_TEXTURE6, &dxMatrix );
			break;

		case Renderer::MAT_TEXTURE7:
			m_textureTransform[7] = mat;
			if ( m_textures[7] )
			{
				SetD3DTextureMatrixFromMatrix4x4 ( m_textureTransform[7], dxMatrix, m_textures[7]->Type() );
			}
			else
			{
				SetD3DMatrixFromMatrix4x4 ( m_textureTransform[7], dxMatrix );
			}
			SetD3DMatrixFromMatrix4x4 ( m_textureTransform[7], dxMatrix );
			result = m_device->SetTransform ( D3DTS_TEXTURE7, &dxMatrix );
			break;
	}

	if ( SUCCEEDED(result) )
	{
		return;
	}
	else
	{
		std::cerr << __FUNCTION__ ": Error, couldn't set matrix " << type << ": Error code " << D3DErrorCodeToString(result) << std::endl;
	}
}
//End DirectXRenderer::SetMatrix



//=========================================================================
//! @function    DirectXRenderer::SetProjectionOrtho
//! @brief       Helper function to set the projection matrix to an orthographic projection
//!				 using the specified parameters.
//!
//!				 Saves the application from having to query the renderer for its handedness
//!				 when generating a projection matrix
//!              
//! @param       left	[in] Left clipping plane
//! @param       right	[in] Right clipping plane
//! @param       bottom [in] Bottom clipping plane
//! @param       top	[in] Top clipping plane
//! @param       zNear	[in] Near clipping plane
//! @param       zFar	[in] Far clipping plane
//!              
//=========================================================================
void DirectXRenderer::SetProjectionOrtho ( Math::Scalar left, Math::Scalar right, Math::Scalar bottom, Math::Scalar top, 
										   Math::Scalar zNear, Math::Scalar zFar )
{
	D3DXMATRIX dxMatrix;

	//Create a projection matrix for a left handed system.
	//Because our math library uses a right handed system, we need a special
	//projection matrix that takes that into account
	Math::Matrix4x4::CreateOrthographicProjectionLH ( m_projectionTransform, left, right, 
													  bottom, top, zNear, zFar );


	//Copy the matrix into a DirectX Matrix
	SetD3DMatrixFromMatrix4x4( m_projectionTransform, dxMatrix );

	//Set the device's projection transform
	m_device->SetTransform ( D3DTS_PROJECTION, &dxMatrix );

	//Flag the view projection matrix as being out of date
	m_viewProjOutOfDate = true;
}
//End DirectXRenderer::SetProjectionOrtho



//=========================================================================
//! @function    DirectXRenderer::SetProjectionPerspective
//! @brief       Set the projection matrix to a perspective projection
//!
//!				 Saves the application from having to bother about the handedness of the renderer
//!				 when generating a projection matrix
//!
//! @param       fovY			[in] Field of view
//! @param       aspectRatio	[in] Ratio of width to height
//! @param       zNear			[in] Near clipping plane
//! @param       zFar			[in] Far clipping plane
//!              
//=========================================================================
void DirectXRenderer::SetProjectionPerspective ( Math::Scalar fovY, Math::Scalar aspectRatio, Math::Scalar zNear, Math::Scalar zFar  )
{
	D3DXMATRIX dxMatrix;

	//Create a projection matrix for a left handed system.
	//Because our math library uses a right handed system, we need a special
	//projection matrix that takes that into account
	Math::Matrix4x4::CreatePerspectiveProjectionLH ( m_projectionTransform, fovY, aspectRatio, zNear, zFar );

	//Copy the matrix into a DirectX Matrix
	SetD3DMatrixFromMatrix4x4( m_projectionTransform, dxMatrix );

	//Set the device's projection transform
	m_device->SetTransform ( D3DTS_PROJECTION, &dxMatrix );

	//Flag the view projection matrix as being out of date
	m_viewProjOutOfDate = true;

}
//End DirectXRenderer::SetProjectionPerspective




//=========================================================================
//! @function    DirectXRenderer::SetViewLookAt
//! @brief       Set the view matrix to a UVN camera matrix
//!              
//!				 Saves the application from having to know about the renderer's
//!				 handedness when generating a camera transform
//!
//! @param       eye	[in] Eye position
//! @param       up		[in] Up vector
//! @param       lookAt	[in] Look at position
//!              
//=========================================================================
void DirectXRenderer::SetViewLookAt ( const Math::Vector3D& eye, const Math::Vector3D& up, const Math::Vector3D& lookAt )
{
	D3DXMATRIX dxMatrix;

	//Create a  UVN camera matrix for a left handed system.
	//Because our math library uses a right handed system, we need a special
	//projection matrix that takes that into account
	Math::Matrix4x4::CreateUVNCameraMatrixLH ( m_viewTransform, eye, up, lookAt );

	//Copy the matrix into a DirectX Matrix
	SetD3DMatrixFromMatrix4x4( m_viewTransform, dxMatrix );

	//Set the device's view transform
	m_device->SetTransform ( D3DTS_VIEW, &dxMatrix );

	//Flag the world view matrix as being out of date
	m_worldViewOutOfDate = true;

	//Flag the view projection matrix as being out of date
	m_viewProjOutOfDate = true;

}
//End DirectXRenderer::SetViewLookAt




//=========================================================================
//! @function    DirectXRenderer::GetMatrix
//! @brief       Get the value of one of the non-ready-only matrices
//!              
//! @param       type [in]	ID of the matrix to get
//!						    The following values can be used
//!							MAT_WORLD	-	Get the world matrix
//!							MAT_VIEW	-	Get the view matrix
//!							MAT_PROJECTION	-	Get the projection matrix
//!							MAT_TEXTURE0 - MAT_TEXTUREN : Get the texture matrix for the texture stage
//!														  specified by the zero based suffix, 
//!														 MAT_TEXTURE1 would be the texture matrix
//!														 for the second texture stage
//!
//! @param       mat  [out] Matrix to hold the result
//!              
//=========================================================================
void DirectXRenderer::GetMatrix ( Renderer::EMatrixType type, Math::Matrix4x4& mat )
{
	switch ( type )
	{
		case Renderer::MAT_WORLD:
			mat = m_worldTransform;
			
		case Renderer::MAT_VIEW:
			mat = m_viewTransform;

		case Renderer::MAT_PROJECTION:
			mat = m_projectionTransform;

		case Renderer::MAT_TEXTURE0:
			mat = m_textureTransform[0];

		case Renderer::MAT_TEXTURE1:
			mat = m_textureTransform[1];
		
		case Renderer::MAT_TEXTURE2:
			mat = m_textureTransform[2];
		
		case Renderer::MAT_TEXTURE3:
			mat = m_textureTransform[3];
		
		case Renderer::MAT_TEXTURE4:
			mat = m_textureTransform[4];
		
		case Renderer::MAT_TEXTURE5:
			mat = m_textureTransform[5];
		
		case Renderer::MAT_TEXTURE6:
			mat = m_textureTransform[6];
		
		case Renderer::MAT_TEXTURE7:
			mat = m_textureTransform[7];
	}
}
//End DirectXRenderer::GetMatrix



//=========================================================================
//! @function    DirectXRenderer::GetMatrix
//! @brief       Get the value of one of the read-only matrices
//!				 These matrices are generated from the other matrices.
//!				 if the matrix is out of date, then it will be regenerated
//!              
//! @param       type [in] ID of the matrix to get
//!						   The following values can be used
//!						   MAT_WORLDVIEW	-	Get the matrix equal to world matrix * view matrix 
//!						   MAT_VIEWPROJ		-	Get the matrix equal to view matrix * projection matrix
//!
//! @param       mat  [out] Matrix to hold the result
//!              
//=========================================================================
void DirectXRenderer::GetMatrix ( Renderer::EReadOnlyMatrixType type, Math::Matrix4x4& mat )
{
	switch ( type )
	{
		case Renderer::MAT_WORLDVIEW:

			//If the worldView matrix is out of date then regenerate it
			if ( m_worldViewOutOfDate )
			{
				m_worldViewMatrix = m_worldTransform;
				m_worldViewMatrix *= m_viewTransform;
				
				m_worldViewOutOfDate = false;
			}

			mat = m_worldViewMatrix;

		case Renderer::MAT_VIEWPROJECTION:

			//If the viewProj matrix is out of date then regenerate it
			if ( m_viewProjOutOfDate )
			{
				m_viewProjMatrix = m_viewTransform;
				m_viewProjMatrix *= m_projectionTransform;
				
				m_viewProjOutOfDate = false;
			}

			mat = m_viewProjMatrix;
	}
}
//End DirectXRenderer::GetMatrix



//=========================================================================
//! @function    DirectXRenderer::Enter2DMode
//! @brief       Set up the renderer for for rendering 2D
//!              objects, such as text, and user interface/HUD
//!              
//!				 This must be called before rendering any 2D output,
//!				 or there will be incorrect results when rendering text/user interface
//!				 unless the application sets up the renderer state for 2D manually
//!
//!				 Note, that although the DirectX projection, view and world matrices are altered,
//!				 (as in the ones stored in the device) the actual world, view, and projection matrices stored in the renderer
//!				 aren't altered. Therefore, any requests for the world, view, or projection matrices
//!				 will return the same matrices that existed before
//!				 this call was made. This is normal behaviour
//!
//=========================================================================
void DirectXRenderer::Enter2DMode()
{
	Math::Matrix4x4 projection;
	Math::Matrix4x4 world;
	D3DXMATRIX		dxMatrix;

	//Create an orthographic projection matrix
	Math::Matrix4x4::CreateOrthographicProjectionLH ( projection, 0, 
													  Window().Width(), Window().Height(), 
													  0, 0.0f, 10.0f );
	SetD3DMatrixFromMatrix4x4 ( projection, dxMatrix );
	m_device->SetTransform ( D3DTS_PROJECTION, &dxMatrix );

	//Set the world matrix
	world.Translate( Math::Vector3D(0.0f, 0.0f, -1.0f) );
	SetD3DMatrixFromMatrix4x4 ( world, dxMatrix );
	m_device->SetTransform ( D3DTS_WORLD, &dxMatrix );

	//Set the view matrix to the identity matrix
	D3DXMatrixIdentity( &dxMatrix );
	m_device->SetTransform ( D3DTS_VIEW, &dxMatrix );
}
//End DirectXRenderer::Enter2DMode



//=========================================================================
//! @function    DirectXRenderer::Exit2DMode
//! @brief       Return the renderer to its previous state, before entering 2D mode
//!              
//=========================================================================
void DirectXRenderer::Exit2DMode()
{
	D3DXMATRIX dxMatrix;
	SetD3DMatrixFromMatrix4x4 ( m_projectionTransform, dxMatrix );

	m_device->SetTransform ( D3DTS_PROJECTION, &dxMatrix );
}
//End DirectXRenderer::Exit2DMode



//=========================================================================
//! @function    DirectXRenderer::Supports
//! @brief       Indicates whether or not the device is capable of supporting
//!				 a feature
//!              
//! @param       capability [in] Feature to check for compatibility
//!              
//! @return      true if the device supports the feature
//!				 false if the device does not support the feature
//=========================================================================
bool DirectXRenderer::Supports( Renderer::ERendererCapability capability ) const
{
	return DirectX9Renderer::Supports(m_deviceCaps, capability);
}
//End DirectXRenderer::Supports



//=========================================================================
//! @function    DirectXRenderer::GetDeviceProperty
//! @brief       Return an integer property of the device, such as MaxStreams 
//!              
//! @param       capability [in] Property to return
//!              
//! @return      Value of the property
//=========================================================================
UInt DirectXRenderer::GetDeviceProperty ( Renderer::EIntegerRendererCapability capability ) const
{
	return DirectX9Renderer::GetPropertyFromDeviceCaps ( m_deviceCaps, capability );
}
//End DirectXRenderer::GetDeviceProperty



//=========================================================================
//! @function    DirectXRenderer::GetDeviceProperty
//! @brief       Return a floating point property of the device
//!              
//! @param       capability [in] Property to retrieve
//!              
//! @return      The value of the property
//=========================================================================
Float DirectXRenderer::GetDeviceProperty ( Renderer::EFloatRendererCapability capability ) const
{
	return DirectX9Renderer::GetPropertyFromDeviceCaps ( m_deviceCaps, capability );
}
//End DirectXRenderer::GetDeviceProperty



//=========================================================================
//! @function    DirectXRenderer::RequiresRestore
//! @brief       Indicates whether or not the device is lost
//!              
//!              
//! @return      true if the device has been lost
//!				 false if the device has not been lost
//!
//! @throw		 If a driver internal error is detected, then a 
//!				 RendererError is thrown
//=========================================================================
bool DirectXRenderer::RequiresRestore () const
{
	HRESULT result = 0;
	result = m_device->TestCooperativeLevel();

	if ( ( result == D3DERR_DEVICELOST )
		|| ( result == D3DERR_DEVICENOTRESET ) )
	{
		return true;
	}

	if ( result == D3DERR_DRIVERINTERNALERROR )
	{
		throw Renderer::RendererError ( "Graphics Driver internal error! Application must exit!\n", 
									D3DERR_DRIVERINTERNALERROR, __FILE__, __FUNCTION__, __LINE__ );
	}

	return false;
}
//End DirectXRenderer::RequiresRestore



//=========================================================================
//! @function    DirectXRenderer::PrepareForRestore
//! @brief       Prepare for a restore operation
//!              
//! @param		 forceRestore [in] Meaningless in this context, ignored
//!
//=========================================================================
void DirectXRenderer::PrepareForRestore ( bool forceRestore )
{
	m_indexBufferManager->PrepareForRestore( false );
	m_vertexBufferManager->PrepareForRestore( false );
	m_textureManager->PrepareForRestore( false );
}
//End DirectXRenderer::PrepareForRestore



//=========================================================================
//! @function    DirectXRenderer::Restore
//! @brief       Restores the DirectX device if it has been lost
//!				 If the device has not been lost then the method simply returns              
//!
//!              Blocks, and keeps trying to restore until the device has been restored
//!
//!	@param		 forceRestore [in] Meaningless in this context, ignored
//!
//=========================================================================
void DirectXRenderer::Restore ( bool forceRestore )
{
	if ( !RequiresRestore() )
	{
		return;
	}

	std::cerr << "Error! Direct3D device lost, attempting to restore" << std::endl;
	PrepareForRestore( false );

	UInt count = 0;

	HRESULT result = D3DERR_DEVICELOST;

	while ( result != D3D_OK )
	{
		while ( result != D3DERR_DEVICENOTRESET )
		{
			result = m_device->TestCooperativeLevel();
			Sleep( 250 );
			
			Window().ProcessMessageQueue();
		}

		result = m_device->Reset(&m_presentParameters);

		if ( result == D3DERR_DRIVERINTERNALERROR )
		{
			throw Renderer::RendererError ( "Graphics Driver internal error! Application must exit!\n", 
											D3DERR_DRIVERINTERNALERROR, __FILE__, __FUNCTION__, __LINE__ );
		}
	}

	m_indexBufferManager->Restore( false );
	m_vertexBufferManager->Restore( false );
	m_textureManager->Restore( false );

	std::cout << "Restored Direct 3D device successfully!" << std::endl;
}
//End DirectXRenderer::Restore



//=========================================================================
//! @function    DirectXRenderer::Resize
//! @brief       Responds to a window resize
//!
//! @param       width  [in]
//! @param       height [in]
//!              
//=========================================================================
void DirectXRenderer::Resize ( UInt width, UInt height )
{

}
//End DirectXRenderer::Resize



//=========================================================================
//! @function    DirectXRenderer::ScreenWidth
//! @brief       Return the width of the screen mode, or window, in pixels
//!              
//!              
//! @return      The width of the display mode
//=========================================================================
UInt DirectXRenderer::ScreenWidth() const
{
	return m_screenWidth;
}
//End DirectXRenderer::ScreenWidth



//=========================================================================
//! @function    DirectXRenderer::ScreenHeight
//! @brief       Return the height of the screen mode, or window, in pixels
//!              
//!              
//! @return      The height of the display mode
//=========================================================================
UInt DirectXRenderer::ScreenHeight() const
{
	return m_screenHeight;
}
//End DirectXRenderer::ScreenHeight



//=========================================================================
// Private methods
//=========================================================================



//=========================================================================
//! @function    DirectXRenderer::CreateD3D
//! @brief       Create the Direct3D object
//!              
//! @throw       RendererError
//=========================================================================
void DirectXRenderer::CreateD3D ( )
{
	m_d3d = Direct3DCreate9 ( D3D_SDK_VERSION );
	
	if ( !m_d3d )
	{
		//Direct3D object was not created
		throw Renderer::RendererError ( "Error! Could not create Direct3D device!", 0,
										__FILE__, __FUNCTION__, __LINE__ );
	}

	HRESULT result = m_d3d->GetDeviceCaps( m_adapter, m_deviceType, &m_deviceCaps );

	if ( result == D3D_OK )
	{	
		std::clog << "Direct3DCreate9 successful. IDirect3D9 object created!" << std::endl;
	}
	else
	{
		std::cerr << "Error, GetDeviceCaps returned " << D3DErrorCodeToString(result) << std::endl;
	}

	// Printing the renderer debug info causes problems with the NVPerfHUD performance analysis tool
	//
	// The following console variable allows the debug info to be disabled
	Core::ConsoleBool ren_printdebuginfo ( "ren_printdebuginfo", true );

	if ( ren_printdebuginfo )
	{
		PrintAdapterDebugInfo();
		PrintDeviceCaps();
	}

	//Fill the list of display modes
	FillDisplayModeList();
}
//End DirectXRenderer::CreateD3D



//=========================================================================
//! @function    DirectXRenderer::CreateDevice
//! @brief       Create the Direct3D device
//!              
//!              
//! @throw       RendererError
//=========================================================================
void DirectXRenderer::CreateDevice ( )
{
	Core::ConsoleUInt init_bpp("init_bpp", 32 );
	Core::ConsoleUInt init_mode( "init_mode", 0 );
	Core::ConsoleBool init_fullscreen ( "init_fullscreen", false );

	//Setup present parameters
	if ( init_fullscreen )
	{
		SetupPresentParamsForFullScreen( init_mode, init_bpp );
	}
	else
	{
		SetupPresentParamsForWindowed( init_mode, init_bpp );
	}

	//Set up behaviour flags
	DWORD behaviourFlags = 0;	
	if (m_deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		behaviourFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		behaviourFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//Create the device
	HRESULT result = 0;
	if ( m_deviceType == D3DDEVTYPE_HAL )
	{

		//The following code allows the use of the nVidia profiling tool
		//NVPerfHUD in debug builds
		#ifdef DEBUG_BUILD
		
			// Look for 'NVIDIA NVPerfHUD' adapter 
			// If it is present, override default settings 
			for (UINT adapter=0;adapter<m_d3d->GetAdapterCount();adapter++) 
			{
				D3DADAPTER_IDENTIFIER9 identifier;
				HRESULT res; 
				res = m_d3d->GetAdapterIdentifier(adapter,0,&identifier); 
				
				if (strcmp(identifier.Description,"NVIDIA NVPerfHUD") == 0) 
				{ 
					m_adapter = adapter; 
					m_deviceType = D3DDEVTYPE_REF; 
					break; 
				} 
			}

		#endif

		result = m_d3d->CreateDevice ( m_adapter, m_deviceType, Window().WindowHandle(),
										behaviourFlags, &m_presentParameters, &m_device );
	}
	else
	{
		result = m_d3d->CreateDevice ( m_adapter, m_deviceType, Window().WindowHandle(),
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_presentParameters, &m_device );
	}

	if ( SUCCEEDED(result) )
	{
		std::clog << "Direct3D device created successfully!" << std::endl;
	}
	else
	{
		std::ostringstream errorMsg;
		errorMsg << "Could not create Direct3D device!\nError code: " << D3DErrorCodeToString(result);

		throw Renderer::RendererError( errorMsg.str().c_str(), result, 
									__FILE__, __FUNCTION__, __LINE__ );
	}
}
//End DirectXRenderer::CreateDevice



//=========================================================================
//! @function    DirectXRenderer::CreateRenderWindow
//! @brief       Create the window that will do the rendering
//!              
//=========================================================================
void DirectXRenderer::CreateRenderWindow ( )
{
	//Get the display mode variables from the console
	Core::ConsoleUInt init_bpp("init_bpp", 32 );
	Core::ConsoleUInt init_mode( "init_mode", 0 );
	Core::ConsoleBool init_fullscreen ( "init_fullscreen", false );

	const Renderer::DisplayMode& mode(GetDisplayModeList().GetMode(init_mode, init_bpp));

	m_window = boost::shared_ptr<Renderer::RendererWindow>
									( new Renderer::RendererWindow("DirectX9Renderer", "DirectX9Renderer",
																	0, 0, mode.Width(), mode.Height()) ); 

	m_window->Initialise();
	m_window->SetFullScreenStyle ( init_fullscreen );

}
//End DirectXRenderer::CreateRenderWindow ( )



//=========================================================================
//! @function    DirectXRenderer::SetupPresentParamsForFullScreen
//! @brief       Set up the present parameters for full screen mode
//!              
//! @param		 modeIndex [in] Index of display mode
//! @param		 bpp	   [in] Bits per pixel of display mode
//!
//=========================================================================
void DirectXRenderer::SetupPresentParamsForFullScreen ( UInt modeIndex, UInt bpp)
{
	ZeroMemory (&m_presentParameters, sizeof(m_presentParameters));
	D3DFORMAT modeFormat;
	modeFormat = (bpp == 32 )?  D3DFMT_X8R8G8B8 : D3DFMT_R5G6B5;

	//First we need to get the correct Direct3D format, depending on whether
	//we're going for a 16-bit or 32-bit mode
	D3DFORMAT backBufferFormat;
	backBufferFormat = (bpp == 32 )?  D3DFMT_A8R8G8B8 : D3DFMT_R5G6B5;

	HRESULT result = 0;
	result = m_d3d->CheckDeviceType( m_adapter, m_deviceType, 
							modeFormat, backBufferFormat, TRUE );

	if ( FAILED(result) )
	{
		throw Renderer::RendererError ( "Error! Display mode not supported!",
								   result, __FILE__, __FUNCTION__, __LINE__ );
	}

	//Get a suitable depth/stencil format
	D3DFORMAT depthStencil;
	bool supportsStencil;
	GetDepthStencilFormat ( modeFormat, depthStencil, supportsStencil ); 

	std::clog << "Using depth/stencil format " << D3DFormatToString(depthStencil) << std::endl;

	m_presentParameters.BackBufferWidth =  GetDisplayModeList().GetMode(modeIndex, bpp).Width();
	m_presentParameters.BackBufferHeight = GetDisplayModeList().GetMode(modeIndex, bpp).Height();
	m_presentParameters.BackBufferFormat = backBufferFormat;
	m_presentParameters.BackBufferCount = 2;
	m_presentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_presentParameters.hDeviceWindow = Window().WindowHandle( );
	m_presentParameters.Windowed = FALSE;
	m_presentParameters.EnableAutoDepthStencil = TRUE;
	m_presentParameters.AutoDepthStencilFormat = depthStencil;
	m_presentParameters.FullScreen_RefreshRateInHz = GetDisplayModeList().GetMode(modeIndex, bpp).RefreshRate();
	m_presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_presentParameters.Flags = 0;

}
//End DirectXRenderer::SetupPresentParamsForFullScreen



//=========================================================================
//! @function    DirectXRenderer::SetupPresentParamsForWindowed
//! @brief       Set up the present paramters for windowed mode
//!              
//! @param		 modeIndex [in] Index of display mode
//! @param		 bpp	   [in] Bits per pixel of display mode
//!
//=========================================================================
void DirectXRenderer::SetupPresentParamsForWindowed ( UInt modeIndex, UInt bpp )
{
	ZeroMemory (&m_presentParameters, sizeof(m_presentParameters));

	//First we have to get the desktop display mode
	D3DDISPLAYMODE desktopMode;
	ZeroMemory (&desktopMode, sizeof(desktopMode));

	HRESULT result = m_d3d->GetAdapterDisplayMode( m_adapter, &desktopMode );

	if ( FAILED(result) )
	{
		std::cerr << __FUNCTION__ ". Couldn't get desktop display mode! Error " 
				  << D3DErrorCodeToString ( result )
				  << std::endl;
	}

	//Check that the display mode is supported in windowed mode

	//First we need to get the correct Direct3D format, depending on whether
	//we're going for a 16-bit or 32-bit mode
	D3DFORMAT backBufferFormat;
	backBufferFormat = (bpp == 32)?  D3DFMT_A8R8G8B8 : D3DFMT_R5G6B5;
	
	result = m_d3d->CheckDeviceType( m_adapter, m_deviceType, 
							desktopMode.Format, backBufferFormat, TRUE );

	if ( FAILED(result) )
	{
		throw Renderer::RendererError ( "Error! Display mode not supported!",
								   result, __FILE__, __FUNCTION__, __LINE__ );
	}

	//Get a suitable depth/stencil format
	D3DFORMAT depthStencil;
	bool supportsStencil;
	GetDepthStencilFormat ( desktopMode.Format, depthStencil, supportsStencil ); 

	std::clog << "Using depth/stencil format " << D3DFormatToString(depthStencil) << std::endl;


	//Now setup the display parameters
	m_presentParameters.BackBufferWidth =  GetDisplayModeList().GetMode(modeIndex, bpp).Width();
	m_presentParameters.BackBufferHeight = GetDisplayModeList().GetMode(modeIndex, bpp).Height();
	m_presentParameters.BackBufferFormat = backBufferFormat;
	m_presentParameters.BackBufferCount = 2;
	m_presentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_presentParameters.hDeviceWindow = Window().WindowHandle();
	m_presentParameters.Windowed = TRUE;
	m_presentParameters.EnableAutoDepthStencil = TRUE;
	m_presentParameters.AutoDepthStencilFormat = depthStencil;
	m_presentParameters.FullScreen_RefreshRateInHz = 0;
	m_presentParameters.PresentationInterval = 0;
	m_presentParameters.Flags = 0;

}
//DirectXRenderer::SetupPresentParamsForWindowed




//=========================================================================
//! @function    DirectXRenderer::FillDisplayModeList
//! @brief       Fills the display mode list with the display modes
//!              that this device can support in hardware
//!              
//=========================================================================
void DirectXRenderer::FillDisplayModeList ( )
{
	HRESULT result = 0;
	D3DDISPLAYMODE mode;
	ZeroMemory ( &mode, sizeof(mode) );
	
	std::clog << "Getting list of supported display modes:\n"
				 "===========================================\n";		

	//Formats we will support
	const D3DFORMAT formats[] = 
	{
		D3DFMT_R5G6B5,
		D3DFMT_X8R8G8B8
	};
	
	UInt numFormats = sizeof(formats) / sizeof(D3DFORMAT);

	bool supportsWindowed = false;
	bool supportsStencil = false;

	for ( UInt formatIndex = 0; formatIndex < numFormats; ++formatIndex )
	{
		if ( !CheckFormat(formats[formatIndex], supportsWindowed) )
		{
			continue;
		}

		D3DFORMAT depthStencil;
		//Check whether our buffer format supports the stencil buffer
		GetDepthStencilFormat(formats[formatIndex], depthStencil, supportsStencil);

		UInt modeCount = m_d3d->GetAdapterModeCount ( m_adapter, formats[formatIndex] );

		std::clog << D3DFormatToString(formats[formatIndex]) << " - "
				  << modeCount << " display modes found\n";


		for ( UInt index = 0; index < modeCount; ++index )
		{
			result = m_d3d->EnumAdapterModes ( m_adapter, formats[formatIndex], index, &mode );

			if ( (mode.Width < m_minModeWidth) &&
				 (mode.Height < m_minModeHeight) )
			{
				//Display mode too small to bother with, just ignore it
				continue;
			}
				
			if ( formats[formatIndex] == D3DFMT_R5G6B5 )
			{
				Renderer::DisplayMode displayMode = Renderer::DisplayMode( index, mode.Width, mode.Height, 
																16, mode.RefreshRate, supportsWindowed,
																supportsStencil );

				m_displayModes.AddMode ( Renderer::DisplayModeList::BITS_16, displayMode );
				std::clog << index << ": " << displayMode.Description() << " " 
						 << displayMode.BitsPerPixel() << "bit" << std::endl;

			}
			else
			{

				Renderer::DisplayMode displayMode = Renderer::DisplayMode ( index, mode.Width, mode.Height, 
																32, mode.RefreshRate, supportsWindowed,
																supportsStencil );

				m_displayModes.AddMode ( Renderer::DisplayModeList::BITS_32, displayMode );
				std::clog << index << ": " << displayMode.Description() << " " 
								<< displayMode.BitsPerPixel() << "bit" << std::endl;
			}
		}
		//End for ( UInt index = 0; index < modeCount; ++index )

		std::clog << std::endl;

	}
	//End for ( UInt formatIndex = 0; formatIndex < numFormats; ++formatIndex )

}
//End DirectXRenderer::FillDisplayModeList



//=========================================================================
//! @function    DirectXRenderer::CheckFormat
//! @brief       Check a format for hardware support
//!              
//! @param       format			 [in]  Format to check for hardware support
//! @param		 supportWindowed [in]  Returns whether or not the format is supported
//!										in windowed mode
//! @return      
//! @throw       
//=========================================================================
bool DirectXRenderer::CheckFormat ( D3DFORMAT format, bool& supportWindowed )
{
	HRESULT result = 0;
	bool supportFullScreen = false;
	D3DFORMAT desiredBackBufferFormat;

	if ( format == D3DFMT_R5G6B5 )
	{
		desiredBackBufferFormat = D3DFMT_R5G6B5;
	}
	else
	{
		desiredBackBufferFormat = D3DFMT_A8R8G8B8;
	}

	//=========================================================================
    // First check support for fullscreen mode
    //=========================================================================

	result = m_d3d->CheckDeviceType ( m_adapter, m_deviceType, format, desiredBackBufferFormat, FALSE );

	if ( result == S_OK )
	{
		std::clog << D3DFormatToString(desiredBackBufferFormat) 
				  <<  " - Full screen mode supported" << std::endl;

		supportFullScreen = true;
	}
	else
	{
		std::clog << D3DFormatToString(desiredBackBufferFormat) 
				  <<  " - Full screen mode not supported - Error: "
				  << D3DErrorCodeToString( result ) << std::endl;

		supportFullScreen = false;
	}

    //=========================================================================
    // Check for support in windowed mode
    //=========================================================================
	
	//First Get the current display mode
	D3DDISPLAYMODE mode;

	if ( FAILED(result = m_d3d->GetAdapterDisplayMode ( m_adapter, &mode )) )
	{
		std::cerr << "GetAdapterDisplayMode failed! Error code " << D3DErrorCodeToString( result ) << std::endl;
		supportWindowed = false;
	}
	else
	{

		result = m_d3d->CheckDeviceType ( m_adapter, m_deviceType, mode.Format, desiredBackBufferFormat, TRUE );

		if ( result == S_OK )
		{
			std::clog << D3DFormatToString(desiredBackBufferFormat) 
				  <<  " - Windowed screen mode supported" << std::endl;
			supportWindowed = true;
		}
		else
		{
			std::clog << D3DFormatToString(desiredBackBufferFormat) 
					  <<  " - Windowed screen mode not supported. Error: " 
					  << D3DErrorCodeToString( result ) << std::endl;
			supportWindowed = false;
		}
	}

	return supportFullScreen;
}
//End DirectXRenderer::CheckFormat



//=========================================================================
//! @function    DirectXRenderer::GetDepthStencilFormat
//! @brief       Get the best depth buffer and stencil buffer format
//!				 for the back buffer format supplied         
//!
//! @param       format			 [in] Back buffer format
//! @param       depthStencil	 [out] DepthStencil buffer format
//! @param		 supportsStencil [out] Indicated whether the format we found
//!									   contains a stencil buffer
//!              
//! @return      true if a depth/stencil buffer format was found
//!				 false if a depth/stencil buffer format could not be found
//! @throw       
//=========================================================================
bool DirectXRenderer::GetDepthStencilFormat ( D3DFORMAT modeFormat, D3DFORMAT& depthStencil, bool& supportsStencil )
{

	depthStencil = D3DFMT_D16;

	//Get the desired back buffer format from the format
	D3DFORMAT desiredBackBufferFormat;

	if ( modeFormat == D3DFMT_R5G6B5 )
	{
		desiredBackBufferFormat = D3DFMT_R5G6B5;
	}
	else
	{
		desiredBackBufferFormat = D3DFMT_A8R8G8B8;
	}

	//Depth stencil formats to search for, in order most preferred first
	const D3DFORMAT formats[] = 
	{
		D3DFMT_D24S8,
		D3DFMT_D24X4S4,
		D3DFMT_D15S1,
		D3DFMT_D32,
		D3DFMT_D16
	};

	UInt formatCount = sizeof(formats) / sizeof(D3DFORMAT);
	HRESULT result = 0;

	for ( UInt index=0; index < formatCount; ++index )
	{
		if ( SUCCEEDED ( result = m_d3d->CheckDepthStencilMatch( m_adapter,
																m_deviceType,
																modeFormat,
																desiredBackBufferFormat,
																formats[index]) ) )
		{
			std::clog << D3DFormatToString(modeFormat) << " - Depth/stencil format " 
					  << D3DFormatToString(formats[index]) << " supported" << std::endl;
			
			if ( (formats[index] == D3DFMT_D24S8)   || 
				 (formats[index] == D3DFMT_D24X4S4) ||
				 (formats[index] == D3DFMT_D15S1) )
			{
				supportsStencil = true;
			}

			depthStencil = formats[index];

			return true;
		}
		else
		{
			std::cerr << D3DFormatToString(modeFormat) << " - " << D3DFormatToString(formats[index])
					  << " not supported. Error: " << D3DErrorCodeToString(result) << std::endl;
		}
	}

	return false;
}
//End DirectXRenderer::GetDepthStencilFormat


//=========================================================================
//! @function    DirectXRenderer::PrintAdapterDebugInfo
//! @brief       Print some debug information about the display adapter
//!              
//!              
//=========================================================================
void DirectXRenderer::PrintAdapterDebugInfo ( )
{
	//D3DADAPTER structure to hold adapter information
	D3DADAPTER_IDENTIFIER9 adapterInfo;
	
	//clear memory of adapterInfo
	ZeroMemory ( &adapterInfo, sizeof( adapterInfo ) );

	//Get adapter information
	if ( SUCCEEDED (m_d3d->GetAdapterIdentifier( m_adapter, 0, &adapterInfo ) ) )
	{
		//Print some information about the adapter to the console Out stream
		std::clog	<< "\n\n" "Adapter info:\n"
					    "===========================================\n"
					<< "Description:\n" << adapterInfo.Description << "\n\n"
					<< "Driver:\n"	<< adapterInfo.Driver		<< "\n\n"
					<< "Version:\n" << HIWORD ( adapterInfo.DriverVersion.HighPart ) << "."
										<< LOWORD ( adapterInfo.DriverVersion.HighPart ) << "."
										<< HIWORD ( adapterInfo.DriverVersion.LowPart  ) << "."
										<< LOWORD ( adapterInfo.DriverVersion.LowPart  ) << "\n\n"
					<< "Vendor ID:\n" << adapterInfo.VendorId << "\n\n"
					<< "Device ID:\n" << adapterInfo.DeviceId << "\n\n"
					<< "Subsys id:\n" << adapterInfo.SubSysId << "\n\n"
					<< "Revision:\n" << adapterInfo.Revision << "\n\n"
					<< "Device identifier:\n" << adapterInfo.DeviceIdentifier.Data1 << " "
												<< adapterInfo.DeviceIdentifier.Data2 << " "
												<< adapterInfo.DeviceIdentifier.Data3 << " "
												<< adapterInfo.DeviceIdentifier.Data4 << " " << std::endl;
	}
	else
	{

		std::cerr << "Error, couldn't get adapter info!" << std::endl;
	}

}
//End DirectXRenderer::PrintAdapterDebugInfo


//Define a macro to make outputing the device caps less tedious,
//and more easily readable
#define OUTPUTCAPSFLAG(cap, flag)\
			if ( cap & flag )\
			{\
				std::clog << #flag "\n";\
			}\
		

//=========================================================================
//! @function    DirectXRenderer::PrintDeviceCaps
//! @brief       Output information about the Direct3D device capabilities
//!              for debugging purposes
//!             
//=========================================================================
void DirectXRenderer::PrintDeviceCaps ( )
{
	
	std::clog << "\n\nAdapter Device Capabilities\n"
				 "===========================================\n";

	std::clog << "\nDeviceType:\n";

	switch ( m_deviceCaps.DeviceType )
	{
		case D3DDEVTYPE_HAL:
			std::clog << "D3DDEVTYPE_HAL\n";
			break;

		case D3DDEVTYPE_NULLREF:
			std::clog << "D3DDEVTYPE_NULLREF\n";
			break;

		case D3DDEVTYPE_REF:
			std::clog << "D3DDEVTYPE_REF\n";
			break;

		case D3DDEVTYPE_SW:
			std::clog << "D3DDEVTYPE_SW\n";
			break;
	}

	//
	std::clog << "\n" "Caps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.Caps, D3DCAPS_READ_SCANLINE );

	std::clog << "\n" "Caps2:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.Caps2, D3DCAPS2_CANAUTOGENMIPMAP  );
	OUTPUTCAPSFLAG ( m_deviceCaps.Caps2, D3DCAPS2_CANCALIBRATEGAMMA );
	OUTPUTCAPSFLAG ( m_deviceCaps.Caps2, D3DCAPS2_CANMANAGERESOURCE );
	OUTPUTCAPSFLAG ( m_deviceCaps.Caps2, D3DCAPS2_DYNAMICTEXTURES   );
	OUTPUTCAPSFLAG ( m_deviceCaps.Caps2, D3DCAPS2_FULLSCREENGAMMA   );
	 
	std::clog << "\n" "Caps3:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.Caps3, D3DCAPS3_ALPHA_FULLSCREEN_FLIP_OR_DISCARD  );
	OUTPUTCAPSFLAG ( m_deviceCaps.Caps3, D3DCAPS3_COPY_TO_VIDMEM );
	OUTPUTCAPSFLAG ( m_deviceCaps.Caps3, D3DCAPS3_COPY_TO_SYSTEMMEM );
	OUTPUTCAPSFLAG ( m_deviceCaps.Caps3, D3DCAPS3_LINEAR_TO_SRGB_PRESENTATION   );

	std::clog << "\n" "PresentationIntervals:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.PresentationIntervals, D3DPRESENT_INTERVAL_IMMEDIATE  );
	OUTPUTCAPSFLAG ( m_deviceCaps.PresentationIntervals, D3DPRESENT_INTERVAL_ONE  );
	OUTPUTCAPSFLAG ( m_deviceCaps.PresentationIntervals, D3DPRESENT_INTERVAL_TWO  );
	OUTPUTCAPSFLAG ( m_deviceCaps.PresentationIntervals, D3DPRESENT_INTERVAL_THREE  );
	OUTPUTCAPSFLAG ( m_deviceCaps.PresentationIntervals, D3DPRESENT_INTERVAL_FOUR  );

	std::clog << "\n" "CursorCaps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.CursorCaps, D3DCURSORCAPS_COLOR );
	OUTPUTCAPSFLAG ( m_deviceCaps.CursorCaps, D3DCURSORCAPS_LOWRES );

	std::clog << "\n" "DevCaps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_CANBLTSYSTONONLOCAL );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_CANRENDERAFTERFLIP );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_DRAWPRIMITIVES2 );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_DRAWPRIMITIVES2EX );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_DRAWPRIMTLVERTEX );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_EXECUTESYSTEMMEMORY );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_EXECUTEVIDEOMEMORY );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_HWRASTERIZATION );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_HWTRANSFORMANDLIGHT );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_NPATCHES );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_PUREDEVICE );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_QUINTICRTPATCHES );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_RTPATCHES	);
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_RTPATCHHANDLEZERO );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_SEPARATETEXTUREMEMORIES );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_TEXTURENONLOCALVIDMEM	);
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_TEXTURESYSTEMMEMORY );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_TEXTUREVIDEOMEMORY );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_TLVERTEXSYSTEMMEMORY );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps, D3DDEVCAPS_TLVERTEXVIDEOMEMORY );

	std::clog << "\n" "PrimitiveMiscCaps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_MASKZ	   );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_CULLNONE );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_CULLNONE );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_MASKZ	   );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_CULLNONE );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_CULLNONE );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_CULLCW );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_CULLCCW );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_COLORWRITEENABLE );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_CLIPPLANESCALEDPOINTS  );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_CLIPTLVERTS );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_TSSARGTEMP );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_BLENDOP );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_NULLREFERENCE );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_INDEPENDENTWRITEMASKS );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_PERSTAGECONSTANT );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_FOGANDSPECULARALPHA );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_SEPARATEALPHABLEND );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_MRTINDEPENDENTBITDEPTHS );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_MRTPOSTPIXELSHADERBLENDING );
	OUTPUTCAPSFLAG ( m_deviceCaps.PrimitiveMiscCaps, D3DPMISCCAPS_FOGVERTEXCLAMPED );

	std::clog << "\n" "RasterCaps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_ANISOTROPY   );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_COLORPERSPECTIVE );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_DITHER );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_DEPTHBIAS   );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_FOGRANGE );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_FOGTABLE   );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_FOGVERTEX );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_MIPMAPLODBIAS );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_MULTISAMPLE_TOGGLE   );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_SCISSORTEST );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_SLOPESCALEDEPTHBIAS   );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_WBUFFER );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_WFOG );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_ZBUFFERLESSHSR   );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_ZFOG );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_ZTEST );
	OUTPUTCAPSFLAG ( m_deviceCaps.RasterCaps, D3DPRASTERCAPS_FOGTABLE );

	std::clog << "\n" "ZCmpCaps:\n";
	PrintZAlphaCmps ( m_deviceCaps.ZCmpCaps );

	std::clog << "\n" "SrcBlendCaps:\n";
	PrintBlendCaps( m_deviceCaps.SrcBlendCaps );
																	
	std::clog << "\n" "DestBlendCaps:\n";	
	PrintBlendCaps( m_deviceCaps.DestBlendCaps );

	std::clog << "\n" "AlphaCmpCaps:\n";	
	PrintZAlphaCmps ( m_deviceCaps.AlphaCmpCaps );

	std::clog << "\n" "ShadeCaps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.ShadeCaps, D3DPSHADECAPS_ALPHAGOURAUDBLEND );
	OUTPUTCAPSFLAG ( m_deviceCaps.ShadeCaps, D3DPSHADECAPS_COLORGOURAUDRGB );
	OUTPUTCAPSFLAG ( m_deviceCaps.ShadeCaps, D3DPSHADECAPS_FOGGOURAUD );
	OUTPUTCAPSFLAG ( m_deviceCaps.ShadeCaps, D3DPSHADECAPS_SPECULARGOURAUDRGB );

	std::clog << "\n" "TextureCaps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_ALPHA );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_ALPHAPALETTE );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_CUBEMAP );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_CUBEMAP_POW2 );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_MIPCUBEMAP );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_MIPMAP );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_MIPVOLUMEMAP );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_NONPOW2CONDITIONAL );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_NOPROJECTEDBUMPENV );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_PERSPECTIVE );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_POW2 );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_PROJECTED );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_SQUAREONLY );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_TEXREPEATNOTSCALEDBYSIZE );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_VOLUMEMAP );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureCaps, D3DPTEXTURECAPS_VOLUMEMAP_POW2 );


	std::clog << "\n" "TextureFilterCaps:\n";
	PrintFilterCaps ( m_deviceCaps.TextureFilterCaps );

	std::clog << "\n" "CubeTextureFilterCaps:\n";
	PrintFilterCaps ( m_deviceCaps.CubeTextureFilterCaps );

	std::clog << "\n" "VolumeTextureFilterCaps:\n";
	PrintFilterCaps ( m_deviceCaps.VolumeTextureFilterCaps );

	std::clog << "\n" "TextureAddressCaps:\n";
	PrintTextureAddressCaps ( m_deviceCaps.TextureAddressCaps );

	std::clog << "\n" "VolumeTextureAddressCaps:\n";
	PrintTextureAddressCaps ( m_deviceCaps.VolumeTextureAddressCaps );

	std::clog << "\n" "LineCaps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.LineCaps, D3DLINECAPS_ALPHACMP  );
	OUTPUTCAPSFLAG ( m_deviceCaps.LineCaps, D3DLINECAPS_ANTIALIAS );
	OUTPUTCAPSFLAG ( m_deviceCaps.LineCaps, D3DLINECAPS_BLEND	  );
	OUTPUTCAPSFLAG ( m_deviceCaps.LineCaps, D3DLINECAPS_FOG		  );
	OUTPUTCAPSFLAG ( m_deviceCaps.LineCaps, D3DLINECAPS_TEXTURE	  );
	OUTPUTCAPSFLAG ( m_deviceCaps.LineCaps, D3DLINECAPS_ZTEST	  );

	std::clog << "\n" "MaxTextureWidth:\n" << m_deviceCaps.MaxTextureWidth << std::endl;
	std::clog << "\n" "MaxTextureHeight:\n" << m_deviceCaps.MaxTextureHeight << std::endl;
	std::clog << "\n" "MaxVolumeExtent:\n" << m_deviceCaps.MaxVolumeExtent << std::endl;
	std::clog << "\n" "MaxTextureRepeat:\n" << m_deviceCaps.MaxTextureRepeat << std::endl;
	std::clog << "\n" "MaxTextureAspectRatio:\n" << m_deviceCaps.MaxTextureAspectRatio << std::endl;
	std::clog << "\n" "MaxAnisotropy:\n" << m_deviceCaps.MaxAnisotropy << std::endl;
	std::clog << "\n" "MaxVertexW:\n" << m_deviceCaps.MaxVertexW << std::endl;
	std::clog << "\n" "GuardBandLeft:\n" << m_deviceCaps.GuardBandLeft << std::endl;
	std::clog << "\n" "GuardBandTop:\n" << m_deviceCaps.GuardBandTop << std::endl;
	std::clog << "\n" "GuardBandRight:\n" << m_deviceCaps.GuardBandRight << std::endl;
	std::clog << "\n" "GuardBandBottom:\n" << m_deviceCaps.GuardBandBottom << std::endl;
	std::clog << "\n" "ExtentsAdjust:\n" << m_deviceCaps.ExtentsAdjust << std::endl;

	std::clog << "\n" "StencilCaps: " << std::endl;
	OUTPUTCAPSFLAG ( m_deviceCaps.StencilCaps, D3DSTENCILCAPS_KEEP );
	OUTPUTCAPSFLAG ( m_deviceCaps.StencilCaps, D3DSTENCILCAPS_ZERO );
	OUTPUTCAPSFLAG ( m_deviceCaps.StencilCaps, D3DSTENCILCAPS_REPLACE );
	OUTPUTCAPSFLAG ( m_deviceCaps.StencilCaps, D3DSTENCILCAPS_INCRSAT );
	OUTPUTCAPSFLAG ( m_deviceCaps.StencilCaps, D3DSTENCILCAPS_DECRSAT );
	OUTPUTCAPSFLAG ( m_deviceCaps.StencilCaps, D3DSTENCILCAPS_INVERT );
	OUTPUTCAPSFLAG ( m_deviceCaps.StencilCaps, D3DSTENCILCAPS_INCR );
	OUTPUTCAPSFLAG ( m_deviceCaps.StencilCaps, D3DSTENCILCAPS_DECR );
	OUTPUTCAPSFLAG ( m_deviceCaps.StencilCaps, D3DSTENCILCAPS_TWOSIDED );

	std::clog << "\n" "FVFCaps: " << std::endl;
	OUTPUTCAPSFLAG ( m_deviceCaps.FVFCaps, D3DFVFCAPS_DONOTSTRIPELEMENTS );
	OUTPUTCAPSFLAG ( m_deviceCaps.FVFCaps, D3DFVFCAPS_PSIZE );
	OUTPUTCAPSFLAG ( m_deviceCaps.FVFCaps, D3DFVFCAPS_TEXCOORDCOUNTMASK );

	std::clog << "\n" "TextureOpCaps: " << std::endl;
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_ADD );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_ADDSIGNED );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_ADDSIGNED2X );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_ADDSMOOTH );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_BLENDCURRENTALPHA );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_BLENDDIFFUSEALPHA );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_BLENDFACTORALPHA );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_BLENDTEXTUREALPHA );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_BLENDTEXTUREALPHAPM );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_BUMPENVMAP );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_BUMPENVMAPLUMINANCE );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_DISABLE );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_DOTPRODUCT3 );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_LERP );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_MODULATE );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_MODULATE2X );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_MODULATE4X );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_MODULATECOLOR_ADDALPHA );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_MODULATEINVALPHA_ADDCOLOR );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_MODULATEINVCOLOR_ADDALPHA );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_MULTIPLYADD );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_PREMODULATE );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_SELECTARG1 );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_SELECTARG2 );
	OUTPUTCAPSFLAG ( m_deviceCaps.TextureOpCaps, D3DTEXOPCAPS_SUBTRACT );

	std::clog << "\n" "MaxTextureBlendStages:\n" << m_deviceCaps.MaxTextureBlendStages << std::endl;
	std::clog << "\n" "MaxSimultaneousTextures:\n" << m_deviceCaps.MaxSimultaneousTextures << std::endl;

	std::clog << "\n" "VertexProcessingCaps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.VertexProcessingCaps, D3DVTXPCAPS_LOCALVIEWER );
	OUTPUTCAPSFLAG ( m_deviceCaps.VertexProcessingCaps, D3DVTXPCAPS_MATERIALSOURCE7 );
	OUTPUTCAPSFLAG ( m_deviceCaps.VertexProcessingCaps, D3DVTXPCAPS_NO_TEXGEN_NONLOCALVIEWER );
	OUTPUTCAPSFLAG ( m_deviceCaps.VertexProcessingCaps, D3DVTXPCAPS_POSITIONALLIGHTS );
	OUTPUTCAPSFLAG ( m_deviceCaps.VertexProcessingCaps, D3DVTXPCAPS_TEXGEN );
	OUTPUTCAPSFLAG ( m_deviceCaps.VertexProcessingCaps, D3DVTXPCAPS_TEXGEN_SPHEREMAP );
	OUTPUTCAPSFLAG ( m_deviceCaps.VertexProcessingCaps, D3DVTXPCAPS_TWEENING );
	OUTPUTCAPSFLAG ( m_deviceCaps.VertexProcessingCaps, D3DVTXPCAPS_DIRECTIONALLIGHTS );

	
	std::clog << "\n" "MaxActiveLights:\n" << m_deviceCaps.MaxActiveLights << std::endl;
	std::clog << "\n" "MaxUserClipPlanes:\n" << m_deviceCaps.MaxUserClipPlanes << std::endl;
	std::clog << "\n" "MaxVertexBlendMatrices:\n" << m_deviceCaps.MaxVertexBlendMatrices << std::endl;
	std::clog << "\n" "MaxVertexBlendMatrixIndex:\n" << m_deviceCaps.MaxVertexBlendMatrixIndex << std::endl;
	std::clog << "\n" "MaxPointSize:\n" << m_deviceCaps.MaxPointSize << std::endl;
	std::clog << "\n" "MaxPrimitiveCount:\n" << m_deviceCaps.MaxPrimitiveCount << std::endl;
	std::clog << "\n" "MaxVertexIndex:\n" << m_deviceCaps.MaxVertexIndex << std::endl;
	std::clog << "\n" "MaxStreams:\n" << m_deviceCaps.MaxStreams << std::endl;
	std::clog << "\n" "MaxStreamStride:\n" << m_deviceCaps.MaxStreamStride << std::endl;
	std::clog << "\n" "VertexShaderVersion:\n" << ((m_deviceCaps.VertexShaderVersion & 0xFF00) >> 8) << "."
											   << ((m_deviceCaps.VertexShaderVersion & 0xFF)) << std::endl;

	std::clog << "\n" "MaxVertexShaderConst:\n" << m_deviceCaps.MaxVertexShaderConst << std::endl;
	std::clog << "\n" "PixelShaderVersion:\n" << ((m_deviceCaps.PixelShaderVersion & 0xFF00) >> 8) << "."
												<< ((m_deviceCaps.PixelShaderVersion & 0xFF)) << std::endl;
	std::clog << "\n" "PixelShader1xMaxValue:\n" << m_deviceCaps.PixelShader1xMaxValue << std::endl;


	std::clog << "\n" "DevCaps2:\n";

	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps2, D3DDEVCAPS2_ADAPTIVETESSRTPATCH );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps2, D3DDEVCAPS2_ADAPTIVETESSNPATCH );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps2, D3DDEVCAPS2_CAN_STRETCHRECT_FROM_TEXTURES );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps2, D3DDEVCAPS2_DMAPNPATCH );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps2, D3DDEVCAPS2_PRESAMPLEDDMAPNPATCH );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps2, D3DDEVCAPS2_STREAMOFFSET );
	OUTPUTCAPSFLAG ( m_deviceCaps.DevCaps2, D3DDEVCAPS2_VERTEXELEMENTSCANSHARESTREAMOFFSET );


	std::clog << "\n" "MaxNpatchTessellationLevel:\n" << m_deviceCaps.MaxNpatchTessellationLevel << std::endl;
	std::clog << "\n" "MasterAdapterOrdinal:\n" << m_deviceCaps.MasterAdapterOrdinal << std::endl;
	std::clog << "\n" "AdapterOrdinalInGroup:\n" << m_deviceCaps.AdapterOrdinalInGroup << std::endl;
	std::clog << "\n" "NumberOfAdaptersInGroup:\n" << m_deviceCaps.NumberOfAdaptersInGroup << std::endl;

	std::clog << "\n" "DeclTypes:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.DeclTypes, D3DDTCAPS_UBYTE4 );
	OUTPUTCAPSFLAG ( m_deviceCaps.DeclTypes, D3DDTCAPS_UBYTE4N );
	OUTPUTCAPSFLAG ( m_deviceCaps.DeclTypes, D3DDTCAPS_SHORT2N );
	OUTPUTCAPSFLAG ( m_deviceCaps.DeclTypes, D3DDTCAPS_SHORT4N );
	OUTPUTCAPSFLAG ( m_deviceCaps.DeclTypes, D3DDTCAPS_USHORT2N );
	OUTPUTCAPSFLAG ( m_deviceCaps.DeclTypes, D3DDTCAPS_USHORT4N );
	OUTPUTCAPSFLAG ( m_deviceCaps.DeclTypes, D3DDTCAPS_UDEC3 );
	OUTPUTCAPSFLAG ( m_deviceCaps.DeclTypes, D3DDTCAPS_DEC3N );
	OUTPUTCAPSFLAG ( m_deviceCaps.DeclTypes, D3DDTCAPS_FLOAT16_2 );
	OUTPUTCAPSFLAG ( m_deviceCaps.DeclTypes, D3DDTCAPS_FLOAT16_4 );

	std::clog << "\n" "NumSimultaneousRTs:\n" << m_deviceCaps.NumSimultaneousRTs << std::endl;
	std::clog << "\n" "StretchRectFilterCaps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.StretchRectFilterCaps, D3DPTFILTERCAPS_MINFPOINT );
	OUTPUTCAPSFLAG ( m_deviceCaps.StretchRectFilterCaps, D3DPTFILTERCAPS_MAGFPOINT );
	OUTPUTCAPSFLAG ( m_deviceCaps.StretchRectFilterCaps, D3DPTFILTERCAPS_MINFLINEAR );
	OUTPUTCAPSFLAG ( m_deviceCaps.StretchRectFilterCaps, D3DPTFILTERCAPS_MAGFLINEAR );

	std::clog << "\n" "VS20Caps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.VS20Caps.Caps, D3DVS20CAPS_PREDICATION );
	OUTPUTCAPSFLAG ( m_deviceCaps.VS20Caps.Caps, D3DVS20_MAX_DYNAMICFLOWCONTROLDEPTH );
	OUTPUTCAPSFLAG ( m_deviceCaps.VS20Caps.Caps, D3DVS20_MIN_DYNAMICFLOWCONTROLDEPTH );
	OUTPUTCAPSFLAG ( m_deviceCaps.VS20Caps.Caps, D3DVS20_MAX_NUMTEMPS );
	OUTPUTCAPSFLAG ( m_deviceCaps.VS20Caps.Caps, D3DVS20_MIN_NUMTEMPS );
	OUTPUTCAPSFLAG ( m_deviceCaps.VS20Caps.Caps, D3DVS20_MAX_STATICFLOWCONTROLDEPTH );
	OUTPUTCAPSFLAG ( m_deviceCaps.VS20Caps.Caps, D3DVS20_MIN_STATICFLOWCONTROLDEPTH );
	std::clog << "VS20Caps.DynamicFlowControlDepth:\n" << m_deviceCaps.VS20Caps.DynamicFlowControlDepth << "\n";
	std::clog << "\n" "VS20Caps.StaticFlowControlDepth:\n" << m_deviceCaps.VS20Caps.StaticFlowControlDepth << "\n";
	std::clog << "\n" "VS20Caps.NumTemps:\n" << m_deviceCaps.VS20Caps.NumTemps << "\n";

	std::clog << "\n" "PS20Caps:\n";
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20CAPS_ARBITRARYSWIZZLE );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20CAPS_GRADIENTINSTRUCTIONS );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20CAPS_PREDICATION );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20CAPS_NODEPENDENTREADLIMIT );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20CAPS_NOTEXINSTRUCTIONLIMIT );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20_MAX_DYNAMICFLOWCONTROLDEPTH );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20_MIN_DYNAMICFLOWCONTROLDEPTH );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20_MAX_NUMTEMPS );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20_MIN_NUMTEMPS );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20_MAX_STATICFLOWCONTROLDEPTH );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20_MIN_STATICFLOWCONTROLDEPTH );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20_MAX_NUMINSTRUCTIONSLOTS );
	OUTPUTCAPSFLAG ( m_deviceCaps.PS20Caps.Caps, D3DPS20_MIN_NUMINSTRUCTIONSLOTS );

	std::clog << "\n" "PS20Caps.DynamicFlowControlDepth:\n" << m_deviceCaps.PS20Caps.DynamicFlowControlDepth << "\n";
	std::clog << "\n" "PS20Caps.StaticFlowControlDepth:\n" << m_deviceCaps.PS20Caps.StaticFlowControlDepth << "\n";
	std::clog << "\n" "PS20Caps.NumTemps:\n" << m_deviceCaps.PS20Caps.NumTemps << "\n";
	std::clog << "\n" "PS20Caps.NumInstructionSlots:\n" << m_deviceCaps.PS20Caps.NumInstructionSlots << "\n";

	std::clog << "\n" "VertexTextureFilterCaps:\n";
	PrintFilterCaps( m_deviceCaps.VertexTextureFilterCaps );

	std::clog << "\n" "MaxVShaderInstructionsExecuted:\n" << m_deviceCaps.MaxVShaderInstructionsExecuted << "\n";
	std::clog << "\n" "MaxPShaderInstructionsExecuted:\n" << m_deviceCaps.MaxPShaderInstructionsExecuted << "\n";
	std::clog << "\n" "MaxVertexShader30InstructionSlots:\n" << m_deviceCaps.MaxVertexShader30InstructionSlots << "\n";
	std::clog << "\n" "MaxPixelShader30InstructionSlots:\n" << m_deviceCaps.MaxPixelShader30InstructionSlots << "\n\n";

	std::clog << std::endl;
}
//End  DirectXRenderer::PrintDeviceCaps


//=========================================================================
//! @function    DirectXRenderer::PrintBlendCaps
//! @brief       Prints the SourceBlend or DestBlend caps of the device caps
//!              
//! @param       caps [in] DWORD containing the flags to be printed
//!              
//=========================================================================
void DirectXRenderer::PrintBlendCaps ( DWORD caps )
{
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_BLENDFACTOR	  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_BOTHINVSRCALPHA );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_BOTHSRCALPHA	  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_DESTALPHA		  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_DESTCOLOR		  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_INVDESTALPHA	  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_INVDESTCOLOR	  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_INVSRCALPHA	  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_INVSRCCOLOR     );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_ONE			  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_SRCALPHA		  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_SRCALPHASAT	  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_SRCCOLOR		  );
	OUTPUTCAPSFLAG ( caps,	D3DPBLENDCAPS_ZERO			  );
}
//End DirectXRenderer::PrintBlendCaps



//=========================================================================
//! @function    DirectXRenderer::PrintZAlphaCmps
//! @brief       Print the ZCmpFlags or AlphaCmdFlags portion of the device caps
//!              
//! @param       caps [in] DWORD containing the flags to print
//!              
//=========================================================================
void DirectXRenderer::PrintZAlphaCmps ( DWORD caps )
{
	OUTPUTCAPSFLAG ( caps,	D3DPCMPCAPS_ALWAYS		 );
	OUTPUTCAPSFLAG ( caps,	D3DPCMPCAPS_EQUAL		 );
	OUTPUTCAPSFLAG ( caps,	D3DPCMPCAPS_GREATER		 );
	OUTPUTCAPSFLAG ( caps,	D3DPCMPCAPS_GREATEREQUAL );
	OUTPUTCAPSFLAG ( caps,	D3DPCMPCAPS_LESS		 );
	OUTPUTCAPSFLAG ( caps,	D3DPCMPCAPS_LESSEQUAL	 );
	OUTPUTCAPSFLAG ( caps,	D3DPCMPCAPS_NEVER		 );
	OUTPUTCAPSFLAG ( caps,	D3DPCMPCAPS_NOTEQUAL	 );
}
//End DirectXRenderer::PrintZAlphaCmps



//=========================================================================
//! @function    DirectXRenderer::PrintFilterCaps
//! @brief       Print the flags in the TextureFilterCaps, CubeTextureFilterCaps
//!				 VertexTextureFilterCaps or VolumeTextureFilterCaps portion of the device caps
//!              
//! @param       caps [in] DWORD containing flags to print
//!              
//! @return      
//! @throw       
//=========================================================================
void DirectXRenderer::PrintFilterCaps ( DWORD caps )
{
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MAGFPOINT );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MAGFLINEAR );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MAGFANISOTROPIC );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MAGFPYRAMIDALQUAD );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MAGFGAUSSIANQUAD );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MINFPOINT );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MINFLINEAR );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MINFANISOTROPIC );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MINFPYRAMIDALQUAD );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MINFGAUSSIANQUAD );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MIPFPOINT );
	OUTPUTCAPSFLAG ( caps, D3DPTFILTERCAPS_MIPFLINEAR );
}
//End DirectXRenderer::PrintFilterCaps



//=========================================================================
//! @function    DirectXRenderer::PrintTextureAddressCaps
//! @brief       Print the TextureAddressCaps or VolumeTextureAddressCaps
//!				 members of the device caps structure
//!              
//! @param       caps [in] DWORD containing caps flags 
//!              
//=========================================================================
void DirectXRenderer::PrintTextureAddressCaps ( DWORD caps )
{
	OUTPUTCAPSFLAG ( caps, D3DPTADDRESSCAPS_BORDER );

	OUTPUTCAPSFLAG ( caps, D3DPTADDRESSCAPS_CLAMP );
	OUTPUTCAPSFLAG ( caps, D3DPTADDRESSCAPS_INDEPENDENTUV );
	OUTPUTCAPSFLAG ( caps, D3DPTADDRESSCAPS_MIRROR );
	OUTPUTCAPSFLAG ( caps, D3DPTADDRESSCAPS_MIRRORONCE );
	OUTPUTCAPSFLAG ( caps, D3DPTADDRESSCAPS_WRAP );
}
//End DirectXRenderer::PrintTextureAddressCaps




