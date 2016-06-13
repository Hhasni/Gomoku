// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AI.class.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 17:15:37 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/12 14:38:13 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AI.class.hpp"

AI::AI( void ): Player("MinMax", 1){
}

AI::AI( AI const &src ){
	*this = src;
}

AI::AI( int np, Game *game ) : Player("MinMax", np){
  	len = 19;
  	decal = len - 4;//len - 4
  	nwin = 5;
    overtime = false;
    depth = 10;
    deltamax = 30;
    human = false;

	Pos_Infinity = std::numeric_limits<int>::max();
	Neg_Infinity = std::numeric_limits<int>::min();
	winPlayer = "";
	g = game;
}

AI::~AI( void ){
}

Node     				 	AI::ft_new_state(std::array<std::array<char, 19>, 19> map_tmp, int y, int x){
  Node    state;

  state.setMap(map_tmp);
  state.x = x;
  state.y = y;
  return (state);
}

int   AI::ft_eval_CAPPED_H(std::array<std::array<char, 19>, 19> map, int n, char c){
  int   ret = 0;
  bool  empty = false;
  for (int i = 0; i < len; ++i){
    int count = 0;
    for (int j = 0; j < len; ++j){
      if (empty && map[i][j] == 0)
        empty = false;
      else if (map[i][j] == c && count == 0 && j > 0 && map[i][j-1] == 0){
        count++;
        empty = true;
      }
      else if (map[i][j] == c){
        if (count == 0)
          count++;
        else if (count != 0){
          count++;
          if (count == n && j < (len-1)){
            if (map[i][j+1] == 0 && !empty)
              ret += 1;
          }
        }
      }
      else{
        empty = false;
        count = 0;
      }
    }
  }
  return (ret);
}

int   AI::ft_eval_CAPPED_V(std::array<std::array<char, 19>, 19> map, int n, char c){
  int   ret = 0;
  bool  empty = false;
  for (int i = 0; i < len; ++i){
    int count = 0;
    for (int j = 0; j < len; ++j){
      if (empty && map[j][i] == 0)
        empty = false;
      else if (map[j][i] == c && count == 0 && j > 0 && map[j-1][i] == 0){
        empty = true;
        count++;
      }
      else if (map[i][j] == c && count == 0)
        count++;
      else if (count != 0 && map[j][i] == c){
        count++;
        if (count == n && j < (len-1)){
          if (map[j+1][i] == 0 && !empty)
            ret += 1;
        }
      }
      else{
        empty = false;
        count = 0;
      }
    }
  }
  return (ret);
}

void AI::ft_machin_learning(){
    deltamax = 15 + rand() % (200 - 15 + 1);
    std::cout << "deltamax == " << deltamax << std::endl;
}

int   AI::ft_eval_CAPPED_D(std::array<std::array<char, 19>, 19> map, int n, char c){
  int   ret = 0;
  int   count = 0;
  bool  empty = false;
  int   p = 0;
  
  for (int k = 0; k < decal; ++k){
    count = 0;
    empty = false;
    for (int i = 0; i < len - k; ++i){ //start up left -> down right toward up right
      if (empty && map[i][i+k] == 0)
        empty = false;
      else if (map[i][i+k] == c && count == 0){
        count++;
        if ((i > 0 && map[i-1][i+k-1] == 0))
          empty = true;
      }
      else if (count != 0 && map[i][i+k] == c){
        count++;
        if (count == n && i < (len - 1 - k)){
          if (map[i+1][i+k+1] == 0 && !empty)
            ret += 1;
        }
      }
      else{
        empty = false;
        count = 0;
      }
    }
    if (k == 0)
      continue;
    count = 0;
    empty = false;
    for (int i = 0; i < len - k; ++i){  //start up left -> down right toward down left
      if (empty && map[i+k][i] == 0)
        empty = false;
      else if (map[i+k][i] == c && count == 0){
        count++;
        if ((i > 0 && map[i+k-1][i-1] == 0))
          empty = true;
      }
      else if (count != 0 && map[i+k][i] == c){
        count++;
        if (count == n && i < (len-1-k)){
          if (map[i+k+1][i+1] == 0 && !empty)
            ret += 1;
        }
      }
      else{
        empty = false;
        count = 0;
      }
    }
  }
  count = 0;
  empty = false;
  for (int k = 0; k < decal; ++k){ 
    p = 0;
    count = 0;
    empty = false;

    for (int i = len - 1 - k; i >= 0; --i){ //start up right -> down left toward left up
      if (empty && map[p][i] == 0)
        empty = false;
      else if (map[p][i] == c && count == 0){
        count++;
        if (p > 0 && (i < (len - 1) && map[p-1][i+1] == 0))//bot
          empty = true;
      }
      else if (count != 0 && map[p][i] == c){
        count++;
        if (count == n && p < (len-1-k)){
          if (i > 0 && map[p+1][i-1] == 0 && !empty)
            ret += 1;
          else if (empty == true)
            ret += 1;
        }
      }
      else{
        empty = false;
        count = 0;
      }
      p++;
    }
    if (k == 0)
      continue;
    count = 0;
    empty = false;
    p = 0;
    for (int i = len - 1; i >= k; --i){ //start up right -> down left toward down right //PRETY SPACE
      if (empty && map[p+k][i] == 0)
        empty = false;
      else if (map[p+k][i] == c && count == 0){
        count++;
        if ((p > 0 && i < (len-1) && map[p+k-1][i+1] == 0))
          empty = true;
      }
      else if (count != 0 && map[p+k][i] == c){
        count++;
        if (count == n && i > 0 && p + k < (len - 1)){
          if (map[p+k+1][i-1] == 0 && !empty)
            ret += 1;
        }
      }
      else{
        empty = false;
        count = 0;
      }
      p++;
    }
  }
  return (ret);
}

