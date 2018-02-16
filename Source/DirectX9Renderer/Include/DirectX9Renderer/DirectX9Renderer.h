//======================================================================================
//! @file         DirectX9Renderer.h
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

#ifndef DIRECTX9RENDERER_DIRECTX9RENDERER_H
#define DIRECTX9RENDERER_DIRECTX9RENDERER_H


#include "Math/Matrix4x4.h"
#include "Renderer/Renderer.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <d3d9types.h>
#include <atlbase.h>
#include <string>


//=========================================================================
// Forward declarations
//=========================================================================
namespace Renderer
{
	class ITextureCreator;
	class TextureManager;
	class IVertexBufferCreator;
	class VertexBufferManager;
	class IIndexBufferCreator;
	class IndexBufferManager;
	class VertexDeclarationManager;
	class IVertexDeclarationCreator;
}


//namespace DirectX9Renderer
namespace DirectX9Renderer
{


	//!@class	DirectXRenderer
	//!@brief	IRenderer implementation for DirectX 9
	//!
	//!			Note to self, this class is starting to get a bit monolithic, it could do with 
	//!			being split into several sub-classes
	class DirectXRenderer : public Renderer::IRenderer
	{
		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			DirectXRenderer();


            //=========================================================================
            // Public methods
            //=========================================================================

			//Get a list of display modes
			const Renderer::DisplayModeList& GetDisplayModeList() const;

			//Initialisation and shutdown
			void Initialise() throw (Renderer::RendererError);
			void ShutDown() throw (Renderer::RendererError);

			//Resources
			Renderer::HTexture	    AcquireTexture ( Renderer::ETextureType type, const Char* fileName, UInt quality, UInt usage, UInt flags );
			Renderer::HTexture		CreateTexture  ( Renderer::ETextureType type, UInt width, UInt height, Imaging::PixelFormat format, 
														 UInt quality, UInt usage, UInt flags );
			Renderer::HVertexBuffer CreateVertexBuffer( size_t vertexSize, size_t vertexCount, Renderer::EUsage usage );
			Renderer::HIndexBuffer  CreateIndexBuffer ( Renderer::EIndexSize indexSize, size_t indexCount, Renderer::EUsage usage );
			Renderer::HVertexDeclaration AcquireVertexDeclaration( Renderer::VertexDeclarationDescriptor& descriptor );

			//Rendering
			void BeginFrame();
			void EndFrame();
			void Clear( UInt bufferFlags );

			void DrawPrimitive( Renderer::EPrimType type, size_t startIndex, size_t vertexCount );

			void DrawIndexedPrimitive ( Renderer::EPrimType type, size_t baseVertexIndex,
										 size_t startIndex, size_t vertexCount ); 

			void DrawIndexedPrimitive ( Renderer::EPrimType type, size_t baseVertexIndex,
										size_t maxVertexIndex, size_t startIndex, size_t vertexCount );

			//Binding render states
			bool  Bind ( Renderer::HTexture& texture, Renderer::ETextureStageID stageID );
			bool  Bind ( Renderer::HVertexBuffer& buffer, UInt streamIndex ) throw();
			bool  Bind ( Renderer::HIndexBuffer& buffer ) throw();
			bool  Bind ( Renderer::HVertexDeclaration& decl ) throw();

			//Render states
			bool SetRenderState ( Renderer::EBoolStateID stateID, bool value ) throw();
			bool SetRenderState ( Renderer::EUIntStateID stateID, UInt value ) throw();
			bool SetRenderState ( Renderer::EFloatStateID stateID, Float value ) throw();

			bool SetTextureStageState ( Renderer::ETextureStageID stageID, Renderer::ETextureStageStateID stateID, UInt value ) throw();
			bool SetTextureStageConstantColour ( Renderer::ETextureStageID stageID, const Renderer::Colour4f& value ) throw(); 
			bool SetColour ( Renderer::EColourStateID stateID, const Renderer::Colour4f& value ) throw();
			bool SetClearColour( const Renderer::Colour4f& colour );

			bool SetMaterialColourSource	( Renderer::EMaterialSourceType sourceType, Renderer::EMaterialSource source ) throw();
			bool SetMaterial				( const Renderer::Material& material ) throw();


			bool SetTextureAddressingMode	( Renderer::ETextureStageID stageID, 
											  Renderer::ETextureAddressModeType type, 
											  Renderer::ETextureAddressingMode mode ) throw();

			bool SetTextureFilter			( Renderer::ETextureStageID stageID, 
											  Renderer::ETextureFilterType type, 
											  Renderer::ETextureFilter filter ) throw();

