/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:30:04 by dhubleur          #+#    #+#             */
/*   Updated: 2022/11/23 15:09:35 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARISON_HPP
# define COMPARISON_HPP

namespace ft
{
    template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
    {
        while (first1 != last1)
        {
            if (!(*first1 == *first2))
                return false;
            first1++;
            first2++;
        }
        return true;
    }

    template< class InputIt1,
          class InputIt2,
          class BinaryPredicate >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
    {
        while (first1 != last1)
        {
            if (!p(*first1, *first2))
                return false;
            first1++;
            first2++;
        }
        return true;
    }

    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            first1++;
            first2++;
        }
        return (first2 != last2);
    }

    template< class InputIt1, class InputIt2, class Compare >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
    {
        while (first1 != last1)
        {
            if (first2 == last2 || comp(*first2, *first1))
                return false;
            else if (comp(*first1, *first2))
                return true;
            first1++;
            first2++;
        }
        return (first2 != last2);
    }

    template< class T >
    bool less( const T& lhs, const T& rhs )
    {
        return lhs < rhs;
    }
}

#endif