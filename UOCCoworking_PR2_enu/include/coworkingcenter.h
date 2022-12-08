#include "data.h"

/* Get a textual representation of a coworking center */
void getCoworkingCenterStr(tCoworkingCenter coworkingCenter, int maxSize, char *str);

/* Get a coworking center object from its textual representation */
void getCoworkingCenterObject(const char *str, tCoworkingCenter *coworkingCenter);

/* Copy the coworking center data in src to dst*/
void coworkingCenterCpy(tCoworkingCenter *dst, tCoworkingCenter src);

/* Compares the coworking center data of p1 and p2*/
int coworkingCenterCmp(tCoworkingCenter p1, tCoworkingCenter p2);

/* Computes points for the given coworking center according to the desired price and distance to center */
int computePoints(tCoworkingCenter coworkingCenter, float price, float distance);

/* Initializes the given coworking centers table */
void coworkingCenterTableInit(tCoworkingCenterTable *coworkingCenterTable);

/* Add a new coworking center to the table of coworking centers */
void coworkingCenterTableAdd(tCoworkingCenterTable *tabCoworkingCenters, tCoworkingCenter coworkingCenter, tError *retVal);

/* Find a coworking center in the table */
int coworkingCenterTableFind(tCoworkingCenterTable tabCoworkingCenters, tCoworkingCenterId id);

/* Load the table of coworking centers from a file */
void coworkingCenterTableLoad(tCoworkingCenterTable *tabCoworkingCenters, const char* filename, tError *retVal);

/* Save a table of coworking centers to a file */
void coworkingCenterTableSave(tCoworkingCenterTable tabCoworkingCenters, const char* filename, tError *retVal);

/* Obtain from a table of coworking centers those of a given type */
void coworkingCenterTableFilterByType(tCoworkingCenterTable tabCoworkingCenters, tCoworkingType type, tCoworkingCenterTable *result);

/* Obtain from a table of coworking centers those that are urban */
void coworkingCenterTableGetUrbanCoworkingCenters(tCoworkingCenterTable tabCoworkingCenters, tCoworkingCenterTable *result);

/* Obtain from a table of coworking centers the average occupation by city */
float coworkingCenterTableComputeAverageOccupation(tCoworkingCenterTable tabCoworkingCenter, char *city);

/* Obtain from a table of coworking centers the maximum price per space of a coworking center */
float coworkingCenterTableGetMaxSpacePrice(tCoworkingCenterTable tabCoworkingCenter);

/* Selects coworking centers in a city with -at least- the given amount of points according to
 *  its price and distance to center */
void coworkingCenterTableSelect(tCoworkingCenterTable tabCoworkingCenter, char *city, 
     float price, float distance, int points,  
     tCoworkingCenterTable *result);

/* Calculates the recommended coworking centers for the specified coworker. Coworking centers are based in the specified city
 * and have a desired price, distante to center and points. */
void coworkerRecommendation(tCoworker coworker, 
                            tCoworkingCenterTable coworkingCenters,
                            char *city, float price, float distance, int points,
                            tCoworkingCenterTable *result);