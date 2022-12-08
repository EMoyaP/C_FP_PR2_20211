#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int bookingCmp( tBooking b1, tBooking b2 )
{
    int result= 0;
    
    if (b1.id < b2.id)
        result= -1;
    else if (b1.id > b2.id)
        result= 1;
    else {
        if (b1.nCoworkers < b2.nCoworkers)
            result= -1;
        else if (b1.nCoworkers > b2.nCoworkers)
            result= 1;
        else {
            result= dateCmp(b1.checkInDate,b2.checkInDate);
            if (result == 0)
            {
                result= dateCmp(b1.checkOutDate,b2.checkOutDate);
                if (result == 0)
                {
                    if (b1.nAssignedSpaces < b2.nAssignedSpaces)
                        result= -1;
                    else if (b1.nAssignedSpaces > b2.nAssignedSpaces)
                        result= 1;
                    else {
                        if (b1.requiredEquipment < b2.requiredEquipment)
                            result= -1;
                        else if (b1.requiredEquipment > b2.requiredEquipment)
                            result= 1;
                    }
                }
            }
        }
    }
    
    return result;
}

void bookingCpy( tBooking *dst, tBooking src )
{
    int i;
    
    dst->id= src.id;
    dst->nCoworkers= src.nCoworkers;
    dateCpy( &dst->checkInDate, src.checkInDate );
    dateCpy( &dst->checkOutDate, src.checkOutDate );
    dst->requiredEquipment= src.requiredEquipment;
    dst->price= src.price;
    dst->nAssignedSpaces= src.nAssignedSpaces;
    for (i= 0; i<MAX_SPACES_PER_BOOKING; i++)
        dst->assignedSpaces[i]= src.assignedSpaces[i];
}

void bookingListInit(tBookingList *list) 
{
    list->nElem= 0;
}

bool isBookingListEmpty(tBookingList list) {
    
    bool empty;
    
	empty= (list.nElem == 0);
    
    return empty;
}

bool isBookingListFull(tBookingList list) {

    bool full= false;

	full= (list.nElem == MAX_BOOKINGS);

    return full;
}

tError bookingListInsert(tBookingList *list, tBooking newElement, int index) {

	tError retVal= OK;

    int i;

	if (list->nElem == MAX_BOOKINGS)
			retVal= ERR_MEMORY;
	else {
		if (index < 1 || index > list->nElem+1)
			retVal= ERR_INVALID_DATA;
		else {
			index--;
			for (i=list->nElem-1; i>= index; i--)
				 bookingCpy( &(list->table[i+1]), list->table[i]);
			list->nElem++;
			bookingCpy( &(list->table[index]), newElement );
		}
	}	
	
	return retVal;
}

tError bookingListDelete(tBookingList *list, int index) 
{
	tError retVal= OK;

	int i;
	
	if (list->nElem==0)
		retVal= ERROR;
	else {
		if (index < 1 || index > list->nElem)
			retVal= ERR_INVALID_DATA;
		else {
			index--;
			for (i=index; i<list->nElem-1; i++)
				 bookingCpy( &(list->table[i]), list->table[i+1] );
			list->nElem--;
		}
	}
	
	return retVal;
}

tError bookingListGet(tBookingList list, int index, tBooking *elem) {
	tError retVal= OK;

	if (list.nElem==0)
		retVal= ERROR;
	else {
		if (index < 1 || index > list.nElem)
			retVal= ERR_INVALID_DATA;
		else {
			index--;
			bookingCpy( elem, list.table[index] );
		}
	}

	return retVal;
}

bool isBookingListEnd(tBookingList list, int index) {
    
    bool end;
    
	end= (index-1 >= list.nElem);

    return end;
}

tError bookingListReplace(tBookingList *list, int index, tBooking elem) {
	tError retVal= OK;

	if (list->nElem==0)
		retVal= ERROR;
	else {
		if (index < 1 || index > list->nElem)
			retVal= ERR_INVALID_DATA;
		else {
			index--;
			bookingCpy( &(list->table[index]), elem );
		}
	}

	return retVal;
}

unsigned int bookingListLength(tBookingList list) {
    
    unsigned int nElements= 0;
    
    nElements= list.nElem;

    return nElements;
}

int bookingListCmp( tBookingList b1, tBookingList b2 )
{
    int i;
    int result= 0;
    
    if (b1.nElem < b2.nElem)
        result= -1;
    else if (b1.nElem > b2.nElem)
        result= 1;
    else {
        i= 0;
        while (i < b1.nElem && result == 0) {
            result= bookingCmp(b1.table[i], b2.table[i]);
            i++;
        }
    }
    
    return result;
}

void bookingListCpy( tBookingList *dst, tBookingList src )
{
    int i;
    
    dst->nElem= src.nElem;
    for (i=0; i< src.nElem; i++)
        bookingCpy(&dst->table[i], src.table[i]);
}
