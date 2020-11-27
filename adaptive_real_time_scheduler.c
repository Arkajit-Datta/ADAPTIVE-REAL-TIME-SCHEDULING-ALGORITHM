/// OPERATING SYSTEM PROJECT
/// ADAPTIVE REAL TIME SCHEDULING ALGORITHM
/// CREATED - ARKAJIT DATTA
/// DATED: 27-NOVEMBER-2020
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<stdbool.h>
//globally defining
//time quantum of various queues
// Taking static inputs but it can done as dynamic
int time_q1 = 3;
int time_q2 = 2;
int time_q3 = 1;

//global clock
int clock = 0;
struct priorityqueue{
        int pid; // process id
        int priority; // priority of the function
        int arrtime; // arrival time
        int burst; // burst time
        int burst_copy;//keeping the copy of the burst time
        struct priorityqueue *left; // left pointer
        struct priorityqueue *right; // right pointer
}*q1, *q2, *q3, *head,*tail = 0;


//this Queue will store the results when the execution of the
// implementation using doubly linked list
struct result{
	int pid_result; // process id
	int arrtime_result; // arrival time
	int burst_result; // burst_time
	int clock_result; // completion time
	struct result *left; //left pointer
	struct result *right; // right pointer

}*r = 0;
// insert function
//head pointer of the queue will will be given insertion will happen accordingly
struct priorityqueue* insert(struct priorityqueue* node,struct priorityqueue* q){
	struct priorityqueue *newnode = (struct priorityqueue*) malloc(sizeof(struct priorityqueue));
	struct priorityqueue *last = (q);

	newnode->pid = node->pid;
	newnode->priority = node->priority;
	newnode->arrtime = node->arrtime;
	newnode->burst = node->burst;
	newnode->burst_copy = node->burst;
	newnode->left = NULL;
	newnode->right = NULL;

	if(q == NULL){
		newnode->left = NULL;
		q = newnode;
		q->right = q; //pointing to the head
	}
	else{
		while(last->right != (q)){
			last = last->right;
		}

		last->right = newnode;
		//left pointer points the previous node
		newnode->left = last;
		newnode->right = (q); //pointing to the head
		(q)->left = newnode;
	}
	printf("\nInsertion completed.....\n");
	return q;

}
//insertion function for result purpose -->
struct result* insert_result(struct result* node,struct result* q){
	struct result *newnode = (struct result*) malloc(sizeof(struct result));
	struct result *last = q;

	newnode->pid_result = node->pid_result;
	newnode->clock_result = node->clock_result;
	newnode->arrtime_result = node->arrtime_result;
	newnode->burst_result = node->burst_result;

	//newnode->left = NULL;
	//newnode->right = NULL;

	if(q == NULL){
		newnode->left = NULL;
		q = newnode;
		q->right = NULL; //pointing to NULL
	}
	else{
		while(last->right != NULL){
			last = last->right;
		}

		last->right = newnode;
		//left pointer points the previous node
		newnode->left = last;
		newnode->right = NULL; //pointing to the head
	}
	return q;
	printf("\nInsertion completed.....\n");

}
//delete node function
// the node to be deleted and the head of that queue must be passed
struct priorityqueue* delete_node(struct priorityqueue *node, struct priorityqueue *q ){
	if(q==NULL || node==NULL){
		printf("\nNULL NODE....nothing to delete....\n");
		printf("\nTerminating the delete operation......\n");
		return q;
	}
	if(q==node){
		q->left->right = node->right;// last node pointing the new head
		q = node->right; //head moves to the right node
		printf("\nProcess pid-> %d.......is completed\n",node->pid);
		printf("\nProcess deleted.......");
	}
	if(node->right != NULL && node->left != NULL){
		printf("\nProcess pid-> %d.......is completed\n",node->pid);
		printf("\nProcess deleted.......");
	}
	if(node->right != NULL){
		node->right->left = node->left;
	}
	if(node->left != NULL){
		node->left->right = node->right;
	}

