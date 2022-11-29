/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:55:13 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 16:05:35 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <functional>
# include <memory>
# include <iostream>
# include <string>
# include "RBTreeNode.hpp"
# include "iterator.hpp"
# include "pair.hpp"

template <class T>
class rbtree_iterator;
template <class T>
class const_rbtree_iterator;

namespace ft
{
	template <
		class Key,
		class Value,
		class ExtractKey,
		class KeyCompare = std::less<Key>,
		class Allocator = std::allocator<Value>
	>
	class RBtree
	{
		public:
			typedef Key																			key_type;
			typedef Value																		value_type;
			typedef KeyCompare																	key_compare;
			typedef ExtractKey																	extract_key;
			typedef ft::RBtreeNode<value_type>													node_type;
			typedef ft::RBtreeNode<value_type>*													node_pointer;
			typedef const ft::RBtreeNode<value_type>*											const_node_pointer;
			typedef Allocator																	value_alocator;
			typedef typename value_alocator::template rebind<node_type>::other					node_allocator;
			typedef std::size_t																	size_type;
			typedef	std::ptrdiff_t																difference_type;
			typedef rbtree_iterator<value_type>													iterator;
			typedef const_rbtree_iterator<value_type>											const_iterator;

			RBtree(): _root(nullptr), _size(0) {};
			RBtree(node_allocator const & alloc, key_compare const & compare): _node_allocator(alloc), _key_compare(compare), _root(nullptr), _size(0) {};

			~RBtree() {
				_destroy_node(_root);
			};

			value_type	get_minimum() const { return _root->minimum_below()->get_value(); }
			value_type	get_maximum() const { return _root->maximum_below()->get_value(); }

			key_compare	key_comp() const { return _key_compare; }

			value_type* at(key_type const & key) const {
				node_pointer node = _find_node(key);
				if (node == nullptr)
					return nullptr;
				return &(node->get_value());
			}

			RBtree(const RBtree & rbtree): _root(nullptr), _size(0) {
				*this = rbtree;
			}

			RBtree & operator=(const RBtree & rbtree) {
				if (this != &rbtree) {
					if (_root != nullptr)
						_destroy_node(_root);
					if (rbtree._root != nullptr)
					{
						_root = _copy_node(rbtree._root, nullptr);
						this->_move_tail();
					}
					_size = rbtree._size;
				}
				return *this;
			}

			void	swap(RBtree & other)
			{
				if (_root == nullptr)
				{
					if (other._root != nullptr)
					{
						_root = other._root;
						other._root = nullptr;
						node_pointer tmp = _root->minimum_below();
						while (tmp != nullptr)
						{
							if (tmp->get_tail())
							{
								tmp->get_tail()->set_parent(nullptr);
								tmp->set_tail(&(_tail));
								_tail.set_parent(tmp);
								break ;
							}
							tmp = tmp->successor();
						}
					}
				}
				else if (other._root == nullptr)
				{
					other._root = _root;
					_root = nullptr;
					node_pointer tmp = other._root->minimum_below();
					while (tmp != nullptr)
					{
						if (tmp->get_tail())
						{
							tmp->get_tail()->set_parent(nullptr);
							tmp->set_tail(&(other._tail));
							other._tail.set_parent(tmp);
							break ;
						}
						tmp = tmp->successor();
					}
				}
				else
				{
					ft::swap(_root, other._root);
					node_pointer tmp = _root->minimum_below();
					while (tmp != nullptr)
					{
						if (tmp->get_tail())
						{
							tmp->set_tail(&(_tail));
							_tail.set_parent(tmp);
							break ;
						}
						tmp = tmp->successor();
					}
					tmp = other._root->minimum_below();
					while (tmp != nullptr)
					{
						if (tmp->get_tail())
						{
							tmp->set_tail(&(other._tail));
							other._tail.set_parent(tmp);
							break ;
						}
						tmp = tmp->successor();
					}
				}
				ft::swap(_size, other._size);
				ft::swap(_node_allocator, other._node_allocator);
				ft::swap(_key_compare, other._key_compare);
				ft::swap(_extract_key, other._extract_key);
			}

			iterator	begin()
			{
				if (!_root)
					return end();
				return iterator(_root->minimum_below());
			}
			iterator	end()
			{
				return iterator(&_tail);
			}

