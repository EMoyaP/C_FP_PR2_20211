/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

#include <stdbool.h>

#define TYPEDEF_COMPLETED

#define MAX_COWORKINGCENTERS 50
#define MAX_ADDRESS 15+1
#define MAX_CITY 15+1
#define MAX_NAME 15+1
#define MAX_SURNAME 15+1
#define MAX_DOC_NUMBER 9+1
#define MAX_COWORKERS 100
#define MAX_PATHNAME 255
#define MAX_FILENAME 25
#define MAX_LINE 514
#define NO_COWORKINGCENTER -1
#define NO_COWORKER -1
#define NO_BOOKING -1
#define MIN_AGE 25
#define MAX_AGE 35
#define MIN_SATISFACTION 85.0
#define MIN_BOOKINGS 10
#define AGE_INTERVAL_FIRST_LIMIT 30
#define AGE_INTERVAL_SECOND_LIMIT 45
#define AGE_INTERVAL_THIRD_LIMIT 60

#define MAX_FLOORS 4
#define MAX_SPACES_PER_FLOOR 10
#define MAX_MOVEMENTS 5
#define MAX_SPACES_PER_BOOKING 4
#define MAX_BOOKINGS 10

#define WORKPLACE_WITH_PHONE_PRICE 10.0
#define WORKPLACE_WITH_PHONE_AND_INTERNET_PRICE 25.0
#define WORKPLACE_WITH_PHONE_AND_INTERNET_PROJECTOR_PRICE 40.0

#define SINGLE_WORKPLACE_PRICE_FACTOR   0.75
#define DOUBLE_WORKPLACE_PRICE_FACTOR   1.0
#define TRIPLE_WORKPLACE_PRICE_FACTOR   1.5
#define QUAD_WORKPLACE_PRICE_FACTOR     1.75
#define LATE_CHECKOUT_PRICE_FACTOR 1.2

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_CANNOT_READ=-1, ERR_CANNOT_WRITE=-2, 
              ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, 
              ERR_ENTRY_NOT_FOUND=-6,
              ERR_NO_COWORKER=-7,ERR_NO_COWORKINGCENTER=-8,ERR_NO_FREE_GAP=-9} tError;

typedef int tCoworkingCenterId;

typedef enum { STARTUPS, FREELANCERS, RURAL, SPECIALIZED, GENERALIST } tCoworkingType; 

typedef struct {
    tCoworkingCenterId id; 
    char name[MAX_NAME]; 
    char address[MAX_ADDRESS];
    char city[MAX_CITY]; 
    int  category; 
    tCoworkingType type; 
    int numSpaces; 
    float price; 
    float distanceFromCityCenter; 
    bool hasMeetingRooms; 
    bool hasKitchen; 
    bool hasAuditorium; 
    float percentOccupation; 
    int occupiedSpaces;
    bool layout[MAX_FLOORS][MAX_SPACES_PER_FLOOR];
} tCoworkingCenter;

typedef struct {
	tCoworkingCenter table[MAX_COWORKINGCENTERS];
	int nCoworkingCenters;
} tCoworkingCenterTable;

typedef int tCoworkerId;

typedef struct {
  int day, month, year;
} tDate;

typedef enum {
  SINGLE, MARRIED, SEPARATED, DIVORCED, WIDOWED
} tCivilState;

typedef enum {
  FREELANCER, TELEWORKER, ENTREPRENEUR, OCCASIONAL, EMPLOYEE, PARTNER, OTHER
} tProfessionalProfile;
  
typedef struct {
    tCoworkerId id;
    char name[MAX_NAME];
    char surname[MAX_SURNAME];	
    char docNumber[MAX_DOC_NUMBER];	
    tDate birthDate;
    char birthCity[MAX_CITY];
    tCivilState status;
    tProfessionalProfile profile;
    int bookingsCounter;
    int points;
    float satisfaction;
} tCoworker;

typedef struct {
	tCoworker table[MAX_COWORKERS];
	int nCoworkers;
} tCoworkerTable;

typedef enum {
  WORKPLACE_ONLY,
  WORKPLACE_WITH_PHONE, 
  WORKPLACE_WITH_PHONE_AND_INTERNET, 
  WORKPLACE_WITH_PHONE_AND_INTERNET_PROJECTOR
} tEquipment;

typedef struct {
    tCoworkerId id;
    int nCoworkers;
    tDate checkInDate;
    tDate checkOutDate;
    tEquipment requiredEquipment;
    float price;
    int nAssignedSpaces;
    int assignedSpaces[MAX_SPACES_PER_BOOKING];
} tBooking;

typedef struct {
	tBooking table[MAX_BOOKINGS];
	unsigned int nElem;
} tBookingList;

typedef struct {
	tCoworkerId table[MAX_COWORKERS];
	unsigned int nElem;
} tCoworkerQueue;

typedef struct {
    tCoworkingCenterId id;
    tDate date;
    tBookingList pendingBookings;
    tBookingList currentBookings;
    tBookingList completedBookings;
    tCoworkerQueue checkinQueue;
    tCoworkerQueue checkoutQueue;
} tMovement;

typedef struct {
    tMovement table[MAX_MOVEMENTS];
    int nMovements;
} tMovementTable;

/* Definition of the application data structure */
typedef struct {
	/* Path where data will be stored */
	char path[MAX_PATHNAME];
	
	/* Coworking centers table */
	tCoworkingCenterTable coworkingCenters;
	
	/* Coworkers table */
	tCoworkerTable coworkers;

	/* Movements table */
    tMovementTable movements;
    
} tAppData;

/*********************** 
 *    COMMON HEADERS
 **********************/

/* Compare two dates */
int dateCmp( tDate d1, tDate d2 );

/* Copy a date onto another date */
void dateCpy( tDate *d1, tDate d2 );

#endif /*__DATA_H*/
