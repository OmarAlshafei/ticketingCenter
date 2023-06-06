//Omar Alshafei
//9/20/2022

//This program reads in information about customers and determines at what time each customer will check out
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#define TOTAL_LINES 12
#define NAME_MAX 15
#define MAX_ITEMS 100
#define MAX_TIME 1000000000

//All the data structures used in this program
typedef struct customer{
	char *name;
	int numTickets;
	int lineNum;
	int time;
}customer;

typedef struct node{
	struct customer *customer;
	struct node *next;
}node;

typedef struct queue{
	struct node *front;
	struct node *back;
}queue;


void init(queue *qPtr){
	qPtr->front = NULL;
	qPtr->back = NULL;
}

//This function adds a new item to a queue
int enqueue(queue* qPtr, customer* val){
  node *temp = malloc(sizeof(node));

  if (temp != NULL){//Check to see if temp is not NULL
    temp->customer = val;//Fills in temp pointer with customer
    temp->next = NULL;

    if (qPtr->back != NULL)
      qPtr->back->next = temp;//Adds temp to the end of the queue
		
    if (qPtr->front == NULL)
    	qPtr->front = temp;//If the front of the queue is empty temp becomes the new front
	
    qPtr->back = temp;//Sets temp as the new back
    return 1;
  } 
  else
  return 0;
}
//This function removes and returns the element at the front of the queue
customer* dequeue(queue *qPtr){
  node *temp; 
  customer* retval;

  if (qPtr->front == NULL)
    return NULL;//Returns NULL if the queue is empty

  temp = qPtr->front;
  retval = qPtr->front->customer;
  qPtr->front = qPtr->front->next;//Removes node from queue

  if (qPtr->front == NULL)
    qPtr->back = NULL; 

  free(temp);//Frees the node
  return retval;//Returns the customer pointer
}
//This function returns true if the queue pointed to by pPtr is empty
int empty(queue *qPtr){
  return (qPtr->front == NULL);
}
//This function gets the element at the front of the queue without removing it
customer* peek(queue *qPtr){
  if(qPtr->front != NULL)
    return qPtr->front->customer;//If the node is not empty it will return customer pointer
  else
    return NULL;//If node is empty it will return NULL
}
//This function dynamically allocates a customer pointer and fills it in with the scanned inputs
customer* makeCustomer(){
  customer *cPtr = malloc(sizeof(customer));
      
  char name[NAME_MAX];
  int time, lineNum, numTickets;
    
  scanf("%d", &time);
  if (time > MAX_TIME)
  exit(1);//If time is greater then MAX_TIME then program will exit
  cPtr->time = time;
    
  scanf("%d", &lineNum);
  if (lineNum > TOTAL_LINES)
  exit(1);//If lineNum is greater then TOTAL_LINES then program will exit
  cPtr->lineNum = lineNum;
    
  scanf("%s", name);
  cPtr->name = malloc(strlen(name)+1 * sizeof(char));//Dynamically allocate the name size
  strcpy(cPtr->name, name);
  
  scanf("%d", &numTickets);
  if (numTickets > MAX_ITEMS)
  exit(1);//If numTickets is greater then MAX_ITEMS then program will exit
  cPtr->numTickets = numTickets;
      
  return cPtr;//Returns filled in customer pointer
}
//This function initalizes and loads a queue
queue *loadqueue(){
	queue* qPtr = (queue*)malloc(TOTAL_LINES * sizeof(queue));
	queue* lines[TOTAL_LINES];
	init(qPtr);//Calls init function to initialize qPtr
	for(int i = 0; i < TOTAL_LINES; i++){//For loop cycles 12 times for each line
		lines[i] = qPtr;
	}
	return *lines;//Returns queue pointer
}
//This function creates and initalizes a queue using loadqueue function, creates customers using the makeCustomer function,
//finds the queue with the smallest count in the front, displays the customer, then dequeues
void customerCheckout(int nCustomers){
	int time, lineNum;
	customer *current;
	queue *lines = loadqueue();//Calls loadQueue function which returns an initalized queue
  	
	for(int i = 0; i < nCustomers; i++){//This loop cycles for every customer in the test case
		current = makeCustomer();//Calls makeCustomer function, returns a filled in customer, and stores it in customer pointer
		lineNum = current->lineNum;
		enqueue(&lines[lineNum - 1], current);//Calls enqueue function to add customer to the queue
	}
	
  customer *lowestItems = peek(&lines[0]);//Creates a customer pointer to store the customer with the lowest check out time
  time = 0;
  
    for (int i = 0; i < nCustomers; i++){//This loop cycles for every customer in the test case
      int line = -1;
      int minTickets = MAX_ITEMS+1;
      long minTime = MAX_TIME+1;
      
      for(int j = 0; j < TOTAL_LINES; j++){//This for loop cycles through the total number of lines
        if(empty(&lines[j]) == 1 || lines[j].front->customer->time > time){ 
        continue;
        } 
        lowestItems = peek(&lines[j]);//Calls peek function and stores returned customer into lowestItems
        if(lowestItems->numTickets < minTickets){//If statement to find customer with least number of tickets
          line = j;//Stores index j into line variable
          minTickets = lowestItems->numTickets;//Stores customer with the current minimum tickets into minTickets
        }
      }
        if(line == -1){
          for(int j = 0; j < TOTAL_LINES; j++){//This for loop cycles through the total number of lines
            if(empty(&lines[j]) == 1 ){ 
              continue;
            }
            lowestItems = peek(&lines[j]);//Calls peek function and stores returned customer into lowestItems
            if(lowestItems->time < minTime){//If statement to find customer with lowest time
              line = j;//Stores index j into line variable
              minTime = lowestItems->time;//Stores customer with the current minimum time into minTime
              time = lowestItems->time;
          }
        }
      }
      time += 30 + lines[line].front->customer->numTickets * 5;//Calculates check out time
      lowestItems = peek(&lines[line]);//Calls peek function to get the customer with lowest checkout time
      printf("%s from line %d checks out at time %d.\n", lowestItems->name, line + 1, time);//Displays the customer
      customer *freeData = dequeue(&lines[line]);//Calls the dequeue function to customer from queue and stores it in freeData
      free(freeData->name);//Frees customer name
      free(freeData);//Frees customer
    }
	free(lines);//Frees queue
}
//The main function reads the number of test cases and the number of customers, and then calls the customerCheckout function
int main(){
  atexit(report_mem_leak);
  
  int testCases, nCustomers;
  
  scanf("%d", &testCases); 
  if (testCases>25)
    exit(1);//If testCases is over 25 the program will exit
    
    for (int j = 0; j < testCases; j++){
      scanf("%d", &nCustomers);
      if (nCustomers>500000)
        exit(1);//If nCustomers is over 500000 the program will exit
        
		  customerCheckout(nCustomers);//Calls customerCheckout function
	  }
  return 0;
}
