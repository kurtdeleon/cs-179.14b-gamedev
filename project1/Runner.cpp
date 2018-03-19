#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <algorithm>

#include "Processor.h"

int GetScheduleType ( std::string schedType )
{
	/* Map that contains the scheduling algorithms and their values. */
	const std::unordered_map<std::string, int> types =
	{
		{"FCFS", 1}, {"SJF", 2}, {"SRTF", 3}, {"P", 4}, {"RR", 5}
	};

	return ( types.count( schedType ) ? types.at( schedType ) : 0 );
}

void GetUserInput( int *processes, int *schedType, int *quantumTime, std::vector<Process*>* processList )
{
	std::string sched_string;
	std::cin >> (*processes) >> sched_string;
	(*schedType) = GetScheduleType( sched_string );
	if ( (*schedType) == 5 ) std::cin >> (*quantumTime);

	for ( int i = 0; i < (*processes); i++ )
	{
		int at, bt, p;
		std::cin >> at >> bt >> p;

		Process* proc = new Process( at, bt, p, i );
		processList->push_back(proc);
	}
}

int main ( void )
{
	/* Takes in number of test cases. */
	int testCases;
	std::cin >> testCases;

	/* Creates a Processor object. */
	Processor processor;

	for ( int i = 0; i < testCases; i++ )
	{
		/* Initializes needed data. */
		int processes, schedType, quantumTime;
		std::vector<Process*> processList;

		/* Gets user input. */
		GetUserInput( &processes, &schedType, &quantumTime, &processList );
		
		/* Determines user's desired scheduling algorithm. */
		/* Returns value if found. Else, returns 0. */
		switch ( schedType )
		{
			case 1: processor.AccessFCFS( processList ); break;
			case 2: processor.AccessSJF( processList ); break;
			case 3: processor.AccessSRTF( processList ); break;
			case 4: processor.AccessP( processList ); break;
			case 5: processor.AccessRR( processList, quantumTime ); break;
			/* Prints if nothing is found. */
			case 0:
			std::cout << "Scheduling type not found. Test case is skipped." << std::endl;
			break;
		}
	}
}