#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coworkingcenter.h"

/* The content of the fields of the coworking center structure is written into the string str */
void getCoworkingCenterStr(tCoworkingCenter coworkingCenter, int maxSize, char *str) {
	    
    /* Build the string */	
	snprintf(str,maxSize-1,"%d %s %s %s %d %d %d %.2f %.2f %d %d %d %.2f", 
             (int)coworkingCenter.id, coworkingCenter.name, coworkingCenter.address, coworkingCenter.city, coworkingCenter.category,
			 (int)coworkingCenter.type, coworkingCenter.numSpaces, coworkingCenter.price,
			 coworkingCenter.distanceFromCityCenter, (int)coworkingCenter.hasMeetingRooms, 
			 (int)coworkingCenter.hasKitchen, (int)coworkingCenter.hasAuditorium, coworkingCenter.percentOccupation);
}

/* The content of the string str is parsed into the fields of the coworking center structure */
void getCoworkingCenterObject(const char *str, tCoworkingCenter *coworkingCenter) {

	int auxId, auxType, auxMeetingSpaces, auxKitchen, auxAuditorium;

    /* read coworking center data */
    sscanf(str, "%d %s %s %s %d %d %d %f %f %d %d %d %f", 
        &auxId, coworkingCenter->name, coworkingCenter->address, coworkingCenter->city, &coworkingCenter->category, 
        &auxType, &coworkingCenter->numSpaces, &coworkingCenter->price,  
        &coworkingCenter->distanceFromCityCenter, &auxMeetingSpaces, &auxKitchen, &auxAuditorium,
        &coworkingCenter->percentOccupation );

    coworkingCenter->id = (tCoworkingCenterId)auxId;
    coworkingCenter->type = (tCoworkingType)auxType;
    if (auxMeetingSpaces != 0)
        coworkingCenter->hasMeetingRooms = true;
    else 
        coworkingCenter->hasMeetingRooms = false;
    if (auxKitchen != 0)
        coworkingCenter->hasKitchen = true;
    else
        coworkingCenter->hasKitchen = false;
    if (auxAuditorium != 0)
        coworkingCenter->hasAuditorium = true;
    else
        coworkingCenter->hasAuditorium = false;
}

void coworkingCenterCpy(tCoworkingCenter *dst, tCoworkingCenter src) 
{    
    dst->id = src.id;
    strcpy(dst->name,src.name);
	strcpy(dst->address,src.address);
	strcpy(dst->city,src.city);
	dst->category = src.category;
	dst->type = src.type;
	dst->numSpaces = src.numSpaces;
	dst->price = src.price;
	dst->distanceFromCityCenter = src.distanceFromCityCenter;
	dst->hasMeetingRooms = src.hasMeetingRooms;
	dst->hasKitchen = src.hasKitchen;
	dst->hasAuditorium = src.hasAuditorium;
	dst->percentOccupation = src.percentOccupation;
}

