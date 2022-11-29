/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:30:22 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/22 16:44:38 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <iostream>
# include "utils.hpp"
# include "iterator.hpp"
# include "comparison.hpp"

namespace ft
{
	template<
    	class T,
    	class Allocator = std::allocator<T>
	>
	class vector
	{
		public:
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef std::size_t											size_type;
			typedef	std::ptrdiff_t										difference_type;
			typedef typename Allocator::reference						reference;
			typedef typename Allocator::const_reference					const_reference;
			typedef typename Allocator::pointer							pointer;
			typedef typename Allocator::const_pointer					const_pointer;
			typedef typename ft::random_access_iterator<pointer>		iterator;
			typedef typename ft::random_access_iterator<const_pointer>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;


			/* ===================== Constructors ===================== */
			vector(): _alloc(Allocator()), _start(0), _allocated(0), _size(0) {};

			explicit vector( const Allocator& alloc ): _alloc(alloc), _start(0), _allocated(0), _size(0) {};

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()): _alloc(alloc), _start(0), _allocated(0), _size(0)
			{
				assign(count, value);
			};

			template< class InputIterator >
			vector( InputIterator first, InputIterator last, const Allocator& alloc = Allocator(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr ): _alloc(alloc), _start(0), _allocated(0), _size(0)
			{
				assign(first, last);
			};

			vector( const vector& other ): _alloc(other._alloc), _start(0), _allocated(0), _size(0)
			{
				assign(other.begin(), other.end());
			};


			/* ===================== Destructor ===================== */
			~vector()
			{
				for (size_type i = 0; i < _allocated; i++)
					_alloc.destroy(_start + i);
				_alloc.deallocate(_start, _allocated);
			};


			/* ===================== Assign ===================== */
			vector& operator=( const vector& other )
			{
				if (this == &other)
					return *this;
				for (size_type i = 0; i < _allocated; i++)
					_alloc.destroy(_start + i);
				_alloc.deallocate(_start, _allocated);
				_start = _alloc.allocate(other.size() * sizeof(T));
				_size = other.size();
				_allocated = other.size();
				for (size_type i = 0; i < other.size(); i++)
					_alloc.construct(_start + i, *(other._start + i));
				return *this;
			};

			void assign( size_type count, const T& value )
			{
				this->resize(0);
				this->insert(this->begin(), count, value);
			};
			template< class InputIterator >
			void assign( InputIterator first, InputIterator last )
			{
				this->resize(0);
				this->insert(this->begin(), first, last);
			};		


			/* ===================== Allocator ===================== */
			allocator_type get_allocator() const { return _alloc; };


			/* ===================== Element access ===================== */
			reference at( size_type pos )
			{
				if (pos >= _size)
					throw std::out_of_range("vector::at");
				return _start[pos];
			};
			const_reference at( size_type pos ) const
			{
				if (pos >= _size)
					throw std::out_of_range("vector::at");
				return _start[pos];
			};

			reference operator[]( size_type pos ) { return _start[pos]; };
			const_reference operator[]( size_type pos ) const { return _start[pos]; };

			reference front() { return _start[0]; };
			const_reference front() const { return _start[0]; };

			reference back() { return _start[_size - 1]; };
			const_reference back() const { return _start[_size - 1]; };

			T* data() { return _start; };
			const T* data() const { return _start; };


			/* ===================== Iterators ===================== */
			iterator begin() { return iterator(_start); };
			const_iterator begin() const { return const_iterator(_start); };

			iterator end() { return iterator(_start + _size); };
			const_iterator end() const { return const_iterator(_start + _size); };

			reverse_iterator rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };

			reverse_iterator rend() { return reverse_iterator(begin()); };
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };


			/* ===================== Capacity ===================== */
			size_type size() const { return _size; };

			bool empty() const { return _size == 0; };

			size_type max_size() const { return _alloc.max_size(); };

			void reserve( size_type new_cap )
			{
				if (new_cap > _allocated)
				{
					pointer tmp = _alloc.allocate(new_cap * sizeof(T));
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(tmp + i, _start[i]);
					for (size_type i = _size; i < new_cap; i++)
						_alloc.construct(tmp + i, T());
					for (size_type i = 0; i < _allocated; i++)
						_alloc.destroy(_start + i);
					_alloc.deallocate(_start, _allocated);
					_allocated = new_cap;
					_start = tmp;
				}
			};

			size_type capacity() const { return _allocated; };


			/* ===================== Modifiers ===================== */
			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				_size = 0;
			};

			iterator insert( const_iterator pos, const T& value ) { return this->insert(pos, 1, value); };

			iterator insert( const_iterator pos, size_type count, const T& value )
			{
				difference_type offset = pos - begin();
				if (count == 0)
					return iterator(begin() + offset);
				while (_size + count > _allocated)
					reserve(_allocated == 0 ? count : _allocated * 2);
				if (_size != 0 && pos != end())
				{
					for (difference_type i = _size - 1; i >= offset; i--)
						_alloc.construct(_start + i + count, _start[i]);
				}
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_start + offset + i, value);
				_size += count;
				return iterator(_start + offset);
			}

			template< class InputIterator >
			iterator insert( const_iterator pos, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr )
			{
				difference_type count = ft::distance(first, last);
				difference_type offset = pos - begin();
				if (first == last)
					return iterator(begin() + offset);
				while (_size + count > _allocated)
					reserve(_allocated == 0 ? count : _allocated * 2);
				if (_size != 0 && pos != end())
				{
					for (difference_type i = _size - 1; i >= offset; i--)
						_alloc.construct(_start + i + count, _start[i]);
				}
				for (difference_type i = 0; i < count; i++)
					_alloc.construct(_start + offset + i, *first++);
				_size += count;
				return iterator(_start + offset);
			}

			iterator erase( iterator pos ) {
				if (pos == end())
					return end();
				return this->erase(pos, pos + 1);
			};

			iterator erase( iterator first, iterator last )
			{
				difference_type count = ft::distance(first, last);
				difference_type offset = first - begin();
				if (count == 0)
					return last;
				for (size_type i = offset + count; i < _size; i++)
				{
					_start[i - count] = _start[i];
				}
				_size -= count;
				return iterator(_start + offset);
			}

			void push_back( const T& value )
			{
				if (_size == _allocated)
					reserve(_allocated == 0 ? 1 : _allocated * 2);
				_alloc.construct(_start + _size, value);
				_size++;
			};

			void pop_back()
			{
				if (_size == 0)
					return;
				_size--;
			};
			
			void resize( size_type count, T value = T() )
			{
				if (count > _size)
					this->insert(end(), count - _size, value);
				else
					this->erase(begin() + count, end());
			}

			void swap( vector& other )
			{
				ft::swap(_start, other._start);
				ft::swap(_size, other._size);
				ft::swap(_allocated, other._allocated);
				ft::swap(_alloc, other._alloc);
			};

		private:
			Allocator		_alloc;
			pointer			_start;
			size_type		_allocated;
			size_type		_size;
		
	};

	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};

	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	};

	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), ft::less<T>);
	};

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		if (lhs == rhs)
			return true;
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), ft::less<T>);
	};

	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs <= rhs);
	};

	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs < rhs);
	};

	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
	{
		lhs.swap(rhs);
	};
}

#endif