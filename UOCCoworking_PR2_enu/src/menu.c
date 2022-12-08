#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "coworkingcenter.h"
#include "coworker.h"

int getOption(int numOptions) {
	int option=0;
		
	while(option<1 || option>numOptions) {
		/* Read the input */
		printf(">> ");
			scanf("%u", &option);
		getchar();
		
		/* Check the user input */
		if(option<1 || option>numOptions) {
			printf("Incorrect option.\n");
		}
	}
	 return option;
}

void readCoworker(tCoworker *coworker, tError *retVal) {	

	*retVal = OK;
	int number;
	char buffer[MAX_LINE];
	int length;

	/* Request information from user */ 
    printf("Coworker id (integer less than %d):\n>> ", MAX_COWORKERS);
    scanf("%d",&number);
	if(number>MAX_COWORKERS) {
		*retVal = ERROR;
	} else{
		coworker->id = (tCoworkerId)number;
	}

    printf("Name (%d char max, no spaces):\n>> ", MAX_NAME-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_NAME) {
		strncpy(coworker->name,buffer,MAX_NAME);
	} else {
		*retVal = ERROR;
	}

    printf("Surname (%d char max, no spaces):\n>> ", MAX_SURNAME-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_SURNAME) {
		strncpy(coworker->surname,buffer,MAX_SURNAME);
	} else {
		*retVal = ERROR;
	}

    printf("Document number (%d char max, no spaces):\n>> ", MAX_DOC_NUMBER-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_DOC_NUMBER) {
		strncpy(coworker->docNumber,buffer,MAX_DOC_NUMBER);
	} else {
		*retVal = ERROR;
	}
    
	printf("Birthdate Year:\n>> ");
	scanf("%d",&coworker->birthDate.year);
	
	printf("Birthdate Month:\n>> ");
	scanf("%d",&coworker->birthDate.month);
   
	printf("Birthdate Day:\n>> ");
	scanf("%d",&coworker->birthDate.day);
	
	printf("City of birth: (max %d char, no spaces):\n>> ", MAX_CITY-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_CITY) {
		strncpy(coworker->birthCity,buffer,MAX_CITY);
	} else {
		*retVal = ERROR;
	}

	printf("Civil state (1 digit being 0=SINGLE, 1=MARRIED, 2=SEPARATED, 3=DIVORCED, 4=WIDOWED):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=4) {
		coworker->status= (tCivilState)(number);
	} else {
		*retVal = ERROR;
	}

	printf("Profile (1 digit being 0-FREELANCER, 1-TELEWORKER, 2-ENTREPRENEUR, 3-OCCASIONAL, 4-EMPLOYEE, 5-PARTNER, 6-OTHER):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=6) {
		coworker->profile= (tProfessionalProfile)(number);
	} else {
		*retVal = ERROR;
	}
    
    /* Initialize the rest of values */
    coworker->bookingsCounter= 0;
    coworker->points= 0;
    coworker->satisfaction= 0.0;
}