			const_iterator	begin() const
			{
				if (!_root)
					return end();
				return const_iterator(static_cast<const_node_pointer>(_root->minimum_below()));
			}

			const_iterator	end() const
			{
				return const_iterator(static_cast<const_node_pointer>(&_tail));
			}

			ft::pair<iterator, bool>	insert(const value_type &value)
			{
				if (!_root)
				{
					_size++;
					_root = _node_allocator.allocate(1);
					_node_allocator.construct(_root, value);
					_root->set_color(BLACK);
					_move_tail();
					return ft::make_pair(iterator(_root), true);
				}
				node_pointer search = _find_node(_extract_key(value));
				if (search)
					return ft::make_pair(iterator(search), false);
				_size++;
				node_pointer node = _root;
				while (node)
				{
					if (_key_compare(_extract_key(value), _extract_key(node->get_value())))
					{
						if (node->get_left())
							node = node->get_left();
						else
						{
							node->set_left(_node_allocator.allocate(1));
							_node_allocator.construct(node->get_left(), value);
							node->get_left()->set_parent(node);
							insert_fix(node->get_left());
							_move_tail();
							search = _find_node(_extract_key(value));;
							break;
						}
					}
					else
					{
						if (node->get_right())
							node = node->get_right();
						else
						{
							node->set_right(_node_allocator.allocate(1));
							_node_allocator.construct(node->get_right(), value);
							node->get_right()->set_parent(node);
							insert_fix(node->get_right());
							_move_tail();
							search = _find_node(_extract_key(value));;
							break;
						}
					}
				}
				return ft::make_pair(iterator(search), true);
			}

			void	print() {
				std::cout << "================================" << std::endl << std::endl;
				if (_root) {
					_printHelper(_root, "", true);
				}
				std::cout << std::endl << "================================" << std::endl;
			};

			iterator	remove(key_type key)
			{
				node_pointer node_to_delete = _find_node(key);
				if (node_to_delete != nullptr)
				{
					iterator next = node_to_delete->get_tail() ? end() : iterator(node_to_delete->successor());
					_size--;
					_remove_node(node_to_delete);
					_move_tail();
					return next;
				}
				return iterator(&_tail);
			}

			const_iterator find(key_type key) const {
				node_pointer node = _find_node(key);
				if (node == nullptr)
					return end();
				return const_iterator(node);
			}

			iterator find(key_type key) {
				node_pointer node = _find_node(key);
				if (node == nullptr)
					return end();
				return iterator(node);
			}

			size_type	size() const { return _size; }

			size_type	max_size() const { return _node_allocator.max_size(); }

			void	clear() {
				_destroy_node(_root);
				_root = nullptr;
				_size = 0;
				_tail.set_parent(nullptr);
			}
			
		private:
			node_allocator	_node_allocator;
			key_compare		_key_compare;
			extract_key		_extract_key;
			node_pointer	_root;
			node_type		_tail;
			size_type		_size;

			node_pointer	_copy_node(node_pointer node, node_pointer parent)
			{
				if (!node)
					return nullptr;
				node_pointer new_node = _node_allocator.allocate(1);
				_node_allocator.construct(new_node, node->get_value());
				new_node->set_color(node->get_color());
				new_node->set_parent(parent);
				if (node->get_left())
					new_node->set_left(_copy_node(node->get_left(), new_node));
				else
					new_node->set_left(nullptr);
				if (node->get_right())
					new_node->set_right(_copy_node(node->get_right(), new_node));
				else
					new_node->set_right(nullptr);
				return new_node;
			}

			void	_destroy_node(node_pointer node)
			{
				if (node)
				{
					node_pointer left = node->get_left();
					node_pointer right = node->get_right();
					_node_allocator.destroy(node);
					_node_allocator.deallocate(node, 1);
					_destroy_node(left);
					_destroy_node(right);
				}
			}

			node_pointer	_find_tail()
			{
				if (!_root)
					return nullptr;
				node_pointer node = _root->minimum_below();
				do
				{
					if (node->get_tail())
						return node;
				} while ((node = node->successor()) != nullptr);
				return nullptr;
			}

