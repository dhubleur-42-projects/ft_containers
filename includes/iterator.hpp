/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:52:11 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 15:19:35 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "RBtree.hpp"

namespace ft
{

	//Basic iterator implementation
	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	>
	struct const_iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template< 
		class Iterator
	>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class Iterator>
		struct iterator_traits<Iterator*>
		{
			typedef Iterator								value_type;
			typedef Iterator*								pointer;
			typedef Iterator&								reference;
			typedef std::ptrdiff_t					difference_type;
			typedef std::random_access_iterator_tag	iterator_category;
		};

	template <class Iterator>
		struct iterator_traits<const Iterator*>
		{
			typedef Iterator								value_type;
			typedef const Iterator*						pointer;
			typedef const Iterator&						reference;
			typedef std::ptrdiff_t					difference_type;
			typedef std::random_access_iterator_tag	iterator_category;
		};

	template <class Iterator>
		class random_access_iterator: public iterator<
										typename iterator_traits<Iterator>::iterator_category,
										typename iterator_traits<Iterator>::value_type,
										typename iterator_traits<Iterator>::difference_type,
										typename iterator_traits<Iterator>::pointer,
										typename iterator_traits<Iterator>::reference>
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			
			//Constructors
			random_access_iterator() : current() {};
			explicit random_access_iterator(iterator_type it) : current(it) {};
			random_access_iterator(const random_access_iterator & src) : current(src.current) {};
			template<
				class U
			>
			random_access_iterator( const random_access_iterator<U>& other ) : current(other.base()) {};

			//Destructor
			~random_access_iterator() {};

			//Accessors
			iterator_type base() const { return current; };

			//Operator overloads
			template<
				class U
			>
			random_access_iterator& operator=( const random_access_iterator<U>& other )
			{
				current = other.base();
				return *this;
			};

			reference operator*() const
			{
				return *current;
			};

			pointer operator->() const { return &(operator*()); };

			reference operator[]( difference_type n ) const { return *(*this + n); };

			random_access_iterator& operator++()
			{
				++current;
				return *this;
			};
			random_access_iterator operator++( int )
			{
				random_access_iterator tmp = *this;
				++current;
				return tmp;
			};

			random_access_iterator& operator--()
			{
				--current;
				return *this;
			};
			random_access_iterator operator--( int )
			{
				random_access_iterator tmp = *this;
				--current;
				return tmp;
			};

			random_access_iterator operator+( difference_type n ) const { return random_access_iterator(current + n); };
			random_access_iterator& operator+=( difference_type n )
			{
				current += n;
				return *this;
			};

			random_access_iterator operator-( difference_type n ) const { return random_access_iterator(current - n); };
			random_access_iterator& operator-=( difference_type n )
			{
				current -= n;
				return *this;
			};

