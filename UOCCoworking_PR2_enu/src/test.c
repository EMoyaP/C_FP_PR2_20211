#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "coworker.h"
#include "coworkingcenter.h"
#include "movement.h"
#include "api.h"
#include "list.h"
#include "queue.h"

#define COWORKER1 "10 LUISA MARTINEZ 38908321Y 1991 7 15 BARCELONA 0 3 25 100 90.00"    
#define COWORKER2 "20 JOHN DOE 44451217G 1977 3 14 LONDON 1 6 25 100 80.00"
#define COWORKER3 "30 PETER WILLIAMS 41072140T 1966 2 28 DUBLIN 3 0 10 50 70.00"
#define COWORKER4 "40 JUSTINE LECLERC 23169220R 1960 8 20 PARIS 2 1 30 20 85.00"
#define COWORKER5 "50 JUSTINE LEBLANC 23169221R 1989 4 22 CANNES 0 5 9 9 90.00"

#define COWORKINGCENTER1 "1 22@ LLACUNA_15 BARCELONA 2 0 50 50.00 7.00 0 0 1 95.00"
#define COWORKINGCENTER2 "2 ZONA_FRANCA MOTORS_54 BARCELONA 5 4 100 400.0 1.0 1 1 1 75.00"
#define COWORKINGCENTER3 "3 ATOCHA MENDEZ_ALVARO_1 MADRID 5 4 200 300.0 2.0 1 0 1 90.00"

#define MOVEMENT1 "1 10 11 2019"
#define BOOKINGS1 "3 10 4 10 11 2019 20 11 2019 1 0.00 0 0 0 0 0 20 3 10 11 2019 24 11 2019 2 0.00 0 0 0 0 0 30 2 10 11 2019 15 11 2019 3 0.00 0 0 0 0 0"
#define BOOKINGS2 "1 40 3 25 10 2019 10 11 2019 0 0.00 1 301 0 0 0"
#define BOOKINGS3 "1 50 3 25 10 2019 9 11 2019 0 70.00 1 302 0 0 0"
#define QUEUE1 "3 10 20 30"
#define QUEUE2 "1 40"

void runTests() {	
	int passedTestPR1= 0, passedTestPR2=0;
	int totalTestPR1= 0, totalTestPR2=0;
    float ratioPR1= 0.0, ratioPR2= 0.0, ratioPR= 0.0;

	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 1 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR1(&totalTestPR1, &passedTestPR1);
    if (totalTestPR1 > 0) {
        ratioPR1= (float)passedTestPR1/totalTestPR1*100.0;
	}

	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 2 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR2(&totalTestPR2, &passedTestPR2);
    if (totalTestPR2 > 0) {
        ratioPR2= (float)passedTestPR2/totalTestPR2*100.0;
	}
    if (totalTestPR1 + totalTestPR2 > 0) {
        ratioPR= (float)(passedTestPR1+passedTestPR2)/(totalTestPR1+totalTestPR2)*100.0;
	}

	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");
	printf("\tPR1: Passed %d of %d [%0.2f%%]\n", passedTestPR1, totalTestPR1, ratioPR1);
	printf("\tPR2: Passed %d of %d [%0.2f%%]\n", passedTestPR2, totalTestPR2, ratioPR2);
	printf("\n\tTotal: Passed %d of %d [%0.2f%%]\n", passedTestPR1+passedTestPR2, totalTestPR1+totalTestPR2, ratioPR);
	printf("===================================\n");	
}

void runTestsPR1(int *totalTest, int *passedTest) {
	*totalTest=0;
	*passedTest=0;
	
	testCpyCmp(totalTest, passedTest);
	testSelection(totalTest, passedTest);
    testFilterCombination(totalTest, passedTest);
    testStatistics(totalTest, passedTest);
    testTableOperation(totalTest, passedTest);
}

void runTestsPR2(int *totalTest, int *passedTest) {
	*totalTest=0;
	*passedTest=0;
    
    testMovementsCheckin(totalTest, passedTest);
    testMovementsCheckout(totalTest, passedTest);
}

