// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   tools.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/03/17 17:00:55 by mmoumini          #+#    #+#             //
//   Updated: 2016/03/17 17:14:11 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Gomoku.hpp"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
	std::stringstream ss(s);
	std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
