// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Hit_box.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 17:15:37 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/09 21:24:11 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Hit_box.class.hpp"
#define HALF_SIZE 6

Hit_box::Hit_box( void ) : x(0), y(0){
}

Hit_box::Hit_box( Hit_box const &src ){
	*this = src;
}

Hit_box::Hit_box( int xc, int yc ) : x(xc), y(yc){
}

Hit_box::~Hit_box( void ){
}

void		Hit_box::initiate( void ){
	this->xa = this->x - HALF_SIZE;
	this->ya = this->y - HALF_SIZE;
	this->xb = this->x + HALF_SIZE;
	this->yb = this->y + HALF_SIZE;
}

bool		Hit_box::isOnThebox( int xc, int yc ){
	if ( xc >= this->xa && xc <= this->xb && yc >= this->ya && yc <= this->yb)
		return (true);
	return (false);
}

Hit_box		& Hit_box::operator=( Hit_box const &rhs ) {
	this->x = rhs.x;
	this->y = rhs.y;
	this->x = rhs.xb;
	this->y = rhs.yb;
	this->x = rhs.xa;
	this->y = rhs.ya;
	return *this;
}
