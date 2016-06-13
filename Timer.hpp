// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Timer.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/16 18:00:37 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/09 13:13:53 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TIMER_HPP
#define TIMER_HPP

#include "SFML/System.hpp"

class Timer {
public:

    Timer( void );

    void Start( void );
    void Pause( void );
    void Reinitialize( void );

    int GetTime( void );
	int GetTime_sec( void );
    int GetTime_milli( void );

private:
    enum State {Started, Paused};

	sf::Clock myClock;

    State myState;
    float myElapsedTimeMil;
    float myElapsedTimeSec;
};

#endif
