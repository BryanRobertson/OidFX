//======================================================================================
//! @file         Renderer.h
//! @brief        Interface for classes that encapsulate a rendering API
//!				  such as DirectX or OpenGL
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Tuesday, 31 May 2005
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

#ifndef RENDERER_RENDERER_H
#define RENDERER_RENDERER_H


#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "Core/Resizable.h"
#include "Core/Restorable.h"
#include "Math/Math.h"
#include "Renderer/Colour4f.h"
#include "Renderer/RendererCapabilities.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/RendererError.h"
#include "Renderer/Texture.h"
#include "Renderer/ScopedBufferLock.h"
#include "Renderer/DisplayModeList.h"
#include "Renderer/DisplayMode.h"
#include "Renderer/RendererTypes.h"
#include "Renderer/RendererConstants.h"
#include "Renderer/RendererStateConstants.h"
#include "Renderer/VertexDeclarationDescriptor.h"
#include "Renderer/VertexDeclaration.h"
#include "Renderer/VertexStreamBinding.h"
#include "Renderer/VertexData.h"
#include "Renderer/RendererWindow.h"
#include "Renderer/Material.h"
#include "Renderer/Renderable.h"


//=========================================================================
// Forward declarations
//=========================================================================
namespace Renderer
{
	class RendererWindow;
	class DisplayModeList;
	class Colour4f;
	class VertexBufferManager;
	class IndexBufferManager;
	class VertexDeclaration;
	class VertexDeclarationDescriptor;
};
namespace Math
{
	class Vector3D;
	class Matrix4x4;
};
//End Forward declarations



//namespace Renderer
namespace Renderer
{


    //=========================================================================
    // Type definitions
    //=========================================================================
	enum EBufferType
	{
		COLOUR_BUFFER = 1,
		DEPTH_BUFFER = 2,
		STENCIL_BUFFER = 4
	};

	//End Type definitions


