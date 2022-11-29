/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTreeNode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:55:13 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 14:22:29 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREENODE_HPP
# define RBTREENODE_HPP

# include "utils.hpp"
# include <iostream>

namespace ft
{
	enum RBTreeColor
	{
		RED,
		BLACK
	};

	template <class Value>
	class RBtreeNode
	{
		public:
			typedef Value								value_type;
			typedef RBtreeNode<value_type>				node_type;
			typedef node_type*							node_pointer;
			typedef value_type&							value_reference;
			typedef const value_type&					const_value_reference;

			RBtreeNode(): _parent(NULL), _left(NULL), _right(NULL), _tail(nullptr),  _isTail(true) {};
			RBtreeNode(value_type value): _value(value), _parent(nullptr), _left(nullptr), _right(nullptr), _tail(nullptr), _isTail(false), _color(RED) {};

			// RBtreeNode(const RBtreeNode & node)
			// {
			// 	*this = node;
			// };

			RBtreeNode & operator=(const RBtreeNode & node)
			{
				if (this != &node)
				{
					_value = node._value;
					_parent = node._parent;
					_left = node._left;
					_right = node._right;
					_tail = nullptr;
					_isTail = false;
					_color = node._color;
				}
				return *this;
			};

			node_pointer get_parent() const { return _parent; };
			node_pointer get_left() const { return _left; };
			node_pointer get_right() const { return _right; };
			node_pointer get_tail() const { return _tail; };
			value_reference get_value() { return _value; };
			const_value_reference get_const_value() const { return _value; };
			RBTreeColor get_color() const { return _color; };
			void set_parent(node_pointer parent) { _parent = parent; };
			void set_left(node_pointer left) { _left = left; };
			void set_right(node_pointer right) { _right = right; };
			void set_tail(node_pointer tail) { _tail = tail; };
			void set_color(RBTreeColor color) { _color = color; };
			bool is_tail() const { return _isTail; };

			node_pointer	minimum_below() const
			{
				node_pointer node = node_pointer(this);

				while (node->get_left())
					node = node->get_left();
				return node;
			}
			node_pointer	maximum_below() const
			{
				node_pointer node = node_pointer(this);

				while (node->get_right())
					node = node->get_right();
				return node;
			}

			node_pointer	successor() const
			{
				node_pointer node = node_pointer(this);

				if (_tail)
					return _tail;
				if (node->get_right())
					return node->get_right()->minimum_below();
				node_pointer parent = node->get_parent();
				while (parent && node == parent->get_right())
				{
					node = parent;
					parent = parent->get_parent();
				}
				return parent;
			}
			node_pointer	predecessor() const
			{
				node_pointer node = node_pointer(this);

				if (node->get_left())
					return node->get_left()->maximum_below();
				node_pointer parent = node->get_parent();
				while (parent && node == parent->get_left())
				{
					node = parent;
					parent = parent->get_parent();
				}
				return parent;
			}

		private:
			value_type		_value;
			node_pointer	_parent;
			node_pointer	_left;
			node_pointer	_right;
			node_pointer	_tail;
			bool			_isTail;
			RBTreeColor		_color;
	};
}

#endif