int coworkingCenterCmp(tCoworkingCenter d1, tCoworkingCenter d2)
{
    int result = 0;
    	
    result= strcmp(d1.name,d2.name);
    if (result==0) 
    {
        result= strcmp(d1.address,d2.address);
        if (result==0)
        {
            result= strcmp(d1.city,d2.city);
            if (result==0)
            {
                if (d1.category > d2.category) 
                    result = 1;
                else if (d1.category < d2.category)
                    result = -1;
                else{
                    if (d1.type > d2.type)
                        result = 1;
                    else if (d1.type < d2.type)
                        result = -1;
                    else{
                        if (d1.numSpaces > d2.numSpaces)
                            result = 1;
                        else if (d1.numSpaces < d2.numSpaces)
                            result = -1;
                        else{
                            if (d1.price > d2.price)
                                result = 1;
                            else if (d1.price < d2.price)
                                result = -1;
                            else{
                                if (d1.distanceFromCityCenter > d2.distanceFromCityCenter)
                                    result = 1;
                                else if (d1.distanceFromCityCenter < d2.distanceFromCityCenter)
                                    result = -1;
                                else{
                                    if (d1.hasMeetingRooms > d2.hasMeetingRooms)
                                        result = 1;
                                    else if (d1.hasMeetingRooms < d2.hasMeetingRooms)
                                        result = -1;
                                    else{
                                        if (d1.hasKitchen > d2.hasKitchen)
                                            result = 1;
                                        else if (d1.hasKitchen < d2.hasKitchen)
                                            result = -1;
                                        else {
                                            if (d1.hasAuditorium > d2.hasAuditorium)
                                                result = 1;
                                            else if (d1.hasAuditorium < d2.hasAuditorium)
                                                result = -1;
                                            else{
                                                if (d1.percentOccupation > d2.percentOccupation)
                                                    result = 1;
                                                else if (d1.percentOccupation < d2.percentOccupation)
                                                    result = -1;
                                            }                                                
                                        }
                                    }
                                }
                            }
                        }
                    }
                }            
            }
        }
    }

    return result;
}

int computePoints(tCoworkingCenter coworkingCenter, float price, float distance)
{
    float points;
    
    points= 0.0;
    
    /* points for having gym or pool */
    if (coworkingCenter.hasKitchen || coworkingCenter.hasMeetingRooms)
        points += 5.0;
        
    /* points for being close to subway */
    if (coworkingCenter.hasAuditorium)
        points += 5.0;
        
    /* points for adjusted price */
    points += ((price - coworkingCenter.price) / price) * 100.0;

    /* points for centric location */
    points += ((distance - coworkingCenter.distanceFromCityCenter) / distance) * 100.0;

    return (int)(points + 0.5);
}

void coworkingCenterTableInit(tCoworkingCenterTable *coworkingCenterTable) {
	
	coworkingCenterTable->nCoworkingCenters= 0;
}

void coworkingCenterTableAdd(tCoworkingCenterTable *tabCoworkingCenters, tCoworkingCenter coworkingCenter, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new coworking center */
	if(tabCoworkingCenters->nCoworkingCenters>=MAX_COWORKINGCENTERS)
		*retVal = ERR_MEMORY;
		
	if (*retVal == OK) {
		/* Add the new coworking center to the end of the table */
		coworkingCenterCpy(&tabCoworkingCenters->table[tabCoworkingCenters->nCoworkingCenters],coworkingCenter);
		tabCoworkingCenters->nCoworkingCenters++;
	}
	
}

