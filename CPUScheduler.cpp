#include<iostream>
#include<fstream>
#include<string>
#include <list>
#include <sstream>
using namespace std;

class CPUIOTime
{

	public:
	
	int cPUTime;
	int iOTime;	
	CPUIOTime(void)
	{
		cPUTime=0;
		iOTime=0;
	}  
};

class Thread
{

	public:
	
	int arrivalTime;
	int numberOfCPU;
	int totalServiceTime;
	int totalIOTime;
	int finishTime;
	int usedTime;
	int state;
	CPUIOTime cPUIOTimes[100];
	Thread(void)
	{
		state=0;
		usedTime=0;
		arrivalTime=0;
		numberOfCPU=0;
	}  
};

class Process
{

	public:
	
	int numberOfThreads;
	int arrivalTime;
	int turnAroundTime;
	int terminated;
	Thread threads[100];
	Process(void)
	{
		terminated=0;
		numberOfThreads=0;
	}  
};


/***********************/
int numberOfProcesses;
int threadSwitch;
int processSwitch;

Process processes[100];
/***********************/

void setProcessesWithArrivalTime()
{
	
	int processArrival[100];

	for(int i=0;i<numberOfProcesses;++i)
	{
		processArrival[i]=processes[i].threads[0].arrivalTime;
		for(int j=1;j<processes[i].numberOfThreads;++j)
		{
			if(processArrival[i]>processes[i].threads[0].arrivalTime)
				processArrival[i]=processes[i].threads[0].arrivalTime;		

		}

		processes[i].arrivalTime=processArrival[i];
		
	}

}


void sortProcessesWithArrivalTime()
{
	
	int processArrival[100];

	for(int i=0;i<numberOfProcesses;++i)
	{
		processArrival[i]=processes[i].threads[0].arrivalTime;
		for(int j=1;j<processes[i].numberOfThreads;++j)
		{
			if(processArrival[i]>processes[i].threads[0].arrivalTime)
				processArrival[i]=processes[i].threads[0].arrivalTime;		

		}
		
	}

	for(int i=0;i<numberOfProcesses-1;++i)
	{
		for(int j=i;j<numberOfProcesses;++j)
		{
			if(processArrival[i]>processArrival[i])
			{
				Process pTemp=processes[i];
				processes[i]=processes[j];
				processes[j]=pTemp;

				int iTemp=processArrival[i];
				processArrival[i]=processArrival[j];
				processArrival[j]=iTemp;
			
			}
		}

	}	


}