			void	_move_tail()
			{
				if (!_root)
				{
					_tail.set_parent(nullptr);
					return;
				}
				node_pointer node = _find_tail();
				if (node)
					node->set_tail(nullptr);
				node = _root->maximum_below();
				node->set_tail(&_tail);
				_tail.set_parent(node);
			}

			void	_rotate_right(node_pointer node)
			{
				node_pointer left = node->get_left();
				node->set_left(left->get_right());
				if (left->get_right())
					left->get_right()->set_parent(node);
				left->set_parent(node->get_parent());
				if (node->get_parent() == nullptr)
					_root = left;
				else if (node == node->get_parent()->get_right())
					node->get_parent()->set_right(left);
				else
					node->get_parent()->set_left(left);
				left->set_right(node);
				node->set_parent(left);
			};

			void	_rotate_left(node_pointer node)
			{
				node_pointer right = node->get_right();
				node->set_right(right->get_left());
				if (right->get_left())
					right->get_left()->set_parent(node);
				right->set_parent(node->get_parent());
				if (node->get_parent() == nullptr)
					_root = right;
				else if (node == node->get_parent()->get_left())
					node->get_parent()->set_left(right);
				else
					node->get_parent()->set_right(right);
				right->set_left(node);
				node->set_parent(right);
			};

			void	insert_fix(node_pointer new_node)
			{
				while (new_node->get_parent()->get_color() == RED)
				{
					node_pointer	parent = new_node->get_parent();
					node_pointer	grand_parent = parent->get_parent();
					if (!grand_parent)
						break;
					if (parent == grand_parent->get_left())
					{
						if (grand_parent->get_right() && grand_parent->get_right()->get_color() == RED)
						{
							grand_parent->get_right()->set_color(BLACK);
							grand_parent->get_left()->set_color(BLACK);
							grand_parent->set_color(RED);
							new_node = grand_parent;
						}
						else
						{
							if (new_node == parent->get_right())
							{
								new_node = parent;
								_rotate_left(new_node);
							}
							parent->set_color(BLACK);
							grand_parent->set_color(RED);
							_rotate_right(grand_parent);
						}
					}
					else
					{
						if (grand_parent->get_left() && grand_parent->get_left()->get_color() == RED)
						{
							grand_parent->get_left()->set_color(BLACK);
							grand_parent->get_right()->set_color(BLACK);
							grand_parent->set_color(RED);
							new_node = grand_parent;
						}
						else
						{
							if (new_node == parent->get_left())
							{
								new_node = parent;
								_rotate_right(new_node);
							}
							parent->set_color(BLACK);
							grand_parent->set_color(RED);
							_rotate_left(grand_parent);
						}
					}
					if (new_node == _root)
						break;
				}
				_root->set_color(BLACK);
			};

			void _printHelper(node_pointer root, std::string indent, bool last)
			{
				if (root != nullptr) {
					std::cout << indent;
					if (last) {
						std::cout << "R----";
						indent += "   ";
					} else {
						std::cout << "L----";
						indent += "|  ";
					}

					std::string sColor = (root->get_color() == RED) ? "RED" : "BLACK";
					std::string tail = (root->get_tail() == nullptr) ? "" : "[TAIL]";
					std::cout << _extract_key(root->get_value()) << " (" << sColor << ")" << " " << tail << std::endl;
					_printHelper(root->get_left(), indent, false);
					_printHelper(root->get_right(), indent, true);
				}
			};

			bool	_key_equivalent(const key_type& lhs, const key_type& rhs) const
			{
				return !_key_compare(lhs, rhs) && !_key_compare(rhs, lhs);
			}

			node_pointer	_find_node(const key_type& key) const
			{
				node_pointer	node = _root;
				while (node)
				{
					if (_key_equivalent(key, _extract_key(node->get_value())))
						return node;
					else if (_key_compare(key, _extract_key(node->get_value())))
						node = node->get_left();
					else
						node = node->get_right();
				}
				return nullptr;
			};

			void	_transplant(node_pointer original, node_pointer new_node)
			{
				if (original == new_node)
					return;
				if (!original->get_parent())
					_root = new_node;
				else if (original == original->get_parent()->get_left())
					original->get_parent()->set_left(new_node);
				else
					original->get_parent()->set_right(new_node);
				if (new_node)
					new_node->set_parent(original->get_parent());
			};