int coworkingCenterTableFind(tCoworkingCenterTable tabCoworkingCenters, tCoworkingCenterId id) {

	int idx = NO_COWORKINGCENTER;
	
	int i=0;
	while(i< tabCoworkingCenters.nCoworkingCenters && idx==NO_COWORKINGCENTER) {
		/* Check if the id is the same */
		if(id==tabCoworkingCenters.table[i].id)  {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void coworkingCenterTableSave(tCoworkingCenterTable tabCoworkingCenters, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=NULL;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all coworkers to the file */
        for(i=0;i<tabCoworkingCenters.nCoworkingCenters;i++) {
            getCoworkingCenterStr(tabCoworkingCenters.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void coworkingCenterTableLoad(tCoworkingCenterTable *tabCoworkingCenters, const char* filename, tError *retVal) {
	
	*retVal = OK;

	FILE *fin=NULL;
	char line[MAX_LINE];
	tCoworkingCenter newCoworkingCenter;
	
	/* Initialize the output table */
	coworkingCenterTableInit(tabCoworkingCenters);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the coworking centers */
		while(!feof(fin) && tabCoworkingCenters->nCoworkingCenters<MAX_COWORKINGCENTERS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getCoworkingCenterObject(line, &newCoworkingCenter);
				/* Add the new coworking center to the output table */
				coworkingCenterTableAdd(tabCoworkingCenters, newCoworkingCenter, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void coworkingCenterTableFilterByType(tCoworkingCenterTable tabCoworkingCenters, tCoworkingType type, tCoworkingCenterTable *result) {

	tError retVal;
	int i;
	coworkingCenterTableInit(result);
	for(i=0;i<tabCoworkingCenters.nCoworkingCenters;i++) {
		if (type == tabCoworkingCenters.table[i].type){
			coworkingCenterTableAdd(result, tabCoworkingCenters.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabCoworkingCenters which cannot have more than MAX_COWORKINGCENTERS*/
		}
	}

}

void coworkingCenterTableGetUrbanCoworkingCenters(tCoworkingCenterTable tabCoworkingCenters, tCoworkingCenterTable *result) {

	tError retVal;
	int i;
	coworkingCenterTableInit(result);
	for(i=0;i<tabCoworkingCenters.nCoworkingCenters;i++) {
		if (tabCoworkingCenters.table[i].hasAuditorium && 
            tabCoworkingCenters.table[i].distanceFromCityCenter < 2.0){
            coworkingCenterTableAdd(result, tabCoworkingCenters.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabCoworkingCenters which cannot have more than MAX_COWORKINGCENTERS*/
		}
	}
}

float coworkingCenterTableComputeAverageOccupation(tCoworkingCenterTable tabCoworkingCenter, char *city) {

	float avgOcc = 0.0;

	int totalSpaces=0, i;
	int occupiedSpaces = 0;
	
	for(i=0;i<tabCoworkingCenter.nCoworkingCenters;i++) {
		if (strcmp( tabCoworkingCenter.table[i].city, city ) == 0){
			occupiedSpaces += tabCoworkingCenter.table[i].numSpaces * tabCoworkingCenter.table[i].percentOccupation / 100.0;			
			totalSpaces += tabCoworkingCenter.table[i].numSpaces;
		}
	}
	if (totalSpaces>0)
		avgOcc = 100.0 * (float)occupiedSpaces / (float)totalSpaces;

	return avgOcc;
}

float coworkingCenterTableGetMaxSpacePrice(tCoworkingCenterTable tabCoworkingCenter){

	float maxPrice = 0.0;
	
	int i;
	
	for(i=0;i<tabCoworkingCenter.nCoworkingCenters;i++) {
		if (tabCoworkingCenter.table[i].price > maxPrice){
			maxPrice = tabCoworkingCenter.table[i].price;
		}
	}

	return maxPrice;
}

void coworkingCenterTableSelect(tCoworkingCenterTable tabCoworkingCenter, char *city, 
                        float price, float distance, int points,  
                        tCoworkingCenterTable *result)
{
    int i, p;

	coworkingCenterTableInit(result);

    for (i= 0; i < tabCoworkingCenter.nCoworkingCenters; i++)
    {
        if (strcmp(tabCoworkingCenter.table[i].city, city) == 0)
        {
            p= computePoints(tabCoworkingCenter.table[i], price, distance);
            if ( p >= points) 
            {
                    coworkingCenterCpy( &(result->table[ result->nCoworkingCenters ]), tabCoworkingCenter.table[i] );
                    result->nCoworkingCenters= result->nCoworkingCenters + 1;
            }
        }
    }
}

void coworkerRecommendation(tCoworker coworker, 
                            tCoworkingCenterTable coworkingCenters,
                            char *city, 
                            float price, float distance, int points,
                            tCoworkingCenterTable *result) 
{
	int i;
    tError retVal;
    tCoworkingCenterTable selectedCoworkingCenters;
        
    coworkingCenterTableSelect(coworkingCenters,city,price,distance,points,&selectedCoworkingCenters);
    coworkingCenterTableInit(result);

	for(i=0;i<selectedCoworkingCenters.nCoworkingCenters;i++) 
    {
		if (strcmp( coworker.birthCity, selectedCoworkingCenters.table[i].city ) != 0) {
			coworkingCenterTableAdd(result, selectedCoworkingCenters.table[i], &retVal);
		}
	}
}
