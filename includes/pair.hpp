/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:18:13 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 15:01:04 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include "comparison.hpp"

namespace ft
{
    template<
        class T1,
        class T2
    >
    struct pair
    {
        public:
            typedef T1 first_type;
            typedef T2 second_type;
        
            first_type first;
            second_type second;

            pair(): first(), second() {};
            pair( const T1& x, const T2& y ): first(x), second(y) {};
            template< class U1, class U2 >
            pair( const pair<U1, U2>& p ): first(p.first), second(p.second) {};
            pair( const pair& p ): first(p.first), second(p.second) {};

            pair& operator=( const pair& p )
            {
                if (this != &p)
                {
                    first = p.first;
                    second = p.second;
                }
                return *this;
            }
    };

    template< class T1, class T2 >
    ft::pair<T1, T2> make_pair( T1 t, T2 u ) { return ft::pair<T1, T2>(t, u); }

    template< class T1, class T2 >
    bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return lhs.first == rhs.first && lhs.second == rhs.second; }

    template< class T1, class T2 >
    bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return !(lhs == rhs); }

    template< class T1, class T2 >
    bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
    }

    template< class T1, class T2 >
    bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return lhs == rhs || lhs < rhs; }

    template< class T1, class T2 >
    bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return !(lhs <= rhs); }

    template< class T1, class T2 >
    bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return !(lhs < rhs); }
}

#endif