void readCoworkingCenter(tCoworkingCenter *coworkingCenter, tError *retVal) {	

	*retVal = OK;

	char buffer[MAX_LINE];
	int number, length;

	printf("Coworking center id (integer less than %d):\n>> ",MAX_COWORKINGCENTERS);
	scanf("%d",&number);
	if(number>MAX_COWORKINGCENTERS) {
		*retVal = ERROR;
	} else {
		coworkingCenter->id= (tCoworkingCenterId)(number);
	}
    
	printf("Coworking center name (max %d char, no spaces):\n>> ", MAX_NAME-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_NAME) {
		strncpy(coworkingCenter->name,buffer,MAX_NAME);
	} else {
		*retVal = ERROR;
	}

    printf("Coworking center address (max %d char, no spaces):\n>> ", MAX_ADDRESS-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_ADDRESS) {
		strncpy(coworkingCenter->address,buffer,MAX_ADDRESS);
	} else {
		*retVal = ERROR;
	}

	printf("Coworking center nearest city (max %d char, no spaces):\n>> ", MAX_CITY-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_CITY) {
		strncpy(coworkingCenter->city,buffer,MAX_CITY);
	} else {
		*retVal = ERROR;
	}

	printf("Coworking center category (one digit between 1 and 5: the highest the better):\n>> ");
	scanf("%d",&(coworkingCenter->category));

	printf("Coworking center type (1 digit being 0=STARTUPS 1=FREELANCERS 2=RURAL 3=SPECIALIZED 4=GENERALIST):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=4) {
		coworkingCenter->type= (tCoworkingType)(number);
	} else {
		*retVal = ERROR;
	}
	
	printf("Coworking center number of spaces:\n>> ");
	scanf("%d",&(coworkingCenter->numSpaces));
	
	printf("Coworking center price per month for a single desk in shared space (in euros)\n>> ");
	scanf("%f",&(coworkingCenter->price));

	printf("Coworking center distance to center of the nearest city (real value in km):\n>> ");
	scanf("%f",&(coworkingCenter->distanceFromCityCenter));
	
	printf("Coworking center has meeting spaces? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		coworkingCenter->hasMeetingRooms = true;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		coworkingCenter->hasMeetingRooms = false;
	} else {
		*retVal = ERROR;
	}

	printf("Coworking center has kitchen? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		coworkingCenter->hasKitchen = true;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		coworkingCenter->hasKitchen = false;
	} else {
		*retVal = ERROR;
	}
    
	printf("Coworking center has auditorium? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		coworkingCenter->hasAuditorium = true;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		coworkingCenter->hasAuditorium = false;
	} else {
		*retVal = ERROR;
	}
    
	printf("Coworking center percentage of occupation (real number between 0 and 100)\n>> ");
	scanf("%f",&(coworkingCenter->percentOccupation));
}

void printCoworkingCenter( tCoworkingCenter coworkingCenter, int index ) 
{    
	char coworkingCenterStr[MAX_LINE];
    getCoworkingCenterStr(coworkingCenter, MAX_LINE, coworkingCenterStr);
    printf("[%u] - %s\n", index, coworkingCenterStr);
}

void printCoworkingCenterTable(tCoworkingCenterTable table) {
    
  	int i;	
	
	if(table.nCoworkingCenters==0) {
		printf("No coworking centers.\n");
	} else {
		for(i=0;i<table.nCoworkingCenters;i++) {
            printCoworkingCenter( table.table[i], i+1 );
		}		
	}
}

void printCoworker( tCoworker coworker, int index ) 
{    
	char coworkerStr[MAX_LINE];
    getCoworkerStr(coworker, MAX_LINE, coworkerStr);
    printf("[%u] - %s\n", index, coworkerStr);
}

void printCoworkerTable(tCoworkerTable table) {
	int i;	
	
	if(table.nCoworkers==0) {
		printf("No coworkers.\n");
	} else {
		for(i=0;i<table.nCoworkers;i++) {
            printCoworker( table.table[i], i+1 );
		}		
	}
}

void allCoworkersRecommendation(tAppData appData,
                                char *city, float price, float distance, int points) 
{
	int i, j;
    tCoworkerTable selectedCoworkers;
    tCoworkingCenterTable recommendedCoworkingCenters;
    
    coworkerTableSelectCoworkers(appData.coworkers, city, &selectedCoworkers);
    
	for(i=0;i<selectedCoworkers.nCoworkers;i++) 
    {
        coworkerRecommendation(selectedCoworkers.table[i], appData.coworkingCenters,
                               city, price, distance, points, &recommendedCoworkingCenters );
        if (recommendedCoworkingCenters.nCoworkingCenters > 0) {
            printf("COWORKER\n");
            printCoworker( selectedCoworkers.table[i], i+1);
        }
            
        for (j= 0; j < recommendedCoworkingCenters.nCoworkingCenters; j++) {
            printf("\t");
            printCoworkingCenter( recommendedCoworkingCenters.table[j], j+1 );            
        }
            
        printf("\n");
	}
}