int     AI::ft_eval_OPEN_D(std::array<std::array<char, 19>, 19> map, int n, char c){
  int   ret = 0;
  int   count = 0;
  bool  joker = false;
  int   p = 0;
  
  for (int k = 0; k < decal; ++k){
    count = 0;
    joker = false;
    for (int i = 0; i < len - k; ++i){ //start up left -> down right toward up right
      if (joker && map[i][i+k] == 0)
        joker = false;
      else if (map[i][i+k] == c && count == 0){
        if ((i > 0 && map[i-1][i+k-1] == 0)){
          joker = true;
          count++;
        }
      }
      else if (count != 0 && map[i][i+k] == c){
        count++;
        if (count == n && i < (len - 1 - k) && map[i+1][i+k+1] == 0)
          ret += 1;
      }
      else{
        joker = false;
        count = 0;
      }
    }
    if (k == 0)
      continue;
    count = 0;
    joker = false;
    for (int i = 0; i < len - k; ++i){  //start up left -> down right toward down left
      if (joker && map[i+k][i] == 0)
        joker = false;
      else if (map[i+k][i] == c && count == 0){
        if ((i > 0 && map[i+k-1][i-1] == 0)){
          joker = true;
          count++;
        }
      }
      else if (count != 0 && map[i+k][i] == c){
        count++;
        if (count == n && i < (len-1-k) && map[i+k+1][i+1] == 0)
          ret += 1;
      }
      else{
        joker = false;
        count = 0;
      }
    }
  }
  count = 0;
  joker = false;
  for (int k = 0; k < decal; ++k){ 
    p = 0;
    count = 0;
    joker = false;

    for (int i = len - 1 - k; i >= 0; --i){ //start up right -> down left toward left up
      if (joker && map[p][i] == 0)
        joker = false;
      else if (map[p][i] == c && count == 0){
        if (p > 0 && (i < (len - 1) && map[p-1][i+1] == 0)){//bof
          joker = true;
          count++;
        }
      }
      else if (count != 0 && map[p][i] == c){
        count++;
        if (count == n && p < (len-1-k) && i > 0 && map[p+1][i-1] == 0){
          ret += 1;
        }
      }
      else{
        joker = false;
        count = 0;
      }
      p++;
    }
    if (k == 0)
      continue;
    count = 0;
    joker = false;
    p = 0;
    for (int i = len - 1; i >= k; --i){ //start up right -> down left toward down right //PRETY SPACE
      if (joker && map[p+k][i] == 0)
        joker = false;
      else if (map[p+k][i] == c && count == 0){
        if ((p > 0 && i < (len-1) && map[p+k-1][i+1] == 0)){
          joker = true;
          count++;
        }
      }
      else if (count != 0 && map[p+k][i] == c){
        count++;
        if (count == n && i > 0 && p + k < (len - 1) && map[p+k+1][i-1] == 0)
          ret += 1;
      }
      else{
        joker = false;
        count = 0;
      }
      p++;
    }
  }
  return (ret);
}

