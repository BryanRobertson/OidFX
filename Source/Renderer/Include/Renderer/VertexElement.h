//======================================================================================
//! @file         VertexElement.h
//! @brief        Class describing an element in a VertexDeclaration
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Sunday, 12 June 2005
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

#ifndef RENDERER_VERTEXELEMENT_H
#define RENDERER_VERTEXELEMENT_H


//namespace Renderer
namespace Renderer
{

	enum EElementType
	{
		DECLTYPE_FLOAT1,
		DECLTYPE_FLOAT2,
		DECLTYPE_FLOAT3,
		DECLTYPE_FLOAT4,
		DECLTYPE_COLOUR,
		DECLTYPE_UBYTE4,
		DECLTYPE_SHORT2,
		DECLTYPE_SHORT4,
		DECLTYPE_UBYTE4N,
		DECLTYPE_SHORT2N,
		DECLTYPE_SHORT4N,
		DECLTYPE_USHORT2N,
		DECLTYPE_USHORT4N,
		DECLTYPE_UDEC3,
		DECLTYPE_DEC3N,
		DECLTYPE_FLOAT16_2,
		DECLTYPE_FLOAT16_4
	};

	enum EElementUsage
	{
		DECLUSAGE_POSITION,
		DECLUSAGE_POSITIONT,
		DECLUSAGE_BLENDWEIGHT,
		DECLUSAGE_BLENDINDEX,
		DECLUSAGE_NORMAL,
		DECLUSAGE_POINTSIZE,
		DECLUSAGE_TEXCOORD,
		DECLUSAGE_TANGENT,
		DECLUSAGE_BINORMAL,
		DECLUSAGE_DIFFUSE,
		DECLUSAGE_SPECULAR
	};

	//!@class	VertexElement
	//!@brief	Class describing an element in a VertexDeclaration
	class VertexElement
	{
		public:
		
			VertexElement ( UInt streamIndex, 
						size_t offset, 
						EElementType type, 
						EElementUsage usage, 
						UInt usageIndex, 
						UInt method )
						: m_streamIndex(streamIndex), m_offset(offset), m_type(type), 
							m_usage(usage), m_usageIndex(usageIndex), m_method(method)
			{
			}

			UInt			StreamIndex() const	{ return m_streamIndex;	}
			size_t			Offset() const		{ return m_offset;		}
			EElementType	Type() const		{ return m_type;		}
			EElementUsage	Usage() const		{ return m_usage;		}
			UInt			UsageIndex() const	{ return m_usageIndex;	}
			UInt			Method() const		{ return m_method;		}

			//Used for sorting
			bool operator < ( const VertexElement& rhs ) const;

			inline friend std::ostream& operator << ( std::ostream& out, const VertexElement& element );

		private:

			UInt		  m_streamIndex;
			size_t		  m_offset;
			EElementType  m_type; 
			EElementUsage m_usage;
			UInt		  m_usageIndex; 
			UInt		  m_method;

	};
	//End class VertexElement



    //=========================================================================
    //! @function    operator <<
    //! @brief       
    //!              
    //! @param       out 
    //! @param       element 
    //!              
    //=========================================================================
	std::ostream& operator << ( std::ostream& out, const VertexElement& element )
	{
		out << "{ " << element.StreamIndex() 
			<< ", " << element.Offset()
			<< ", ";

		switch ( element.Type() )
		{
			case DECLTYPE_FLOAT1:
				out << "DECLTYPE_FLOAT1";
				break;

			case DECLTYPE_FLOAT2:
				out << "DECLTYPE_FLOAT2";
				break;

			case DECLTYPE_FLOAT3:
				out << "DECLTYPE_FLOAT3";
				break;

			case DECLTYPE_FLOAT4:
				out << "DECLTYPE_FLOAT4";
				break;

			case DECLTYPE_COLOUR:
				out << "DECLTYPE_COLOUR";
				break;

			case DECLTYPE_UBYTE4:
				out << "DECLTYPE_UBYTE4";
				break;

			case DECLTYPE_SHORT2:
				out << "DECLTYPE_SHORT2";
				break;

			case DECLTYPE_SHORT4:
				out << "DECLTYPE_SHORT4";
				break;

			case DECLTYPE_UBYTE4N:
				out << "DECLTYPE_UBYTE4N";
				break;

			case DECLTYPE_SHORT2N:
				out << "DECLTYPE_SHORT2N";
				break;

			case DECLTYPE_SHORT4N:
				out << "DECLTYPE_SHORT4N";
				break;

			case DECLTYPE_USHORT2N:
				out << "DECLTYPE_USHORT2N";
				break;

			case DECLTYPE_USHORT4N:
				out << "DECLTYPE_USHORT4N";
				break;

			case DECLTYPE_UDEC3:
				out << "DECLTYPE_UDEC3";
				break;

			case DECLTYPE_DEC3N:
				out << "DECLTYPE_DEC3N";
				break;

			case DECLTYPE_FLOAT16_2:
				out << "DECLTYPE_FLOAT16_2";
				break;

			case DECLTYPE_FLOAT16_4:
				out << "DECLTYPE_FLOAT16_4";
				break;
		}

		out << ", ";

		switch ( element.Usage() )
		{
			case DECLUSAGE_POSITION:
				out << "DECLUSAGE_POSITION";
				break;

			case DECLUSAGE_POSITIONT:
				out << "DECLUSAGE_POSITIONT";
				break;

			case DECLUSAGE_BLENDWEIGHT:
				out << "DECLUSAGE_BLENDWEIGHT";
				break;

			case DECLUSAGE_BLENDINDEX:
				out << "DECLUSAGE_BLENDINDEX";
				break;

			case DECLUSAGE_NORMAL:
				out << "DECLUSAGE_NORMAL";
				break;

			case DECLUSAGE_POINTSIZE:
				out << "DECLUSAGE_POINTSIZE";
				break;

			case DECLUSAGE_TEXCOORD:
				out << "DECLUSAGE_TEXCOORD";
				break;

			case DECLUSAGE_TANGENT:
				out << "DECLUSAGE_TANGENT";
				break;

			case DECLUSAGE_BINORMAL:
				out << "DECLUSAGE_BINORMAL";
				break;

			case DECLUSAGE_DIFFUSE:
				out << "DECLUSAGE_DIFFUSE";
				break;

			case DECLUSAGE_SPECULAR:
				out << "DECLUSAGE_SPECULAR";
				break;
		}

		out << ", " << element.UsageIndex() <<  ", " << element.Method() << "}";

		return out;
	}
	//End operator << ( std::ostream& out, const VertexElement& element )

};
//end namespace Renderer


#endif
//#ifndef VERTEXELEMENT_H