		protected:
			Iterator current;

			
	};

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator==( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs ) { return lhs.base() == rhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator!=( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs ) { return lhs.base() != rhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator<( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs ) { return lhs.base() < rhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator<=( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs ) { return lhs.base() <= rhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator>( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs ) { return lhs.base() > rhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator>=( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs ) { return lhs.base() >= rhs.base(); };

	template<
		class Iter
	>
	random_access_iterator<Iter> operator+( typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& it ) { return random_access_iterator<Iter>(it.base() + n); };

	template<
		class Iterator1,
		class Iterator2
	>
	typename random_access_iterator<Iterator1>::difference_type operator-( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs ) { return lhs.base() - rhs.base(); };







	template <
		class Iterator
	>
	class reverse_iterator : public iterator<
										typename iterator_traits<Iterator>::iterator_category,
										typename iterator_traits<Iterator>::value_type,
										typename iterator_traits<Iterator>::difference_type,
										typename iterator_traits<Iterator>::pointer,
										typename iterator_traits<Iterator>::reference>
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

			//Constructors
			reverse_iterator() : current() {};
			explicit reverse_iterator(iterator_type it) : current(it) {};
			reverse_iterator(const reverse_iterator & src) : current(src.current) {};
			template<
				class U
			>
			reverse_iterator( const reverse_iterator<U>& other ) : current(other.base()) {};

			//Destructor
			~reverse_iterator() {};

			//Accessors
			iterator_type base() const { return current; };

			//Operator overloads
			template<
				class U
			>
			reverse_iterator& operator=( const reverse_iterator<U>& other )
			{
				current = other.base();
				return *this;
			};

			reference operator*() const
			{
				iterator_type tmp = current;
				return *(--tmp);
			};

			pointer operator->() const { return &(operator*()); };

			reference operator[]( difference_type n ) const { return *(*this + n); };

			reverse_iterator& operator++()
			{
				--current;
				return *this;
			};
			reverse_iterator operator++( int )
			{
				reverse_iterator tmp = *this;
				--current;
				return tmp;
			};

			reverse_iterator& operator--()
			{
				++current;
				return *this;
			};
			reverse_iterator operator--( int )
			{
				reverse_iterator tmp = *this;
				++current;
				return tmp;
			};

			reverse_iterator operator+( difference_type n ) const { return reverse_iterator(current - n); };
			reverse_iterator& operator+=( difference_type n )
			{
				current -= n;
				return *this;
			};

			reverse_iterator operator-( difference_type n ) const { return reverse_iterator(current + n); };
			reverse_iterator& operator-=( difference_type n )
			{
				current += n;
				return *this;
			};

		protected:
			Iterator current;
	};

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return rhs.base() == lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return rhs.base() != lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return rhs.base() < lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return rhs.base() <= lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return rhs.base() > lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return rhs.base() >= lhs.base(); };

	template<
		class Iter
	>
	reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) { return reverse_iterator<Iter>(it.base() - n); };

	template<
		class Iterator1,
		class Iterator2
	>
	typename reverse_iterator<Iterator1>::difference_type operator-( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return rhs.base() - lhs.base(); };






	template <class T>
	class rbtree_iterator
	{
		public:
			typedef T										value_type;
			typedef std::bidirectional_iterator_tag			iterator_category;
			typedef ptrdiff_t								difference_type;
			typedef typename ft::RBtreeNode<value_type>		node_type;
			typedef node_type*								node_pointer;
			typedef value_type&								reference;
			typedef value_type*								pointer;
			
			//Constructors
			rbtree_iterator() : current() {};
			explicit rbtree_iterator(node_pointer it) : current(it) {};
			rbtree_iterator(const rbtree_iterator & src) : current(src.current) {};
			template<
				class U
			>
			rbtree_iterator( const rbtree_iterator<U>& other ) : current(other.base()) {};

			//Destructor
			~rbtree_iterator() {};

			//Accessors
			node_pointer base() const { return current; };

			//Operator overloads
			template<
				class U
			>
			rbtree_iterator& operator=( const rbtree_iterator<U>& other )
			{
				current = other.base();
				return *this;
			};

			reference operator*() const
			{
				return current->get_value();
			};

			pointer operator->() const { return &(operator*()); };

			rbtree_iterator& operator++()
			{
				current = current->successor();
				return *this;
			};
			rbtree_iterator operator++( int )
			{
				rbtree_iterator tmp = *this;
				current = current->successor();
				return tmp;
			};

			rbtree_iterator& operator--()
			{
				current = current->predecessor();
				return *this;
			};
			rbtree_iterator operator--( int )
			{
				rbtree_iterator tmp = *this;
				current = current->predecessor();
				return tmp;
			};

		protected:
			node_pointer current;

			
	};

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator==( const rbtree_iterator<Iterator1>& lhs, const rbtree_iterator<Iterator2>& rhs ) { return rhs.base() == lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator!=( const rbtree_iterator<Iterator1>& lhs, const rbtree_iterator<Iterator2>& rhs ) { return rhs.base() != lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator<( const rbtree_iterator<Iterator1>& lhs, const rbtree_iterator<Iterator2>& rhs ) { return rhs.base() < lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator<=( const rbtree_iterator<Iterator1>& lhs, const rbtree_iterator<Iterator2>& rhs ) { return rhs.base() <= lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator>( const rbtree_iterator<Iterator1>& lhs, const rbtree_iterator<Iterator2>& rhs ) { return rhs.base() > lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator>=( const rbtree_iterator<Iterator1>& lhs, const rbtree_iterator<Iterator2>& rhs ) { return rhs.base() >= lhs.base(); };


	template <class T>
	class const_rbtree_iterator
	{
		public:
			typedef T										value_type;
			typedef std::bidirectional_iterator_tag			iterator_category;
			typedef ptrdiff_t								difference_type;
			typedef typename ft::RBtreeNode<value_type>		node_type;
			typedef const node_type*						node_pointer;
			typedef const value_type&						reference;
			typedef const value_type*						pointer;
			
			//Constructors
			const_rbtree_iterator() : current() {};
			explicit const_rbtree_iterator(node_pointer it) : current(it) {};
			const_rbtree_iterator(const const_rbtree_iterator & src) : current(src.current) {};
			template<
				class U
			>
			const_rbtree_iterator( const rbtree_iterator<U>& other ) : current(other.base()) {};

			//Destructor
			~const_rbtree_iterator() {};

			//Accessors
			node_pointer base() const { return current; };

			//Operator overloads
			template<
				class U
			>
			const_rbtree_iterator& operator=( const rbtree_iterator<U>& other )
			{
				current = other.base();
				return *this;
			};

			reference operator*() const
			{
				return static_cast<node_pointer>(current)->get_const_value();
			};

			pointer operator->() const { return &(operator*()); };

			const_rbtree_iterator& operator++()
			{
				current = current->successor();
				return *this;
			};
			const_rbtree_iterator operator++( int )
			{
				const_rbtree_iterator tmp = *this;
				current = current->successor();
				return tmp;
			};

			const_rbtree_iterator& operator--()
			{
				current = current->predecessor();
				return *this;
			};
			const_rbtree_iterator operator--( int )
			{
				const_rbtree_iterator tmp = *this;
				current = current->predecessor();
				return tmp;
			};

		protected:
			node_pointer current;

			
	};

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator==( const const_rbtree_iterator<Iterator1>& lhs, const const_rbtree_iterator<Iterator2>& rhs ) { return rhs.base() == lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator==( const const_rbtree_iterator<Iterator1>& lhs, const rbtree_iterator<Iterator2>& rhs ) { return rhs.base() == lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator==( const rbtree_iterator<Iterator1>& lhs, const const_rbtree_iterator<Iterator2>& rhs ) { return rhs.base() == lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator!=( const const_rbtree_iterator<Iterator1>& lhs, const const_rbtree_iterator<Iterator2>& rhs ) { return rhs.base() != lhs.base(); };

	template<
		class Iterator1,
		class Iterator2
	>
	bool operator!=( const const_rbtree_iterator<Iterator1>& lhs, const rbtree_iterator<Iterator2>& rhs ) { return rhs.base() != lhs.base(); };
	
	template<
		class Iterator1,
		class Iterator2
	>
	bool operator!=( const rbtree_iterator<Iterator1>& lhs, const const_rbtree_iterator<Iterator2>& rhs ) { return rhs.base() != lhs.base(); };



	template<class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last)
    {
        typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
        while (first != last)
        {
            first++;
            rtn++;
        }
        return (rtn);
    }
}

#endif