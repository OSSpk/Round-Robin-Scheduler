#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;


//----------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------NOTE-------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------//

//In an OS, the round robin scheduler doesn't know before hand that how many jobs will come. But in our case since we are writing
//a code which will ACT like a Round Robin Scheduler, we know before hand the total number of jobs that we have to schedule. But we
//will treat the jobs as if we don't know them before hand. I tried my best to make it run like a real Round Robin Scheduler.

//----------------------------------------------------------------------------------------------------------------------------//


//----------------------------------Assumptions------------------------------------------------------------------------------//

// 1) I need to have a stopping criteria to stop the program. So once the bursttime of every proccess has become zero, we have finished our work.
// 2) Assuming the input file contains correct data i.e all times are +ve and it follows the format given in the sample input file.
// 3) If the running time is say 50 and a process arrives at 50 then I am executing that proccess instead of starting to execute from the beginning of the queue.
//----------------------------------------------------------------------------------------------------------------------------//


struct proccess
{
	string PID;
	int arrival_Time;
	int burst_Time;

	proccess()
	{
		PID = "";
		arrival_Time = 0;
		burst_Time = 0;
	}

	// A job with  burst time equal to zero is treated as Completed //
};



//-------------------------------------------------------------------------------------------------------//


int main()
{
	//-----------Getting the length of the quantum-----------//

	cout << "\n\nEnter the length of the quantum [1-100]: ";

	int quantum = 0;

	cin >> quantum;

	//Check for invalid quantum size
	while (quantum < 1 || quantum > 100)
	{
		cout << "\nInvalid Length. Enter a valid quantum length in [1-100]: ";
		cin >> quantum;
	}


	//-----------Now reading the data of the processes from the file-----------//

	ifstream fin ("Assign-1.ip");

	if (fin.is_open())
	{
		string buffer;
		string temp;

		//Getting the first line in the file
		getline(fin,buffer);

		//Creating a vector of proccesses
		vector <proccess> jobs;


		//Getting the processes from the file
		while (!fin.eof())
		{
			getline(fin, buffer);

			//Whenever you encounter a blank line, just ignore it
			if (!buffer.empty())
			{
				proccess P;

				//Now parsing the buffer to get PID, arrival time and burst time

				int i = 0;

				//First reading the PID
				for (i = 0; buffer[i] != ','; i++)
				{
					P.PID.push_back(buffer[i]);
				}

				i++;

				temp = "";

				//Then reading the Arrival Time
				for (; buffer[i] != ','; i++)
				{
					temp.push_back(buffer[i]);
				}

				P.arrival_Time = atoi(temp.c_str());

				i++;

				temp = "";

				//Then reading the Burst Time
				for (; buffer[i] != '\0'; i++)
				{
					temp.push_back(buffer[i]);
				}

				P.burst_Time = atoi(temp.c_str());

				jobs.push_back(P);
			}
		}

		fin.close();

//-----------------------------------------------------------------------------------------------------//
//-----------------------------------------PROCCESSING-----------------------------------------------//
//-----------------------------------------------------------------------------------------------------//

		//Number of Processes
		int total_Processes = jobs.size();


		if (total_Processes > 0)
		{
			ofstream fout ("Assign-1.op");

			if(fout.is_open())
			{
				fout << "Quantum Number each " << quantum <<" Cycles, Executing Process' Name\n";

				int running_Time = 1;

				int quantum_Number = 1;

				bool isIdle = true;		//Tells if the CPU was sitting Idle in a particular time quantum

				int has_burst_zero = 0;


				//Continue until each proccess' burst time becomes equal to zero
				while (has_burst_zero != total_Processes)
				{
					isIdle = true;

					for (int i = 0; i < total_Processes; i++)
					{
						if (jobs[i].arrival_Time < running_Time && jobs[i].burst_Time > 0)
						{
							fout << quantum_Number << ',' << jobs[i].PID << endl;

							jobs[i].burst_Time = jobs[i].burst_Time - quantum;

							running_Time = running_Time + quantum;
							quantum_Number++;

							isIdle = false;

							if (jobs[i].burst_Time <= 0)
								has_burst_zero++;	//Increment size by one
						}
					}

					if (isIdle)
					{
						fout << quantum_Number << ',' << "CPU is Idle" << endl;
						quantum_Number++;
						running_Time = running_Time + quantum;
					}
				}

				cout <<"\nOutput file generated successfully.\n";
			}

			else
				cout << "\nThe output file could not be created.\n";
		}

		else
			cout << "\nThe file is empty. There are no proccesses to schedule.\n";
	}


	else
		cout << "\nThe input file could not be opened.\n";

	return 0;
}
