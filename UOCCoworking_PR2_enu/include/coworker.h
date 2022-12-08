#include "data.h"

/* Get a textual representation of a coworker */
void getCoworkerStr(tCoworker coworker, int maxSize, char *str);
	
/* Get a coworker object from its textual representation */
void getCoworkerObject(const char *str, tCoworker *coworker);

/* Compare two dates */
int dateCmp( tDate d1, tDate d2 );

/* Compares two strings in uppercase */
int strcmpUpper( char *s1, char *s2 );

/* Compare two coworkers */
int coworkerCmp(tCoworker coworker1, tCoworker coworker2);

/* Copy the coworker data in src to dst*/
void coworkerCpy(tCoworker *dst, tCoworker src);

/* Initialize the table of coworkers */
void coworkerTableInit(tCoworkerTable *table);

/* Add a new coworker to the table of coworkers */
void coworkerTableAdd(tCoworkerTable *table, tCoworker coworker, tError *retVal);

/* Find a coworker in the table and returns its position */
int coworkerTableFind(tCoworkerTable table, tCoworkerId id);

/* Remove the first occurence of a coworker in the table */
void coworkerTableDel(tCoworkerTable *table, tCoworker coworker);

/* Load the table of coworkers from a file */
void coworkerTableLoad(tCoworkerTable *table, const char* filename, tError *retVal);

/* Save a table of coworkers to a file */
void coworkerTableSave(tCoworkerTable table, const char* filename, tError *retVal);

/* Selects urban coworkers for a given city */
void coworkerTableSelectCoworkers(tCoworkerTable coworkers, char *city, tCoworkerTable *result);

/* Selects satisfied coworkers */
void coworkerTableSelectSatisfiedCoworkers(tCoworkerTable coworkers, tCoworkerTable *result);

/* Calculates the average points obtained per booking */
float coworkerTableGetAvgPointsPerBooking(tCoworkerTable tabCoworker);

/* Calculates the maximum satisfaction percentage per age interval */
void coworkerTableGetMaxSatisfactionPerAgeInterval(tCoworkerTable tabCoworker,
     float *upto29, float *between30and44, float *between45and59, float *from60);