void testMovementsCheckin(int *totalTest, int *passedTest) 
{ 
    int coworkingCenterIndex, prevOccupiedSpaces, postOccupiedSpaces, nAssignedSpaces;
    int bookingIndex10, bookingIndex20, bookingIndex30, bookingIndex40;
    int prevPendingBookings, postPendingBookings;
    int prevCurrentBookings, postCurrentBookings;
    tAppData appData;
    tMovement movement;
    tCoworker coworker;
    bool equals;
    tCoworkingCenter coworkingCenter;
    tError retVal;
    tDate date;

    appDataInit(&appData);

    /* add coworkingCenters */
    getCoworkingCenterObject(COWORKINGCENTER1, &coworkingCenter);
    coworkingCenterTableAdd(&appData.coworkingCenters, coworkingCenter, &retVal);		
    getCoworkingCenterObject(COWORKINGCENTER2, &coworkingCenter);
    coworkingCenterTableAdd(&appData.coworkingCenters, coworkingCenter, &retVal);		
    getCoworkingCenterObject(COWORKINGCENTER3, &coworkingCenter);
    coworkingCenterTableAdd(&appData.coworkingCenters, coworkingCenter, &retVal);		
    
    /* add coworkers */
    getCoworkerObject(COWORKER1, &coworker);
    coworkerTableAdd(&appData.coworkers, coworker, &retVal);		
    getCoworkerObject(COWORKER2, &coworker);
    coworkerTableAdd(&appData.coworkers, coworker, &retVal);		
    getCoworkerObject(COWORKER3, &coworker);
    coworkerTableAdd(&appData.coworkers, coworker, &retVal);		
    getCoworkerObject(COWORKER4, &coworker);
    coworkerTableAdd(&appData.coworkers, coworker, &retVal);		
    getCoworkerObject(COWORKER5, &coworker);
    coworkerTableAdd(&appData.coworkers, coworker, &retVal);		

    /* add a movement */
    getMovementObject(MOVEMENT1, &movement);
    getBookingObject(BOOKINGS1,&movement.pendingBookings);
    getBookingObject(BOOKINGS2,&movement.currentBookings);
    getBookingObject(BOOKINGS3,&movement.completedBookings);
    movementTableAdd(&appData.movements, movement, &retVal);
    
    /* update coworkingCenter occupation */
    coworkingCenterIndex= coworkingCenterTableFind(appData.coworkingCenters,movement.id);
    updateCoworkingCenterOccupation( &appData.coworkingCenters.table[coworkingCenterIndex], movement.currentBookings );

    printf("==================================\n");
	printf(" CHECK-IN PROCESS\n");
	printf("==================================\n");

	printf("\nTest 1.1: Find coworker booking (existing coworkers)");
	(*totalTest)++;
    bookingIndex10= findCoworkerBooking(movement.pendingBookings, 10);
    bookingIndex20= findCoworkerBooking(movement.pendingBookings, 20);
    bookingIndex30= findCoworkerBooking(movement.pendingBookings, 30);
    if (bookingIndex10 == 1 && 
        bookingIndex20 == 2 && 
        bookingIndex30 == 3) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (Incorrect index for existing coworkers)\n");
	}

	printf("\nTest 1.2: Find coworker booking (non-existing coworkers)");
	(*totalTest)++;
    bookingIndex40= findCoworkerBooking(movement.pendingBookings, 40);
    if (bookingIndex40 == NO_BOOKING) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (Incorrect index for existing coworkers)\n");
	}

	printf("\nTest 1.3: Empty checkin queue");
	(*totalTest)++;
    date.day= 9; date.month= 11; date.year= 2019; 
    processCheckins( &appData.coworkingCenters.table[coworkingCenterIndex], appData.coworkers, date, 
                     &appData.movements.table[0].checkinQueue,
                     &appData.movements.table[0].pendingBookings, 
                     &appData.movements.table[0].currentBookings );
    equals= (movementCmp( movement, appData.movements.table[0] ) == 0);

    if (equals){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (no changes expected caused by an empty checkin queue)\n");
	}

	printf("\nTest 1.4: Checkin queue non-empty. Coworkers with incorrect checkin date");
	(*totalTest)++;
    prevOccupiedSpaces= appData.coworkingCenters.table[coworkingCenterIndex].occupiedSpaces;
    prevPendingBookings= bookingListLength(appData.movements.table[0].pendingBookings);
    prevCurrentBookings= bookingListLength(appData.movements.table[0].currentBookings);
    getCoworkerQueueObject(QUEUE1,&appData.movements.table[0].checkinQueue);
    processCheckins( &appData.coworkingCenters.table[coworkingCenterIndex], appData.coworkers, date, 
                     &appData.movements.table[0].checkinQueue,
                     &appData.movements.table[0].pendingBookings, 
                     &appData.movements.table[0].currentBookings);
    postOccupiedSpaces= appData.coworkingCenters.table[coworkingCenterIndex].occupiedSpaces;
    postPendingBookings= bookingListLength(appData.movements.table[0].pendingBookings);
    postCurrentBookings= bookingListLength(appData.movements.table[0].currentBookings);

    if (prevOccupiedSpaces == postOccupiedSpaces && 
        isCoworkerQueueEmpty(appData.movements.table[0].checkinQueue) && 
        prevPendingBookings == postPendingBookings && 
        prevCurrentBookings == postCurrentBookings) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (no checkin should be effective since date does not match)\n");
	}

	printf("\nTest 1.5: Checkin queue non-empty. Coworkers with correct checkin date");
	(*totalTest)++;
    date.day= 10; date.month= 11; date.year= 2019; 
    prevOccupiedSpaces= appData.coworkingCenters.table[coworkingCenterIndex].occupiedSpaces;
    prevPendingBookings= bookingListLength(appData.movements.table[0].pendingBookings);
    prevCurrentBookings= bookingListLength(appData.movements.table[0].currentBookings);
    getCoworkerQueueObject(QUEUE1,&appData.movements.table[0].checkinQueue);
    processCheckins( &appData.coworkingCenters.table[coworkingCenterIndex], appData.coworkers, date, 
                     &appData.movements.table[0].checkinQueue,
                     &appData.movements.table[0].pendingBookings, 
                     &appData.movements.table[0].currentBookings);

    postOccupiedSpaces= appData.coworkingCenters.table[coworkingCenterIndex].occupiedSpaces;
    postPendingBookings= bookingListLength(appData.movements.table[0].pendingBookings);
    postCurrentBookings= bookingListLength(appData.movements.table[0].currentBookings);
    if (prevOccupiedSpaces < postOccupiedSpaces && 
        isCoworkerQueueEmpty(appData.movements.table[0].checkinQueue)) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (No checkins processed)\n");
	}

	printf("\nTest 1.6: Checkin queue non-empty. Correct date. Bookings list management");
	(*totalTest)++;
    if (prevPendingBookings == postPendingBookings+3 && 
        prevCurrentBookings == postCurrentBookings-3) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (3 checkins should have been processed on the current date)\n");
	}    

	printf("\nTest 1.7: Current bookings properly processed");    
	(*totalTest)++;
    bookingIndex10= findCoworkerBooking(appData.movements.table[0].currentBookings, 10);
    if (bookingIndex10 != NO_COWORKER)
        nAssignedSpaces= appData.movements.table[0].currentBookings.table[bookingIndex10-1].nAssignedSpaces;
    else
        nAssignedSpaces= 0;

    if (nAssignedSpaces == 1 && 
        appData.movements.table[0].currentBookings.table[bookingIndex10-1].assignedSpaces[nAssignedSpaces-1] == 401) 
    {
        printf("\n\t-> OK\n");
        (*passedTest)++;                
    }
    else {
		printf("\n\t-> FAIL (No spaces assigned to current booking)\n");
    }
}

