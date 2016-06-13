// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Timer.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/16 18:01:07 by mmoumini          #+#    #+#             //
//   Updated: 2015/05/24 00:53:08 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Timer.hpp"

Timer::Timer( void ) :  myState(Paused), myElapsedTimeMil(0.0f), myElapsedTimeSec(0.0f)
{
}

void Timer::Start( void )
{
	if(myState != Started)
	{
		myClock.restart();
		myState = Started;
	}
}

void Timer::Pause( void )
{
	if(myState != Paused)
	{
		myState = Paused;
		myElapsedTimeMil += myClock.getElapsedTime().asMilliseconds();
		myElapsedTimeSec += myClock.getElapsedTime().asSeconds();
	}
}

void Timer::Reinitialize( void )
{
	myClock.restart();
	Pause();
	myElapsedTimeSec = 0.0f;
	myElapsedTimeMil = 0.0f;

}

int Timer::GetTime_milli( void )
{
	float time;

	if(myState == Paused)
	{
		time = myElapsedTimeMil;
	}
	else
	{
		time = myClock.getElapsedTime().asMilliseconds() + myElapsedTimeMil;
	}
	while(time >= 1000)
		time -= 1000;
	return time / 10;
}
int Timer::GetTime( void )
{
	float time;

	if(myState == Paused)
	{
		time = myElapsedTimeSec;
	}
	else
	{
		time = myClock.getElapsedTime().asSeconds() + myElapsedTimeSec;
	}
	return time / 60;
}
int Timer::GetTime_sec( void )
{
	float time;

	if(myState == Paused)
	{
		time = myElapsedTimeSec;
	}
	else
	{
		time = myClock.getElapsedTime().asSeconds() + myElapsedTimeSec;
	}
	while(time >= 60)
		time -= 60;
	return time;
}
