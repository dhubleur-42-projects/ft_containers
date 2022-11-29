/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:50:41 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 16:14:09 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <uchar.h>

namespace ft
{
	template<
		bool B,
		class T = void
	>
	struct enable_if {};
	template<
		class T
	>
	struct enable_if<true, T> { typedef T type; };
	
	template <class T, T v>
	struct integral_constant
	{
		static const T					value = v;
		typedef T						value_type;
		typedef integral_constant<T,v>	type;
		operator value_type(void) { return (v); }
	};

	template <class T>
		struct remove_cv
		{ typedef T	type; };

	template <class T>
		struct remove_cv<const T>
		{ typedef T	type; };

	template <class T>
		struct remove_cv<volatile T>
		{ typedef T	type; };

	template <class T>
		struct remove_cv<const volatile T>
		{ typedef T	type; };


	typedef ft::integral_constant<bool, true>	true_type;
	typedef ft::integral_constant<bool, false>	false_type;

	template<typename T> struct is_integral_base		:	ft::false_type {};
	template<> struct is_integral_base<bool>		:	ft::true_type {};
	template<> struct is_integral_base<char>		:	ft::true_type {};
	template<> struct is_integral_base<char16_t>	:	ft::true_type {};
	template<> struct is_integral_base<char32_t>	:	ft::true_type {};
	template<> struct is_integral_base<wchar_t>		:	ft::true_type {};
	template<> struct is_integral_base<short>		:	ft::true_type {};
	template<> struct is_integral_base<int>			:	ft::true_type {};
	template<> struct is_integral_base<long>		:	ft::true_type {};
	template<> struct is_integral_base<long long>	:	ft::true_type {};

	template <class T>
	struct is_integral: is_integral_base<typename ft::remove_cv<T>::type> {};

	const
		class nullptr_t
		{
			public:
			template<class T>
			operator T*() const
				{ return 0; }
			template<class C, class T>
				operator T C::*() const
				{ return 0; }   
			private:
				void operator&() const;

		} nullptr = {};

	template <typename T>
	void swap(T & a, T & b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template <class Arg, class Result>
	struct unary_function
	{
		typedef Arg		argument_type;
		typedef Result	result_type;
	};

	template <class FirstArg, class SecondArg, class Result>
	struct binary_function
	{
		typedef FirstArg		first_argument_type;
		typedef SecondArg		second_argument_type;
		typedef Result	result_type;
	};

	template <class Pair>
	struct PairtSelectKey : public unary_function<Pair, typename Pair::first_type>
	{
		typedef typename unary_function<Pair, typename Pair::first_type>::result_type	result_type;
		result_type&	operator()(Pair& pair) const { return (pair.first); }
		const result_type&	operator()(const Pair& pair) const { return (pair.first); }
	};

	template <class T>
	struct Identity : public unary_function<T, T>
	{
		typedef typename unary_function<T, T>::result_type	result_type;
		result_type&	operator()(T& value) const { return (value); }
		const result_type&	operator()(const T& value) const { return (value); }
	};

}

#endif