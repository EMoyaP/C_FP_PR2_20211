#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appDataInit(tAppData *object);

/* Load the application data from file */
void appDataLoad(tAppData *object, tError *error);

/* Save the application data to a file */
void appDataSave(tAppData object, tError *error);

/* Allow to assign a path to the application data */
void appDataSetPath(tAppData *object, const char *path);

/* 
 * API
 */

/* Return a table with the coworkers */
void getCoworkers(tAppData object, tCoworkerTable *result);

/* Get the coworker information */
void getCoworker(tAppData object, tCoworkerId coworkerId, tCoworker *coworker, tError *retVal);

/* Add a new coworker */
void addCoworker(tAppData *object, tCoworker coworker, tError *retVal);

/* Remove a certain coworker */
void removeCoworker(tAppData *object, tCoworker coworker);

/* Return the table of coworking centers */
void getCoworkingCenters(tAppData object, tCoworkingCenterTable *result);

/* Get the coworking center information */
void getCoworkingCenter(tAppData object, tCoworkingCenterId coworkingCenterId, tCoworkingCenter *coworkingCenter, tError *retVal);

/* Add a new coworking center */
void addCoworkingCenter(tAppData *object, tCoworkingCenter coworkingCenter, tError *retVal);

/* Finds the booking of a coworker within a list  */
int findCoworkerBooking( tBookingList bookings, tCoworkerId coworkerId );

/* Frees the spaces of a booking */
void freeSpacesOfBooking(tCoworkingCenter *coworkingCenter, tBooking booking);

/* Calculates the price of a booking */
float calculatePrice(tCoworkingCenter coworkingCenter, tBooking booking, tDate date);

/* Processes the checkouts in a center */
void processCheckouts( tCoworkingCenter *coworkingCenter, tCoworkerTable coworkers, tDate date, tCoworkerQueue *queue, 
                       tBookingList *currentBookings, tBookingList *completedBookings );

/* Returns the number of available spaces of a given capatity */
int availableSpaces(tCoworkingCenter coworkingCenter, int capacity);

/* Assigns a number of spaces of a given capacity in a center and register them in the booking */
void assignSpace(tCoworkingCenter *coworkingCenter, int capacity, int amount, tBooking *booking);

/* Assigns the spaces of a booking */
void assignSpacesForBooking(tCoworkingCenter *coworkingCenter, tBooking *booking);

/* Updates the occupation of the center according to ongoing bookings */
void processCheckins( tCoworkingCenter *coworkingCenter, tCoworkerTable coworkers, tDate date, tCoworkerQueue *queue, 
                      tBookingList *pendingBookings, tBookingList *currentBookings );

/* Processes the checkins in a center */
void updateCoworkingCenterOccupation( tCoworkingCenter *coworkingCenter, tBookingList currentBookings );

/* Processes a center movements */
void processMovement( tMovement *movement, 
                      tCoworkerTable *coworkers, tCoworkingCenterTable *coworkingCenters, tError *retVal );

/* Processes all centers movements */
void processAllMovements(tAppData *object, tError *retVal);
