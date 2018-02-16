//======================================================================================
//! @file         Billboard.h
//! @brief        Class representing a billboarded sprite
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Saturday, 15 October 2005
//! @copyright    Bryan Robertson 2005
//
//                This file is part of OidFX Engine.
//
//                OidFX Engine is free software; you can redistribute it and/or modify
//                it under the terms of the GNU General Public License as published by
//                the Free Software Foundation; either version 2 of the License, or
//                (at your option) any later version.
//
//                OidFX Engine is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty of
//                MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//                GNU General Public License for more details.
//
//                You should have received a copy of the GNU General Public License
//                along with OidFX Engine; if not, write to the Free Software
//                Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//======================================================================================


#ifndef OIDFX_BILLBOARD_H
#define OIDFX_BILLBOARD_H


#include "Math/Vector3D.h"
#include "Renderer/Effect.h"


//=========================================================================
// Forward declarations
//=========================================================================
namespace OidFX		{ class Camera; }



//namespace OidFX
namespace OidFX
{


	//!@class	Billboard
	//!@brief	Class representing a billboarded sprite, can only be created
	//!			through the BillboardManager
	class Billboard
	{
		public:

			//=========================================================================
            // Constructor
            //=========================================================================
			Billboard ( Renderer::HEffect& effect );

            //=========================================================================
            // Public types
            //=========================================================================
			enum EXFormType 
			{ 
				XFORM_ROTATE,
				XFORM_SCALE,
				XFORM_OPACITY
			};

			enum EWaveType
			{
				WAVE_SINE,
				WAVE_TRIANGLE,
				WAVE_SQUARE,
				WAVE_SAWTOOTH,
				WAVE_INVERSE_SAWTOOTH
			};

			struct WaveXForm
			{
				EXFormType	transformType;
				EWaveType	waveType;
				Float		base;
				Float		frequency;
				Float		phase;
				Float		amplitude;
			};

			//! Warning, don't change this, it indexes into the m_vertices array
			enum EVertexIdent
			{
				VERT_TOPLEFT,
				VERT_TOPRIGHT,
				VERT_BOTTOMLEFT,
				VERT_BOTTOMRIGHT
			};

            //=========================================================================
            // Public methods
            //=========================================================================
			void Update ( Float timeElapsedInSeconds );
			void RecalculateVertices ( const OidFX::Camera& camera );

			inline const Math::Vector3D& GetVertex ( EVertexIdent ident );

			inline Renderer::HEffect	 GetEffect() const throw();
			inline const Math::Vector3D& GetPosition() const throw();
			inline Float GetScale() const throw();
			inline Float GetRotation() const throw();
			inline Float GetOpacity() const throw();
			inline Float GetScaleAnim() const throw();
			inline Float GetRotateAnim() const throw();
			inline Float GetOpacityAnim() const throw();

			inline void SetEffect	   ( const Renderer::HEffect& effect ) throw();
			inline void SetPosition	   ( const Math::Vector3D& position ) throw();
			inline void SetScale	   ( Float amount ) throw();
			inline void SetRotation    ( Float amount ) throw();
			inline void SetOpacity	   ( Float opacity ) throw();
			inline void SetScaleAnim   ( Float amount ) throw();
			inline void SetRotateAnim  ( Float amount ) throw();
			inline void SetOpacityAnim ( Float amount ) throw();

			inline void AddWaveTransform ( EXFormType transformType, EWaveType waveType, Float base,
											Float frequency, Float phase, Float amplitude  ) throw();


		private:

            //=========================================================================
            // Private methods
            //=========================================================================
			void UpdateTransforms( Float timeElapsedInSeconds );

            //=========================================================================
            // Private types
            //=========================================================================
			typedef Core::Vector<WaveXForm>::Type WaveXFormStore;

			//=========================================================================
            // Private data
            //=========================================================================

			//Vertices are recalculated each frame using the attributes of the 
			Math::Vector3D		m_vertices[4];

