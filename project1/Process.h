struct Process
{
	int arrivalTime, burstTime, priority, index, cpuTimeUsed;
	bool hasArrived, hasEnded;

	Process ( int at, int bt, int p, int in )
	{
		cpuTimeUsed = 0;
		arrivalTime = at;
		burstTime = bt;
		priority = p;
		index = in;
		hasArrived = false;
		hasEnded = false;
	}

	void UpdateArrivalStatus()
	{
		arrivalTime--;
		if ( arrivalTime <= 0 ) 
		{
			hasArrived = true;
		}
	}

	void UpdateBurstStatus()
	{
		cpuTimeUsed++;
		if ( cpuTimeUsed == burstTime )
		{
			hasEnded = true;
		}
	}
};