#include <stdio.h>
#include <math.h>
#include <string.h>
#include <api.h>
#include <time.h>
#include "coworker.h"
#include "coworkingcenter.h"
#include "movement.h"
#include "list.h"
#include "queue.h"

void appDataInit(tAppData *object) {
	/* Set parent folder as the default path */
	strcpy(object->path, "../");
	
	/* Initialize the coworker table */
	coworkerTableInit(&(object->coworkers));
	
	/* Initialize the coworking centers table */
	coworkingCenterTableInit(&(object->coworkingCenters));
    
	/* Initialize the movements table */
	movementTableInit(&(object->movements));
}

void appDataLoad(tAppData *object, tError *retVal) {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Load the table of coworking centers */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%scoworkingcenters.txt", object->path);
	coworkingCenterTableLoad(&(object->coworkingCenters), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of coworking centers\n");
	}

	/* Load the table of coworkers */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%scoworkers.txt", object->path);
	coworkerTableLoad(&(object->coworkers), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of coworkers\n");
	}
    
	/* Load the table of movements */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%smovements.txt", object->path);
	movementTableLoad(&(object->movements), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of movements\n");
	}
}

void appDataSave(tAppData object, tError *retVal)  {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Save the table of coworking centers */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%scoworkingcenters.txt", object.path);
	coworkingCenterTableSave(object.coworkingCenters, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of coworking centers\n");
	}
	
	/* Save the table of coworkers */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%scoworkers.txt", object.path);
	coworkerTableSave(object.coworkers, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of coworkers\n");
	}
    
	/* Save the table of movements */
	snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%smovements.txt", object.path);
	movementTableSave(object.movements, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of movements\n");
	}
}

void appDataSetPath(tAppData *object, const char *path)  {		
	strncpy(object->path, path, MAX_PATHNAME);	
}


/*********************** 
 *        API
 **********************/

void getCoworkingCenters(tAppData object, tCoworkingCenterTable *result) {
	*result = object.coworkingCenters;	
}