			bool SetTextureCoordGeneration  ( Renderer::ETextureStageID stageID, UInt textureCoordinateSet, Renderer::ETextureCoordGen mode ) throw();

			bool SetTextureBorderColour		( Renderer::ETextureStageID stageID, const Renderer::Colour4f& colour ) throw();
			bool SetTextureParameter		( Renderer::ETextureStageID stageID, Renderer::ETextureParamType type, UInt value ) throw();

			//Blending/Depth test/Stencil test/Alpha test
			bool SetBlendOp	  ( Renderer::EBlendOp op );
			bool SetBlendFunc ( Renderer::EBlendMode src, Renderer::EBlendMode dst );
			bool SetDepthFunc ( Renderer::ECmpFunc cmp );
			bool SetAlphaFunc ( Renderer::ECmpFunc );
			bool SetStencilFunc ( Renderer::ECmpFunc cmp );
			bool SetStencilOp   ( Renderer::EStencilOpType type, Renderer::EStencilOp op );
			bool SetStencilFuncCCW ( Renderer::ECmpFunc cmp );
			bool SetStencilOpCCW   ( Renderer::EStencilOpType type, Renderer::EStencilOp op );

			//Fog
			bool SetFogMode ( Renderer::EFogType type, Renderer::EFogMode mode );

			//Shading/culling
			bool SetShadeMode ( Renderer::EShadeMode mode );
			bool SetCullingMode ( Renderer::ECullMode mode );
			bool SetFillMode ( Renderer::EFillMode mode );

			//Accessors for render states
			const Renderer::Colour4f& GetClearColour () const;

			//Tranformation matrices
			void SetMatrix ( Renderer::EMatrixType type, const Math::Matrix4x4& mat ) throw();

			void SetProjectionOrtho		  ( Math::Scalar left, Math::Scalar right, Math::Scalar bottom, Math::Scalar top, 
											Math::Scalar zNear, Math::Scalar zFar );
			void SetProjectionPerspective ( Math::Scalar fovY, Math::Scalar aspectRatio, Math::Scalar zNear, Math::Scalar zFar  );
			void SetViewLookAt			  ( const Math::Vector3D& eye, const Math::Vector3D& up, const Math::Vector3D& lookAt );

			void GetMatrix ( Renderer::EMatrixType type, Math::Matrix4x4& mat ) throw();
			void GetMatrix ( Renderer::EReadOnlyMatrixType type, Math::Matrix4x4& mat ) throw(); 

			//2D mode
			void Enter2DMode ();
			void Exit2DMode ();

			//Renderer capabilities
			bool  Supports( Renderer::ERendererCapability capability ) const throw();
			UInt  GetDeviceProperty  ( Renderer::EIntegerRendererCapability capability ) const throw();
			Float GetDeviceProperty ( Renderer::EFloatRendererCapability capability ) const throw();

			//Accessors
			inline Renderer::RendererWindow& Window();
			inline const std::string& Name() const;
			UInt ScreenWidth() const throw();
			UInt ScreenHeight() const throw();

			virtual inline Math::EHandedness GetHandedness() const;

			//IRestorable
			virtual bool RequiresRestore() const;
			virtual void PrepareForRestore( bool forceRestore );
			virtual void Restore( bool forceRestore );

			//IResizable
			virtual void Resize ( UInt width, UInt height );

			//DirectX specific
			inline CComPtr<IDirect3D9>			D3D();
			inline CComPtr<IDirect3DDevice9>	Device();

		private:

			
            //=========================================================================
            // Private methods
            //=========================================================================

			//Direct3D related
			void CreateD3D ( );
			void CreateRenderWindow ( );
			void CreateDevice ( );

			//Initialisation related
			void SetupPresentParamsForWindowed( UInt modeIndex, UInt bpp );
			void SetupPresentParamsForFullScreen( UInt modeIndex, UInt bpp );
			void FillDisplayModeList( );
			bool CheckFormat ( D3DFORMAT format, bool& supportsWindowed );
			bool GetDepthStencilFormat ( D3DFORMAT modeFormat, D3DFORMAT& depthStencil, bool& supportsStencil );

			//Debug information
			void PrintAdapterDebugInfo ( );
			void PrintDeviceCaps ( );
			void PrintBlendCaps ( DWORD caps );
			void PrintZAlphaCmps ( DWORD caps );
			void PrintFilterCaps ( DWORD caps );
			void PrintTextureAddressCaps ( DWORD caps );