	//!@class	IRenderer
	//!@brief	Interface for classes that encapsulate a rendering API such as DirectX or OpenGL
	//!			
	//!			Classes that implement the IRenderer interface should bear the following in mind. 
	//!			Applications that use IRenderer will always use a right handed coordinate system
	//!			(positive z values come out of the screen, negative z values go into the screen)
	//!			If IRenderer implementations use a left handed system, as DirectX does, for example
	//!			then the IRenderer implementation is responsible for supplying the appropriate matrices
	//!			to translate between the two coordinate systems, through the methods that create projection and view matrices
	//!			(SetProjectionOrtho, SetProjectionPerspective, SetViewLookAt)
	//!
	//!			Texture coordinates are set out such that (0.0, 0.0) is at the top left of the texture,
	//!			and (1.0, 1.0) is at the bottom right.
	//!
	//!			(0.0, 0.0)		
	//!			--------------
	//!			|		     |
	//!			|  		     |
	//!			|            |
	//!			|            |
	//!			--------------		  
	//!						(1.0, 1.0)
	//!
	//!			Due to a design mistake, this means that an OpenGL renderer wouldn't work at the moment.
	//!			I have a solution to this problem, but I don't have time to implement it right now, because
	//!			OpenGL support isn't a huge priority at the moment.
	//!
	//!			In future I will most likely create some kind of vertex buffer iterator class, that is used
	//!			when setting the contents of a vertex buffer. This iterator would have methods for
	//!			setting the different properties of the current vertex, doing any required translation of
	//!			texture coordinates, colour formats, etc.
	//!
	class IRenderer : public boost::noncopyable, 
					  public Core::IRestorable, 
					  public Core::IResizable
	{
		public:

			virtual ~IRenderer() {	}

			//Get a list of display modes
			virtual const DisplayModeList& GetDisplayModeList() const = 0;

			//Initialisation and shutdown
			virtual void Initialise() throw (RendererError) = 0;
			virtual void ShutDown() throw (RendererError) = 0;

			//Resources
			virtual HTexture	  AcquireTexture	( ETextureType type, const Char* fileName, UInt quality, UInt usage, UInt flags ) = 0;
			virtual HTexture	  CreateTexture  ( ETextureType type, UInt width, UInt height, Imaging::PixelFormat format, 
									    UInt quality, UInt usage, UInt flags ) = 0;
			virtual HVertexBuffer CreateVertexBuffer( size_t vertexSize, size_t vertexCount, EUsage usage ) = 0;
			virtual HIndexBuffer  CreateIndexBuffer ( EIndexSize indexSize, size_t indexCount, Renderer::EUsage usage ) = 0;
			virtual HVertexDeclaration AcquireVertexDeclaration( VertexDeclarationDescriptor& descriptor ) = 0;

			//Rendering
			virtual void BeginFrame() = 0;
			virtual void EndFrame() = 0;
			virtual void Clear( UInt bufferFlags ) = 0;

			virtual void DrawPrimitive( EPrimType type, size_t startIndex, size_t vertexCount ) = 0;
			virtual void DrawIndexedPrimitive ( EPrimType type, size_t baseVertexIndex,
												size_t startIndex, size_t vertexCount ) = 0; 

			virtual void DrawIndexedPrimitive ( EPrimType type, size_t baseVertexIndex,
												size_t maxVertexIndex, size_t startIndex, size_t vertexCount ) = 0; 

			//Binding render states
			virtual bool Bind ( HTexture& texture, ETextureStageID stageID ) throw() = 0;
			virtual bool Bind ( HVertexBuffer& buffer, UInt streamIndex ) throw() = 0;
			virtual bool Bind ( HIndexBuffer& buffer ) throw() = 0;
			virtual bool Bind ( HVertexDeclaration& declaration ) throw() = 0;

			//Render states
			virtual bool SetRenderState ( EBoolStateID stateID, bool value ) throw() = 0;
			virtual bool SetRenderState ( EUIntStateID stateID, UInt value ) throw() = 0;
			virtual bool SetRenderState ( EFloatStateID stateID, Float value ) throw() = 0;
			
			virtual bool SetTextureStageState			( ETextureStageID stageID, ETextureStageStateID stateID, UInt value ) throw() = 0;
			virtual bool SetTextureStageConstantColour  ( ETextureStageID stageID, const Colour4f& value ) throw() = 0;
			virtual bool SetColour ( EColourStateID stateID, const Colour4f& value ) throw() = 0;
			virtual bool SetClearColour( const Colour4f& colour ) = 0;

			virtual bool SetMaterialColourSource	( EMaterialSourceType sourceType, EMaterialSource source ) throw() = 0;
			virtual bool SetMaterial				( const Material& material ) throw()  = 0;

			virtual bool SetTextureAddressingMode	( ETextureStageID stageID, ETextureAddressModeType type, ETextureAddressingMode mode ) throw() = 0;
			virtual bool SetTextureCoordGeneration  ( ETextureStageID stageID, UInt textureCoordinateSet, ETextureCoordGen mode ) throw() = 0;
			virtual bool SetTextureFilter			( ETextureStageID stageID, ETextureFilterType type, ETextureFilter filter ) throw() = 0;
			virtual bool SetTextureBorderColour		( ETextureStageID stageID, const Colour4f& colour ) throw() = 0;
			virtual bool SetTextureParameter		( ETextureStageID stageID, ETextureParamType type, UInt value ) throw() = 0;

			//Blending/Depth test/Stencil test/Alpha test
			virtual bool SetBlendOp			( EBlendOp op ) = 0;
			virtual bool SetBlendFunc		( EBlendMode src, EBlendMode dst ) = 0;
			virtual bool SetDepthFunc		( ECmpFunc cmp ) = 0;
			virtual bool SetAlphaFunc		( ECmpFunc ) = 0;
			virtual bool SetStencilFunc		( ECmpFunc cmp ) = 0;
			virtual bool SetStencilOp		( EStencilOpType type, EStencilOp op ) = 0;
			virtual bool SetStencilFuncCCW	( ECmpFunc cmp ) = 0;
			virtual bool SetStencilOpCCW	( EStencilOpType type, EStencilOp op ) = 0;
			

			//Fog
			virtual bool SetFogMode ( EFogType type, EFogMode mode ) = 0;

			//Shading/culling
			virtual bool SetShadeMode ( EShadeMode mode ) = 0;
			virtual bool SetCullingMode ( ECullMode mode ) = 0;
			virtual bool SetFillMode ( EFillMode mode ) = 0;

			//Accessors for render states
			virtual const Colour4f& GetClearColour () const = 0;

			//Transformation matrices
			virtual void SetMatrix ( EMatrixType type, const Math::Matrix4x4& mat ) throw() = 0;
			virtual void SetProjectionOrtho ( Math::Scalar left, Math::Scalar right, Math::Scalar bottom, Math::Scalar top, 
											  Math::Scalar zNear, Math::Scalar zFar ) = 0;
			virtual void SetProjectionPerspective ( Math::Scalar fovY, Math::Scalar aspectRatio, Math::Scalar zNear, Math::Scalar zFar  ) = 0;
			virtual void SetViewLookAt ( const Math::Vector3D& eye, const Math::Vector3D& up, const Math::Vector3D& lookAt ) = 0;

			virtual void GetMatrix ( EMatrixType type, Math::Matrix4x4& mat ) throw() = 0;
			virtual void GetMatrix ( EReadOnlyMatrixType type, Math::Matrix4x4& mat ) throw() = 0;

			//2D mode
			virtual void Enter2DMode() = 0;
			virtual void Exit2DMode()  = 0;

			//Renderer capabilities
			virtual bool  Supports( ERendererCapability capability ) const throw() = 0;
			virtual UInt  GetDeviceProperty ( EIntegerRendererCapability capability ) const throw() = 0;
			virtual Float GetDeviceProperty ( EFloatRendererCapability capablity ) const throw() = 0;

			//Accessors
			virtual RendererWindow& Window() = 0;
			virtual const std::string& Name() const = 0;
			virtual UInt ScreenWidth() const = 0;
			virtual UInt ScreenHeight() const = 0;

			virtual Math::EHandedness GetHandedness() const = 0;

			//IRestorable
			virtual bool RequiresRestore() const = 0;
			virtual void PrepareForRestore ( bool forceRestore ) = 0;
			virtual void Restore( bool forceRestore ) = 0;

			//IResizable
			virtual void Resize ( UInt width, UInt height ) = 0;

		protected:
		
	};
	//End class BaseRenderer

};
//end namespace Renderer


#endif
//#ifndef RENDERER_RENDERER_H