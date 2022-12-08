#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void coworkerQueueInit( tCoworkerQueue *queue ) {
	queue->nElem=0;
}

void coworkerQueueHead(tCoworkerQueue queue, tCoworkerId *head) {
	*head= queue.table[0];
}

bool isCoworkerQueueEmpty(tCoworkerQueue queue) {	
	bool empty = true;
	empty = (queue.nElem==0);
	return empty;
}

bool isCoworkerQueueFull(tCoworkerQueue queue) {	
	bool full = false;
	full = (queue.nElem==MAX_COWORKERS);
	return full;
}

int coworkerQueueLength(tCoworkerQueue queue)
{
    return queue.nElem;
}

void coworkerQueueEnqueue(tCoworkerQueue *queue, tCoworkerId newElement) 
{
    queue->table[queue->nElem]= newElement;
	queue->nElem++;

}

void coworkerQueueDequeue(tCoworkerQueue *queue) {
	
	unsigned int i=0;
	
	for (i=0; i<queue->nElem-1; i++) {
		queue->table[i]= queue->table[i+1];
	}
	queue->nElem--;
}

void coworkerQueueCpy(tCoworkerQueue *dst, tCoworkerQueue src)
{   
    tCoworkerId id;
    
    coworkerQueueInit(dst);
    while (!isCoworkerQueueEmpty(src)) {
            coworkerQueueHead(src, &id);
            coworkerQueueEnqueue(dst, id);
            coworkerQueueDequeue(&src);
    }
}

int coworkerQueueCmp(tCoworkerQueue q1, tCoworkerQueue q2)
{
    int result;
    tCoworkerId id1, id2;
    
    result= 0;
    
    if (coworkerQueueLength(q1) < coworkerQueueLength(q2))
        result= -1;
    else if (coworkerQueueLength(q1) > coworkerQueueLength(q2))
        result= 1;
    else {
        while (!isCoworkerQueueEmpty(q1) && result==0) {
                coworkerQueueHead(q1,&id1);
                coworkerQueueHead(q2,&id2);
                result= (id1 == id2);
                coworkerQueueDequeue(&q1);
                coworkerQueueDequeue(&q2);
        }            
    }
    
    return result;
}

void getCoworkerIdStr( tCoworkerId coworker, int maxSize, char *str )
{
    snprintf(str, maxSize-1, "%d", coworker);            
} 

void getCoworkerIdObject(const char *str, tCoworkerId *coworker) 
{
	int auxCoworkerId;
    
    sscanf(str, "%d", &auxCoworkerId); 
    *coworker= auxCoworkerId;
}

/* The content of the fields of the queue structure is written into the string str */
void getCoworkerQueueStr( tCoworkerQueue queue, int maxSize, char *str) 
{
	tCoworkerId coworkerId;
    char tempStr[MAX_LINE];    

    /* write the size of the stack */
    snprintf(str, maxSize-1, "%d", coworkerQueueLength(queue));

    while(!isCoworkerQueueEmpty(queue))
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);

        /* get the top of the stack */
        coworkerQueueHead(queue, &coworkerId);

        /* write it as a string */
        snprintf(str, maxSize-1, "%s %d", tempStr, coworkerId);

        /* dequeue the head element to allow writting of next element */
        coworkerQueueDequeue(&queue);
    }
}

/* The content of the string str is parsed into the fields of the queue structure */
void getCoworkerQueueObject(const char *str, tCoworkerQueue *queue) 
{
	int i, size, auxCoworkerId;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   
	tCoworkerId newCoworkerId;

    /* read queue size */
    sscanf(str, "%d %[^\n]s", &size, tempStr); 

    /* Initialize the quaue */
    coworkerQueueInit(queue);

    for (i= 0; i< size; i++)
    {
        /* read the loaded data as a string*/
        sscanf(tempStr, "%d %[^\n]s", &auxCoworkerId, nextStr); 
        newCoworkerId= (tCoworkerId)(auxCoworkerId);

        /* enqueue it on the queue */
        coworkerQueueEnqueue( queue, newCoworkerId );

        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}

void coworkerQueueSave(tCoworkerQueue queue, const char* filename, tError *retVal) {

	*retVal = OK;
	FILE *fout=NULL;
	char str[MAX_LINE];
	tCoworkerId req;
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {

		/* Save all coworkers to the file */
		while(!isCoworkerQueueEmpty(queue)){
			coworkerQueueHead(queue, &req);
			getCoworkerIdStr(req, MAX_LINE, str);
			fprintf(fout, "%s\n", str);
			coworkerQueueDequeue(&queue);
		}
           
        /* Close the file */
		fclose(fout);
	} 
}

void coworkerQueueLoad(tCoworkerQueue *queue, const char* filename, tError *retVal) {
	
	*retVal = OK;
	
	FILE *fin=NULL;
	char line[MAX_LINE];
	tCoworkerId newCoworker;
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

	/* Initialize the queue */
		coworkerQueueInit(queue);

		/* Read all the lines (coworkers) */
		while(!feof(fin) && !isCoworkerQueueFull(*queue)) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getCoworkerIdObject(line, &newCoworker);
				/* Add the new coworker to the queue */
				coworkerQueueEnqueue(queue, newCoworker);		
			}
		}

		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}