void testMovementsCheckout(int *totalTest, int *passedTest) 
{ 
    int coworkingCenterIndex, bookingIndex40, nAssignedSpaces; 
    int prevOccupiedSpaces, postOccupiedSpaces;
    int prevCompletedBookings, postCompletedBookings;
    int prevCurrentBookings, postCurrentBookings;
    
    tAppData appData;
    tMovement movement;
    tCoworker coworker;
    tBooking booking;
    bool equals;
    tCoworkingCenter coworkingCenter;
    tError retVal;
    tDate date;
    float price;

    appDataInit(&appData);

    /* add coworkingCenters */
    getCoworkingCenterObject(COWORKINGCENTER1, &coworkingCenter);
    coworkingCenterTableAdd(&appData.coworkingCenters, coworkingCenter, &retVal);		
    getCoworkingCenterObject(COWORKINGCENTER2, &coworkingCenter);
    coworkingCenterTableAdd(&appData.coworkingCenters, coworkingCenter, &retVal);		
    getCoworkingCenterObject(COWORKINGCENTER3, &coworkingCenter);
    coworkingCenterTableAdd(&appData.coworkingCenters, coworkingCenter, &retVal);		

    /* add coworkers */
    getCoworkerObject(COWORKER1, &coworker);
    coworkerTableAdd(&appData.coworkers, coworker, &retVal);		
    getCoworkerObject(COWORKER2, &coworker);
    coworkerTableAdd(&appData.coworkers, coworker, &retVal);		
    getCoworkerObject(COWORKER3, &coworker);
    coworkerTableAdd(&appData.coworkers, coworker, &retVal);		
    getCoworkerObject(COWORKER4, &coworker);
    coworkerTableAdd(&appData.coworkers, coworker, &retVal);		
    getCoworkerObject(COWORKER5, &coworker);
    coworkerTableAdd(&appData.coworkers, coworker, &retVal);		

    /* add a movement */
    getMovementObject(MOVEMENT1, &movement);
    getBookingObject(BOOKINGS1,&movement.pendingBookings);
    getBookingObject(BOOKINGS2,&movement.currentBookings);
    getBookingObject(BOOKINGS3,&movement.completedBookings);
    movementTableAdd(&appData.movements, movement, &retVal);

    /* update coworkingCenter occupation */
    coworkingCenterIndex= coworkingCenterTableFind(appData.coworkingCenters,movement.id);
    updateCoworkingCenterOccupation( &appData.coworkingCenters.table[coworkingCenterIndex], movement.currentBookings );
    date.day= 10; date.month= 11; date.year= 2019; 

	printf("==================================\n");
	printf(" CHECK-OUT PROCESS\n");
	printf("==================================\n");

	printf("\nTest 2.1: Calculate price for TRIPLE space, 3 coworkers with WORKPLACE_ONLY required equipment. Checkout on date.");
	(*totalTest)++;
    bookingCpy(&booking, movement.currentBookings.table[0]);
    booking.requiredEquipment= WORKPLACE_ONLY;
    booking.nCoworkers= 3;
    dateCpy( &booking.checkOutDate, date );
    price= calculatePrice(appData.coworkingCenters.table[coworkingCenterIndex], booking, date);
    if (price == 1200.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
        printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",1200.0, price);
	}

	printf("\nTest 2.2: Calculate price for TRIPLE space, 3 coworkers with WORKPLACE + PHONE required equipment. Checkout on date.");
	(*totalTest)++;
    booking.requiredEquipment= WORKPLACE_WITH_PHONE;
    price= calculatePrice(appData.coworkingCenters.table[coworkingCenterIndex], booking, date);

    if (price == 1680.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
        printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",1680.0, price);
	}

	printf("\nTest 2.3: Calculate price for QUAD space, 3 coworkers with WORKPLACE + PHONE + INTERNET required equipment. Checkout on date.");
	(*totalTest)++;
    booking.assignedSpaces[0]= 401;
    booking.requiredEquipment= WORKPLACE_WITH_PHONE_AND_INTERNET;
    price= calculatePrice(appData.coworkingCenters.table[coworkingCenterIndex], booking, date);
    if (price == 2600.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
        printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",2600.0, price);
	}

	printf("\nTest 2.4: Calculate price for QUAD space, 3 coworkers with WORKPLACE + PHONE + INTERNET + PROJECTOR required equipment. Late Checkout.");
	(*totalTest)++;
    booking.requiredEquipment= WORKPLACE_WITH_PHONE_AND_INTERNET_PROJECTOR;
    date.day= 11;
    price= calculatePrice(appData.coworkingCenters.table[coworkingCenterIndex], booking, date);
    if (price == 4233.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",4233.0, price);
	}

	printf("\nTest 2.5: Calculate price for two DOUBLE spaces, 4 coworkers with WORKPLACE + PHONE + INTERNET + PROJECTOR required equipment. Late Checkout.");
	(*totalTest)++;
    booking.nCoworkers= 4;
    booking.assignedSpaces[0]= 201;
    booking.assignedSpaces[1]= 202;
    booking.nAssignedSpaces= 2;
    booking.requiredEquipment= WORKPLACE_WITH_PHONE_AND_INTERNET_PROJECTOR;
    price= calculatePrice(appData.coworkingCenters.table[coworkingCenterIndex], booking, date);
    if (price == 5304.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",5304.0, price);
	}

	printf("\nTest 2.6: Calculate price for one SINGLE and one DOUBLE spaces, 3 coworkers in WORKPLACE + PHONE + INTERNET + PROJECTOR required equipment. Checkout on date.");
	(*totalTest)++;
    date.day= 10;
    booking.checkOutDate.day= 10;
    booking.nCoworkers= 3;
    booking.assignedSpaces[0]= 101;
    booking.assignedSpaces[1]= 201;
    booking.nAssignedSpaces= 2;
    booking.requiredEquipment= WORKPLACE_WITH_PHONE_AND_INTERNET_PROJECTOR;
    price= calculatePrice(appData.coworkingCenters.table[coworkingCenterIndex], booking, date);
    if (price == 3320.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
        printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",3320.0, price);
	}
    
	printf("\nTest 2.7: Empty checkout queue");
	(*totalTest)++;
    date.day= 9; date.month= 11; date.year= 2019; 
    processCheckouts( &appData.coworkingCenters.table[coworkingCenterIndex], appData.coworkers, date, 
                      &appData.movements.table[0].checkoutQueue,
                      &appData.movements.table[0].currentBookings, 
                      &appData.movements.table[0].completedBookings );
    equals= (movementCmp( movement, appData.movements.table[0] ) == 0);

    if (equals){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (no changes expected caused by an empty checkin queue)\n");
	}

	printf("\nTest 2.8: Checkout queue non-empty. Coworkers with incorrect checkout date");
	(*totalTest)++;
    prevOccupiedSpaces= appData.coworkingCenters.table[coworkingCenterIndex].occupiedSpaces;
    prevCurrentBookings= bookingListLength(appData.movements.table[0].currentBookings);
    prevCompletedBookings= bookingListLength(appData.movements.table[0].completedBookings);
    getCoworkerQueueObject(QUEUE2,&appData.movements.table[0].checkoutQueue);
    processCheckouts( &appData.coworkingCenters.table[coworkingCenterIndex], appData.coworkers, date, 
                      &appData.movements.table[0].checkoutQueue,
                      &appData.movements.table[0].currentBookings, 
                      &appData.movements.table[0].completedBookings );

    postOccupiedSpaces= appData.coworkingCenters.table[coworkingCenterIndex].occupiedSpaces;
    postCurrentBookings= bookingListLength(appData.movements.table[0].currentBookings);
    postCompletedBookings= bookingListLength(appData.movements.table[0].completedBookings);

    if (prevOccupiedSpaces == postOccupiedSpaces && 
        isCoworkerQueueEmpty(appData.movements.table[0].checkoutQueue) && 
        prevCurrentBookings == postCurrentBookings && 
        prevCompletedBookings == postCompletedBookings) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (no checkout should be effective since date does not match)\n");
	}

	printf("\nTest 2.9: Checkout queue non-empty. Coworkers with correct checkout date");
	(*totalTest)++;
    date.day= 10; date.month= 11; date.year= 2019; 

    prevOccupiedSpaces= appData.coworkingCenters.table[coworkingCenterIndex].occupiedSpaces;
    prevCurrentBookings= bookingListLength(appData.movements.table[0].currentBookings);
    prevCompletedBookings= bookingListLength(appData.movements.table[0].completedBookings);
    getCoworkerQueueObject(QUEUE2,&appData.movements.table[0].checkoutQueue);

    processCheckouts( &appData.coworkingCenters.table[coworkingCenterIndex], appData.coworkers, date, 
                      &appData.movements.table[0].checkoutQueue,
                      &appData.movements.table[0].currentBookings, 
                      &appData.movements.table[0].completedBookings);
    postOccupiedSpaces= appData.coworkingCenters.table[coworkingCenterIndex].occupiedSpaces;
    postCurrentBookings= bookingListLength(appData.movements.table[0].currentBookings);
    postCompletedBookings= bookingListLength(appData.movements.table[0].completedBookings);
    if (prevOccupiedSpaces > postOccupiedSpaces && 
        isCoworkerQueueEmpty(appData.movements.table[0].checkoutQueue)) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (No checkouts processed)\n");
	}

	printf("\nTest 2.10: Checkout queue non-empty. Correct date. Bookings list management");
	(*totalTest)++;
    if (prevCurrentBookings == postCurrentBookings+1 && 
        prevCompletedBookings == postCompletedBookings-1) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (1 checkout should have been processed on the current date)\n");
	}    

	printf("\nTest 2.11: Current bookings properly processed (price calculated)");    
	(*totalTest)++;
    bookingIndex40= findCoworkerBooking(appData.movements.table[0].completedBookings, 40);

    if (bookingIndex40 != NO_COWORKER)
        nAssignedSpaces= appData.movements.table[0].completedBookings.table[bookingIndex40-1].nAssignedSpaces;
    else
        nAssignedSpaces= 0;

    if (nAssignedSpaces == 1 && 
        appData.movements.table[0].completedBookings.table[bookingIndex40-1].price == 1200.0) 
    {
        printf("\n\t-> OK\n");
        (*passedTest)++;                
    }
    else {
		printf("\n\t-> FAIL (No space price calculated for a completed booking)\n");
    }

	printf("\nTest 2.12: Current bookings properly processed (spaces free)");    
	(*totalTest)++;
    if (appData.coworkingCenters.table[0].layout[2][0] == false) 
    {
        printf("\n\t-> OK\n");
        (*passedTest)++;                
    }
    else {
		printf("\n\t-> FAIL (Space 301 should be free after checkout)\n");
    }
}

