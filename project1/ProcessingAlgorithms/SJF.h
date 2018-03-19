class SJF
{
private:
	int timeElapsed, currentProcessIndex;
	bool isActive;
	Process* currentProcess;
	std::vector<Process*> readyVector;
	std::vector<Process*> processes;

	void PreArrivalUpdate()
	{
		for ( Process* p : processes )
		{
			p->UpdateArrivalStatus();
			if ( p->hasArrived )
			{
				readyVector.push_back( p );
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

	void GetShortestJob()
	{
		int shortestIndex = 0;
		for ( int i = 0; i < readyVector.size(); i++ )
		{
			if ( readyVector[shortestIndex]->burstTime > readyVector[i]->burstTime )
			{
				shortestIndex = i;
			}
		}
		currentProcessIndex = shortestIndex;
	}

public:
	SJF( std::vector<Process*> &p )
	{
		timeElapsed = 0;
		isActive = false;
		processes = p;
		currentProcess = NULL;
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

			if ( !readyVector.empty() )
			{
				if ( currentProcess == NULL )
				{
					GetShortestJob();
					currentProcess = readyVector[currentProcessIndex];
				}

				if ( UpdateAndCheckProcess( currentProcess ) )
				{
					PrintProcessInfo ( currentProcess );
					iter_swap( readyVector.begin() + currentProcessIndex, 
						readyVector.begin() + (readyVector.size()-1) );
					readyVector.pop_back();
					delete currentProcess;
					currentProcess = NULL;
				}
			}

			if ( processes.empty() && readyVector.empty() )
			{
				break;
			}
		}
	}
};