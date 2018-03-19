#include <vector>
#include <queue>

class FCFS
{
private:
	int timeElapsed;
	bool isActive;
	std::queue<Process*> readyQueue;
	std::vector<Process*> processes;

	void PreArrivalUpdate()
	{
		for ( Process* p : processes )
		{
			p->UpdateArrivalStatus();
			if ( p->hasArrived )
			{
				readyQueue.push( p );
				if ( !isActive )
				{
					isActive = true;
					timeElapsed++;
				}
			}
		}

		processes.erase( std::remove_if( processes.begin(), processes.end(), 
			[](Process* p){ return p->hasArrived; }), processes.end() );
	}

	bool UpdateAndCheckProcess ( Process* p )
	{
		p->UpdateBurstStatus();
		return p->hasEnded;
	}

	void PrintProcessInfo ( Process* p )
	{
		printf("TE: %d, I: %d, CT: %d X\n", 
			timeElapsed, p->index, p->cpuTimeUsed);
	}

public:
	FCFS( std::vector<Process*> &p )
	{
		timeElapsed = 0;
		isActive = false;
		processes = p;
	}

	void Run()
	{
		while( true )
		{	
			if ( isActive )
			{
				timeElapsed++;
			}
			if ( !processes.empty() )
			{
				PreArrivalUpdate();
			}

			if ( !readyQueue.empty() )
			{
				if ( UpdateAndCheckProcess( readyQueue.front() ) )
				{
					PrintProcessInfo ( readyQueue.front() );
					readyQueue.pop();
				}
			}

			if ( processes.empty() && readyQueue.empty() )
			{
				break;
			}
		}
	}
};