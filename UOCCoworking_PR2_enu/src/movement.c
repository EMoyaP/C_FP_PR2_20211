#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movement.h"
#include "list.h"
#include "queue.h"
#include "coworker.h"

/* The content of the fields of the booking structure is written into the string str */
void getBookingStr(tBookingList bookings, int maxSize, char *str) {

    int i;
    char tempStr[MAX_LINE];  
    tBooking booking;  

    /* write the size of the list */
    snprintf(str, maxSize-1, "%d", bookingListLength(bookings));
    
	/* loop the elements of the list of booking writting its elements */
	for(i=1; !isBookingListEnd(bookings,i); i++) 
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);

        /* get the current booking */
		bookingListGet(bookings, i, &booking);
        
        /* write it as a string */
        snprintf(str, maxSize-1, "%s %d %d %d %d %d %d %d %d %d %.2f %d %d %d %d %d", tempStr, 
                booking.id, booking.nCoworkers, 
                booking.checkInDate.day, booking.checkInDate.month, booking.checkInDate.year, 
                booking.checkOutDate.day, booking.checkOutDate.month, booking.checkOutDate.year, 
                booking.requiredEquipment, booking.price, booking.nAssignedSpaces, booking.assignedSpaces[0], 
                booking.assignedSpaces[1], booking.assignedSpaces[2], booking.assignedSpaces[3] );
    }
}