int     AI::ft_eval_OPEN_V(std::array<std::array<char, 19>, 19> map, int n, char c){
  int   ret = 0;
  bool  joker = false;
  for (int i = 0; i < len; ++i){
    int count = 0;
    for (int j = 0; j < len; ++j){
      if (joker && map[j][i] == 0)
        joker = false;
      else if (map[j][i] == c){
        if (count == 0 && j > 0 && map[j-1][i] == 0){
          joker = true;
          count++;
        }
        else if (count != 0 && map[j][i] == c){
          count++;
          if (count == n && j < (len-1) && map[j+1][i] == 0)
            ret += 1;
        }
      }
      else{
        joker = false;
        count = 0;
      }
    }
  }
  return (ret);
}

int     AI::ft_eval_OPEN_H(std::array<std::array<char, 19>, 19> map, int n, char c){
  int   ret = 0;
  bool  joker = false;
  for (int i = 0; i < len; ++i){
    int count = 0;
    for (int j = 0; j < len; ++j){
      if (joker && map[i][j] == 0)
        joker = false;
      else if (map[i][j] == c){
        if (count == 0 && j > 0 && map[i][j-1] == 0){
          count++;
          joker = true;
        }
        else if (count != 0){
          count++;
          if (count == n && j < (len-1) && map[i][j+1] == 0)
            ret += 1;
        }
      }
      else{
        joker = false;
        count = 0;
      }
    }
  }
  return (ret);
}

int     AI::ft_eval_open_four(std::array<std::array<char, 19>, 19> map, char c){
  return(ft_eval_OPEN_H(map, 4, c) + ft_eval_OPEN_V(map, 4, c) + ft_eval_OPEN_D(map, 4, c));
}

int     AI::ft_eval_open_three(std::array<std::array<char, 19>, 19> map, char c){
  return(ft_eval_OPEN_H(map, 3, c) + ft_eval_OPEN_V(map, 3, c) + ft_eval_OPEN_D(map, 3, c));
}

int     AI::ft_eval_caped_four(std::array<std::array<char, 19>, 19> map, char c){
  return(ft_eval_CAPPED_H(map, 4, c) + ft_eval_CAPPED_V(map, 4, c) + ft_eval_CAPPED_D(map, 4, c));
}



