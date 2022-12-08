#include "data.h"
#include "api.h"

/* Request an option to the user and check its validity */
int getOption(int numOptions);

/* Define the main menu options type */
typedef enum {MAIN_MENU_LOAD, MAIN_MENU_SAVE, MAIN_MENU_COWORKER, 
                MAIN_MENU_COWORKINGCENTER, MAIN_MENU_STAT,
                MAIN_MENU_EXIT} tMainMenuOptions;

/* Define the coworkers management menu options type */
typedef enum {COWORKER_MENU_LIST, COWORKER_MENU_ADD, COWORKER_MENU_DEL, 
                COWORKER_MENU_CLEAR_ALL, COWORKER_MENU_SELECT_URBAN_COWORKERS,
                COWORKER_MENU_SATISFIED_COWORKERS,
                COWORKER_MENU_EXIT} tCoworkerMenuOptions;

/* Define the coworking centers management menu options type */
typedef enum {COWORKINGCENTER_MENU_LIST, COWORKINGCENTER_MENU_ADD, COWORKINGCENTER_MENU_TYPE, COWORKINGCENTER_MENU_URBAN_COWORKINGCENTERS,
                COWORKINGCENTER_COWORKERS_RECOMMENDATION,
                COWORKINGCENTER_MENU_EXIT} tCoworkingCenterMenuOptions;

/* Define the stats menu options type */
typedef enum {STAT_MENU_NUM_AVG_POINTS_PER_BOOKING, STAT_MENU_MAX_SATISFACTION_PER_AGE_INTERVAL,
                STAT_MENU_AVG_OCCUPATION, STAT_MENU_MAX_SPACE_PRICE,
                STAT_MENU_EXIT} tStatMenuOptions;

/* Print the main menu options */
void printMainMenuOptions();

/* Get the option for the main menu */
tMainMenuOptions getMenuOption();

/* Perform the actions for the main menu */
void mainMenu(tAppData *appData);

/* Print the coworker management menu options */
void printCoworkerMenuOptions();

/* Get the option for the coworker management menu */
tCoworkerMenuOptions getCoworkerMenuOption();

/* Perform the actions for the coworker management menu */
void coworkerMenu(tAppData *appData);

/* Print the coworking centers management menu options */
void printCoworkingCenterMenuOptions();

/* Get the option for the coworking centers management menu */
tCoworkingCenterMenuOptions getCoworkingCenterMenuOption();

/* Perform the actions for the coworking centers management menu */
void coworkingCenterMenu(tAppData *appData);

/* Print the stats menu options */
void printStatMenuOptions();

/* Get the option for the status menu */
tStatMenuOptions getStatMenuOption();

/* Perform the actions for the status menu */
void statMenu(tAppData appData);

/* Prints recommended coworking centers for each coworker. Coworking centers are based in the specified city
 * and have a desired price, distante to center and points. */
void allCoworkersRecommendation(tAppData appData,
                                char *city, float price, float distance, int points);