	free(node); //deleting pointer
	return q;
}

//Is Empty function
// This function will check if the process is there in the queue
// It will compare the arrival time with the global clock
bool isempty(struct priorityqueue *q){
	if(q == NULL){
		return 1;
	}
	else{
		if(q->arrtime <= clock){
			return 0;
		}
		else if(q->arrtime > clock){
			return 1;
		}
	}
}

//swap function
// has to be used in bubble sort

void swap(int a, int b){
	int c;
	c = a;
	a = b;
	b = c;
}
//sort function
// This function will sort the process's in the queue according to the process arrival time

struct priorityqueue* bubbleSort(struct priorityqueue* start)
{
    int swapped, i;
    struct priorityqueue *ptr1;
    struct priorityqueue *lptr = start;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->right != lptr)
        {
            if (ptr1->arrtime > ptr1->right->arrtime)
            {
				// swapping all the elements
                swap(ptr1->arrtime, ptr1->right->arrtime);
                swap(ptr1->pid, ptr1->right->pid);
                swap(ptr1->priority, ptr1->right->priority);
                swap(ptr1->burst, ptr1->right->burst);
                swap(ptr1->burst_copy, ptr1->right->burst_copy);
                swapped = 1;
            }
            ptr1 = ptr1->right;
        }
        lptr = ptr1;
    }
    while (swapped);

    return start;
}
//sleep function
//This function will sleep the CPU when the lower priority jobs are scheduled
void sleep(int sleep_time){
	clock += sleep_time;
}

//schedule function
// This function will schedule the processes in the queue
struct result* schedule(struct priorityqueue* q, int time_q, struct result* r){
	// default: it will schedule the higher priority function
	struct priorityqueue *head;
	struct result* res = (struct result*) malloc(sizeof(struct result));
	head = q;
	int del_num = 0;
	int ele_count = 1;

	//head is again initialized to queue head pointer
	head = q;
	if(time_q>1){
	if(isempty(q)==0){
		while (head->right != q){
			ele_count++;
			printf("The number of process --> %d\n",ele_count);
			head = head->right;
		}
		while(del_num != ele_count){
			if(head->arrtime <= clock){

				head->burst -= time_q;
				clock += time_q;
				printf("clock--> %d\n",clock);

				if(head->burst <= 0){
					res->pid_result = head->pid;
					res->arrtime_result = head->arrtime;
					res->burst_result = head->burst_copy;
					res->clock_result = clock;
					r = insert_result(res,r); //inserting the node in the result queue
					delete_node(head,q); // deleting the node
					del_num++;
					printf("\ndel_count --> %d\n",del_num);
				}
			}
			else{
				clock = clock + 1;
			}
			if(del_num == ele_count){
				return r;
			}
			head = head->right; //going to the next node
		}
	}
	else{
		printf("\nERROR: The queue is empty........nothing to schedule.......\n");
		return r;
	}
	}
	else{
		if(isempty(q)==0){
			while (head->right != q){
			ele_count++;
			printf("The number of process --> %d\n",ele_count);
			head = head->right;
		}
		while(del_num != ele_count){
			if(head->arrtime <= clock){

				head->burst -= time_q;
				clock += time_q;
				sleep(2); // sleep time is given to be 2 for experimental basis
				printf("clock--> %d\n",clock);
				if(head->burst <= 0){
					res->pid_result = head->pid;
					res->arrtime_result = head->arrtime;
					res->burst_result = head->burst_copy;
					res->clock_result = clock;
					r = insert_result(res,r); //inserting the node in the result queue
					delete_node(head,q); // deleting the node
					del_num++;
					printf("\ndel_count --> %d\n",del_num);
				}
			}
			else{
				clock = clock + 1;
			}
			if(del_num == ele_count){
				return r;
			}
			head = head->right;
		}
	}
	else{
		printf("\nERROR: The queue is empty........nothing to schedule.......\n");
		return r;
	}
	}
}

