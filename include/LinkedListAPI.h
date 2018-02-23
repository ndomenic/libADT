/**
 * @file LinkedListAPI.h
 * @author Nicholas Domenichini <ndomenic@uoguelph.ca>
 * @brief Function definitions for a double linked list API
 **/

#ifndef LINKED_LIST_HEAD
#define LINKED_LIST_HEAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/**
 * Structure for a ListNode element in a List
 * Member 'data' is a pointer to an arbirtary piece of data
 * Member 'prev' is a pointer to the previous ListNode in the List
 * Member 'next' is a pointer to the next ListNode in the list
 **/
typedef struct ListNode {
	void * data;
	struct ListNode * prev;
	struct ListNode * next;
} ListNode;

/**
 * Structure for a List 
 * Member 'head' is a pointer to the first ListNode in the List
 * Member 'tail' is a pointer to the last ListNode in the List
 * Member 'length' is used to keep track of the length of the List
 * Member 'toString' is a function pointer to convert a piece of data into a string
 * Member 'destroyData' is a function pointer to destroy a piece of data
 * Member 'compareData' is a function pointer to compare to pieces of data
 **/
typedef struct List {
	ListNode * head;
	ListNode * tail;
	size_t length;
	char * (*printData)(void * data);
	void (*destroyData)(void * data);
	int (*compareData)(const void * a, const void * b);
} List;

/**
 * Structure for a List iterator
 * Member 'list' is a pointer to the List
 * Member 'currentNode' is a pointer to the current ListNode
 **/
typedef struct ListIterator {
	List * list;
	ListNode * currentNode;
} ListIterator;

/**
 * Function to create a new ListNode structure for insertion into a List data structure
 * @pre Parameter 'data' should exist as a preallocated item and be represented as a void pointer
 * @param 'data' is a pointer to an arbitrary piece of data to be added to the new ListNode struct
 * @return A pointer to a newly allocated ListNode structure with 'data' as its data member
 **/
ListNode * createListNode(void * data);

/**
 * Function to create a new List data structure. The function pointers passed to the
 * function tell the List how to deal with the arbitrary data it will be storing
 * @param 'printData' returns a string representing its 'data' parameter
 * @param 'destroyData' destroys the 'data' parameter passed to it
 * @param 'compareData' compares two sets of arbitrary data for equality
 * @return A newly allocated List structure pointer with the appropriate function pointers
 **/
List * createList(char * (*printData)(void * data), void (*destroyData)(void * data), int (*compareData)(const void * a, const void * b));

/**
 * Inserts an arbitrary piece of data into the front of the List data structure
 * @pre A valid List structure must exist for the data to be inserted into must exist
 * @param 'list' is a pointer to the List that the data will be inserted into
 * @param 'data' is a pointer to the data to be inserted
 * @return EXIT_SUCCESS is returned if the insertion is successful; EXIT_FAILURE on failure
 **/
int insertListFront(List * list, void * data);

/**
 * Inserts an arbitrary piece of data into the back of the List data structure
 * @pre A valid List structure must exist for the data to be inserted intomust exist
 * @param 'list' is a pointer to the List that the data will be inserted into
 * @param 'data' is a pointer to the data to be inserted
 * @return EXIT_SUCCESS is returned if the insertion is successful; EXIT_FAILURE on failure
 **/
int insertListBack(List * list, void * data);

/**
 * Inserts an arbitrary piece of data into a sorted List data structure
 * @pre A valid List structure must exist for the data to be inserted intomust exist
 * @param 'list' is a pointer to the List that the data will be inserted into
 * @param 'data' is a pointer to the data to be inserted
 * @return EXIT_SUCCESS is returned if the insertion is successful; EXIT_FAILURE on failure
 **/
int insertSortedList(List * list, void * data);

/**
 * Destroys the entire list data structure and all of its elements
 * @pre A valid List structure must exist to be destroyed must exist
 * @param 'list' is a pointer to the List that will be destroyed
 * @return EXIT_SUCCESS is returned if the destruction is successful; EXIT_FAILURE on failure
 **/
int destroyList(List * list);

/**
 * Removes the first element from the List structure
 * @pre A vali List structure from which data will be removed from must exist
 * @param 'list' is a pointer to the List that will be destroyed
 * @return EXIT_SUCCESS is returned if the removal is successful; EXIT_FAILURE on failure
 **/
