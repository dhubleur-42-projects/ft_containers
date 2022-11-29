/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:53:11 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 17:01:09 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>
#include <vector>
#include <list>

#ifndef TEST_SRC
# define TEST_SRC ft
#endif

void    printContent(TEST_SRC::vector<int> &v)
{
	std::cout << "Content: ";
	for (TEST_SRC::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main()
{
	std::cout << "/======================================\\" << std::endl;
	std::cout << "|               Vector                 |" << std::endl;
	std::cout << "\\======================================/" << std::endl;
	
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Default Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Capacity: " << v.capacity() << std::endl;
		std::cout << "Begin == end: " << (v.begin() == v.end()) << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Count/Value Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v(5, 42);
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Capacity: " << v.capacity() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Iterator Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		std::list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		TEST_SRC::vector<int> v(l.begin(), l.end());
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Capacity: " << v.capacity() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Copy Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> src(5, 42);
		TEST_SRC::vector<int> v(src);
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Capacity: " << v.capacity() << std::endl;
		printContent(v);
		src.insert(src.begin(), 0);
		std::cout << std::endl;
		std::cout << "Changed source: ";
		printContent(src);
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Capacity: " << v.capacity() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "operator=" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> src(5, 42);
		TEST_SRC::vector<int> v(3, 21);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		v = src;
		std::cout << std::endl;
		std::cout << "Source: ";
		printContent(src);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "assign count/value" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v(3, 21);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		v.assign(5, 42);
		std::cout << std::endl;
		std::cout << "Assigned to 5 * '42'" << std::endl;
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "assign iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> src(5, 42);
		TEST_SRC::vector<int> v(3, 21);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		v.assign(src.begin(), src.end());
		std::cout << std::endl;
		std::cout << "Source: ";
		printContent(src);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "at" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "at(0): " << v.at(0) << std::endl;
		std::cout << "at(9): " << v.at(4) << std::endl;
		try
		{
			int res = v.at(10);
			std::cout << "at(10): " << res << std::endl;
		}
		catch (std::out_of_range &e)
		{
			std::cout << "at(10) threw exception" << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "operator[]" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "v[0]: " << v[0] << std::endl;
		std::cout << "v[4]: " << v[4] << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "front()" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "front(): " << v.front() << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "back()" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "back(): " << v.back() << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "iterator begin" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		TEST_SRC::vector<int>::iterator it = v.begin();
		std::cout << "begin(): " << *it << std::endl;
		it++;
		std::cout << "begin() + 1: " << *it << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "iterator end" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		TEST_SRC::vector<int>::iterator it = v.end();
		it--;
		std::cout << "end() - 1: " << *it << std::endl;
		it--;
		std::cout << "end() - 2: " << *it << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "iterator rbegin" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		TEST_SRC::vector<int>::reverse_iterator it = v.rbegin();
		std::cout << "rbegin(): " << *it << std::endl;
		it++;
		std::cout << "rbegin() + 1: " << *it << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "iterator rend" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		TEST_SRC::vector<int>::reverse_iterator it = v.rend();
		it--;
		std::cout << "rend() - 1: " << *it << std::endl;
		it--;
		std::cout << "rend() - 2: " << *it << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "empty" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Empty: " << v.empty() << std::endl;
		std::cout << "Inserting 10 elements" << std::endl;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Empty: " << v.empty() << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "reserve" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Capacity: " << v.capacity() << std::endl;
		std::cout << "Reserving 10 elements" << std::endl;
		v.reserve(10);
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Capacity: " << v.capacity() << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "clear" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		v.reserve(10);
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Capacity: " << v.capacity() << std::endl;
		printContent(v);
		std::cout << "Clearing ..." << std::endl;
		v.clear();
		std::cout << "Size: " << v.size() << std::endl;
		std::cout << "Capacity: " << v.capacity() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "insert pos value" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v(5, 42);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "Inserting 21 at pos begin() + 1 ..." << std::endl;
		std::cout << "Inserted iterator value: " << *v.insert(v.begin() + 1, 21) << std::endl;
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "insert pos count/value" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v(5, 42);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "Inserting 3 * '21' at pos begin() + 1 ..." << std::endl;
		v.insert(v.begin() + 1, 3, 21);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "insert iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v(5, 42);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		TEST_SRC::vector<int> src;
		for (int i = 0; i < 3; ++i)
			src.push_back(i);
		std::cout << "Source: ";
		printContent(src);
		std::cout << "Inserting source at pos begin() + 1 ..." << std::endl;
		v.insert(v.begin() + 1, src.begin(), src.end());
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "erase pos" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "Erase at pos begin() + 1 ..." << std::endl;
		std::cout << "Erased iterator value: " << *v.erase(v.begin() + 1) << std::endl;
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "Erase at pos end() - 1 ..." << std::endl;
		std::cout << "Erased iterator == end(): " << (v.erase(v.end() - 1) == v.end()) << std::endl;
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "erase iterators" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "Erase between (begin() + 1) and (end() - 3) ..." << std::endl;
		std::cout << "Erased iterator value: " << *v.erase(v.begin() + 1, v.end() - 3) << std::endl;
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "push_back" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v(5, 42);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		TEST_SRC::vector<int> src;
		for (int i = 0; i < 3; ++i)
			src.push_back(i);
		std::cout << "Source: ";
		printContent(src);
		std::cout << "Pushing source ..." << std::endl;
		for (TEST_SRC::vector<int>::iterator it = src.begin(); it != src.end(); ++it)
			v.push_back(*it);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "pop_back" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "Popping back ..." << std::endl;
		v.pop_back();
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "end() -1: " << *(v.end() - 1) << std::endl;
		std::cout << "Popping back ..." << std::endl;
		v.pop_back();
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "end() -1: " << *(v.end() - 1) << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "resize to bigger" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v(5, 42);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "Resizing to 10 ..." << std::endl;
		v.resize(10);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "resize to smaller" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
		std::cout << "Resizing to 5 ..." << std::endl;
		v.resize(5);
		std::cout << "Size: " << v.size() << std::endl;
		printContent(v);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "swap" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v1(5, 42);
		TEST_SRC::vector<int> v2(3, 21);
		std::cout << "v1 size: " << v1.size() << std::endl;
		std::cout << "v1: ";
		printContent(v1);
		std::cout << "v2 size: " << v2.size() << std::endl;
		std::cout << "v2: ";
		printContent(v2);
		std::cout << "Swapping ..." << std::endl;
		v1.swap(v2);
		std::cout << "v1 size: " << v1.size() << std::endl;
		std::cout << "v1: ";
		printContent(v1);
		std::cout << "v2 size: " << v2.size() << std::endl;
		std::cout << "v2: ";
		printContent(v2);
	}
	std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Spam test" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::vector<int> v;
		for (int i = 0; i < 1000000; ++i)
			v.push_back(i);
	}
}