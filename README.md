# ADAPTIVE REAL TIME SCHEDULING ALGORITHM
The above-mentioned algorithm of Adaptive Multilevel feedback Queue is implemented using the C language. The Data-structure of Circular Queue using Doubly Linked List have been used for the same. Similarly, as stated in the , 3 different queues with different priorities were made with attributes such as – Arrival time, Burst time, Priority and Process id. 
Certain functions were made to Run the Algorithm 
•	struct priorityqueue* insert(struct priorityqueue* node,struct priorityqueue* q)  for inserting the process in the Queue.
•	struct priorityqueue* delete_node(struct priorityqueue *node, struct priorityqueue *q )  for deleting the process and freeing up the space when the process is done.
•	bool isempty(struct priorityqueue *q) This function will check if the process is there in the queue. It will compare the arrival time with the global clock
•	void bubbleSort(struct priorityqueue *start)  This function will sort the processes according to the arrival time. If the input of the functions are not given according to the arrival time in sequential order then this function will do the sorting.
•	void sleep (int sleep_time) This function will sleep the CPU when the lower priority jobs are scheduled. This function brings the adaptive nature to the Scheduling algorithm.
•	struct result* schedule(struct priorityqueue* q, int time_q, struct result* r)  this is the main function which schedules the process inside one single queue in Round robin fashion and also uses the delete function to delete the processes when it is done. After deleting the process the results are saved in a structure called RESULT.
The way Schedule function is called 
r = schedule(q1,time_q1,r); //Highest Priority
r = schedule(q2,time_q2,r); //Medium Priority
r = schedule(q3,time_q3,r); //Least Priority
Queues are scheduled on the basis of the priority.
 
