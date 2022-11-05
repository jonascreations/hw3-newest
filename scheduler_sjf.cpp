/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler.h"
#include "scheduler_sjf.h"
#include "pcb.h"

SchedulerSJF::SchedulerSJF()
{
}
void SchedulerSJF::init(std::vector<PCB>& process_list)
{
	process_list_hold = &process_list;
}

void SchedulerSJF::print_results()
{
	for(int i = 0; i < process_list_hold->capacity(); i++)
	{
		process_list_hold->at(i).print_wait_throughput();
	}
	get_avgs();
}
/**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
void SchedulerSJF::simulate()
{
	process_list_hold->shrink_to_fit();
	//cout << process_list_hold->capacity()<< endl;
	//process_list_hold->at(0).print();
	int time_count = 0;
	int current_process_count = find_next_shortest();//set shortest job
	
	cout << "Running Process " << process_list_hold->at(current_process_count).name << " for " << process_list_hold->at(current_process_count).burst_time << " time units" << endl;
	while(1)
	{
		if(no_burst_time())
		{
			process_list_hold->at(current_process_count).throughput_hold = time_count;
			process_list_hold->at(current_process_count).wait_time_hold =  time_count - process_list_hold->at(current_process_count).burst_time_hold;
			break;
		}
		if(process_list_hold->at(current_process_count).burst_time <= 0)
		{
			process_list_hold->at(current_process_count).throughput_hold = time_count;
			process_list_hold->at(current_process_count).wait_time_hold =  time_count - process_list_hold->at(current_process_count).burst_time_hold;
			current_process_count = find_next_shortest();
			cout << "Running Process " << process_list_hold->at(current_process_count).name << " for " << process_list_hold->at(current_process_count).burst_time << " time units" << endl;
			
		}
		process_list_hold->at(current_process_count).burst_time--;
		time_count++;
		
	}
	
	
}

int SchedulerSJF::find_next_shortest()
{
	//find next process that doesnt have 0 burst time into "shortest process"
	int shortest_process = 0;
	for(int i = 0; i < process_list_hold->capacity(); i++)
	{
		if(process_list_hold->at(i).burst_time > 0)
		{
			shortest_process = i;
			break;
		}
	}
	//finds the shortest time
	for(int i = 0; i < process_list_hold->capacity(); i++)
	{
		if(process_list_hold->at(i).burst_time < process_list_hold->at(shortest_process).burst_time && process_list_hold->at(i).burst_time != 0)
		{
			shortest_process = i;
		}
	}
	return shortest_process;
}

int SchedulerSJF::no_burst_time()
{
	int shortest_process = 0;
	for(int i = 1; i < process_list_hold->capacity(); i++)
	{
		if(process_list_hold->at(i).burst_time != 0)
		{
			return 0;
		}
	}
	return 1;
}

void SchedulerSJF::get_avgs()
{
	double total = 0;
	for(int i = 0; i < process_list_hold->capacity(); i++)
	{
		total += process_list_hold->at(i).throughput_hold;
	}
	cout << "Average turn-around time = " << total/(process_list_hold->capacity());
	total = 0;//reset double var
	for(int i = 0; i < process_list_hold->capacity(); i++)
	{
		total += process_list_hold->at(i).wait_time_hold;
	}
	cout << ", Average waiting time = " << total/(process_list_hold->capacity()) << endl;
}

SchedulerSJF::~SchedulerSJF(){}



// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here