/*****************
 **   MAIN MENU **
*****************/
void printMainMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Main Menu \n");
	printf("=======================\n");
	printf("1) Load data from file\n");
	printf("2) Save data to file\n");
	printf("3) Manage coworkers\n");
	printf("4) Manage coworking centers\n");
	printf("5) View statistics\n");
	printf("6) Exit\n");	
}

tMainMenuOptions getMainMenuOption() {
	/* Convert to the correct type */
	return (tMainMenuOptions)(getOption(6)-1);
}

void mainMenu(tAppData *appData) 
{
	tMainMenuOptions option;
	tError retVal;
		
	/* Assign the data path */
	appDataSetPath(appData,"../");
		
	/* Start the menu */
    
    /* Show list of options and ask the user for an option */
    printMainMenuOptions();
    option=getMainMenuOption();
    
	while (option!=MAIN_MENU_EXIT) 
    {
		/* Do the action for the given option */
		if (option == MAIN_MENU_LOAD) {
			appDataLoad(appData,&retVal);
			if(retVal==OK) {
				printf("Data loaded\n");
			} else {	
				printf("No previous data loaded\n");
			}
		} else if (option == MAIN_MENU_SAVE) {
			appDataSave(*appData,&retVal);
			if(retVal==OK) {
				printf("Data saved\n");
			} else {	
				printf("Cannot save the data\n");
			}
		} else if (option == MAIN_MENU_COWORKER) {
			coworkerMenu(appData);
		} else if (option == MAIN_MENU_COWORKINGCENTER) {
			coworkingCenterMenu(appData);
		} else if (option == MAIN_MENU_STAT) {
			statMenu(*appData);
		} 
        
		/* Show list of options and ask the user for an option */
		printMainMenuOptions();
		option=getMainMenuOption();
	}
}

/*********************************
 **   COWORKER MANAGEMENT MENU **
*********************************/
void printCoworkerMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage Coworkers\n");
	printf("=======================\n");
	printf("1) List coworkers\n");	
	printf("2) Add coworker\n");
	printf("3) Delete coworker\n");	
	printf("4) Clear all coworkers\n");
	printf("5) Select urban coworkers in city\n");	
	printf("6) Get list of satisfied coworkers\n");	
	printf("7) Exit\n");	
}

tCoworkerMenuOptions getCoworkerMenuOption() {
	/* Convert to the correct type */
	return (tCoworkerMenuOptions)(getOption(7)-1);
}

void coworkerMenu(tAppData *appData) {
	tCoworkerMenuOptions option;
	tCoworker newCoworker;
	tCoworkerTable coworkerTable,resultTable;
	char coworkerStr[MAX_LINE];
	char cityStr[MAX_LINE];
	int i, pos=0;
	tError retVal;
			
	/* Start the menu */
    /* Show list of options and ask the user for an option */
    printCoworkerMenuOptions();
    option=getCoworkerMenuOption();    
    
	while(option!=COWORKER_MENU_EXIT)
    {		
		/* Do the action for the given option */
		if (option == COWORKER_MENU_LIST ) {
			getCoworkers(*appData, &coworkerTable);
			printCoworkerTable(coworkerTable);
		} else if (option == COWORKER_MENU_ADD) {
			printf("Enter the information for the new coworker:\n");
			readCoworker(&newCoworker,&retVal);
			getCoworkerStr(newCoworker, MAX_LINE, coworkerStr);
			if(retVal==OK) {
				addCoworker(appData, newCoworker, &retVal);
				if(retVal==OK){
					printf("Coworker added: %s\n", coworkerStr);
				} else if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("Duplicated coworker not added: %s\n", coworkerStr);
				} else {
					printf("No more space. Coworker not added: %s\n", coworkerStr);
				}
			} else {
				printf("Error in input. Coworker not added: \n%s\n", coworkerStr);
			}
		} else if (option == COWORKER_MENU_DEL) {
			getCoworkers(*appData, &coworkerTable);			
			/* Print the coworkers */			
			printCoworkerTable(coworkerTable);		

			if (coworkerTable.nCoworkers > 0) {
				/* Ask the number of the register to be removed */
				printf("Enter the number of the coworker to delete:\n");
				pos=getOption(coworkerTable.nCoworkers);
				/* Remove the selected coworker */				
				removeCoworker(appData, coworkerTable.table[pos-1]);
			}
		} else if (option == COWORKER_MENU_CLEAR_ALL) {
			getCoworkers(*appData, &coworkerTable);	
			for (i= coworkerTable.nCoworkers-1; i >= 0; i--) {
				/* Remove the coworker */				
				removeCoworker(appData, coworkerTable.table[i]);
			}
		} else if (option == COWORKER_MENU_SELECT_URBAN_COWORKERS) {
            
			printf("City:\n");
			scanf("%s",cityStr);			
			getCoworkers(*appData, &coworkerTable);
			coworkerTableSelectCoworkers(coworkerTable,cityStr,&resultTable); 
			printCoworkerTable(resultTable);
			
		} else if (option == COWORKER_MENU_SATISFIED_COWORKERS) {
            getCoworkers(*appData, &coworkerTable);
			coworkerTableSelectSatisfiedCoworkers(coworkerTable,&resultTable);
            printCoworkerTable(resultTable);	
		}
        
        /* Show list of options and ask the user for an option */
        printCoworkerMenuOptions();
        option=getCoworkerMenuOption();        
	}
}

