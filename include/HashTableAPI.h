/**
 * @file HashTableAPI.h
 * @author Nicholas Domenichini <ndomenic@uoguelph.ca>
 * @brief Function definitions for a hash table
 **/

#ifndef HASH_TABLE_HEAD
#define HASH_TABLE_HEAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/**
 * Structure for a HTableNode element in a List
 * Member 'key' is the key for the current data element
 * Member 'data' is a pointer to an arbirtary piece of data
 * Member 'next' is a pointer to the next HTableNode in the collision list
 **/
typedef struct HTableNode {
	int key;
	void * data;
	struct HTableNode * next;
} HTableNode;

/**
 * Structure for a HTable
 * Member 'size' is the size of the hash table
 * Member 'table' is a dynamically allocated array of HTableNodes 
 * Member 'printData' is a function pointer to convert a piece of data into a string
 * Member 'destroyData' is a function pointer to destroy a piece of data
 * Member 'hashData' is a function pointer to hash a piece of data
 **/
typedef struct HTable {
	size_t size;
	HTableNode ** table;
	char * (*printData)(void * data);
	void (*destroyData)(void * data);
	int (*hashData)(size_t tableSize, int key);
} HTable;

/**
 * Function to create a new HTableNode structure for insertion into a HTable data structure
 * @pre Parameter 'data' should exist as a preallocated item and be represented as a void pointer
 * @param 'key' is an integer representing the key for the data appropriately
 * @param 'data' is a pointer to an arbitrary piece of data to be added to the new ListNode struct
 * @return A pointer to a newly allocated HTableNode structure with 'data' as its data member and 'key' as the key
 **/
HTableNode * createHTableNode(int key, void * data);

/**
 * Function to create a new HTable data structure. The function pointers passed to the
 * function tell the HTable how to deal with the arbitrary data it will be storing
 * @param 'printData' returns a string representing its 'data' parameter
 * @param 'destroyData' destroys the 'data' parameter passed to it
 * @param 'hashData' returns an index for where the key's data should be stored in the table
 * @return A newly allocated List structure pointer with the appropriate function pointers
 **/
HTable * createTable(size_t size, char * (*printData)(void * data), void (*destroyData)(void * data), int (*hashData)(size_t tableSize, int key));

/**
 * Inserts an arbitrary piece of data into the HTable data structure
 * @pre A valid HTable structure must exist for the data to be inserted into
 * @param 'hTable' is a pointer to the HTable that the data will be inserted into
 * @param 'key' is an integer representing the data to be inserting
 * @param 'data' is a pointer to the data to be inserted
 * @return EXIT_SUCCESS is returned if the insertion is successful; EXIT_FAILURE on failure
 **/
int insertData(HTable * hTable, int key, void * data);

/**
 * Destroys the entire hash table data structure and all of its elements
 * @pre A valid HTable structure must exist to be destroyed
 * @param 'hTable' is a pointer to the HTable that will be destroyed
 * @return EXIT_SUCCESS is returned if the destruction is successful; EXIT_FAILURE on failure
 **/
int destroyTable(HTable * hTable);

/**
 * Removes the specified element from the HTable structure
 * @pre A valid HTable structure from which data will be removed from must exist
 * @param 'hTable' is a pointer to the HTable to remove the data from
 * @param 'key' is an integer representing the data to be removed
 * @return EXIT_SUCCESS is returned if the removal is successful; EXIT_FAILURE on failure
 **/
int removeData(HTable * hTable, int key);

/**
 * Retrieves the specified data from HTable Structure
 * @pre A valid HTable structure from which the data will be retreived from must exist
 * @param 'hTable' is a pointer to the HTable that will be accessed
 * @param 'key' is an integer representing the data to be accessed
 * @return A void pointer to the requested data; NULL on failure
 **/
void * lookupData(HTable * hTable, int key);

/**
 * Converts all of the items in the HTable to a human readable string
 * @pre A valid HTable structure to be printed from must exist
 * @param 'hTable' is a pointer to the HTable that will be accessed
 * @return A newly allocated string regardless of htable size; NULL on failure
 **/
char * printTable(HTable * hTable);

#endif