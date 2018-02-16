//======================================================================================
//! @file         VisibleObjectList.h
//! @brief        Class containing a list of visible objects to be rendered
//!				  When the scene is rendered, all visible objects add themselves               
//!				  to a VisibleObjectList, in order to be queued for rendering
//!               
//! @author       Bryan Robertson
//! @date         Thursday, 14 July 2005
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

#ifndef OIDFX_VISIBLEOBJECTLIST_H
#define OIDFX_VISIBLEOBJECTLIST_H


#include <list>
#include <boost/pool/pool_alloc.hpp>


//=========================================================================
// Forward declaration
//=========================================================================
namespace Renderer { class RenderQueue; }
namespace OidFX	   { class SceneNode;	}


//namespace OidFX
namespace OidFX
{


	//!@class	VisibleObjectList
	//!@brief	Class containing a list of visible objects to be rendered
	//!
	//!			When the scene is rendered, all visible objects add themselves               
	//!			to a VisibleObjectList, in order to be queued for rendering
	class VisibleObjectList
	{
		public:

            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			VisibleObjectList();

            //=========================================================================
            // Public types
            //=========================================================================
			typedef std::list<SceneNode*, boost::fast_pool_allocator<SceneNode*> > List;
			typedef List::iterator				iterator;
			typedef List::const_iterator		const_iterator;

            //=========================================================================
            //  Public methods
            //=========================================================================
			void QueueAllForRendering ( Renderer::RenderQueue& queue );
			
			inline void AddObject ( SceneNode& node )		{ m_list.push_back(&node);		}
			inline void Clear()								{ m_list.clear();				}
			inline size_t Size() const						{ return m_list.size();			}

			inline iterator			Begin()					{ return m_list.begin();		}
			inline iterator			End()					{ return m_list.end();			}
			inline const_iterator	Begin()	const			{ return m_list.begin();		}
			inline const_iterator	End() const				{ return m_list.end();			}

		private:

            //=========================================================================
            // Private data
            //=========================================================================
			List m_list;

	};
	//End class VisibleObjectList


};
//end namespace OidFX


#endif
//#ifndef OIDFX_VISIBLEOBJECTLIST_H