bool	AI::ft_is_finished_for(std::array<std::array<char, 19>, 19> map, char c){
	int count = 0;
	int p = 0;
	for (int i = 0; i < len; ++i){
		count = 0;
		for (int j = 0; j < len; ++j){
			if (map[j][i] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
		}
	}
	count = 0;
	for (int i = 0; i < len; ++i){
		count = 0;
		for (int j = 0; j < len; ++j){
			if (map[i][j] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
		}
	}
	count = 0;
	for (int k = 0; k < decal; ++k){
		count = 0;
		for (int i = 0; i < len - k; ++i){
			if (map[i][i+k] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
		}
		count = 0;
		p = 0;
		for (int i = len - 1; i >= k; --i){
			if (map[p][i-k] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
			p++;
		}
		if (k == 0)
			continue;
		count = 0;
		for (int i = 0; i < len - k; ++i){
			if (map[i+k][i] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
		}
		p = 0;
		count = 0;
		for (int i = len - 1; i >= k; --i){
			if (map[i][p+k] == c){
				count++;
				if (count == nwin)
					return (true);
			}
			else
				count = 0;
			p++;
		}
	}
	return (false);

}


int     AI::ft_eval(Node & node, std::array<std::array<char, 19>, 19> map, char c){
  int sum_ot = 0;
  int sum_of = 0;
  int sum_cf = 0;
  (void)node;

  sum_ot = ft_eval_open_three(map, c) * 75;
  sum_of = ft_eval_open_four(map, c) * 500;
  sum_cf = ft_eval_caped_four(map, c) * 200;
  return (sum_cf+sum_of+sum_ot);
}

int     AI::ft_my_fucking_heuristic(Node & node, std::array<std::array<char, 19>, 19> map, int gamma){
  if (ft_is_finished_for(map, 'O')){
    return (-10000 - gamma);
  }
  if (ft_is_finished_for(map, 'X')){
    return (10000 + gamma);
  }
  return (ft_eval(node, map, 'X') - ft_eval(node, map, 'O'));
}

int     AI::ft_heuristic(Node & node, int gamma){
    int ret = 0;

    ret = ft_my_fucking_heuristic(node, node.getMap(), gamma*20);
    if (node.nbTakenWhite > 8)
      ret -= 8000;
    else if (node.nbTakenWhite > 6)
      ret -= 6000;
    else if (node.nbTakenWhite > 4)
      ret -= 4000;
    else if (node.nbTakenWhite > 2)
      ret -= 2000;
    else if (node.nbTakenWhite > 0)
      ret -= 1000;
    if (node.nbTakenBlack > 8)
      ret += 8000;
    else if (node.nbTakenBlack > 6)
      ret += 6000;
    else if (node.nbTakenBlack > 4)
      ret += 4000;
    else if (node.nbTakenBlack > 2)
      ret += 2000;
    else if (node.nbTakenBlack > 0)
      ret += 1000;
    return (ret);
}



void    AI::ft_display_map(Node &node){// display 3x3 map with coordinates A to C for Y, and 1 to 3 for X

  std::array<std::array<char, 19>, 19> map = node.getMap();
  char  c = 'A';

  std::cout << "turn : " << int(g->turn) << std::endl;
  std::cout << "BLACK : " << int(node.nbTakenWhite) << "\t\t\tWHITE : " << int(node.nbTakenBlack) << std::endl;
  std::cout << "  1 2 3 4 5 6 7 8 910111213141516171819" << std::endl << c << ' ';
  for (int i = 0; i < len; ++i){
    for (int j = 0; j < len; ++j){
      if (!map[i][j])
        std::cout << ' ';
      else
        std::cout << map[i][j];
      if (j < (len - 1))
        std::cout << '|';
    }
    std::cout << std::endl;
    if ((int)(c - 64) < len)
      std::cout << " ---------------------------------------" << std::endl << ++c << ' ';
  }
  std::cout << std::endl;
}



std::multimap<int,Node> 	AI::ft_get_child(std::pair<int,Node &> node, bool MaxP)
{
    std::multimap<int, Node> myhash;
    Node    *tmp_state = new Node();
    int plop = 0;
    // int nb = 0;

    std::array<std::array<char, 19>, 19> map = node.second.getMap();
    for (int i = 0; i < len; ++i){
      for (int j = 0; j < len; ++j){
        if (map[i][j] == 0){
          if ((j > 0 && map[i][j-1] != 0) ||
            (j < len - 1 && map[i][j+1] != 0) ||
            (i > 0 && map[i-1][j] != 0) ||
            (i < len - 1 && map[i+1][j] != 0) ||
            (i < len - 1 && j > 0 && map[i+1][j-1] != 0) ||
            (i > 0 && j < len - 1 && map[i-1][j+1] != 0) ||
            (i > 0 && j > 0 && map[i-1][j-1] != 0) ||
            (i < len - 1 && j < len - 1 && map[i+1][j+1] != 0)) 
          {
          std::array<std::array<char, 19>, 19> tmp = map;
          if (!MaxP)
            tmp[i][j] = 'O';
          else
            tmp[i][j] = 'X';
          *tmp_state = ft_new_state(tmp, i, j);
          tmp_state->nbTakenWhite = node.second.nbTakenWhite;
          tmp_state->nbTakenBlack = node.second.nbTakenBlack;
          if (g->ft_check_is_catchable(*tmp_state)){
            if (tmp_state->nbTakenWhite > 0){
              tmp_state->isSlash = true;
            }
            plop = ft_heuristic(*tmp_state, 0);
          }
          else{
            plop = ft_heuristic(*tmp_state, 0);
          }
          myhash.insert(std::pair<int, Node>(plop, *tmp_state));
          }
        }
      }
    }
    return (myhash);
}


int   						AI::ft_MINIMAX_AB_MAX(std::pair<int,Node&> root, int depth, int a, int b, Node *tmp_n, int bkp_depth){
  std::multimap<int, Node> hash_child;
  int i = 0;

  if (overtime)
    return (0);

  hash_child = ft_get_child(root, true);
  int delta = a;
  for (std::multimap<int,Node>::reverse_iterator it = hash_child.rbegin(); it != hash_child.rend(); it++){
    delta = ft_MiniMax_A_B_Pruning(*it, depth-1, a, b, false, tmp_n, bkp_depth);
    if (delta > a){
      if (depth == bkp_depth)
        *tmp_n = it->second;
      a = std::max(a, delta);
    }
    if (a >= b)
      break;
    if (i >= deltamax)
      break;
    i++;
  }
  return (a);
}

int   						AI::ft_MINIMAX_AB_MIN(std::pair<int,Node&> root, int depth, int a, int b, Node *tmp_n, int bkp_depth){
  std::multimap<int, Node> hash_child;
  int i = 0;

  if (overtime)
    return (0);
  hash_child = ft_get_child(root, false);
  int delta = b;
  for (std::multimap<int,Node>::iterator it = hash_child.begin(); it != hash_child.end(); it++){
    delta = ft_MiniMax_A_B_Pruning(*it, depth-1, a, b, true, tmp_n, bkp_depth);
    if (delta < b){
      if (depth == bkp_depth)
        *tmp_n = it->second;
      b = std::min(b, delta);
    }
    if (a >= b)
      break;
    if (i >= deltamax)
      break;
    i++;
  }
  return (b);
}

int 						AI::ft_MiniMax_A_B_Pruning(std::pair<int, Node &> root, int depth, int a, int b, bool MaximizingPlayer, Node *tmp_n, int bkp_depth){

	if (overtime)
		return (0);
	if (depth == 0 || (ft_is_terminal_node(root.second.getMap(), false) && !root.second.istmpwin)){
		return(root.first);
	}
	if (MaximizingPlayer)
		return (ft_MINIMAX_AB_MAX(root, depth, a, b, tmp_n, bkp_depth));
	else
		return (ft_MINIMAX_AB_MIN(root, depth, a, b, tmp_n, bkp_depth));
}


int   AI::caller(Node *tmp, Game * game){
  Node *bkp = new Node();  
  int testdepth = 0;
  *bkp = *tmp;

  while (testdepth++ <= depth){
    *tmp = *bkp;
    ft_MiniMax_A_B_Pruning(game->State, testdepth, Neg_Infinity, Pos_Infinity, false, bkp, testdepth);
  }
  return (0);
}

bool    AI::ft_check_if_win(std::array<std::array<char, 19>, 19> const map, char *p){
  (void)p;
  if (ft_is_finished_for(map, 'O'))
    return (true);
  if (ft_is_finished_for(map, 'X'))
    return (true);
  return (false);
}

bool    AI::ft_is_terminal_node(Node node, bool flag){
  (void)flag;
  std::array<std::array<char, 19>, 19> map = node.getMap();
  char  p = 0;
  if (ft_check_if_win(map, &p)){
    if (p == 'O')
      winPlayer = "Black";
    else
      winPlayer = "White";
    return (true);
  }
  if (node.nbTakenWhite >= 10){
    winPlayer = "White";
    return (true);
  }
  if (node.nbTakenBlack >= 10){
    winPlayer = "Black";
    return (true);
  }
  return (false);
}

void  AI::ft_ia_tmp( Game & game){

  Node *tmp = new Node();
  tmp->setMap(game.State.second.getMap());

  tmp->nbTakenWhite = game.State.second.nbTakenWhite;
  tmp->nbTakenBlack = game.State.second.nbTakenBlack;
  overtime = false;

  std::future<int>  hThread(std::async(std::launch::async, &AI::caller, this, tmp, &game));
  if (hThread.wait_for(std::chrono::milliseconds(500)) == std::future_status::timeout) {
    overtime = true;
  }
  game.State.second.setMap(tmp->getMap());
  game.State.second.x = tmp->x;
  game.State.second.y = tmp->y;
  if (tmp->isSlash){
    game.State.second.nbTakenWhite = tmp->nbTakenWhite;
    game.State.second.nbTakenBlack = tmp->nbTakenBlack;
    game.Slashme();
  }
  return ;
}

t_pions		*AI::put_token( Game & game){
	t_pions		*pions = new t_pions;

  ft_ia_tmp(game);
  pions->x = game.State.second.x;
  pions->y = game.State.second.y;
	pions->player = this->player;
	return (pions);
}

AI		& AI::operator=( AI const &rhs ) {
	this->name = rhs.name;
	this->player = rhs.player;
	return *this;
}