int main(int argc, char *argv[])
{
	
	string line;
	int index;
	int firstInteger;
	int secondInteger;
	int thirdInteger;
	string firstString;
	string secondString;
	string thirdString;
	int i=0;
	int j,k;
	
	list<string> verboseList;
  	list<string>::iterator it;

	int detailed=0,verbose=0,roundRobin=0,quantum=0;
	int inputFile=1;

	/*********Realising Command line arguments*************/
	
	if(argc==3)
	{
		string d="-d";
		if(d.compare(argv[1])==0)
			detailed=1;
		d="-v";
		if(d.compare(argv[1])==0)
			verbose=1;
		inputFile=2;	
	}

	if(argc==4)
	{
		string d="-d";
		if(d.compare(argv[1])==0)
			detailed=1;
		d="-v";
		if(d.compare(argv[1])==0)
			verbose=1;
		if(d.compare(argv[2])==0)
			verbose=1;
		d="-r";
		if(d.compare(argv[1])==0)
		{
			roundRobin=1;
			string q=argv[2];
			quantum=atoi(q.c_str());
		}
		inputFile=3;	
	}

	if(argc==5)
	{
		string d="-d";
		if(d.compare(argv[1])==0)
			detailed=1;
		d="-v";
		if(d.compare(argv[1])==0)
			verbose=1;
		d="-r";
		if(d.compare(argv[2])==0)
		{
			roundRobin=1;
			string q=argv[3];
			quantum=atoi(q.c_str());
		}
		inputFile=4;	
	}

	if(argc==6)
	{
		string d="-d";
		if(d.compare(argv[1])==0)
			detailed=1;
		d="-v";
		if(d.compare(argv[2])==0)
			verbose=1;
		d="-r";
		if(d.compare(argv[3])==0)
		{
			roundRobin=1;
			string q=argv[4];
			quantum=atoi(q.c_str());
		}
		inputFile=5;	
	}

	/**************************************************************************************/

	ifstream myfile(argv[inputFile]);
	if(myfile.is_open())
	{
			
	/********Reading The First Line****************************************/
		getline(myfile,line);

		index=line.find(" ");
		firstString=line.substr(0,index);
		line=line.substr(index+1);
		index=line.find(" ");
		secondString=line.substr(0,index);
		thirdString=line.substr(index+1);

			
		firstInteger = atoi(firstString.c_str());			
		secondInteger = atoi(secondString.c_str());
		thirdInteger = atoi(thirdString.c_str());
			
		numberOfProcesses=firstInteger;
		threadSwitch=secondInteger;
		processSwitch=thirdInteger;


		/********Completed Reading The First Line******************************/

		while(i<numberOfProcesses)
		{
			getline(myfile,line);
			//cout<<line<<"\n";

			index=line.find(" ");
			firstString=line.substr(0,index);
			secondString=line.substr(index+1);
				
			firstInteger = atoi(firstString.c_str());			
			secondInteger = atoi(secondString.c_str());			

			Process p;
			p.numberOfThreads=secondInteger;
			//cout<<"Number of threads"<<secondInteger<<"of Process No "<<i<<"\n";
				
			j=0;
			while(j<p.numberOfThreads)
			{
				getline(myfile,line);
					
				//cout<<line<<"\n";

				index=line.find(" ");
				firstString=line.substr(0,index);
				line=line.substr(index+1);
				index=line.find(" ");
				secondString=line.substr(0,index);
				thirdString=line.substr(index+1);
			
				firstInteger = atoi(firstString.c_str());			
				secondInteger = atoi(secondString.c_str());
				thirdInteger = atoi(thirdString.c_str());

				//cout<<"Arrival Time"<<secondInteger<<" cpu No "<<thirdInteger<<"Of Thread"<<j<<"\n";
							
				Thread t;
				t.arrivalTime=secondInteger;
				t.numberOfCPU=thirdInteger;

				k=0;
				while(k<t.numberOfCPU)
				{
					getline(myfile,line);
						
					//cout<<line<<"\n";

					index=line.find(" ");
					firstString=line.substr(0,index);
					line=line.substr(index+1);
					index=line.find(" ");
					secondString=line.substr(0,index);
					thirdString=line.substr(index+1);

			
					firstInteger = atoi(firstString.c_str());			
					secondInteger = atoi(secondString.c_str());
					thirdInteger = atoi(thirdString.c_str());
						
					CPUIOTime c;
					c.cPUTime=secondInteger;
					c.iOTime=thirdInteger;
					
					t.cPUIOTimes[k]=c;
					++k;
				}

				p.threads[j]=t;

				++j;
			}				
				
			processes[i]=p;

			++i;

		}
			
		myfile.close();
	}
	else {cout<< "Unable to open file";return 0;}


	if(!roundRobin)
	{
          	

		/************************************************************************/
		setProcessesWithArrivalTime();

		int cpuBurstTime=0;
		int ioBurstTime=0;
		int totalTime=0;
		int totalTurnAroundTime=0;

	

		int clock=0,completed=0;
		int alreadyRunning=0;
		int found=0;

		stringstream c;
		stringstream t;
		stringstream p;
							
		while(!completed)
		{
			
			found=0;
			cpuBurstTime=0;
			totalTurnAroundTime=0;
			for(int i=0;i<numberOfProcesses;++i)
			{					
				for(int j=0;j<processes[i].numberOfThreads;++j)
				{
					int threadCPUTime=0;
					int threadIOTime=0;
					for(int k=0;k<processes[i].threads[j].numberOfCPU;++k)
					{
						threadCPUTime=threadCPUTime+processes[i].threads[j].cPUIOTimes[k].cPUTime;	
						//totalTime=totalTime+processes[i].threads[j].cPUIOTimes[k].cPUTime;	
						threadIOTime=threadIOTime+processes[i].threads[j].cPUIOTimes[k].iOTime;	
						//totalTime=totalTime+processes[i].threads[j].cPUIOTimes[k].iOTime;	
						cpuBurstTime+=threadCPUTime;							
							
					}

					processes[i].threads[j].totalServiceTime=threadCPUTime;
					processes[i].threads[j].totalIOTime=threadIOTime;

					//State Transition
					p.str("");
					t.str("");
					c.str("");

					if((processes[i].threads[j].arrivalTime<=clock) && (processes[i].threads[j].state==0))
					{
						found=1;
						processes[i].threads[j].state=1;//new to ready
							
						p<<i;
						t<<j;
						c<<clock;
						string s="At Time "+c.str()+" Thread "+t.str()+" of Process "+p.str()+" moves from new to ready";
						verboseList.push_back (s);
					}
					else if(!alreadyRunning && (processes[i].threads[j].arrivalTime<=clock) && (processes[i].threads[j].state==1))
					{	
						found=1;
						alreadyRunning=1;
						processes[i].threads[j].state=2;//ready to running
						processes[i].threads[j].usedTime=processes[i].threads[j].usedTime+1;	
							
						p<<i;
						t<<j;
						c<<clock;
						string s="At Time "+c.str()+" Thread "+t.str()+" of Process "+p.str()+" moves from ready to running";
						verboseList.push_back (s);

					}
					else if(alreadyRunning && processes[i].threads[j].usedTime>=(threadCPUTime+threadIOTime) && (processes[i].threads[j].state==2))
					{
						alreadyRunning=0;
						processes[i].threads[j].state=3;//running to terminate
						processes[i].threads[j].finishTime=clock;							

						p<<i;
						t<<j;
						c<<clock;
						string s="At Time "+c.str()+" Thread "+t.str()+" of Process "+p.str()+" moves from running to terminate";
						verboseList.push_back (s);	
					}
					else if(processes[i].threads[j].state==2)
					{							
						found=1;													
						processes[i].threads[j].usedTime=processes[i].threads[j].usedTime+1;								
					}
					else if((processes[i].threads[j].arrivalTime>clock) && (processes[i].threads[j].state==0))
					{
						found=1;//thread not yet arrived
					}
															
					
				}
				//Process TurnArround
				/*if(processes[i].threads[processes[i].numberOfThreads-1].state==3 && !processes[i].terminated)
				{
					processes[i].terminated=1;
					processes[i].turnAroundTime=clock-processes[i].arrivalTime;					
					totalTurnAroundTime+=processes[i].turnAroundTime;
				}*/
				
			}
			if(found==0)completed=1;									
									

			++clock;
		}
		
		//Calculating Total Turn Around Time of thread
		int totalNumberOfThreads=0;
		totalTurnAroundTime=0;
		for(int i=0;i<numberOfProcesses;++i)
		{					
			for(int j=0;j<processes[i].numberOfThreads;++j)
				
				totalTurnAroundTime+=(processes[i].threads[j].finishTime-processes[i].threads[j].arrivalTime);						
			totalNumberOfThreads+=processes[i].numberOfThreads;	
		}			
			
		/************************************************************************/
		
		cout<<"FCFS:\n\n";
		cout<<"Total Time required is "<<clock<<" time units\n";
		cout<<"Average Turnaround Time is "<<(float)totalTurnAroundTime/totalNumberOfThreads<<" time units\n";
		cout<<"CPU Utilization is "<<(float)(cpuBurstTime*100)/clock;


		if(detailed)
		{
			cout<<"\n\n\nDetailed Mode\n";
			for(int i=0;i<numberOfProcesses;++i)
			{					
				for(int j=0;j<processes[i].numberOfThreads;++j)
				{
					t.str("");
					p.str("");

					t<<j;
					p<<i;
					
					string s="Thread " + t.str() + " of Process " + p.str();
					cout<<"\n\n"<<s<<"\n\n";
					cout<<"\nArrival Time "<<processes[i].threads[j].arrivalTime;
					cout<<"\nService Time "<<processes[i].threads[j].totalServiceTime;
					cout<<"\nIO Time "<<processes[i].threads[j].totalIOTime;
					cout<<"\nTurn Around Time "<<processes[i].threads[j].finishTime-processes[i].threads[j].arrivalTime;
					cout<<"\nFinish Time "<<processes[i].threads[j].finishTime;
				}
				
			}

		}

		if(verbose)
		{
			cout<<"\n\n\nVerbose Mode\n";

			for (it=verboseList.begin(); it!=verboseList.end(); ++it)
			{
				cout<<"\n"<<(*it);
			}

		}
	
		return 0;
	}
        
	if(roundRobin)
	{
          	

		/************************************************************************/
		setProcessesWithArrivalTime();

		int cpuBurstTime=0;
		int ioBurstTime=0;
		int totalTime=0;
		int totalTurnAroundTime=0;

	

		int clock=0,completed=0;
		int alreadyRunning=0;
		int found=0;

		stringstream c;
		stringstream t;
		stringstream p;
							
		while(!completed)
		{
			
			found=0;
			cpuBurstTime=0;
			totalTurnAroundTime=0;
			for(int i=0;i<numberOfProcesses;++i)
			{					
				for(int j=0;j<processes[i].numberOfThreads;++j)
				{
					int threadCPUTime=0;
					int threadIOTime=0;
					for(int k=0;k<processes[i].threads[j].numberOfCPU;++k)
					{
						threadCPUTime=threadCPUTime+processes[i].threads[j].cPUIOTimes[k].cPUTime;	
						//totalTime=totalTime+processes[i].threads[j].cPUIOTimes[k].cPUTime;	
						threadIOTime=threadIOTime+processes[i].threads[j].cPUIOTimes[k].iOTime;	
						//totalTime=totalTime+processes[i].threads[j].cPUIOTimes[k].iOTime;	
						cpuBurstTime+=threadCPUTime;							
							
					}

					processes[i].threads[j].totalServiceTime=threadCPUTime;
					processes[i].threads[j].totalIOTime=threadIOTime;

					//State Transition
					p.str("");
					t.str("");
					c.str("");

					if((processes[i].threads[j].arrivalTime<=clock) && (processes[i].threads[j].state==0))
					{
						found=1;
						processes[i].threads[j].state=1;//new to ready
							
						p<<i;
						t<<j;
						c<<clock;
						string s="At Time "+c.str()+" Thread "+t.str()+" of Process "+p.str()+" moves from new to ready";
						verboseList.push_back (s);
					}
					else if((processes[i].threads[j].arrivalTime<=clock) && (processes[i].threads[j].state==4))
					{
						found=1;
						processes[i].threads[j].state=1;//blocked to ready
							
						p<<i;
						t<<j;
						c<<clock;
						string s="At Time "+c.str()+" Thread "+t.str()+" of Process "+p.str()+" moves from blocked to ready";
						verboseList.push_back (s);
					}
					else if(!alreadyRunning && (processes[i].threads[j].arrivalTime<=clock) && (processes[i].threads[j].state==1))
					{	
						found=1;
						alreadyRunning=1;
						processes[i].threads[j].state=2;//ready to running
						processes[i].threads[j].usedTime=processes[i].threads[j].usedTime+1;	
							
						p<<i;
						t<<j;
						c<<clock;
						string s="At Time "+c.str()+" Thread "+t.str()+" of Process "+p.str()+" moves from ready to running";
						verboseList.push_back (s);

					}
					else if(alreadyRunning && processes[i].threads[j].usedTime>=(threadCPUTime+threadIOTime) && (processes[i].threads[j].state==2))
					{
						alreadyRunning=0;
						processes[i].threads[j].state=3;//running to terminate
						processes[i].threads[j].finishTime=clock;							

						p<<i;
						t<<j;
						c<<clock;
						string s="At Time "+c.str()+" Thread "+t.str()+" of Process "+p.str()+" moves from running to terminate";
						verboseList.push_back (s);	
					}
					else if(alreadyRunning && (processes[i].threads[j].usedTime%quantum==0) && (processes[i].threads[j].state==2))
					{
						found=1;
						alreadyRunning=0;
						processes[i].threads[j].state=4;//running to blocked
						
						p<<i;
						t<<j;
						c<<clock;
						string s="At Time "+c.str()+" Thread "+t.str()+" of Process "+p.str()+" moves from running to blocked";
						verboseList.push_back (s);
					}
					else if(processes[i].threads[j].state==2)
					{							
						found=1;													
						processes[i].threads[j].usedTime=processes[i].threads[j].usedTime+1;								
					}
					else if((processes[i].threads[j].arrivalTime>clock) && (processes[i].threads[j].state==0))
					{
						found=1;//thread not yet arrived
					}
					else if(processes[i].threads[j].state==1)
					{
						found=1;//waiting in ready queue
					}																
					
				}
				
				
			}
			if(found==0)completed=1;									
									

			++clock;
		}
			
		//Calculating Total Turn Around Time Of Threads
		int totalNumberOfThreads=0;
		totalTurnAroundTime=0;
		for(int i=0;i<numberOfProcesses;++i)
		{					
			for(int j=0;j<processes[i].numberOfThreads;++j)				
				totalTurnAroundTime+=(processes[i].threads[j].finishTime-processes[i].threads[j].arrivalTime);
			totalNumberOfThreads+=processes[i].numberOfThreads;						
				
		}		
			
		/************************************************************************/
		
		cout<<"Round Robin (Quantum = "<<quantum<<" time units):\n\n";
		cout<<"Total Time required is "<<clock<<" time units\n";
		cout<<"Average Turnaround Time is "<<(float)totalTurnAroundTime/totalNumberOfThreads<<" time units\n";
		cout<<"CPU Utilization is "<<(float)(cpuBurstTime*100)/clock;


		if(detailed)
		{
			cout<<"\n\n\nDetailed Mode\n";
			for(int i=0;i<numberOfProcesses;++i)
			{					
				for(int j=0;j<processes[i].numberOfThreads;++j)
				{
					t.str("");
					p.str("");

					t<<j;
					p<<i;
					
					string s="Thread " + t.str() + " of Process " + p.str();
					cout<<"\n\n"<<s<<"\n\n";
					cout<<"\nArrival Time "<<processes[i].threads[j].arrivalTime;
					cout<<"\nService Time "<<processes[i].threads[j].totalServiceTime;
					cout<<"\nIO Time "<<processes[i].threads[j].totalIOTime;
					cout<<"\nTurn Around Time "<<processes[i].threads[j].finishTime-processes[i].threads[j].arrivalTime;
					cout<<"\nFinish Time "<<processes[i].threads[j].finishTime;
				}
				
			}

		}

		if(verbose)
		{
			cout<<"\n\n\nVerbose Mode\n";

			for (it=verboseList.begin(); it!=verboseList.end(); ++it)
			{
				cout<<"\n"<<(*it);
			}

		}
	
		return 0;
	}
	
		
	return 0;
}