void testCpyCmp(int *totalTest, int *passedTest) {	

	tCoworker d1, d2, d4, d5;

	printf("==================================\n");
	printf(" COWORKERS COMPARISON (Exercise 3)\n");
	printf("==================================\n");
	
	printf("\nTest 3.1: Compare equal coworkers");
	(*totalTest)++;
	getCoworkerObject(COWORKER1, &d1);
    if (coworkerCmp(d1,d1)==0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	printf("\nTest 3.2: Comparison, first coworker greater than first");
	(*totalTest)++;
	getCoworkerObject(COWORKER4, &d4);
	getCoworkerObject(COWORKER5, &d5);
    if (coworkerCmp(d4,d5)>0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 3.3: Comparison, second coworker lower than second");
	(*totalTest)++;
    if (coworkerCmp(d5,d4)<0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 3.4: Compare case-unsensitive strings");
	(*totalTest)++;
	coworkerCpy(&d2,d1);
#ifdef TYPEDEF_COMPLETED
    strcpy(d2.name, "Luisa");
    strcpy(d2.surname, "Martinez");
    strcpy(d2.docNumber, "38908321y");
    strcpy(d2.birthCity, "Barcelona");
#endif 
    if (coworkerCmp(d1,d2)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}    
}	

void testSelection(int *totalTest, int *passedTest) {	
	tCoworkerTable coworkers, result;
	tCoworker coworker1, coworker2, coworker3, coworker4, coworker5;	
	tError retVal;
		
	printf("=================================================\n");
	printf(" COWORKER SELECTION (Exercise 4)\n");
	printf("=================================================\n");

	printf("\nTest 4.1: Select coworkers on an empty table");
	(*totalTest)++;
	coworkerTableInit(&coworkers);	
	coworkerTableInit(&result);

    coworkerTableSelectCoworkers(coworkers, "BARCELONA", &result);
	if(result.nCoworkers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nCoworkers);
	}

	getCoworkerObject(COWORKER1, &coworker1);
	getCoworkerObject(COWORKER2, &coworker2);
    getCoworkerObject(COWORKER3, &coworker3);
    getCoworkerObject(COWORKER4, &coworker4);
    coworkerTableAdd(&coworkers,coworker1,&retVal);
    coworkerTableAdd(&coworkers,coworker2,&retVal);
    coworkerTableAdd(&coworkers,coworker3,&retVal);
    coworkerTableAdd(&coworkers,coworker4,&retVal);

	printf("\nTest 4.2: Coworkers from coincident city in non empty table");
	(*totalTest)++;	
    coworkerTableSelectCoworkers(coworkers, "BARCELONA", &result);
	if(result.nCoworkers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nCoworkers);
	}

    getCoworkerObject(COWORKER5, &coworker5);
    coworkerTableAdd(&coworkers,coworker5,&retVal);	

	printf("\nTest 4.3: Coworkers from a non coincident city in non empty table");
	(*totalTest)++;	
    coworkerTableSelectCoworkers(coworkers, "MADRID", &result);;
	if(result.nCoworkers==2) {
		if((coworkerCmp(result.table[0], coworker1)!=0) ||
           (coworkerCmp(result.table[1], coworker5)!=0))  {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.nCoworkers);
	}

	printf("\nTest 4.4: Selection criteria: year of birth");
	(*totalTest)++;
#ifdef TYPEDEF_COMPLETED
    coworkers.table[0].birthDate.year= 1980;
#endif
	coworkerTableInit(&result);	
    coworkerTableSelectCoworkers(coworkers, "MADRID", &result);;
	if(result.nCoworkers==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 1, result.nCoworkers);
	}
	
	printf("\nTest 4.5: Selection criteria: civil state");
	(*totalTest)++;
#ifdef TYPEDEF_COMPLETED
    coworkers.table[4].status= MARRIED;
#endif
	coworkerTableInit(&result);	
    coworkerTableSelectCoworkers(coworkers, "MADRID", &result);;
	if(result.nCoworkers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nCoworkers);
	}
	
	printf("\nTest 4.6: Selection criteria: profile");
	(*totalTest)++;
