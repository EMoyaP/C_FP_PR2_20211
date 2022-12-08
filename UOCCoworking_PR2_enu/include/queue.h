#include "data.h"

void coworkerQueueInit( tCoworkerQueue *queue );
void coworkerQueueHead(tCoworkerQueue queue, tCoworkerId *head);
bool isCoworkerQueueEmpty(tCoworkerQueue queue);
bool isCoworkerQueueFull(tCoworkerQueue queue);
int  coworkerQueueLength(tCoworkerQueue queue);
void coworkerQueueEnqueue(tCoworkerQueue *queue, tCoworkerId newElement);
void coworkerQueueDequeue(tCoworkerQueue *queue);
void coworkerQueueCpy(tCoworkerQueue *dst, tCoworkerQueue src);
int  coworkerQueueCmp(tCoworkerQueue q1, tCoworkerQueue q2);
void coworkerQueueSave(tCoworkerQueue tabCoworkers, const char* filename, tError *retVal);
void coworkerQueueLoad(tCoworkerQueue *tabCoworkers, const char* filename, tError *retVal);
void getCoworkerQueueStr( tCoworkerQueue queue, int maxSize, char *str);
void getCoworkerQueueObject(const char *str, tCoworkerQueue *queue) ;
 
