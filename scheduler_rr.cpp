/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler.h"
#include "scheduler_rr.h"
#include "pcb.h"
#include <queue>

SchedulerRR::SchedulerRR(int time_quantum)
{
	this->time_quantum = time_quantum;
}
void SchedulerRR::init(std::vector<PCB>& process_list)
{
	process_list_hold = &process_list;
}

void SchedulerRR::print_results()
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
void SchedulerRR::simulate()
{
	process_list_hold->shrink_to_fit();
	//cout << process_list_hold->capacity()<< endl;
	//process_list_hold->at(0).print();
	std::queue<PCB*> pcbQueue;
	
	//int current_process_count = find_next_priority();//set shortest job
	
	//cout << "Running Process " << process_list_hold->at(current_process_count).name << " for " << process_list_hold->at(current_process_count).burst_time << " time units" << endl;
	//pcbQueue.push(&process_list_hold->at(0));
	
	for(int i = 0; i < process_list_hold->capacity(); i++)//add vector to queue
	{
		pcbQueue.push(&process_list_hold->at(i));
		//process_list_hold->at(i).print_wait_throughput();
	}
	//cout << "here 1" << pcbQueue.front()->id << endl;
	int time_count = 0;
	//cout << "here " << pcbQueue.front()->name << " " << pcbQueue.front()->burst_time << endl;
	cout << "Running Process " << pcbQueue.front()->name << " for " << ((pcbQueue.front()->burst_time <= time_quantum) ? pcbQueue.front()->burst_time : time_quantum) << " time units" << endl;
	while(!pcbQueue.empty())
	{
		//cout << "here2" << endl;
		for(int i = 0; i < time_quantum; i++)
		{
			//cout << "here3 " << pcbQueue.front()->id << " " << pcbQueue.front()->burst_time << endl;
			pcbQueue.front()->burst_time--;
			time_count++;
			if(pcbQueue.front()->burst_time <= 0)//if process done pop
			{
				//cout << "here5 " << pcbQueue.front()->id << " " << pcbQueue.front()->burst_time << endl;
				//cout << "here4" << endl;
				pcbQueue.front()->throughput_hold = time_count;
				pcbQueue.front()->wait_time_hold =  time_count - pcbQueue.front()->burst_time_hold;
				pcbQueue.pop();
				//cout << "Running Process " << pcbQueue.front()->name << " for " << ((pcbQueue.front()->burst_time <= time_quantum) ? pcbQueue.front()->burst_time : time_quantum) << " time units" << endl;
				break;
			}
			if(i >= time_quantum-1)//if process not done pop push
			{
				pcbQueue.front()->throughput_hold = time_count;
				pcbQueue.front()->wait_time_hold =  time_count - pcbQueue.front()->burst_time_hold;
				pcbQueue.push(pcbQueue.front());
				//cout << "here " << pcbQueue.front()->id << " " << pcbQueue.front()->burst_time << endl;
				pcbQueue.pop();
				//cout << "Running Process " << pcbQueue.front()->name << " for " << ((pcbQueue.front()->burst_time <= time_quantum) ? pcbQueue.front()->burst_time : time_quantum) << " time units" << endl;
			}
		}
		if(!pcbQueue.empty())
		{
			cout << "Running Process " << pcbQueue.front()->name << " for " << ((pcbQueue.front()->burst_time <= time_quantum) ? pcbQueue.front()->burst_time : time_quantum) << " time units" << endl;
		}
		//cout << "here " << pcbQueue.front()->id << " " << pcbQueue.front()->burst_time << endl;
		//pcbQueue.pop();
		//cout << "here " << pcbQueue.front()->id << " " << pcbQueue.front()->burst_time << endl;
		
		
		
	}
	/*
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
			current_process_count = find_next_priority();
			cout << "Running Process " << process_list_hold->at(current_process_count).name << " for " << process_list_hold->at(current_process_count).burst_time << " time units" << endl;
			
		}
		process_list_hold->at(current_process_count).burst_time--;
		time_count++;
		
	}
	*/
	
}

int SchedulerRR::find_next_priority()
{
	//find next process that doesnt have burst of zero
	int shortest_process = 0;
	for(int i = 0; i < process_list_hold->capacity(); i++)
	{
		if(process_list_hold->at(i).burst_time > 0)
		{
			shortest_process = i;
			break;
		}
	}
	//finds the highest priority with a burst time
	for(int i = 0; i < process_list_hold->capacity(); i++)
	{
		if(process_list_hold->at(i).priority > process_list_hold->at(shortest_process).priority && process_list_hold->at(i).burst_time != 0)
		{
			shortest_process = i;
		}
	}
	return shortest_process;//return highest priority with burst time
}

void SchedulerRR::get_avgs()
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


int SchedulerRR::no_burst_time()
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

SchedulerRR::~SchedulerRR(){}
// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here