#ifdef TYPEDEF_COMPLETED
    coworkers.table[4].status= SINGLE;
    coworkers.table[4].profile= ENTREPRENEUR;
#endif
    coworkerTableSelectCoworkers(coworkers, "MADRID", &result);;
	if(result.nCoworkers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nCoworkers);
	}
    
	printf("\nTest 4.7: Selection of satisfied coworkers (check satisfaction index)");
	(*totalTest)++;
    coworkerTableSelectSatisfiedCoworkers(coworkers, &result);
	if(result.nCoworkers==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 1, result.nCoworkers);
	}    

	printf("\nTest 4.8: Selection of satisfied coworkers (check number of bookings)");
#ifdef TYPEDEF_COMPLETED
	(*totalTest)++;
    coworkers.table[4].bookingsCounter++;
#endif
    coworkerTableSelectSatisfiedCoworkers(coworkers, &result);
	if(result.nCoworkers==2) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.nCoworkers);
	}    
}

void testFilterCombination(int *totalTest, int *passedTest) 
{
    tCoworker coworker1, coworker2, coworker3, coworker4;
    tCoworkingCenter coworkingCenter1, coworkingCenter2, coworkingCenter3;
    tCoworkerTable coworkers;
    tCoworkingCenterTable coworkingCenters;
    tCoworkingCenterTable result;
	tError retVal;
    
	getCoworkerObject(COWORKER1, &coworker1);
	getCoworkerObject(COWORKER2, &coworker2);
    getCoworkerObject(COWORKER3, &coworker3);
    getCoworkerObject(COWORKER4, &coworker4);
    coworkerTableInit(&coworkers);    
    coworkerTableAdd(&coworkers,coworker1,&retVal);
    coworkerTableAdd(&coworkers,coworker2,&retVal);
    coworkerTableAdd(&coworkers,coworker3,&retVal);
    coworkerTableAdd(&coworkers,coworker4,&retVal);
    
    getCoworkingCenterObject(COWORKINGCENTER1, &coworkingCenter1);
    getCoworkingCenterObject(COWORKINGCENTER2, &coworkingCenter2);
    getCoworkingCenterObject(COWORKINGCENTER3, &coworkingCenter3);
    coworkingCenterTableInit(&coworkingCenters);
    coworkingCenterTableAdd(&coworkingCenters,coworkingCenter1,&retVal);
    coworkingCenterTableAdd(&coworkingCenters,coworkingCenter2,&retVal);
    coworkingCenterTableAdd(&coworkingCenters,coworkingCenter3,&retVal);
    
	printf("=================================================\n");
	printf(" FILTER COMBINATION (Exercise 5)\n");
	printf("=================================================\n");
                            
	printf("\nTest 5.1: Coworker recommendation: no match (one coworking center in the same coworker city");
	(*totalTest)++;
	coworkerRecommendation(coworker1,coworkingCenters,"BARCELONA",250.0,5.0,40,&result);
	if (result.nCoworkingCenters==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, result.nCoworkingCenters);
	}

	printf("\nTest 5.2: Coworker recommendation: match (one coworking center in a different city than coworker's)");
	(*totalTest)++;
	coworkerRecommendation(coworker1,coworkingCenters,"MADRID",250.0,5.0,40,&result);
	if (result.nCoworkingCenters==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 1, result.nCoworkingCenters);
	}
    
	printf("\nTest 5.3: Coworker recommendation: match (searhing coworking centers in the same coworkers city)");
	(*totalTest)++;
	coworkerRecommendation(coworker2,coworkingCenters,"BARCELONA",250.0,5.0,40,&result);
	if (result.nCoworkingCenters==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 1, result.nCoworkingCenters);
	}
    
	printf("\nTest 5.4: Coworker recommendation: match (relax point criteria)");
	(*totalTest)++;
	coworkerRecommendation(coworker2,coworkingCenters,"BARCELONA",250.0,5.0,30,&result);
	if (result.nCoworkingCenters==2) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 1, result.nCoworkingCenters);
	}
}
	
