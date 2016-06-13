// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 13:11:13 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/10 18:38:35 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Gomoku.hpp"
#include "Game.class.hpp"
#include "Human.class.hpp"
#include "Player.class.hpp"
#include "AI.class.hpp"
#pragma clang optimize on
int							main( void )
{

	Node 			Start  = Node();

	sf::RenderWindow		*app;
	Game					game(0, Start);
	// Player					*p1;
	// Player					*p2;

	// p1 = new Human("mous", 1);
	// p2 = new Human("mous", 2);
	app = new sf::RenderWindow( sf::VideoMode(WIN_LENGTH, WIN_HEIGHT, 32), "Gomoku42");	
	game.init(app);
	return (0);
}