void getCoworkingCenter(tAppData object, tCoworkingCenterId coworkingCenterId, tCoworkingCenter *coworkingCenter, tError *retVal) {
	
	int i;
	*retVal = OK;

	/* Check if there is a coworking center with this id */
	i = coworkingCenterTableFind(object.coworkingCenters, coworkingCenterId);
	if (i!=NO_COWORKINGCENTER) {
		coworkingCenterCpy(coworkingCenter,object.coworkingCenters.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}
}

void addCoworkingCenter(tAppData *object, tCoworkingCenter coworkingCenter, tError *retVal) 
{
	*retVal = OK;
	tCoworkingCenter tmp;

	/* Check if there is another coworking center with the same id */
	getCoworkingCenter(*object, coworkingCenter.id, &tmp, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new coworking center using the coworking center table method */
		coworkingCenterTableAdd(&(object->coworkingCenters), coworkingCenter, retVal);
	}
}

void getCoworkers(tAppData object, tCoworkerTable *result) {
	*result = object.coworkers;	
}

void getCoworker(tAppData object, tCoworkerId id, tCoworker *coworker, tError *retVal) {
	
	int i;
	*retVal = OK;
	
	/* Check if there is a coworker with this id */
	i = coworkerTableFind(object.coworkers, id);
	if (i!=NO_COWORKER) {
		coworkerCpy(coworker,object.coworkers.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}
}

void addCoworker(tAppData *object, tCoworker coworker, tError *retVal) {
	*retVal = OK;
	tCoworker tmpCoworker;
    
	/* Check if there is another coworker with the same id */
	getCoworker(*object, coworker.id, &tmpCoworker, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new coworker using the coworker table method */
		coworkerTableAdd(&(object->coworkers), coworker, retVal);
	}
}

void removeCoworker(tAppData *object, tCoworker coworker) 
{	
	/* Call the method from the coworkers table*/
	coworkerTableDel(&(object->coworkers), coworker);
}

int findCoworkerBooking( tBookingList bookings, tCoworkerId coworkerId )
{
    int index= NO_BOOKING;
/**************** PR2 EX1A ****************/

    int length;
    tBooking booking;
    bool found;
    tError retVal= OK;
    
    index= 1;
    found= false;
    length= bookingListLength(bookings);    
    while (index<=length && !found && retVal == OK)
    {
		retVal= bookingListGet(bookings,index,&booking);
        found= (booking.id == coworkerId);
        index++;
    }

    if (found)
        index= index-1;
    else
        index= NO_BOOKING;
/******************************************/

    return index;
}

void freeSpacesOfBooking(tCoworkingCenter *coworkingCenter, tBooking booking)
{
    int i, spaceNumber, floor, space;

    for (i= 0; i<booking.nAssignedSpaces; i++)
    {
        spaceNumber= booking.assignedSpaces[i];
        floor= (spaceNumber / 100);
        space= (spaceNumber % 100);
        coworkingCenter->layout[floor-1][space-1]= false;
        coworkingCenter->occupiedSpaces--;
    }

    coworkingCenter->percentOccupation= 100.0 * ((float)coworkingCenter->occupiedSpaces / (float)coworkingCenter->numSpaces);
}

int numberOfDays(tDate d1, tDate d2)
{
    double seconds;
    struct tm t1= { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    struct tm t2= { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    t1.tm_mday= d1.day;
    t1.tm_mon= d1.month-1;
    t1.tm_year= d1.year-1900;
    t2.tm_mday= d2.day;
    t2.tm_mon= d2.month-1;
    t2.tm_year= d2.year-1900; 
    seconds= fabs( difftime( mktime(&t1), mktime(&t2) ) );
    
    return (int)(seconds / 86400.0);
}

float calculatePrice(tCoworkingCenter coworkingCenter, tBooking booking, tDate date)
{
    float price= 0.0; 
	
/**************** PR2 EX2A ****************/    

	float singleRoom; 
	float doubleRoom;
	float tripleRoom;
	float quadRoom;
    int i;
	int floor;
	int nDays;

    //calculate price for each type of space
    singleRoom = SINGLE_WORKPLACE_PRICE_FACTOR * coworkingCenter.price;
    doubleRoom = DOUBLE_WORKPLACE_PRICE_FACTOR * coworkingCenter.price;
    tripleRoom = TRIPLE_WORKPLACE_PRICE_FACTOR* coworkingCenter.price;
    quadRoom = QUAD_WORKPLACE_PRICE_FACTOR * coworkingCenter.price;
    
    //add room price for reservation
    price= 0;
    for (i= 0; i<booking.nAssignedSpaces; i++)
    {
        floor= booking.assignedSpaces[i] / 100;
        if (floor == 1)
            price += singleRoom;
        else if (floor == 2)
            price += doubleRoom;
        else if (floor == 3)
            price += tripleRoom;
        else
            price += quadRoom;
    }
    
    //add price per person accoding to numer of coworkers and requiredEquipment
	if (booking.requiredEquipment == WORKPLACE_WITH_PHONE)
        price += (booking.nCoworkers * WORKPLACE_WITH_PHONE_PRICE);
    else if (booking.requiredEquipment == WORKPLACE_WITH_PHONE_AND_INTERNET)
        price += (booking.nCoworkers * WORKPLACE_WITH_PHONE_AND_INTERNET_PRICE);
    else if (booking.requiredEquipment == WORKPLACE_WITH_PHONE_AND_INTERNET_PROJECTOR)
        price += (booking.nCoworkers * WORKPLACE_WITH_PHONE_AND_INTERNET_PROJECTOR_PRICE);

    //product by number of days for this stay 
	nDays = numberOfDays(date,booking.checkInDate);
    price *= (float)(nDays);
    
    //late checkout penalty
    if (dateCmp(date,booking.checkOutDate)>0)
        price *= LATE_CHECKOUT_PRICE_FACTOR;


/******************************************/
    return price;
}

void processCheckouts( tCoworkingCenter *coworkingCenter, tCoworkerTable coworkers, tDate date, tCoworkerQueue *queue, 
                       tBookingList *currentBookings, tBookingList *completedBookings )
{
/**************** PR2 EX2B ****************/
   tCoworkerId coworkerId;
   tBooking booking;
   float price;
   int index;
   
       
   while (!isCoworkerQueueEmpty(*queue))
   {
       coworkerQueueHead(*queue, &coworkerId);
       if (coworkerTableFind(coworkers, coworkerId) != NO_COWORKER)
       {
           index= findCoworkerBooking(*currentBookings, coworkerId);
           if (index != NO_BOOKING)
           {
               bookingListGet(*currentBookings,index,&booking);
               if (dateCmp(booking.checkOutDate,date)==0)
               {
                   bookingListDelete(currentBookings,index);
                   price= calculatePrice(*coworkingCenter,booking,date);
                   freeSpacesOfBooking(coworkingCenter,booking);
                   booking.price= price;
                   bookingListInsert(completedBookings,booking,1);               
               }
           }
       }
       
       coworkerQueueDequeue(queue);
   }
/******************************************/
}

int availableSpaces(tCoworkingCenter coworkingCenter, int capacity)
{
    int i, available;
    available= 0;

    for (i= 0; i < MAX_SPACES_PER_FLOOR; i++)
         if (coworkingCenter.layout[capacity-1][i] == false)
             available++;

    return available;
}

void assignSpace(tCoworkingCenter *coworkingCenter, int capacity, int amount, tBooking *booking)
{
    int i, spaceNumber;

    for (i= 0; i < MAX_SPACES_PER_FLOOR && amount > 0; i++)
         if (coworkingCenter->layout[capacity-1][i] == false)
         {
             coworkingCenter->layout[capacity-1][i] = true; 
             coworkingCenter->occupiedSpaces++;
             spaceNumber= (capacity*100 + i + 1);
             booking->assignedSpaces[ booking->nAssignedSpaces ]= spaceNumber;
             booking->nAssignedSpaces++;
             amount--;
         }

    coworkingCenter->percentOccupation= 100.0 * ((float)coworkingCenter->occupiedSpaces / (float)coworkingCenter->numSpaces);
}

void assignSpacesForBooking(tCoworkingCenter *coworkingCenter, tBooking *booking)
{
    int singleSpaces, doubleSpaces, tripleSpaces, quadSpaces;

    singleSpaces= availableSpaces(*coworkingCenter,1);
    doubleSpaces= availableSpaces(*coworkingCenter,2);
    tripleSpaces= availableSpaces(*coworkingCenter,3);
    quadSpaces =  availableSpaces(*coworkingCenter,4);

    if (booking->nCoworkers == 1)
    {
        if (singleSpaces >= 1)
            assignSpace(coworkingCenter,1,1,booking);
        else if (doubleSpaces >= 1)
            assignSpace(coworkingCenter,1,1,booking);            
        else if (tripleSpaces >= 1)
            assignSpace(coworkingCenter,1,1,booking);            
        else if (quadSpaces >= 1)
            assignSpace(coworkingCenter,1,1,booking);            
    } else if (booking->nCoworkers == 2) {
        if (doubleSpaces >= 1)
            assignSpace(coworkingCenter,2,1,booking);
        else if (singleSpaces >= 2)
            assignSpace(coworkingCenter,1,2,booking);            
        else if (tripleSpaces >= 1)
            assignSpace(coworkingCenter,3,1,booking);            
        else if (quadSpaces >= 1)
            assignSpace(coworkingCenter,4,1,booking); 
    } else if (booking->nCoworkers == 3) {
        if (tripleSpaces >= 1)
            assignSpace(coworkingCenter,3,1,booking);
        else if (doubleSpaces >= 1 && singleSpaces >= 1) {
            assignSpace(coworkingCenter,1,1,booking);            
            assignSpace(coworkingCenter,2,1,booking);              
        }
        else if (tripleSpaces >= 3)
            assignSpace(coworkingCenter,3,3,booking);
        else if (doubleSpaces >= 2)
            assignSpace(coworkingCenter,2,2,booking);         
        else if (quadSpaces >= 4)
            assignSpace(coworkingCenter,4,1,booking);         
    } else {
        if (quadSpaces >= 1)
            assignSpace(coworkingCenter,4,1,booking);
        else if (doubleSpaces >= 2)
            assignSpace(coworkingCenter,2,1,booking);
        else if (tripleSpaces >= 3 && singleSpaces >= 1) {
            assignSpace(coworkingCenter,3,1,booking);            
            assignSpace(coworkingCenter,1,1,booking);            
        }
        else if (singleSpaces >= 4)
            assignSpace(coworkingCenter,1,4,booking);         
        else if (tripleSpaces >= 1 && doubleSpaces >= 1) {
            assignSpace(coworkingCenter,3,1,booking);            
            assignSpace(coworkingCenter,2,1,booking);            
        }
        else if (tripleSpaces >= 2)
            assignSpace(coworkingCenter,3,2,booking);
    }
}

void processCheckins( tCoworkingCenter *coworkingCenter, tCoworkerTable coworkers, tDate date, tCoworkerQueue *queue, 
                      tBookingList *pendingBookings, tBookingList *currentBookings )
{
/**************** PR2 EX1B ****************/

	tCoworkerId coworkerId;
	tBooking booking;
	int index;
	
	while (!isCoworkerQueueEmpty(*queue))
	{
       coworkerQueueHead(*queue, &coworkerId);
       
		if (coworkerTableFind(coworkers, coworkerId) != NO_COWORKER)
		{
			index= findCoworkerBooking(*pendingBookings, coworkerId);
			if (index != NO_BOOKING)
			{
				bookingListGet(*pendingBookings,index,&booking);
				if (dateCmp(booking.checkInDate,date)==0)
				{
					bookingListDelete(pendingBookings,index);
					assignSpacesForBooking(coworkingCenter,&booking);
					bookingListInsert(currentBookings,booking,1);               
				}
			}
		}
       
       coworkerQueueDequeue(queue);
	}

/******************************************/
}

void updateCoworkingCenterOccupation( tCoworkingCenter *coworkingCenter, tBookingList currentBookings )
{
    int length, index, i, j, floor, space, spaceNumber;
    tBooking booking;

    /* initialize all spaces as non-occupied */
    coworkingCenter->occupiedSpaces= 0;
    for (i = 0; i < MAX_FLOORS; i++)
        for (j= 0; j < MAX_SPACES_PER_FLOOR; j++)
            coworkingCenter->layout[i][j]= false;            

    index= 1;
    length= bookingListLength(currentBookings);    

    for (index=1; index<=length; index++)
    {
        bookingListGet(currentBookings,index,&booking);

        /* mark all spaces of a current booking as occupied */
        for (i = 0; i < booking.nAssignedSpaces; i++) 
        {
            spaceNumber= booking.assignedSpaces[i];
            floor= spaceNumber / 100;
            space = spaceNumber % 100;
            coworkingCenter->layout[floor-1][space-1]= true;
            coworkingCenter->occupiedSpaces++;
        }
    }

    /* calculate total spaces amb percentage of occupation */
    coworkingCenter->numSpaces= (MAX_FLOORS * MAX_SPACES_PER_FLOOR);
    coworkingCenter->percentOccupation= 100.0 * ((float)coworkingCenter->occupiedSpaces / (float)coworkingCenter->numSpaces);
}

void processMovement( tMovement *movement, 
                      tCoworkerTable *coworkers, tCoworkingCenterTable *coworkingCenters, tError *retVal )
{
    int index;

    index= coworkingCenterTableFind(*coworkingCenters,movement->id);

    if (index == NO_COWORKINGCENTER)
       *retVal = ERR_NO_COWORKINGCENTER;
    else
    {
        /* update the occupation of the coworkingCenter according to ongoing bookings */
        updateCoworkingCenterOccupation( &coworkingCenters->table[index], movement->currentBookings );

        /* process the checkouts */
        processCheckouts( &coworkingCenters->table[index], *coworkers, movement->date, 
                          &movement->checkoutQueue, 
                          &movement->currentBookings, &movement->completedBookings );

        /* process the checkins */
        processCheckins(  &coworkingCenters->table[index], *coworkers, movement->date, 
                          &movement->checkinQueue, 
                          &movement->pendingBookings, &movement->currentBookings );
        *retVal = OK;
    }
}

void processAllMovements(tAppData *object, tError *retVal)
{    
    int i;

    for (i= 0; i < object->movements.nMovements; i++) 
    {
        /* process the movement */
        processMovement( &object->movements.table[i], &object->coworkers, &object->coworkingCenters, retVal );
    }
}