int removeListFront(List * list);

/**
 * Removes the last element from the List structure
 * @pre A valid List structure from which data will be removed from must exist
 * @param 'list' is a pointer to the List that will be destroyed
 * @return EXIT_SUCCESS is returned if the removal is successful; EXIT_FAILURE on failure
 **/
int removeListBack(List * list);

/**
 * Removes the specified element from the List structure
 * @pre A valid List structure from which data will be removed from must exist
 * @param 'list' is a pointer to the List that will be destroyed
 * @param 'data' is a pointer to the data that is to be removed from the list
 * @return EXIT_SUCCESS is returned if the removal is successful; EXIT_FAILURE on failure
 **/
int removeFromList(List * list, void * data);

/**
 * Retrieves the data from the first element in the List Structure
 * @pre A valid List structure from which the data will be retreived from must exist
 * @param 'list' is a pointer to the List that will be accessed
 * @return A void pointer to the requested data; NULL on failure
 **/
void * getFromListFront(List * list);

/**
 * Retrieves the data from the last element in the List Structure
 * @pre A valid List structure from which the data will be retreived from must exist
 * @param 'list' is a pointer to the List that will be accessed
 * @return A void pointer to the requested data; NULL on failure
 **/
void * getFromListBack(List * list);

/**
 * Retrieves the index of the specified piece of data in the List
 * @pre A valid List structure from which the index will be retreived from must exist
 * @param 'list' is a pointer to the List that will be accessed
 * @param 'data' is a pointer to the data to be found in the List
 * @return The index of the requested piece of data in the List; -1 on failure
 **/
size_t getListIndex(List * list, void * data);

/**
 * Retrieves the piece of the data at the specified index in the List
 * @pre A valid List structure from which the data will be retreived from must exist
 * @param 'list' is a pointer to the List that will be accessed
 * @param 'index' is an index for the requested piece of information
 * @return A void pointer to the requested data; NULL on failure
 **/
void * getListData(List * list, size_t index);

/**
 * Searches for a piece of data in the List to see if it is contained within
 * @pre A valid List structure to be searched for the specified data must exist
 * @param 'list' is a pointer to the List that will be accessed
 * @param 'data' is a pointer to the data to be found in the List
 * @return True if the data is found in the List; false if not found or an error occurs
 **/
bool listContains(List * list, void * data);

/**
 * Converts all of the items in the List to a human readable string
 * @pre A valid List structure to be printed from must exist
 * @param 'list' is a pointer to the List that will be accessed
 * @return A newly allocated string regardless of list length; NULL on failure
 **/
char * printList(List * list);

/**
 * Converts all of the items in the List to a human readable string in reverse
 * @pre A valid List structure to be printed from must exist
 * @param 'list' is a pointer to the List that will be accessed
 * @return A newly allocated string regardless of list length; NULL on failure
 **/
char * printListReverse(List * list);

/**
 * Creates a statically allocated ListIterator structure for iterating through a List
 * @pre A valid List structure to be accessed for iteration must exist
 * @param 'list' is a pointer to the List that will be accessed
 * @return A new ListIterator structure pointing to the begining of the list; on failure, members are NULL
 **/
ListIterator createListIterator(List * list);

/**
 * Moves the iterator to the next element in the list
 * @pre A valid ListIterator strucutre must exist
 * @param 'iterator' the ListIterator structure to be modified
 * @return A pointer to the iterator's previous node's data; NULL on iteration failure
 **/
void * listIterateNext(ListIterator * iterator);

/**
 * Moves the iterator to the previous element in the list
 * @pre A valid ListIterator strucutre must exist
 * @param 'iterator' the ListIterator structure to be modified
 * @return A pointer to the iterator's previous node's data; NULL on iteration failure
 **/
void * listIteratePrev(ListIterator * iterator);

/**
 * Resets the specified ListIterator strucutre to the beginning of the list
 * @pre A valid ListIterator strucutre must exist
 * @param 'iterator' the ListIterator structure to be modified
 * @return EXIT_SUCCESS is returned if the reset is successful; EXIT_FAILURE on failure
 **/
int resetListIterator(ListIterator * iterator);

#endif