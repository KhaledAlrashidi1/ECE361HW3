/*
 * MLStree_starter.c - Starter source code file for MLS binary tree
 *
 * Author: Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 30-Oct-2020
 * 
 * This is starter source code for a binary tree ADT targeted to the
 * MLS standings app (ECE 361 hw3).  You need to develop the four
 * functions that say // ADD CODE HERE
 *
 * @note code is based on the BinarySearchTree example used during
 * the ECE 361 lectures 
 *
 * @note This is a reasonably sized subset of my binary tree ADT.  You
 * can build on this or go in your own direction.  You are the softare
 * engineer on this project.  If you decide to go your own way, it is 
 * in your benefit to preserve the structure of the prototypes in MLStree.harderr
 * because they are used in test_MLStree.c
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLStree.h"

 
 /*
 * createMLStree() - creates an MLS tree 
 *
 * @param	cont				Eastern or Western conference
 * @param	numTeams			Number of teams in the conference
 * @param 	numPlayoffTeams		Number of teams qualifying for playoffs
 *
 * @return	a pointer to the new MLStree if it succeeds.  NULL if it fails.
 * root node is NULL to start with because the tree has 0 nodes
 *
 */
 MLStreePtr_t createMLStree(MLSconf_t conf, int numTeams, int numPlayoffTeams) {
	MLStreePtr_t temp;
	
	// allocate space for the new tree
	temp = malloc(sizeof(MLStree_t));
	if (temp == NULL) {
		#if (_VERBOSE_ > 0)
			printf("ERROR(createMLSTree()): Could not allocate space for MLStree\n");
		#endif		
		return NULL;
	}
	
	// initialize the tree struct
	
	// ADD YOUR CODE HERE
     temp->root = NULL;
     temp->conf = conf;
     temp->numTeams = numTeams;
     temp->numPlayoffTeams = numPlayoffTeams;
	return temp;
}


/**
 * insert() - inserts a new team info record into the tree
 *
 * @param	tree	pointer to the MLStree to add the node to
 * @param	info	team info record to add
 * @return	pointer to the new tree node

 * @note Not a good idea to expose the data node but w/o a pointer to
 * root I don't see much harm and it could be useful...and, in fact, INFO
 * made use of it several times in my application
 */
TreeNodePtr_t insert(MLStreePtr_t tree, TeamInfo_t info) {
	TreeNodePtr_t	 tempNodePtr;		// pointer to a new node
	TreeNodePtr_t	 current, parent;	// pointers to traverse the tree
	
	// make sure there is a tree
	if (tree == NULL) {
		#if (_VERBOSE_ > 0)
			printf("ERROR(insert(): Not a valid MLS tree\n");
		#endif		
		return NULL;
	}
	
	// add and populate the new node to the tree
	
	// ADD YOUR CODE HERE
    tempNodePtr = (TreeNodePtr_t) malloc(sizeof(TreeNode_t));
        if (tempNodePtr == NULL)
            return NULL;
        tempNodePtr->info = info;
        //printf("%f\n", tempNodePtr->info.ppg);
        tempNodePtr->rightChild = NULL;
        tempNodePtr->leftChild = NULL;

        // insert the node based on the PPG (points per game) because PPG
        // is being used in the MLS 2020 season to determine the standings.
        // The binary tree should be built with the PPG of the leftChild <
        // PPG of its parent node and the PPG of the rightChild > the PPG of
        // its parent node.
        // Study the sample code provided to design this function

        // ADD YOUR CODE HERE
        //tree->root = (TreeNodePtr_t) malloc(sizeof(TreeNode_t));
        if(tree->root == NULL){
            tree->root = tempNodePtr;
        }
        else {
            current = tree->root;
            parent = NULL;
            
            while(1){
                parent = current;
                
                //go to left of the tree
                if(info.ppg < parent->info.ppg){
                    current = current->leftChild;
                    
                    
                    //insert to the left
                    if(current == NULL){
                        parent->leftChild = tempNodePtr;
                        return tempNodePtr;
                    }
                }  //go to right of the tree
                else {
                    current = current->rightChild;
                    
                    //insert to the right
                    if(current == NULL){
                        parent->rightChild = tempNodePtr;
                        return tempNodePtr;
                    }
                }
            }
        }
    return tempNodePtr;
}


/*
 * printStandings() - prints the standings (table)
 *
 * @param	tree	pointer to the MLStree to search
 *
 * @note teams that qualify for the playoffs get an x in the first column
 *
 * @note function should do a reverse in-order traversal since we want the
 * teams listed from highest PPG to lowest PPG.  
 * Try to mimic the Table entries shown in the hw3_results.txt file.  It's
 * going to take some playing around and likely lots of compiles to get the
 * formatting to where you like it.  That's why writing a makefile for this
 * assignment will be helpful. 
 */

void inOrder(TreeNodePtr_t root, int numTeams, int numPlayoffTeams)
{

    //printf("position is %d\n", position);
    if (root == NULL) // or if (!root)
         return;
    
    if(numTeams < numPlayoffTeams){
    inOrder(root->rightChild, numTeams, numPlayoffTeams);
    printf("  %2d   x  %35s     %d   %3.2f   %2d   %2d   %2d   %2d\n", numTeams++, root->info.name, root->info.pts, root->info.ppg, root->info.gp, root->info.win, root->info.loss, root->info.tie);
    inOrder(root->leftChild, numTeams, numPlayoffTeams);
    }
    else
    {
        inOrder(root->rightChild, numTeams, numPlayoffTeams);
        printf("  %2d      %35s     %d   %3.2f   %2d   %2d   %2d   %2d\n", numTeams++, root->info.name, root->info.pts, root->info.ppg, root->info.gp, root->info.win, root->info.loss, root->info.tie);
        inOrder(root->leftChild, numTeams, numPlayoffTeams);

    }
}


 void printStandings(MLStreePtr_t tree) {
     MLStreePtr_t 	current = tree;	// pointer to traverse the tree
     current->root = tree->root;
     current->numPlayoffTeams = tree->numPlayoffTeams;
     int numTeams = 1;

	// Study the sample code to get an idea of how to do a recursive
	// in-order traversal
	
	// ADD YOUR CODE HERE
     printf("   #                                     Club    PTS    PPG   GP    W    L    T\n" );
     inOrder(current->root, numTeams, current->numPlayoffTeams);
     printf("x - team has qualified for the playoffs\n\n");

 }