            //=========================================================================
            // Private data members
            //=========================================================================

			//Debugging
			UInt		m_trisPerFrame;

			//Render window
			boost::shared_ptr<Renderer::RendererWindow> m_window;
			
			//Tranformation matrices
			Math::Matrix4x4 m_worldTransform;
			Math::Matrix4x4 m_viewTransform;
			Math::Matrix4x4 m_projectionTransform;
			Math::Matrix4x4 m_textureTransform[Renderer::TEXTURE_STAGE_COUNT];
			Math::Matrix4x4 m_worldViewMatrix;
			Math::Matrix4x4 m_viewProjMatrix;
			bool			m_worldViewOutOfDate;
			bool			m_viewProjOutOfDate;

			//DirectX related
			CComPtr<IDirect3D9>			m_d3d;
			CComPtr<IDirect3DDevice9>	m_device;
			
			D3DPRESENT_PARAMETERS		m_presentParameters;
			D3DCOLOR					m_backgroundColour;
			Renderer::Colour4f			m_backgroundColourAsColour4;
			D3DDEVTYPE					m_deviceType;
			UInt						m_adapter;
			D3DCAPS9					m_deviceCaps;
			UInt						m_minModeWidth;
			UInt						m_minModeHeight;

			Float						m_stencilClearValue;
			Float						m_depthClearValue;

			//Resources
			boost::shared_ptr<Renderer::ITextureCreator>	  m_textureCreator;
			boost::shared_ptr<Renderer::TextureManager>		  m_textureManager;
			boost::shared_ptr<Renderer::IVertexBufferCreator> m_vertexBufferCreator;
			boost::shared_ptr<Renderer::IIndexBufferCreator>  m_indexBufferCreator;
			boost::shared_ptr<Renderer::VertexBufferManager>  m_vertexBufferManager;
			boost::shared_ptr<Renderer::IndexBufferManager>	  m_indexBufferManager;
			boost::shared_ptr<Renderer::IVertexDeclarationCreator> m_declarationCreator;
			boost::shared_ptr<Renderer::VertexDeclarationManager> m_vertexDeclarationManager;

			//Currently set textures
			Renderer::HTexture	m_textures[Renderer::TEXTURE_STAGE_COUNT];

			//		
			UInt					  m_screenWidth;
			UInt					  m_screenHeight;
			Renderer::DisplayModeList m_displayModes;
			std::string m_name;

	};
	//End class DirectXRenderer



    //=========================================================================
    //! @function    DirectXRenderer::Window
    //! @brief       Get a reference to the renderer's window
    //!              
    //!              
    //! @return      A reference to the renderer's window
    //=========================================================================
	Renderer::RendererWindow& DirectXRenderer::Window()
	{
		debug_assert ( m_window, "Error, attempted to access renderer window, when it hasn't been created!" );
		return *m_window;
	}
	//End DirectXRenderer::Window



    //=========================================================================
    //! @function    DirectXRenderer::Name
    //! @brief       Return the name of the renderer
    //!              
    //!              
    //! @return      The name of the renderer
    //=========================================================================
	const std::string& DirectXRenderer::Name() const
	{
		return m_name;
	}
	//End DirectXRenderer::Name



    //=========================================================================
    //! @function    DirectXRenderer::GetHandedness
    //! @brief       Returns the handedness of the renderer
    //!              
	//!				 DirectX uses a left handed system
    //!              
    //! @return      MATH::LEFT_HANDED
    //=========================================================================
	Math::EHandedness DirectXRenderer::GetHandedness() const
	{
		return Math::LEFT_HANDED;
	}
	//End DirectXRenderer::GetHandedness



    //=========================================================================
    //! @function    DirectXRenderer::D3D
    //! @brief       Get access to the renderer's IDirect3D9 object
    //!                   
    //! @return      A reference to the renderer's IDirect3D9 object
    //=========================================================================
	CComPtr<IDirect3D9> DirectXRenderer::D3D()
	{
		return m_d3d;
	}
	//End DirectXRenderer::D3D


    //=========================================================================
    //! @function    DirectXRenderer::Device
    //! @brief       Get access to the renderer's device object
	//!  
    //! @return      A reference to the renderer's device
    //=========================================================================
	CComPtr<IDirect3DDevice9> DirectXRenderer::Device()
	{
		return m_device;
	}
	//End DirectXRenderer::Device


};
//end namespace DirectX9Renderer


#endif
//#ifndef DIRECTX9RENDERER_DIRECTX9RENDERER_H
