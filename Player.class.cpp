// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 17:15:37 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/10 18:41:57 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Player.class.hpp"

Player::Player( void ) : name("unknow"), player(1){

}

Player::Player( Player const &src ){
	*this = src;
}

Player::Player( std::string n, int np ) : name(n), player(np){
}

Player::Player( int np ) : name("unknow"), player(np){
}

Player::~Player( void ){
}


int			Player::GetPlayerN( void ){
	return ( this->player );
}

std::string			Player::GetPlayerName( void ){
	return ( this->name );
}

void		Player::ChangePlayer( void ){
	if ( this->player == 1 )
		this->player = 2;
	else
		this->player = 1;
}

Player		& Player::operator=( Player const &rhs ) {
	this->name = rhs.name;
	this->player = rhs.player;
	return *this;
}
