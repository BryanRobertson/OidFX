//======================================================================================
//! @file         Containers.h
//! @brief        Typedefs for container types
//!               
//!               
//!               
//! @author       Bryan Robertson
//! @date         Wednesday, 21 September 2005
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


#ifndef CORE_CONTAINERS_H
#define CORE_CONTAINERS_H


//#include <boost/multi_array.hpp>


//namespace Core
namespace Core
{

	//=========================================================================
    // Typedef String as PooledString
    //=========================================================================
	typedef PooledString		String;
	typedef PooledStringStream	StringStream;
	

    //=========================================================================
    // The following template classes are used to create typedefs for 
	// STL containers which use FastPoolAllocator
    //=========================================================================

	//! Acts as a typedef for a std::vector that uses FastPoolAllocator
	template <class ValueType> 
		struct Vector
		{
			typedef std::vector<ValueType, FastPoolAllocator<ValueType>::Type >	Type;
		};
	//End struct Vector
/*
	//! Acts as a typedef for a boost::multiarray that uses FastPoolAllocator
	template <class ValueType, std::size_t count>
		struct MultiArray
		{
			typedef boost::multi_array<ValueType, count, FastPoolAllocator<ValueType>::Type > Type;
		};
	//End struct MultiArray
*/

	//! Acts as a typedef for a std::list that uses FastPoolAllocator
	template <class ValueType>
		struct List
		{
			typedef std::list<ValueType, FastPoolAllocator<ValueType>::Type >		Type;
		};
	//End struct List


	//! Acts as a typedef for a std::queue that uses FastPoolAllocator
	template <class ValueType>
		struct Queue
		{
			typedef std::queue<ValueType, FastPoolAllocator<ValueType>::Type >	Type;
		};
	//End struct Queue


	//! Acts as a typedef for a std::deque that uses FastPoolAllocator
	template <class ValueType>
		struct Deque
		{
			typedef std::deque<ValueType, FastPoolAllocator<ValueType>::Type >	Type;
		};
	//End struct Deque


	//! Acts as a typedef for a std::priority_queue that uses FastPoolAllocator
	template <class ValueType, class Sequence = Vector<ValueType>::Type, class Compare = std::less<ValueType> >
		struct PriorityQueue
		{
			typedef std::priority_queue<ValueType, Sequence, Compare>	Type;
		};
	//End struct PriorityQueue


	//! Acts as a typedef for a std::set that uses FastPoolAllocator
	template <class ValueType>
		struct Set
		{
			typedef std::set<ValueType, FastPoolAllocator<ValueType>::Type >		Type;
		};
	//End struct Set


	//! Acts as a typedef for a std::multiset that uses FastPoolAllocator
	template <class ValueType>
		struct MultiSet
		{
			typedef std::multiset<ValueType, FastPoolAllocator<ValueType>::Type >		Type;
		};
	//End struct Set
		

	//! Acts as a typedef for a std::map that uses FastPoolAllocator
	template <class Key, class ValueType, class Compare = std::less<Key> >
		struct Map
		{
			typedef std::map<Key, ValueType, Compare, 
							 FastPoolAllocator<std::pair<const Key,ValueType> > >	Type;
		};
	//End struct Map


	//! Acts as a typedef for a std::multimap that uses FastPoolAllocator
	template <class Key, class ValueType, class Compare = std::less<Key> >
		struct MultiMap
		{
			typedef std::multimap<Key, ValueType, Compare, 
								  FastPoolAllocator<std::pair<const Key,ValueType> > >	Type;
		};
	//End struct MultiMap


//Check that there is library support for std::hash_map
#ifdef CORE_HASHMAP_SUPPORTED
		
	//! Acts as a typedef for a std::hash_map that uses FastPoolAllocator
	template <class Key, class ValueType, class HashFunc = std::hash<Key>, class EqualKey = std::equal_to<Key> >
		struct HashMap
		{
			typedef std::hash_map<Key, ValueType, HashFunc, EqualKey, 
								  FastPoolAllocator<std::pair<const Key,ValueType> > >	Type;
		};
	//End struct HashMap


	//! Acts as a typedef for a std::hash_multimap that uses FastPoolAllocator
	template <class Key, class ValueType, class HashFunc = std::hash<Key>, class EqualKey = std::equal_to<Key> >
		struct HashMultiMap
		{
			typedef std::hash_multimap<Key, ValueType, HashFunc, EqualKey, 
									   FastPoolAllocator<std::pair<const Key,ValueType> > >	Type;
		};
	//End struct HashMultiMap


#endif
//ifdef CORE_HASHMAP_SUPPORTED


//Check that there is library support for std::hash_set
#ifdef CORE_HASHSET_SUPPORTED

	
	//! Acts as a typedef for a std::hash_set that uses FastPoolAllocator
	template <class Key, class HashFunc = std::hash<Key>, class EqualKey = std::equal_to<Key> >
		struct HashSet
		{
			typedef std::hash_set<Key, HashFunc, EqualKey, FastPoolAllocator<Key> >	Type;
		};
	//End struct HashSet


	//! Acts as a typedef for a std::hash_multiset that uses FastPoolAllocator
	template <class Key, class HashFunc = std::hash<Key>, class EqualKey = std::equal_to<Key> >
		struct HashMultiSet
		{
			typedef std::hash_multiset<Key, HashFunc, EqualKey, FastPoolAllocator<Key> >		Type;
		};
	//End struct HashMultiSet


#endif
//#ifdef CORE_HASHSET_SUPPORTED



}
//end namespace Core


#endif
//#ifndef