/********************************
 **   COWORKINGCENTER MANAGEMENT MENU **
********************************/
void printCoworkingCenterMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage coworking centers\n");
	printf("=======================\n");
	printf("1) List coworking centers\n");	
	printf("2) Add coworking center\n");
	printf("3) List coworking centers by type\n");
	printf("4) List urban coworking centers\n");
    printf("5) List recommended coworking centers to coworkers\n");
	printf("6) Exit\n");	
}

tCoworkingCenterMenuOptions getCoworkingCenterMenuOption() {
	/* Convert to the correct type */
	return (tCoworkingCenterMenuOptions)(getOption(6)-1);
}

void coworkingCenterMenu(tAppData *appData) {
	tError retVal = OK;
	tCoworkingCenterMenuOptions option;
	tCoworkingCenterTable coworkingCenterTable, typeTable, urbanTable;
	tCoworkingCenter newCoworkingCenter;
	char coworkingCenterStr[MAX_LINE];
	char cityStr[MAX_LINE];
	int type, points;
    float price, distance;
			
	/* Start the menu */
    /* Show list of options and ask the user for an option */
    printCoworkingCenterMenuOptions();
    option=getCoworkingCenterMenuOption();	
    
	while(option!=COWORKINGCENTER_MENU_EXIT)
    {
		/* Do the action for the given option */
		if (option == COWORKINGCENTER_MENU_LIST) {
			getCoworkingCenters(*appData, &coworkingCenterTable);
			printCoworkingCenterTable(coworkingCenterTable);
		} else if (option == COWORKINGCENTER_MENU_ADD) {
			readCoworkingCenter(&newCoworkingCenter,&retVal);
			getCoworkingCenterStr(newCoworkingCenter, MAX_LINE, coworkingCenterStr);
			if(retVal==OK) {
				addCoworkingCenter(appData, newCoworkingCenter, &retVal);
				if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("ERROR: A coworking center with the same ID already exists\n");
				} else {
					printf("Coworking center added: %s\n", coworkingCenterStr);
				}
			} else {
				printf("Error in input. Coworking center not added: \n%s\n", coworkingCenterStr);
			}
		} else if (option == COWORKINGCENTER_MENU_TYPE) {
			getCoworkingCenters(*appData, &coworkingCenterTable);
			printf("Coworking center type (1 digit being 0=STARTUPS 1=FREELANCERS 2=RURAL 3=SPECIALIZED 4=GENERALIST):\n");
			scanf("%d",&type);
			coworkingCenterTableFilterByType(coworkingCenterTable, (tCoworkingType)type, &typeTable);
			printCoworkingCenterTable(typeTable);
		} else if (option == COWORKINGCENTER_MENU_URBAN_COWORKINGCENTERS) {
			getCoworkingCenters(*appData, &coworkingCenterTable);
			coworkingCenterTableGetUrbanCoworkingCenters(coworkingCenterTable, &urbanTable);
			printCoworkingCenterTable(urbanTable);
		} else if (option == COWORKINGCENTER_COWORKERS_RECOMMENDATION) { 
			printf("Search in city:\n");
			scanf("%s",cityStr);			
			printf("Objective price:\n");
			scanf("%f",&price);	
			printf("Desired distance:\n");
			scanf("%f",&distance);			
			printf("Minimum points:\n");
			scanf("%d",&points);			
            allCoworkersRecommendation(*appData, cityStr, price, distance, points);
        }
        
		/* Show list of options and ask the user for an option */
		printCoworkingCenterMenuOptions();
		option=getCoworkingCenterMenuOption();
    }
}


