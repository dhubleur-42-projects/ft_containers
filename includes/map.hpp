/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:47:54 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 15:50:12 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "RBtree.hpp"
# include "pair.hpp"
# include "utils.hpp"

namespace ft
{
	template<
		class Key,
		class Value,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, Value> >
	>
	class map
	{
		public:
			typedef Key     																								key_type;
			typedef Value   																								mapped_type;
			typedef ft::pair<const Key, Value> 																				value_type;
			typedef std::size_t																								size_type;
			typedef	std::ptrdiff_t																							difference_type;
			typedef Compare																									key_compare;
			typedef Allocator																								allocator_type;
			typedef typename allocator_type::reference																		reference;
			typedef typename allocator_type::const_reference																const_reference;
			typedef typename allocator_type::pointer																		pointer;
			typedef typename allocator_type::const_pointer																	const_pointer;
			typedef typename ft::RBtree<key_type, value_type, ft::PairtSelectKey<value_type>, key_compare, allocator_type>  tree_type;
			typedef typename tree_type::iterator																			iterator;
			typedef typename tree_type::const_iterator																		const_iterator;
			typedef typename ft::reverse_iterator<iterator>																	reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>															const_reverse_iterator;
	
			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				friend class map;
				public:
					typedef typename binary_function<value_type, value_type, bool>::result_type				result_type;
					typedef typename binary_function<value_type, value_type, bool>::first_argument_type		first_argument_type;
					typedef typename binary_function<value_type, value_type, bool>::second_argument_type	second_argument_type;
					bool	operator()(const value_type& x, const value_type& y) { return (comp(x.first, y.first)); }
				protected:
					value_compare(key_compare comp) : comp(comp) {}
					key_compare	comp;
			};


			/* ===================== Constructors ===================== */
			map() {};

			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) { _tree = tree_type(comp, alloc); };
			
			template< class InputIterator >
			map( InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
			{
				_tree = tree_type(alloc, comp);
				this->insert(first, last);
			};
			
			map( const map& other ) { *this = other; };


			/* ===================== Destructor ===================== */
			~map() {};


			/* ===================== Assign ===================== */
			map& operator=( const map& other ) { _tree = other._tree; return *this; };


			/* ===================== Allocator ===================== */
			allocator_type get_allocator() const { return _tree.get_allocator(); };


			/* ===================== Element access ===================== */
			Value& at( const Key& key )
			{
				value_type *value = _tree.at(key);
				if (value == NULL)
					throw std::out_of_range("map::at");
				return value->second;
			}
			
			const Value& at( const Key& key ) const
			{
				value_type *value = _tree.at(key);
				if (value == NULL)
					throw std::out_of_range("map::at");
				return value->second;
			}

			Value& operator[]( const Key& key )
			{
				value_type *value = _tree.at(key);
				if (value == NULL)
				{
					ft::pair<iterator, bool> pair = _tree.insert(ft::make_pair(key, Value()));
					value = &(*pair.first);
				}
				return value->second;
			}

			/* ===================== Iterators ===================== */
			iterator begin() { return _tree.begin(); };

			const_iterator begin() const { return _tree.begin(); };

			iterator end() { return _tree.end(); };

			const_iterator end() const { return _tree.end(); };

			reverse_iterator rbegin() { return reverse_iterator(end()); };

			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };

			reverse_iterator rend() { return reverse_iterator(begin()); };

			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };


			/* ===================== Capacity ===================== */
			bool empty() const { return (_tree.size() == 0); };

			size_type size() const { return _tree.size(); };

			size_type max_size() const { return _tree.max_size(); };


			/* ===================== Modifiers ===================== */
			void clear() { _tree.clear(); };

			ft::pair<iterator, bool> insert( const value_type& value ) { return _tree.insert(value);}

			iterator insert( iterator pos, const value_type& value ) { (void)pos; return _tree.insert(value).first; };

			template< class InputIterator >
			void insert( InputIterator first, InputIterator last )
			{
				while (first != last)
				{
					_tree.insert(*first);
					first++;
				}
			};

			iterator erase( iterator pos )
			{
				return _tree.remove((*pos).first);
			};

			iterator erase( iterator first, iterator last )
			{
				iterator result = first;
				iterator tmp;
				while (first != last)
				{
					tmp = first;
					first++;
					result = erase(tmp);
				}
				return result;
			};

			size_type erase( const Key& key )
			{
				if (_tree.at(key) == nullptr)
					return 0;
				_tree.remove(key);
				return 1;
			}

			void swap( map& other ) { _tree.swap(other._tree); };


			/* ===================== Lookup ===================== */
			size_type count( const Key& key ) const
			{
				if (_tree.at(key) == nullptr)
					return 0;
				return 1;
			};

			iterator find( const Key& key )
			{
				value_type *value = _tree.at(key);
				if (value == NULL)
					return end();
				return iterator(_tree.find(key));
			};

			const_iterator find( const Key& key ) const
			{
				value_type *value = _tree.at(key);
				if (value == NULL)
					return end();
				return const_iterator(_tree.find(key)); 
			};

			ft::pair<iterator,iterator> equal_range( const Key& key ) { return ft::make_pair(lower_bound(key), upper_bound(key)); };

			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			};

			iterator lower_bound( const Key& key )
			{
				for (iterator it = begin(); it != end(); it++)
				{
					if ((*it).first >= key)
						return it;
				}
				return end();
			};

			const_iterator lower_bound( const Key& key ) const
			{
				for (const_iterator it = begin(); it != end(); it++)
				{
					if ((*it).first >= key)
						return it;
				}
				return end();
			};

			iterator upper_bound( const Key& key )
			{
				for (iterator it = begin(); it != end(); it++)
				{
					if ((*it).first > key)
						return it;
				}
				return end();
			};

			const_iterator upper_bound( const Key& key ) const
			{
				for (const_iterator it = begin(); it != end(); it++)
				{
					if ((*it).first > key)
						return it;
				}
				return end();
			};

			key_compare key_comp() const { return _tree.key_comp(); };

			value_compare value_comp() const { return value_compare(_tree.key_comp()); };
	
			friend bool operator==( const ft::map<Key,Value,Compare,Allocator>& lhs, const ft::map<Key,Value,Compare,Allocator>& rhs ) { return lhs._tree == rhs._tree; };

			friend bool operator<( const ft::map<Key,Value,Compare,Allocator>& lhs, const ft::map<Key,Value,Compare,Allocator>& rhs ) { return lhs._tree < rhs._tree; };

		protected:
			tree_type	_tree;
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return !(lhs == rhs); };

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return (lhs == rhs) || (lhs < rhs); };

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return !(lhs <= rhs); };

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return !(lhs < rhs); };

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) { lhs.swap(rhs); };

}

#endif