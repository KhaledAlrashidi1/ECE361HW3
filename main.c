/**
 * test_MLStree.c - Source code file for a simple test program for the MLS binary tree
 *
 * Author: Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 30-Oct-2020
 *
 * This is source code for testing my MLStree binary tree ADT that is
 * used in the MLS standings app (ECE 361 hw3)
 *
 * @note you may have to make some modifications to tailor the test program
 * to your binary tree ADT
 *
 * @note this program tests the three functions you need to create in your
 * binary tree ADT.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLStree.h"
#include "MLSapp_Helpers.h"


// main program
int main(void) {
    
    FILE *titlefile;
    char title[256];
    TeamInfoPtr_t InfoPtr = (TeamInfoPtr_t) malloc(sizeof(TeamInfo_t));
    TeamInfo_t info, winnerTeam;
    InfoPtr = &info;
    TeamInfoPtr_t winnerTeamPtr = &winnerTeam;
    MLStreePtr_t west_conf = createMLStree(WEST, 12, 8);
    MLStreePtr_t east_conf = createMLStree(EAST, 14, 10);
    int counter = 0;
    float highestPPG = 0;
    
    printf("Welcome to the MLS app for this unprecedented MLS 2020 season\n\n");
    printf("Reading team info file ./MLS2020.txt...\n");
    if((titlefile = fopen("MLS2020.txt", "r")) == NULL)
        perror("Opening title file");
    else {
        while (fgets(title, 256, titlefile) != NULL){
                title[strlen(title) - 1] = 0; // trim off newline character
                //printf("%3d: \"%s\"\n", ++counter, title);
                if(title[0] == '/')
                    printf("%s\n", title);
            
                else
                {
                    parseTeamInfo(title, InfoPtr);
                    
                    if(highestPPG < info.ppg)
                    {
                        highestPPG = info.ppg;
                        winnerTeam = info;
                    }
                    
                    if(info.conf == 0)
                    {
                        printf("Added %s to Eastern Conference\n", info.name);
                        insert(east_conf, info);
                        ++counter;
                    }
                    else
                    {
                        printf("Added %s to Western Conference\n", info.name);
                        insert(west_conf, info);
                        ++counter;
                    }
                }
            }
            printf("\n");
        // fgets() returned NULL: either EOF or an error occurred
        // if (feof(titlefile))
            //printf("Total: %d titles.\n", counter);
    }

    
    printf("The current standings are:\n");
    printf("Eastern Conference:\n");
    printStandings(east_conf);
    
    printf("Western Conference:\n");
    printStandings(west_conf);
    
    printf("\nCongratulations the MLS 2020 Shield winner - %s", winnerTeam.name);
    printTeamInfo(winnerTeamPtr);
    printf("\nMLS 25 yrs and counting...\n");
    
}

