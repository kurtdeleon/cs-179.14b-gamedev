#include <vector>
#include <queue>

class RR
{
private:
	int timeElapsed, quantumTime, timeSlice;
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
				//printf(">>>>Process added on: %d\n", timeElapsed);
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
		timeSlice++;
		p->UpdateBurstStatus();
		return p->hasEnded;
	}

	void PrintProcessInfo ( Process* p )
	{
		printf("TE: %d, I: %d, CT: %d %s\n", 
			timeElapsed, p->index, p->cpuTimeUsed, 
			(p->hasEnded ? "X" : " "));
	}

	void RequeueCurrentProcess()
	{
		PrintProcessInfo ( readyQueue.front() );
		readyQueue.push( readyQueue.front() );
		readyQueue.pop();
		timeSlice = 0;
	}

public:
	RR( std::vector<Process*> &p, int q )
	{
		timeElapsed = 0;
		timeSlice = 0;
		quantumTime = q;
		isActive = false;
		processes = p;
	}

	void Run()
	{
		while( true )
		{	
			if ( isActive )// 302 - 73
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
					timeSlice = 0;
				}

				if ( timeSlice == quantumTime )
				{
					RequeueCurrentProcess();
				}

				
			}

			if ( processes.empty() && readyQueue.empty() )
			{
				break;
			}
		}
	}
};