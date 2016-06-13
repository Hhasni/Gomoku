// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Gomoku.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 13:10:05 by mmoumini          #+#    #+#             //
//   Updated: 2016/05/27 16:04:45 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _GOMOKU_HPP_
# define _GOMOKU_HPP_

typedef struct s_pions {
    int         x;
    int         y;
    int         player;
}               t_pions;

#define WIN_HEIGHT 600
#define WIN_LENGTH 800
#define GO_CASE 30
#define ORIGIN_X (WIN_LENGTH - (GO_CASE * 18)) / 2
#define ORIGIN_Y (WIN_HEIGHT - (GO_CASE * 18)) / 2
#include "SFML/Graphics.hpp"
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio.hpp"
#include "Timer.hpp"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <random>
#include <ctime>
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

#endif