			void	_remove_fix(node_pointer x)
			{
				while (x != _root && x->get_color() == BLACK)
				{
					if (x == x->get_parent()->get_left())
					{
						node_pointer w = x->get_parent()->get_right();
						if (w->get_color() == RED)
						{
							w->set_color(BLACK);
							x->get_parent()->set_color(RED);
							_rotate_left(x->get_parent());
							w = x->get_parent()->get_right();
						}
						if (w->get_left()->get_color() == BLACK && w->get_right()->get_color() == BLACK)
						{
							w->set_color(RED);
							x = x->get_parent();
						}
						else
						{
							if (w->get_right()->get_color() == BLACK)
							{
								w->get_left()->set_color(BLACK);
								w->set_color(RED);
								_rotate_right(w);
								w = x->get_parent()->get_right();
							}
							w->set_color(x->get_parent()->get_color());
							x->get_parent()->set_color(BLACK);
							w->get_right()->set_color(BLACK);
							_rotate_left(x->get_parent());
							x = _root;
						}
					}
					else
					{
						node_pointer w = x->get_parent()->get_left();
						if (w->get_color() == RED)
						{
							w->set_color(BLACK);
							x->get_parent()->set_color(RED);
							_rotate_right(x->get_parent());
							w = x->get_parent()->get_left();
						}
						if (w->get_right()->get_color() == BLACK && w->get_left()->get_color() == BLACK)
						{
							w->set_color(RED);
							x = x->get_parent();
						}
						else
						{
							if (w->get_left()->get_color() == BLACK)
							{
								w->get_right()->set_color(BLACK);
								w->set_color(RED);
								_rotate_left(w);
								w = x->get_parent()->get_left();
							}
							w->set_color(x->get_parent()->get_color());
							x->get_parent()->set_color(BLACK);
							w->get_left()->set_color(BLACK);
							_rotate_right(x->get_parent());
							x = _root;
						}
					}
				}
			};

			void	_remove_node(node_pointer z)
			{
				node_pointer	y = z;
				node_pointer	x = nullptr;
				RBTreeColor	y_original_color = y->get_color();
				if (z->get_left() == nullptr)
				{
					x = z->get_right();
					_transplant(z, z->get_right());
				}
				else if (z->get_right() == nullptr)
				{
					x = z->get_left();
					_transplant(z, z->get_left());
				}
				else
				{
					y = z->get_right()->minimum_below();
					y_original_color = y->get_color();
					x = y->get_right();
					if (y->get_parent() == z)
					{
						if (x)
							x->set_parent(y);
					}
					else
					{
						_transplant(y, y->get_right());
						y->set_right(z->get_right());
						y->get_right()->set_parent(y);
					}
					_transplant(z, y);
					y->set_left(z->get_left());
					y->get_left()->set_parent(y);
					y->set_color(z->get_color());
				}
				_node_allocator.destroy(z);
				_node_allocator.deallocate(z, 1);
				if (y_original_color == BLACK && x)
					_remove_fix(x);
			};
	};

	template <
		class Key,
		class Value,
		class ExtractKey,
		class KeyCompare,
		class Allocator
	>
	bool operator==( const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& lhs, const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <
		class Key,
		class Value,
		class ExtractKey,
		class KeyCompare,
		class Allocator
	>
	bool operator!=( const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& lhs, const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& rhs )
	{
		return !(lhs == rhs);
	}

	template <
		class Key,
		class Value,
		class ExtractKey,
		class KeyCompare,
		class Allocator
	>
	bool operator<( const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& lhs, const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <
		class Key,
		class Value,
		class ExtractKey,
		class KeyCompare,
		class Allocator
	>
	bool operator<=( const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& lhs, const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& rhs )
	{
		if (lhs.size() == rhs.size())
			return true;
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <
		class Key,
		class Value,
		class ExtractKey,
		class KeyCompare,
		class Allocator
	>
	bool operator>( const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& lhs, const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& rhs )
	{
		return !(lhs <= rhs);
	}

	template <
		class Key,
		class Value,
		class ExtractKey,
		class KeyCompare,
		class Allocator
	>
	bool operator>=( const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& lhs, const ft::RBtree<Key,Value,ExtractKey,KeyCompare,Allocator>& rhs )
	{
		return !(lhs < rhs);
	}
}

#endif