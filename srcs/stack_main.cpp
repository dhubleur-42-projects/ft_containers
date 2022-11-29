/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_main.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:53:11 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 16:57:23 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <iostream>
#include <stack>
#include <list>

#ifndef TEST_SRC
# define TEST_SRC ft
#endif

int main()
{
	std::cout << "/======================================\\" << std::endl;
	std::cout << "|                Stack                 |" << std::endl;
	std::cout << "\\======================================/" << std::endl;
    {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Default Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::stack<int> s;
		std::cout << "Size: " << s.size() << std::endl;
	}
    std::cout << std::endl;
    std::cout << std::endl;
    {
        std::cout << "----------------------------------------" << std::endl;
		std::cout << "Copy Constructor" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::stack<int> s;
		s.push(42);
        s.push(21);
        s.push(84);
        s.push(7);
        std::cout << "Origin size: " << s.size() << std::endl;
        std::cout << "Origin top: " << s.top() << std::endl;
        TEST_SRC::stack<int> s2(s);
        std::cout << "Copy size: " << s2.size() << std::endl;
        std::cout << "Copy top: " << s2.top() << std::endl;
        std::cout << "Add element to origin..." << std::endl;
        s.push(42);
        std::cout << "Copy size: " << s2.size() << std::endl;
        std::cout << "Copy top: " << s2.top() << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    {
        std::cout << "----------------------------------------" << std::endl;
		std::cout << "operator=" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		TEST_SRC::stack<int> s;
		s.push(42);
        s.push(21);
        s.push(84);
        s.push(7);
        std::cout << "Origin size: " << s.size() << std::endl;
        std::cout << "Origin top: " << s.top() << std::endl;
        TEST_SRC::stack<int> s2;
        s2 = s;
        std::cout << "Copy size: " << s2.size() << std::endl;
        std::cout << "Copy top: " << s2.top() << std::endl;
        std::cout << "Add element to origin..." << std::endl;
        s.push(42);
        std::cout << "Copy size: " << s2.size() << std::endl;
        std::cout << "Copy top: " << s2.top() << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    {
        std::cout << "----------------------------------------" << std::endl;
		std::cout << "top" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::stack<int> s;
		s.push(42);
        s.push(21);
        s.push(84);
        s.push(7);
        std::cout << "Size: " << s.size() << std::endl;
        std::cout << "Top: " << s.top() << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    {
        std::cout << "----------------------------------------" << std::endl;
		std::cout << "empty" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::stack<int> s;
        std::cout << "Size: " << s.size() << std::endl;
        std::cout << "Empty: " << s.empty() << std::endl;
        s.push(42);
        std::cout << "Add element ..." << std::endl;
        std::cout << "Size: " << s.size() << std::endl;
        std::cout << "Empty: " << s.empty() << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    {
        std::cout << "----------------------------------------" << std::endl;
		std::cout << "push" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::stack<int> s;
		s.push(42);
        s.push(21);
        s.push(84);
        s.push(7);
        std::cout << "Size: " << s.size() << std::endl;
        std::cout << "Top: " << s.top() << std::endl;
        s.push(42);
        std::cout << "Add element ..." << std::endl;
        std::cout << "Size: " << s.size() << std::endl;
        std::cout << "Top: " << s.top() << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    {
        std::cout << "----------------------------------------" << std::endl;
		std::cout << "pop" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
        TEST_SRC::stack<int> s;
		s.push(42);
        s.push(21);
        s.push(84);
        s.push(7);
        std::cout << "Size: " << s.size() << std::endl;
        std::cout << "Top: " << s.top() << std::endl;
        s.pop();
        std::cout << "Pop element ..." << std::endl;
        std::cout << "Size: " << s.size() << std::endl;
        std::cout << "Top: " << s.top() << std::endl;
    }
}