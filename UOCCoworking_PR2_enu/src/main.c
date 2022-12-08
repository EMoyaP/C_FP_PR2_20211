/*
* Author: EUGENIO MOYA
* Course: 20211
* Description: PR2_20211
*/

#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "test.h"

int main(int argc, char **argv)
{
	int i;
	bool testMode=false;
	
	/* Define the variable to store the application data */
	tAppData appData;
	
	setbuf(stdout, NULL);  
	
	/* Initialize the data object */
	appDataInit(&appData);
			
	/* Parse input parameters to see if we should run in normal mode or in test mode */
	for(i=1; i<argc; i++) {
		if(strcmp(argv[i], "-t")==0) {
			testMode=true;			
		}
	}
	
	/* If test mode is active, run the tests. Otherwise, start the menu */
	if(testMode) {
		runTests(); 
	} else {
		mainMenu(&appData);
	}
	
	return 0;
}
