/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "scheduler.h"
#include "scheduler_fcfs.h"
#include "pcb.h"
SchedulerFCFS::SchedulerFCFS()
{
}
void SchedulerFCFS::init(std::vector<PCB>& process_list)
{
	process_list_hold = &process_list;
}

void SchedulerFCFS::print_results()
{
	for(int i = 0; i < int(process_list_hold->capacity()); i++)
	{
		process_list_hold->at(i).print_wait_throughput();
	}
	get_avgs();
}
/**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
void SchedulerFCFS::simulate()
{
         // changes list to be correct size for the list
	process_list_hold->shrink_to_fit();
	//cout << "in scheduler" << endl;
	//cout << process_list_hold->capacity()<< endl;
	//process_list_hold->at(0).print();
	int time_count = 0;
	int current_process_count = 0;
	cout << "Running Process " << process_list_hold->at(current_process_count).name << " for " << process_list_hold->at(current_process_count).burst_time << " time units" << endl;
	while(1)
	{
// while it has processes it will hold 
		if(process_list_hold->at(current_process_count).burst_time <= 0)
		{
			//cout << "          process count" << (process_list_hold->capacity())-2 << "<" << "current_process_count" << current_process_count << endl;
			if(int(process_list_hold->capacity())-2 < current_process_count)
			{
				//process_list_hold->at(current_process_count).
				process_list_hold->at(current_process_count).throughput_hold = time_count;
				process_list_hold->at(current_process_count).wait_time_hold =  time_count - process_list_hold->at(current_process_count).burst_time_hold;
				break;
			}
			else
			{
				process_list_hold->at(current_process_count).throughput_hold = time_count;
				process_list_hold->at(current_process_count).wait_time_hold =  time_count - process_list_hold->at(current_process_count).burst_time_hold;
				current_process_count++;
				cout << "Running Process " << process_list_hold->at(current_process_count).name << " for " << process_list_hold->at(current_process_count).burst_time << " time units" << endl;
				continue;
			}
		}
		
		process_list_hold->at(current_process_count).burst_time--;
		time_count++;
		
	}
	
}
// shows the average time for this scheduler
void SchedulerFCFS::get_avgs()
{
	double total = 0;
	for(int i = 0; i < int(process_list_hold->capacity()); i++)
	{
		total += process_list_hold->at(i).throughput_hold;
	}
	cout << "Average turn-around time = " << total/(process_list_hold->capacity());
	total = 0;//reset double var
	for(int i = 0; i < int(process_list_hold->capacity()); i++)
	{
		total += process_list_hold->at(i).wait_time_hold;
	}
	cout << ", Average waiting time = " << total/(process_list_hold->capacity()) << endl;
}

SchedulerFCFS::~SchedulerFCFS(){}
// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here