/* The content of the string str is parsed into the fields of the booking structure */
void getBookingObject(const char *str, tBookingList *bookings) 
{
	int i, size, auxCoworkerId, auxRequiredEquipment;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   
	tBooking newBooking;

    /* read list size */
    sscanf(str, "%d %[^\n]s", &size, tempStr); 

    /* Initialize the bookings table */
    bookingListInit(bookings);

    for (i= 1; i<= size; i++)
    {
        /* read the loaded booking as a string*/
        sscanf(tempStr, "%d %d %d %d %d %d %d %d %d %f %d %d %d %d %d %[^\n]s", 
            &auxCoworkerId, &newBooking.nCoworkers, 
            &newBooking.checkInDate.day, &newBooking.checkInDate.month, &newBooking.checkInDate.year,
            &newBooking.checkOutDate.day, &newBooking.checkOutDate.month, &newBooking.checkOutDate.year,
            &auxRequiredEquipment, &newBooking.price, &newBooking.nAssignedSpaces, &newBooking.assignedSpaces[0],
            &newBooking.assignedSpaces[1], &newBooking.assignedSpaces[2], &newBooking.assignedSpaces[3],
            nextStr); 

        newBooking.id= (tCoworkerId)(auxCoworkerId);
        newBooking.requiredEquipment= (tEquipment)(auxRequiredEquipment);

        /* add the booking to the table */
        bookingListInsert(bookings,newBooking,i);

        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}

/* The content of the fields of the movement structure is written into the string str */
void getMovementStr(tMovement movement, int maxSize, char *str) {
	
    /* Build the string */	
	snprintf(str,maxSize-1,"%d %d %d %d", 
             (int)movement.id, movement.date.day, movement.date.month, movement.date.year);             
}

/* The content of the string str is parsed into the fields of the movement structure */
void getMovementObject(const char *str, tMovement *movement) {

	int auxId;
 			 
    /* read movement data */
    sscanf(str, "%d %d %d %d", 
        &auxId, &movement->date.day, &movement->date.month, &movement->date.year);

    movement->id = (tCoworkingCenterId)auxId;
    bookingListInit( &movement->pendingBookings );
    bookingListInit( &movement->currentBookings );
    bookingListInit( &movement->completedBookings );
    coworkerQueueInit(&movement->checkinQueue);
    coworkerQueueInit(&movement->checkoutQueue);
}

void movementCpy(tMovement *dst, tMovement src) 
{
    dst->id= src.id;
    dateCpy(&dst->date, src.date);
    bookingListCpy( &dst->pendingBookings, src.pendingBookings );
    bookingListCpy( &dst->currentBookings, src.currentBookings );
    bookingListCpy( &dst->completedBookings, src.completedBookings );
    coworkerQueueCpy( &dst->checkinQueue, src.checkinQueue );
    coworkerQueueCpy( &dst->checkoutQueue, src.checkoutQueue );
}

int movementCmp(tMovement d1, tMovement d2)
{
    int result = 0;

    if (d1.id > d2.id)
        result= 1;
    else if (d1.id < d2.id)
        result= -1;
    else {
        result= dateCmp(d1.date, d2.date);
        if (result==0) {
            result= bookingListCmp(d1.pendingBookings,d2.pendingBookings);
            if (result==0) {
                result= bookingListCmp(d1.currentBookings,d2.currentBookings);
                if (result==0) {
                    result= bookingListCmp(d1.completedBookings,d2.completedBookings);
                    if (result==0) {
                        result= coworkerQueueCmp(d1.checkinQueue,d2.checkinQueue);
                        if (result==0) {
                            result= coworkerQueueCmp(d1.checkoutQueue,d2.checkoutQueue);
                        }                                        
                    }                                        
                }                                        
            }
        }
    }

    return result;
}

void movementTableInit(tMovementTable *movementsTable) {
	
	movementsTable->nMovements= 0;
}

void movementTableAdd(tMovementTable *tabMovements, tMovement movement, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new movement */
	if(tabMovements->nMovements>=MAX_MOVEMENTS)
		*retVal = ERR_MEMORY;

	if (*retVal == OK) {
		/* Add the new movement to the end of the table */
		movementCpy(&tabMovements->table[tabMovements->nMovements],movement);
		tabMovements->nMovements++;
	}
}

void movementTableSave(tMovementTable tabMovements, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=NULL;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} 
    else 
    {
        /* Save general movement data to the file */
        for(i=0;i<tabMovements.nMovements;i++) 
        {
            getMovementStr(tabMovements.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            
            /* Save the bookings lists */
            getBookingStr(tabMovements.table[i].pendingBookings, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            getBookingStr(tabMovements.table[i].currentBookings, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            getBookingStr(tabMovements.table[i].completedBookings, MAX_LINE, str);
            fprintf(fout, "%s\n", str);

            /* Save the queues */
            getCoworkerQueueStr(tabMovements.table[i].checkinQueue, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            getCoworkerQueueStr(tabMovements.table[i].checkoutQueue, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
                    
        /* Close the file */
        fclose(fout);
	}
}

void movementTableLoad(tMovementTable *tabMovements, const char* filename, tError *retVal) 
{	
	char line[MAX_LINE];
	tMovement newMovement;
    int movementLines;
	FILE *fin=NULL;
	*retVal = OK;
	
	/* Initialize the output table */
	movementTableInit(tabMovements);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the movements */
		while(!feof(fin) && tabMovements->nMovements<MAX_MOVEMENTS) 
        {
			/* Read the movement object */
            movementLines= 0;
			line[0] = '\0';
			fgets(line, MAX_LINE-1, fin);
			line[MAX_LINE-1]='\0';
			if (strlen(line)>0) {
               getMovementObject(line, &newMovement);
               movementLines++;
            }

			/* Read the pending bookings object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getBookingObject(line,&newMovement.pendingBookings);
                    movementLines++;
                }
            }
                
			/* Read the current bookings object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getBookingObject(line,&newMovement.currentBookings);
                    movementLines++;
                }
            }
            
			/* Read the completed bookings object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getBookingObject(line,&newMovement.completedBookings);
                    movementLines++;
                }
            }
            
			/* Read the check-in queue object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getCoworkerQueueObject(line,&newMovement.checkinQueue);                    
                    movementLines++;
                }
            }
            
			/* Read the check-out queue object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getCoworkerQueueObject(line,&newMovement.checkoutQueue);
                    movementLines++;
                }
            }
            
            /* Add the new movement to the output table */
            if (movementLines == 6) 
                movementTableAdd(tabMovements, newMovement, retVal);		
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}
