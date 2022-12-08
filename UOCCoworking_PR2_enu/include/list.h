#include "data.h"

void bookingListInit(tBookingList *list);
bool isBookingListEmpty(tBookingList list);
bool isBookingListFull(tBookingList list);
tError bookingListInsert(tBookingList *list, tBooking newElement, int index);
tError bookingListDelete(tBookingList *list, int index);
tError bookingListGet(tBookingList list, int index, tBooking *booking);
bool isBookingListEnd(tBookingList list, int index);
tError bookingListReplace(tBookingList *list, int index, tBooking elem);
unsigned int bookingListLength(tBookingList list);
int bookingListCmp( tBookingList b1, tBookingList b2 );
void bookingListCpy( tBookingList *dst, tBookingList src );
void bookingCpy( tBooking *dst, tBooking src );
int bookingCmp( tBooking b1, tBooking b2 );
