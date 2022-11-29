/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:23:40 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 16:42:08 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <set>
#include <vector>
#include "set.hpp"

#ifndef TEST_SRC
# define TEST_SRC ft
#endif

void    printContent(TEST_SRC::set<int> &m)
{
	std::cout << "Content: ";
	for (TEST_SRC::set<int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main()
{
    std::cout << "/======================================\\" << std::endl;
	std::cout << "|                 Set                  |" << std::endl;
	std::cout << "\\======================================/" << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Default Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::set<int> m;
		std::cout << "Size: " << m.size() << std::endl;
		std::cout << "Begin == end: " << (m.begin() == m.end()) << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Iterator Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
		TEST_SRC::set<int> m(v.begin(), v.end());
		std::cout << "Size: " << m.size() << std::endl;
		std::cout << "Begin == end: " << (m.begin() == m.end()) << std::endl;
        printContent(m);
	}
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Copy Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        m.insert(4);
        TEST_SRC::set<int> m2(m);
        std::cout << "Size: " << m2.size() << std::endl;
        printContent(m2);
        std::cout << "New element in m2" << std::endl;
        m2.insert(5);
        printContent(m2);
        std::cout << "Original: ";
        printContent(m);
	}
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Operator=" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        m.insert(4);
        TEST_SRC::set<int> m2(m);
        m2.insert(5);
        m2.insert(6);
        m2.insert(7);
        std::cout << "Before" << std::endl;
        std::cout << "m (" << m.size() << "): ";
        printContent(m);
        std::cout << "m2 (" << m2.size() << "): ";
        printContent(m2);
        m2 = m;
        std::cout << "After" << std::endl;
        std::cout << "m (" << m.size() << "): ";
        printContent(m);
        std::cout << "m2 (" << m2.size() << "): ";
        printContent(m2);
        std::cout << "Add element to m" << std::endl;
        m.insert(8);
        std::cout << "m2 (" << m2.size() << "): ";
        printContent(m2);
	}
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        m.insert(4);
        for (TEST_SRC::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
            std::cout << *it << std::endl;
        }
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "const iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        m.insert(4);
        for (TEST_SRC::set<int>::const_iterator it = m.begin(); it != m.end(); ++it) {
            std::cout << *it << std::endl;
        }
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "reverse iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        m.insert(4);
        for (TEST_SRC::set<int>::reverse_iterator it = m.rbegin(); it != m.rend(); ++it) {
            std::cout << *it << std::endl;
        }
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "const reverse iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        m.insert(4);
        for (TEST_SRC::set<int>::const_reverse_iterator it = m.rbegin(); it != m.rend(); ++it) {
            std::cout << *it << std::endl;
        }
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "empty()" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        std::cout << "Empty: " << m.empty() << std::endl;
        m.insert(1);
        std::cout << "Empty: " << m.empty() << std::endl;
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "size()" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        std::cout << "Size: " << m.size() << std::endl;
        m.insert(1);
        std::cout << "Size: " << m.size() << std::endl;
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "clear()" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        m.clear();
        std::cout << "Clear ..." << std::endl;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "insert value" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::cout << "Insert 42 ..." << std::endl;
        TEST_SRC::pair<TEST_SRC::set<int>::iterator, bool> ret = m.insert(42);
        std::cout << "Insert working: " << ret.second << std::endl;
        std::cout << "Insert iterator: " << *(ret.first) << " => " << *(ret.first) << std::endl;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::cout << "Insert 42 ..." << std::endl;
        ret = m.insert(42);
        std::cout << "Insert working: " << ret.second << std::endl;
        std::cout << "Insert iterator: " << *(ret.first) << " => " << *(ret.first) << std::endl;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "insert iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::vector<int> src;
        src.push_back(42);
        src.push_back(43);
        std::cout << "Insert src (42, 43 inside) ..." << std::endl;
        m.insert(src.begin(), src.end());
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "erase pos" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::cout << "Erase begin() + 1 ..." << std::endl;
        m.erase(++(m.begin()));
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "erase iterators" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        m.insert(4);
        m.insert(5);
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::cout << "Erase begin() + 1 to begin() + 3 ..." << std::endl;
        m.erase(++(m.begin()), ++(++(++(m.begin()))));
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "erase key" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::cout << "Erase 2 ..." << std::endl;
        std::cout << "Erased: " << m.erase(2) << std::endl;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::cout << "Erase 2 ..." << std::endl;
        std::cout << "Erased: " << m.erase(2) << std::endl;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "swap" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        m.insert(4);
        TEST_SRC::set<int> m2(m);
        m2.insert(5);
        m2.insert(6);
        m2.insert(7);
        std::cout << "Before" << std::endl;
        std::cout << "m (" << m.size() << "): ";
        printContent(m);
        std::cout << "m2 (" << m2.size() << "): ";
        printContent(m2);
        m2.swap(m);
        std::cout << "After" << std::endl;
        std::cout << "m (" << m.size() << "): ";
        printContent(m);
        std::cout << "m2 (" << m2.size() << "): ";
        printContent(m2);
        std::cout << "Add element to m" << std::endl;
        m.insert(8);
        std::cout << "m2 (" << m2.size() << "): ";
        printContent(m2);
	}
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "count" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::set<int> m;
        m.insert(1);
        m.insert(2);
        m.insert(3);
        std::cout << "count(1): " << m.count(1) << std::endl;
        std::cout << "count(5): " << m.count(5) << std::endl;
    }
}