void testStatistics(int *totalTest, int *passedTest) 
{
    float avg,upto29,between30and44,between45and59,from60;
    tCoworker coworker1, coworker2, coworker3, coworker4, coworker5;
    tCoworkerTable coworkers;
	tError retVal;

	getCoworkerObject(COWORKER1, &coworker1);
	getCoworkerObject(COWORKER2, &coworker2);
    getCoworkerObject(COWORKER3, &coworker3);
    getCoworkerObject(COWORKER4, &coworker4);
    getCoworkerObject(COWORKER5, &coworker5);
    coworkerTableInit(&coworkers);    
    
	printf("=================================================\n");
	printf(" STATISTICS (Exercise 6)\n");
	printf("=================================================\n");
                            
	printf("\nTest 6.1: Average of an empty table");
	(*totalTest)++;
    avg= coworkerTableGetAvgPointsPerBooking(coworkers);
	if (avg==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number average result. Expected %.2f and returned %.2f)\n", 0.0, avg);
	}
    
    coworkerTableAdd(&coworkers,coworker1,&retVal);
	printf("\nTest 6.2: Average of a single element");
	(*totalTest)++;
    avg= coworkerTableGetAvgPointsPerBooking(coworkers);
	if (avg==4.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number average result. Expected %.2f and returned %.2f)\n", 4.0, avg);
	}
    
    coworkerTableAdd(&coworkers,coworker2,&retVal);
    coworkerTableAdd(&coworkers,coworker3,&retVal);
    coworkerTableAdd(&coworkers,coworker4,&retVal);
    
	printf("\nTest 6.3: Average of several elements");
	(*totalTest)++;
    avg= coworkerTableGetAvgPointsPerBooking(coworkers);
	if (avg==3.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number average result. Expected %.2f and returned %.2f)\n", 3.0, avg);
	}
    
    coworkerTableInit(&coworkers); 

	printf("\nTest 6.4: Max satisfaction index of an empty table");
	(*totalTest)++;
    coworkerTableGetMaxSatisfactionPerAgeInterval(coworkers,&upto29,&between30and44,&between45and59,&from60);    
	if (upto29==0.0 && between30and44==0.0 && between45and59==0.0 && from60==0.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected results. Expected zero values and returned non-zero values)\n");
	}
    
    coworkerTableAdd( &coworkers,coworker1,&retVal );
    coworkerTableAdd( &coworkers,coworker2,&retVal );
    coworkerTableAdd( &coworkers,coworker3,&retVal );
    coworkerTableAdd( &coworkers,coworker4,&retVal );

	printf("\nTest 6.5: Max satisfaction index of an non-empty table (one coworker per range)");
	(*totalTest)++;
    coworkerTableGetMaxSatisfactionPerAgeInterval(coworkers,&upto29,&between30and44,&between45and59,&from60);  
	if (upto29==90.0 && between30and44==80.0 && between45and59==70.0 && from60==85.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (Expected %.2f, %.2f, %.2f, %.2f but returned %.2f, %.2f, %.2f, %.2f)\n",
        90.0, 80.0, 70.0, 85.0, upto29, between30and44, between45and59, from60);
	}

    coworkerTableAdd( &coworkers,coworker5,&retVal );

	printf("\nTest 6.6: Max satisfaction index of an non-empty table (several coworkers per range)");
	(*totalTest)++;
    coworkerTableGetMaxSatisfactionPerAgeInterval(coworkers,&upto29,&between30and44,&between45and59,&from60);  
	if (upto29==90.0 && between30and44==90.0 && between45and59==70.0 && from60==85.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (Expected %.2f, %.2f, %.2f, %.2f but returned %.2f, %.2f, %.2f, %.2f)\n",
        90.0, 90.0, 70.0, 85.0, upto29, between30and44, between45and59, from60);
	}
}

