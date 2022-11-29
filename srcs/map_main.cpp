/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:23:40 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 17:02:56 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <vector>
#include "map.hpp"

#ifndef TEST_SRC
# define TEST_SRC ft
#endif

void    printContent(TEST_SRC::map<int, int> &m)
{
	std::cout << "Content: ";
	for (TEST_SRC::map<int, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << (*it).first << "=" << (*it).second << " ";
	std::cout << std::endl;
}

int main()
{
    std::cout << "/======================================\\" << std::endl;
	std::cout << "|                 Map                  |" << std::endl;
	std::cout << "\\======================================/" << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Default Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::map<int, int> m;
		std::cout << "Size: " << m.size() << std::endl;
		std::cout << "Begin == end: " << (m.begin() == m.end()) << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Iterator Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        std::vector<TEST_SRC::pair<int, int> > v;
        v.push_back(TEST_SRC::make_pair(1, -1));
        v.push_back(TEST_SRC::make_pair(2, -2));
        v.push_back(TEST_SRC::make_pair(3, -3));
        v.push_back(TEST_SRC::make_pair(4, -4));
		TEST_SRC::map<int, int> m(v.begin(), v.end());
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
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        m.insert(TEST_SRC::make_pair(4, -4));
        TEST_SRC::map<int, int> m2(m);
        std::cout << "Size: " << m2.size() << std::endl;
        printContent(m2);
        std::cout << "New element in m2" << std::endl;
        m2.insert(TEST_SRC::make_pair(5, -5));
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
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        m.insert(TEST_SRC::make_pair(4, -4));
        TEST_SRC::map<int, int> m2(m);
        m2.insert(TEST_SRC::make_pair(5, -5));
        m2.insert(TEST_SRC::make_pair(6, -6));
        m2.insert(TEST_SRC::make_pair(7, -7));
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
        m.insert(TEST_SRC::make_pair(8, -8));
        std::cout << "m2 (" << m2.size() << "): ";
        printContent(m2);
	}
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "at" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        m.insert(TEST_SRC::make_pair(4, -4));
        printContent(m);
        std::cout << "at(1): " << m.at(1) << std::endl;
        try {
            int i = m.at(5);
            std::cout << "at(5): " << i << std::endl;
        } catch (std::exception &e) {
            std::cout << "at(5) threw exception" << std::endl;
        }
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "operator[]" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        m.insert(TEST_SRC::make_pair(4, -4));
        printContent(m);
        std::cout << "m[1]: " << m[1] << std::endl;
        std::cout << "m[5]: " << m[5] << std::endl;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::cout << "Insert using m[42] = 21" << std::endl;
        m[42] = 21;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        m.insert(TEST_SRC::make_pair(4, -4));
        for (TEST_SRC::map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
            std::cout << it->first << " (key) => (value) " << it->second << std::endl;
        }
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "const iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        m.insert(TEST_SRC::make_pair(4, -4));
        for (TEST_SRC::map<int, int>::const_iterator it = m.begin(); it != m.end(); ++it) {
            std::cout << it->first << " (key) => (value) " << it->second << std::endl;
        }
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "reverse iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        m.insert(TEST_SRC::make_pair(4, -4));
        for (TEST_SRC::map<int, int>::reverse_iterator it = m.rbegin(); it != m.rend(); ++it) {
            std::cout << it->first << " (key) => (value) " << it->second << std::endl;
        }
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "const reverse iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        m.insert(TEST_SRC::make_pair(4, -4));
        for (TEST_SRC::map<int, int>::const_reverse_iterator it = m.rbegin(); it != m.rend(); ++it) {
            std::cout << it->first << " (key) => (value) " << it->second << std::endl;
        }
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "empty()" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        std::cout << "Empty: " << m.empty() << std::endl;
        m.insert(TEST_SRC::make_pair(1, -1));
        std::cout << "Empty: " << m.empty() << std::endl;
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "size()" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        std::cout << "Size: " << m.size() << std::endl;
        m.insert(TEST_SRC::make_pair(1, -1));
        std::cout << "Size: " << m.size() << std::endl;
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "clear()" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
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
        TEST_SRC::map<int, int> m;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::cout << "Insert make_pair(42, 21) ..." << std::endl;
        TEST_SRC::pair<TEST_SRC::map<int, int>::iterator, bool> ret = m.insert(TEST_SRC::make_pair(42, 21));
        std::cout << "Insert working: " << ret.second << std::endl;
        std::cout << "Insert iterator: " << ret.first->first << " => " << ret.first->second << std::endl;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::cout << "Insert make_pair(42, 21) ..." << std::endl;
        ret = m.insert(TEST_SRC::make_pair(42, 21));
        std::cout << "Insert working: " << ret.second << std::endl;
        std::cout << "Insert iterator: " << ret.first->first << " => " << ret.first->second << std::endl;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "insert iterator" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        std::cout << "Size: " << m.size() << std::endl;
        printContent(m);
        std::vector<TEST_SRC::pair<int, int> > src;
        src.push_back(TEST_SRC::make_pair(42, 21));
        src.push_back(TEST_SRC::make_pair(43, 20));
        std::cout << "Insert src (make_pair(42, 21) and make_pair(43, 20) inside) ..." << std::endl;
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
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
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
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        m.insert(TEST_SRC::make_pair(4, -4));
        m.insert(TEST_SRC::make_pair(5, -5));
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
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
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
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        m.insert(TEST_SRC::make_pair(4, -4));
        TEST_SRC::map<int, int> m2(m);
        m2.insert(TEST_SRC::make_pair(5, -5));
        m2.insert(TEST_SRC::make_pair(6, -6));
        m2.insert(TEST_SRC::make_pair(7, -7));
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
        m.insert(TEST_SRC::make_pair(8, -8));
        std::cout << "m2 (" << m2.size() << "): ";
        printContent(m2);
	}
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "count" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        std::cout << "count(1): " << m.count(1) << std::endl;
        std::cout << "count(5): " << m.count(5) << std::endl;
    }
    std::cout << std::endl;
	std::cout << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "find" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::map<int, int> m;
        m.insert(TEST_SRC::make_pair(1, -1));
        m.insert(TEST_SRC::make_pair(2, -2));
        m.insert(TEST_SRC::make_pair(3, -3));
        std::cout << "find(1): " << (*(m.find(1))).second << std::endl;
        std::cout << "find(5) == end(): " << (m.find(5) == m.end()) << std::endl;
    }
    std::cout << std::endl;
	std::cout << std::endl;
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Spam test" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::map<int, int> m;
		for (int i = 0; i < 1000; ++i)
			m.insert(TEST_SRC::make_pair(i, -i));
        std::cout << "Search 420: " << (*(m.find(420))).second << std::endl;
	}
}