#include "Process.h"
#include "ProcessingAlgorithms/FCFS.h"
#include "ProcessingAlgorithms/SJF.h"
//#include "ProcessingAlgorithms/SRTF.h"
//#include "ProcessingAlgorithms/P.h"
#include "ProcessingAlgorithms/RR.h"

/* 

Uncomment corresponding statements only after you make
or while you're testing the shit.

Feel free to use FCFS as a template.

Follow the code structure, and the passing of functions.

The algorithm will SIMULATE the processor itself.
So there are CLOCK CYCLES, and the norm.

*/

class Processor
{
private:
	FCFS *fcfs;
	SJF *sjf;
	//SRTF *srtf;
	//P *p;
	RR *rr;

public:

	/*

	Put your main loop in Run()
	break the loop when all processes are deleted.

	delete <name of algo> will delete the dynamically-created object.
	the pointer will exist as long as the Processor object is alive.
	
	*/

	void AccessFCFS( std::vector<Process*> &processes )
	{

		fcfs = new FCFS( processes );
		fcfs->Run();
		delete fcfs;
	}

	void AccessSJF( std::vector<Process*> &processes )
	{
		sjf = new SJF( processes );
		sjf->Run();
		delete sjf;
	}

	void AccessSRTF( std::vector<Process*> &processes )
	{
		/*srtf = new SRTF( processes );
		srtf->Run();
		delete srtf;*/
	}

	void AccessP( std::vector<Process*> &processes )
	{
		/*p = new P( processes );
		p->Run();
		delete p;*/
	}

	void AccessRR( std::vector<Process*> &processes, int quantumTime )
	{
		rr = new RR( processes, quantumTime );
		rr->Run();
		delete rr;
	}
};