void testTableOperation(int *totalTest, int *passedTest) 
{
    tCoworker coworker1, coworker2, coworker3, coworker4, coworker5;
    tCoworkerTable coworkers;
	tError retVal;

    coworkerTableInit(&coworkers);    
	getCoworkerObject(COWORKER1, &coworker1);
	getCoworkerObject(COWORKER2, &coworker2);
    getCoworkerObject(COWORKER3, &coworker3);
    getCoworkerObject(COWORKER4, &coworker4);
    getCoworkerObject(COWORKER5, &coworker5);

	printf("=================================================\n");
	printf(" TABLE OPERATIONS (Exercise 7)\n");
	printf("=================================================\n");
                            
	printf("\nTest 7.1: Deletion in empty table");
	(*totalTest)++;
    coworkerTableDel( &coworkers,coworker1 );
	if (coworkers.nCoworkers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected behaviour in deletion\n");
	}
    
    coworkerTableAdd( &coworkers,coworker1,&retVal );
    
	printf("\nTest 7.2: Deletion of non-existing coworker in non-empty table");
	(*totalTest)++;
    coworkerTableDel( &coworkers,coworker2 );
	if (coworkers.nCoworkers==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected behaviour in deletion\n");
	}
    
	printf("\nTest 7.3: Deletion of existing coworker in non-empty table (no gap)");
	(*totalTest)++;
    coworkerTableDel( &coworkers,coworker1 );
	if (coworkers.nCoworkers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected behaviour in deletion\n");
	}

    coworkerTableAdd( &coworkers,coworker1,&retVal );
    coworkerTableAdd( &coworkers,coworker2,&retVal );
    coworkerTableAdd( &coworkers,coworker3,&retVal );

	printf("\nTest 7.4: Deletion requires coworkers displacement to fill the gap");
	(*totalTest)++;
    coworkerTableDel( &coworkers,coworker1 );
	if (coworkers.nCoworkers==2 && 
        coworkers.table[0].id == 20 &&
        coworkers.table[1].id == 30) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected behaviour in deletion\n");
	}
}