			Renderer::HEffect	m_effect;
			Math::Vector3D		m_position;
			Float				m_scale;
			Float				m_rotation;
			Float				m_opacity;
			Float				m_scaleAnim;
			Float				m_rotateAnim;
			Float				m_opacityAnim;

			Float				m_wavePosition;

			WaveXFormStore		m_transforms;

	};
	//End class Billboard


    //=========================================================================
    //! @function    Billboard::GetEffect
    //! @brief       Return the effect this billboard uses
    //!              
    //! @return      The effect this billboard uses
    //=========================================================================
	Renderer::HEffect Billboard::GetEffect() const 
	{
		return m_effect;
	}
	//End Billboard::GetEffect



    //=========================================================================
    //! @function    Billboard::GetVertex
    //! @brief       Get one of the billboard's vertices
    //!              
    //! @param       ident [in] Identifier of the vertex
    //!              
    //! @return      The appropriate billboard vertex
    //=========================================================================
	const Math::Vector3D& Billboard::GetVertex ( EVertexIdent ident )
	{
		debug_assert ( static_cast<UInt>(ident) < 4, "Ident out of range!" );

		return m_vertices[static_cast<UInt>(ident)];
	}
	//End Billboard::GetVertex


    //=========================================================================
    //! @function    Billboard::GetPosition
    //! @brief       Return the position of the billboard
    //!              
	//! @return		 The position of the billboard
    //=========================================================================
	const Math::Vector3D& Billboard::GetPosition() const
	{
		return m_position;
	}
	//End Billboard::GetPosition 



    //=========================================================================
    //! @function    Billboard::GetScale
    //! @brief       Return the scale of the billboard
    //!              
	//!				 The scale is the radius with which the billboard will be drawn
	//!
	//! @return		 The scale of the billboard
    //=========================================================================
	Float Billboard::GetScale() const
	{
		return m_scale;
	}
	//End Billboard::GetScale



    //=========================================================================
    //! @function    Billboard::GetRotation
    //! @brief       Return the rotation of the billboard in radians
    //!              
    //! @return      The rotation of the billboard in radians
    //=========================================================================
	Float Billboard::GetRotation() const
	{
		return m_rotation;
	}
	//End Billboard::GetRotation



    //=========================================================================
    //! @function    Billboard::GetOpacity
    //! @brief       Return the opacity of the billboard
	//!
    //! @return      The opacity of the billboard
    //=========================================================================
	Float Billboard::GetOpacity() const
	{
		return m_opacity;
	}
	//End Billboard::GetOpacity



    //=========================================================================
    //! @function    Billboard::GetScaleAnim
    //! @brief       Return the rate of change of the scale value of the billboard
    //!              
	//!				 The scale is the radius with which the billboard will be drawn
	//!
    //! @return      The animated scale value of the billboard
    //=========================================================================
	Float Billboard::GetScaleAnim() const
	{
		return m_scaleAnim;
	}
	//End Billboard::GetScaleAnim



    //=========================================================================
    //! @function    Billboard::GetRotateAnim
    //! @brief       Return the rate of change of the rotation of the billboard
    //!              
    //! @return      The rate of change of the billboard rotation
    //=========================================================================
	Float Billboard::GetRotateAnim() const
	{
		return m_rotateAnim;
	}
	//End Billboard::GetRotateAnim


    //=========================================================================
    //! @function    Billboard::GetOpacityAnim
    //! @brief       Return the rate of change of the opacity of the billboard
    //!              
    //! @return      The rate of change of the opacity of the billboard
    //=========================================================================
	Float Billboard::GetOpacityAnim() const
	{
		return m_opacityAnim;
	}
	//End Billboard::GetOpacityAnim


    //=========================================================================
    //! @function    Billboard::SetEffect
    //! @brief       Set the effect used to render the billboard
    //!              
    //! @param       effect [in]
    //!              
    //=========================================================================
	void Billboard::SetEffect ( const Renderer::HEffect& effect ) throw()
	{
		m_effect = effect;
	}
	//End Billboard::SetEffect