//displaying function which will show the result
void display_result(struct result* r){
	int wait_average = 0;
	int completion_time_average = 0;
	int wait_time;
	float cpu_util = 0;
	int count = 0;//counting the number of process
	struct result *head;
	head = r;
	printf("\n PRINTING THE RESULTS WITH LOGS...........\n");
	printf("\t\t\t RESULTS\n\n");
	printf("process_id\tarrival time\tburst time\tCompletion Time\t\tWaiting Time\n");
	while(head != NULL){
		wait_time = head->clock_result-head->burst_result-head->arrtime_result;
		printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",head->pid_result,head->arrtime_result,head->burst_result,head->clock_result,wait_time);
		wait_average += wait_time;
		completion_time_average += head->clock_result;
		cpu_util += ((float) head->burst_result/(float) head->clock_result);
		count++;
		head = head->right;
	}
	printf("\nAverage Waiting Time --> %d\n",wait_average/count);
	printf("\nAverage Completion Time (Average TAT)--> %d\n",completion_time_average/count);
	printf("\n CPU UTILIZATION --> %f\n",cpu_util);
}

//main function
int main()
{
	int ch; //choice in the switch case function
	int n; // number of processes
	// defining the queues

	struct priorityqueue *node = (struct priorityqueue*) malloc(sizeof(struct priorityqueue));
	while(1) {
	printf("\t\t\tADAPTIVE REAL TIME SCHEDULER\n\n");
	printf("1. INSERT PROCESS\t\t2. RUN\t\t3. PRINT RESULTS\t\t4. FREE-UP\t\t5. EXIT");
	printf("\nEnter the choice--> ");
	scanf("%d",&ch);

switch(ch){
case 1:
	printf("\nEnter the number of processes --> ");
	scanf("%d",&n);

	for(int i=0;i<n;i++){
		printf("\nEnter the pid number of process-%d--> ",i+1);
		scanf("%d",&node->pid);
		printf("\nEnter the arrival time of the process-%d -->",i+1);
		scanf("%d",&node->arrtime);
		printf("\nEnter the burst time of the process-%d -->",i+1);
		scanf("%d",&node->burst);
		printf("\nEnter the priority of the process-%d -->",i+1);
		scanf("%d",&node->priority);

		// checking the priority and inserting in the queue accordingly
		if(node->priority>100){
			q1 = insert(node,q1);
		}
		else if (node->priority>50 && node->priority<100){
			q2 = insert(node,q2);
		}
		else if(node->priority>0 && node->priority<50){
			q3 = insert(node,q3);
		}
	}
	//printf("\n\n for testing purpose %d %d\n\n",q1->right,q1);
	break;
case 2:
	printf("\n Running the scheduling process................\n");
	//sorting the queues according to the arrival time and then running.
	//q1 = bubbleSort(q1);
	//q2 = bubbleSort(q2);
	//q3 = bubbleSort(q3);
	printf("\n******SCHEDULING QUEUE-1 (HIGHEST PRIORITY)*********\n\n");
	r = schedule(q1,time_q1,r);
	printf("\n******SCHEDULING QUEUE-2 (MEDIUM PRIORITY)*********\n\n");
	r = schedule(q2,time_q2,r);
	printf("\n******SCHEDULING QUEUE-3 (LOWEST PRIORITY)*********\n\n");
	r = schedule(q3,time_q3,r);
	printf("\n\n The scheduling process is completed..........\n\n");
	printf("\n\n RESULTS ARE READY TO BE PRINTED.........\n\n");
	break;

case 3:
	printf("\n PRINTING THE RESULTS ...............\n");
	display_result(r);
	break;

case 4:
	//free up space for next execution

	 q1 = NULL;
	 q2 = NULL;
	 q3 = NULL;
	 printf("\n\nThe queue is free now, Ready for execution.........\n");
	break;
case 5:
	exit(0);

}
	}
}