/******************
 **   STAT MENU **
******************/
void printStatMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Stats \n");
	printf("=======================\n");
	printf("1) Get average points per booking\n");	
	printf("2) Get max satisfaction per year interval\n");	
	printf("3) Get average coworking center occupation for a coworking center of a city\n");	
	printf("4) Get maximum coworking center space price\n");	
	printf("5) Exit\n");	
}

tStatMenuOptions getStatMenuOption() {
	/* Convert to the correct type */
	return (tStatMenuOptions)(getOption(5)-1);
}

void statMenu(tAppData appData) 
{
	tStatMenuOptions option;
	tCoworkerTable coworkerTable;
	tCoworkingCenterTable coworkingCenterTable;
	char coworkingCenterStr[MAX_LINE];
    float avg, upto29, between30and44, between45and59, from60;
	
	/* Start the menu */
    /* Show list of options and ask the user for an option */
    printStatMenuOptions();
    option=getStatMenuOption();
    
	while(option!=STAT_MENU_EXIT)
    {
		/* Do the action for the given option */
		if (option == STAT_MENU_NUM_AVG_POINTS_PER_BOOKING) {			
			getCoworkers(appData, &coworkerTable);
			avg= coworkerTableGetAvgPointsPerBooking(coworkerTable);
            printf("Average points per booking: %.2f\n", avg);

		} else if (option == STAT_MENU_MAX_SATISFACTION_PER_AGE_INTERVAL) {
			getCoworkers(appData, &coworkerTable);
			coworkerTableGetMaxSatisfactionPerAgeInterval(coworkerTable, 
                        &upto29, &between30and44, &between45and59, &from60);     
            printf("Max satisfaction for age interval up to 29 years old: %.2f\n", upto29);
            printf("Max satisfaction for ages in [30,44]: %.2f\n", between30and44);
            printf("Max satisfaction for ages in [45,59]: %.2f\n", between45and59);
            printf("Max satisfaction for from 60 years old: %.2f\n", from60);
		
		} else if (option == STAT_MENU_AVG_OCCUPATION) {
            getCoworkingCenters(appData, &coworkingCenterTable);
            printf("Coworking center nearest city (max %d char, no spaces):\n>> ", MAX_CITY-1);
            scanf("%s",coworkingCenterStr);
            printf("Average occupation of coworking centers in %s is %.2f %%\n", 
                   coworkingCenterStr, coworkingCenterTableComputeAverageOccupation(coworkingCenterTable,coworkingCenterStr));
		} else if (option == STAT_MENU_MAX_SPACE_PRICE) {
			getCoworkingCenters(appData, &coworkingCenterTable);
			printf("Maximum coworking center space price: %.2f euros\n", coworkingCenterTableGetMaxSpacePrice(coworkingCenterTable));
		} 

        /* Show list of options and ask the user for an option */
        printStatMenuOptions();
        option=getStatMenuOption();
    }
}
