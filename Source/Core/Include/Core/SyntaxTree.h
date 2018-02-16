//======================================================================================
//! @file         SyntaxTree.h
//! @brief        Template class used for parsing, representing a tree of parsed tokens
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Monday, 04 July 2005
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

#ifndef CORE_SYNTAXTREE_H
#define CORE_SYNTAXTREE_H


#include <list>
#include <boost/any.hpp>


//namespace Core
namespace Core
{


	//!@class	SyntaxTree
	//!@brief	Template class used for parsing, representing a tree of parsed tokens
	//!
	//!@param	NodeDescriptor		A type that can describe a node
	template <class NodeDescriptor>
		class SyntaxTree
	{
		public:


            //=========================================================================
            // Constructors/Destructor
            //=========================================================================
			SyntaxTree ( const NodeDescriptor& rootValue );

            //=========================================================================
            // Public types
            //=========================================================================
			
			//!Class representing a node in the syntax tree
			class Node
			{
				public:

					//Friends
					friend class SyntaxTree;

					//Constructors
                    Node ( const NodeDescriptor& desc, const boost::any& data, Node* parent )
						: m_desc(desc), m_data(data), m_parent(parent)
					{
					}

					Node ( const NodeDescriptor& desc, Node* parent )
						: m_desc(desc), m_parent(parent)
					{
					}

					//Public types
					typedef std::list<Node>					ChildStore;
					typedef ChildStore::iterator			iterator;
					typedef ChildStore::const_iterator		const_iterator;


					//Public methods
					
					//!Add a child as a root node, returning the new root node
					Node* AddChild( const NodeDescriptor& desc )	
					{
						m_children.push_back(Node(desc, this));
						return &m_children.back();
					}

					//!Add a child node
					void AddChild( const NodeDescriptor& desc, const boost::any& data )	
					{
						m_children.push_back(Node(desc, data, this));	
					}
					
					const NodeDescriptor&		Description() const				{ return m_desc;	}
					const boost::any&			Data() const					{ return m_data;	}
					const Node*					Parent() const					{ return m_parent;	}
					
					UInt				ChildrenCount() const	{ return m_children.size();		}

					//Iterator methods
					iterator			ChildrenBegin()			{ return m_children.begin();	}
					iterator			ChildrenEnd()			{ return m_children.end();		}
					const_iterator		ChildrenBegin()	const	{ return m_children.begin();	}
					const_iterator		ChildrenEnd() const		{ return m_children.end();		}

				private:

					//Private methods
					Node* Parent()	{ return m_parent;	}

					//Private data
					NodeDescriptor	m_desc;
					boost::any		m_data;
					Node*			m_parent;
					ChildStore		m_children;
					
			};

            //=========================================================================
            // Public methods
            //=========================================================================
			void AddRootNode ( const NodeDescriptor& desc );
			void AddNode	 ( const NodeDescriptor& desc, const boost::any& data = boost::any() );
			void EndRootNode ( );

			//Accessors
			inline const Node* Root() const { return &m_root;						}
			bool IsEmpty() const			{ return (m_root.ChildrenCount() == 0);	}

		private:

            //=========================================================================
            // Private data
            //=========================================================================
			Node  m_root;
			Node* m_current;

	};
	//End class SyntaxTree



    //=========================================================================
    //! @function    SyntaxTree<NodeDescriptor>::SyntaxTree
    //! @brief       SyntaxTree constructor
	//!
    //! @param		 Node descriptor value used for the root of the tree              
    //=========================================================================
	template <class NodeDescriptor>
		SyntaxTree<NodeDescriptor>::SyntaxTree ( const NodeDescriptor& rootValue )
		: m_root(rootValue, 0 ), m_current(&m_root)
	{
	}
	//End SyntaxTree<NodeDescriptor>::SyntaxTree



    //=========================================================================
    //! @function    SyntaxTree<NodeDescriptor>::AddRootNode
    //! @brief       Add a node to the tree, to act as a root node for
	//!				 any nodes that will be added to the tree subsequently
    //!             
	//!				 Any nodes added to the tree will be children of this node,
	//!				 until a corresponding call to EndRootNode is made
	//!
    //! @param       desc [in]	Descriptor for the node
    //!              
    //=========================================================================
	template <class NodeDescriptor>
		void SyntaxTree<NodeDescriptor>::AddRootNode ( const NodeDescriptor& desc )
	{
		m_current = m_current->AddChild ( desc );
	}
	//End SyntaxTree<NodeDescriptor>::AddRootNode




    //=========================================================================
    //! @function    SyntaxTree<NodeDescriptor>::AddNode
    //! @brief       Add a node to the tree as a child of the current node
    //!              
    //! @param       desc [in]
    //! @param       data [in]
    //!              
    //! @return      
    //! @throw       
    //=========================================================================
	template <class NodeDescriptor>
		void SyntaxTree<NodeDescriptor>::AddNode ( const NodeDescriptor& desc, const boost::any& data )
	{
		m_current->AddChild( desc, data );
	}
	//End SyntaxTree<NodeDescriptor>::AddNode



    //=========================================================================
    //! @function    SyntaxTree<NodeDescriptor>::EndRootNode
    //! @brief       Ends a root node. Any nodes created after this call
    //!              will be siblings of the previous root node.
	//!				 This should not be called if the current node is the root
	//!				 of the tree
    //=========================================================================
	template <class NodeDescriptor>
		void SyntaxTree<NodeDescriptor>::EndRootNode ()
	{
		debug_assert(m_current->Parent() != 0, "Called EndRootNode on the root of the tree, this is not allowed!" );

		m_current = m_current->Parent();
	}
	//End SyntaxTree<NodeDescriptor>::EndRootNode

};
//end namespace Core


#endif
//#ifndef CORESYNTAXTREE_H