    //=========================================================================
    //! @function    Billboard::SetPosition
    //! @brief       Set the position of the billboard
	//!				 (the point in space about which the billboard vertices are centered)
    //!              
    //! @param       position [in]	New position for the billboard.
    //!              
    //=========================================================================
	void Billboard::SetPosition( const Math::Vector3D& position )
	{
		m_position = position;
	}
	//End Billboard::SetPosition


    //=========================================================================
    //! @function    Billboard::SetScale
    //! @brief       Set the scale factor of the billboard
    //!              
	//!				 The scale is the radius with which the billboard will be drawn
	//!
    //! @param       amount [in] The new scale factor for the billboard
    //!              
    //=========================================================================
	void Billboard::SetScale( Float amount )
	{
		m_scale = amount;
	}
	//End Billboard::SetScale


    //=========================================================================
    //! @function    Billboard::SetRotation
    //! @brief       Set the rotation of the billboard in radians
    //!              
    //! @param       amount [in] The new rotation amount for the billboard
    //!              
    //=========================================================================
	void Billboard::SetRotation( Float amount )
	{
		m_rotation = amount;
	}
	//End Billboard::SetRotation


    //=========================================================================
    //! @function    Billboard::SetOpacity
    //! @brief       Set the opacity of the billboard
    //!              
    //! @param       opacity [in] Number between 0 and 1 representing the opacity
    //!							  the value will be clamped to this range automatically              
	//!
    //=========================================================================
	void Billboard::SetOpacity( Float opacity )
	{

		if ( opacity > 1.0f )
		{
			opacity = 1.0f;
		}
		else if ( opacity < 0.0f )
		{
			opacity = 0.0f;
		}

		m_opacity = opacity;

	}
	//End Billboard::SetOpacity



    //=========================================================================
    //! @function    Billboard::SetScaleAnim
    //! @brief       Set the rate of change of the scale factor
    //!              
	//!				 The scale is the radius with which the billboard will be drawn
	//!
    //! @param       amount [in] New rate of change for the scale factor
    //!              
    //=========================================================================
	void Billboard::SetScaleAnim( Float amount )
	{
		m_scaleAnim = amount;
	}
	//End Billboard::SetScaleAnim



    //=========================================================================
    //! @function    Billboard::SetRotateAnim
    //! @brief       Set the rate of change of the rotation
    //!              
    //! @param       amount [in] New rate of change for rotation
    //!              
    //=========================================================================
	void Billboard::SetRotateAnim( Float amount )
	{
		m_rotateAnim = amount;
	}
	//End Billboard::SetRotateAnim


    //=========================================================================
    //! @function    Billboard::SetOpacityAnim
    //! @brief       Set the rate of change of the opacity
    //!              
    //! @param       amount [in] New rate of change for opacity
    //!              
    //=========================================================================
	void Billboard::SetOpacityAnim( Float amount )
	{
		m_opacityAnim = amount;
	}
	//End  Billboard::SetOpacityAnim


    //=========================================================================
    //! @function    Billboard::AddWaveTransform
    //! @brief       
    //!              
    //! @param       transformType [in]	
    //! @param       waveType	   [in]	
    //! @param       base		   [in]	
    //! @param       frequency	   [in]	
    //! @param       phase		   [in]	
    //! @param       amplitude	   [in]	
    //!              
    //=========================================================================
	void Billboard::AddWaveTransform ( EXFormType transformType, 
									  EWaveType waveType,
									  Float base,
									  Float frequency,
									  Float phase,
									  Float amplitude )
	{
		WaveXForm xform =
		{
			transformType,
			waveType,		
			base,
			frequency,
			phase,
			amplitude
		};

		m_transforms.push_back( xform );
	}
	//End Billboard::AddWaveTransform



}
//end namespace OidFX



#endif
//#ifndef OIDFX_BILLBOARD_H

