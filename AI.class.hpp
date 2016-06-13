// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AI.class.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 18:38:14 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/12 14:36:49 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _AI_HPP_
# define _AI_HPP_

#include "Player.class.hpp"

#include <unistd.h>
# include "Node.hpp"
#include <math.h>
#include <time.h>
#include <future>
#include <thread>

class AI : public Player {

public:
	Game *g;
	int len;
	int nwin;
	int decal;
	int Pos_Infinity;
	int Neg_Infinity;
	int depth;
	int deltamax;
	bool overtime;
	std::string winPlayer;

	AI( void );
	AI( AI const &src );
	AI( int np, Game *game );
	~AI( void );


	void    ft_display_map(Node &node);
	int   	caller(Node *,Game *);
	void 	ft_ia_tmp(Game &);

	bool	ft_is_finished_for(std::array<std::array<char, 19>, 19> map, char c);
	int   	ft_eval_CAPPED_H(std::array<std::array<char, 19>, 19>, int, char);
	int   	ft_eval_CAPPED_V(std::array<std::array<char, 19>, 19>, int, char);
	int   	ft_eval_CAPPED_D(std::array<std::array<char, 19>, 19>, int, char);
	int 	ft_eval_OPEN_H(std::array<std::array<char, 19>, 19>, int, char);
	int 	ft_eval_OPEN_D(std::array<std::array<char, 19>, 19>, int, char);
	int 	ft_eval_OPEN_V(std::array<std::array<char, 19>, 19>, int, char);
	int 	ft_eval_open_four(std::array<std::array<char, 19>, 19>, char);
	int		ft_eval_open_three(std::array<std::array<char, 19>, 19>, char);
	int		ft_eval_caped_four(std::array<std::array<char, 19>, 19>, char);
	int 	ft_eval(Node & node, std::array<std::array<char, 19>, 19>p, char);

	bool   	ft_check_if_win(std::array<std::array<char, 19>, 19> const map, char *p);

	bool    ft_is_terminal_node(Node node, bool flag);

	int 	ft_heuristic(Node &, int);
	int 	ft_my_fucking_heuristic(Node & node, std::array<std::array<char, 19>, 19>, int);

	Node 	ft_new_state(std::array<std::array<char, 19>, 19>, int, int);
	std::multimap<int,Node> ft_get_child(std::pair<int, Node &>, bool);


	int 	ft_MiniMax_A_B_Pruning(std::pair<int, Node &> , int , int , int , bool , Node *, int);
	int  	ft_MINIMAX_AB_MAX(std::pair<int,Node&>, int, int, int, Node *, int);
	int  	ft_MINIMAX_AB_MIN(std::pair<int,Node&>, int, int, int, Node *, int);

	void	ft_machin_learning();
	t_pions	*put_token( Game & game );
	AI & operator=( AI const &rhs );
};

#endif
