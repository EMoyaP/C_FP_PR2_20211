/* Run all the test set */
#include "data.h"
#include "api.h"

/* Runs the applications tests */
void runTests();

/* Runs the applications tests corresponding to PR1 */
void runTestsPR1(int* totalTest, int* passedTest);

/* Runs the applications tests corresponding to PR2 */
void runTestsPR2(int* totalTest, int* passedTest);

/* Test the serialization of coworkers */
void testSerialization(int* totalTest, int* passedTest);

/* Test the copy and comparison of coworkers */
void testCpyCmp(int* totalTest, int* passedTest);

/* Test the coworker data persistence */
void testPersistence(int* totalTest, int* passedTest);

/* Test the coworker search */
void testSearch(int* totalTest, int* passedTest);

/* Test the coworker statistics */
void testCount(int* totalTest, int* passedTest);

/* Test the coworker sorting */
void testSort(int* totalTest, int* passedTest);

/* Test the api calls */
void testApi(int* totalTest, int* passedTest);

/* Test the selection calls */
void testSelection(int* totalTest, int* passedTest);

/* Test the filter combination calls */
void testFilterCombination(int* totalTest, int* passedTest);

/* Test the statistics calls */
void testStatistics(int* totalTest, int* passedTest);

/* Test the table operations calls */
void testTableOperation(int* totalTest, int* passedTest);

/* Test the table movements calls: checkins */
void testMovementsCheckin(int *totalTest, int *passedTest);

/* Test the table movements calls: checkouts */
void testMovementsCheckout(int *totalTest, int *passedTest);
