/**
 * @file LinkedListAPI.c
 * @author Nicholas Domenichini <ndomenic@uoguelph.ca>
 * @brief Function implementations for a double linked list API
 **/

#include "LinkedListAPI.h"

ListNode * createListNode(void * data) {
    ListNode * node = malloc(sizeof(ListNode));
    if (!node) {
    	return NULL;
    }

    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

List * createList(char * (*printData)(void * data), void (*destroyData)(void * data), int (*compareData)(const void * a, const void * b)) {
	List * list = malloc(sizeof(List));
	if (!list) {
		return NULL;
	}

	assert(printData);
	assert(destroyData);
	assert(compareData);

	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
	list->printData = printData;
	list->destroyData = destroyData;
	list->compareData = compareData;

	return list;
}

int insertListFront(List * list, void * data) {
    if (!list) {
        return EXIT_FAILURE;
    }

    ListNode * node = createListNode(data);
    if (!node) {
    	return EXIT_FAILURE;
    }

    if (!list->head && !list->tail) {
        list->head = node;
        list->tail = node;
        list->length++;
        return EXIT_SUCCESS;
    }

    node->next = list->head;
    list->head->prev = node;
    list->head = node;
    list->length++;

    return EXIT_SUCCESS;
}

int insertListBack(List * list, void * data) {
    if (!list) {
        return EXIT_FAILURE;
    }

    ListNode * node = createListNode(data);
    if (!node) {
    	return EXIT_FAILURE;
    }

    if (!list->head && !list->tail) {
        list->head = node;
        list->tail = node;
        list->length++;
        return EXIT_SUCCESS;
    }

    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
    list->length++;

    return EXIT_SUCCESS;
}

int insertSortedList(List * list, void * data) {
	if (!list) {
        return EXIT_FAILURE;
    }

    if (!list->head && !list->tail) {
        return insertListFront(list, data);
    }

    if (list->compareData(data, getFromListFront(list)) < 0) {
        return insertListFront(list, data);
    }

    if (list->compareData(data, getFromListBack(list)) >= 0) {
        return insertListBack(list, data);
    }

    ListNode * node = createListNode(data);
    if (!node) {
    	return EXIT_FAILURE;
    }
    ListNode * temp = list->head;

    while (temp) {
    	if (list->compareData(node->data, temp->data) > 0 && list->compareData(node->data, temp->next->data) <= 0) {
            node->next = temp->next;
            temp->next->prev = node;
            node->prev = temp;
            temp->next = node;
            list->length++;
            return EXIT_SUCCESS;
        }
    	temp = temp->next;
    }

    free(node);
    node = NULL;

    return EXIT_FAILURE;
}

int destroyList(List * list) {
    if (!list) {
        return EXIT_FAILURE;
    }

    ListNode * temp = list->head;

    while (list->head) {
        temp = list->head;
        list->head = list->head->next;

        temp->next = NULL;
        temp->prev = NULL;
        list->destroyData(temp->data);
        free(temp);
    }

    free(list);
    list = NULL;

    return EXIT_SUCCESS;
}

int removeListFront(List * list) {
	if (!list || list->length == 0) {
        return EXIT_FAILURE;
    }

    ListNode * temp = list->head;
    list->head = temp->next;
    if (list->head) {
    	list->head->prev = NULL;
    }

    list->destroyData(temp->data);
    free(temp);
    temp = NULL;

    return EXIT_SUCCESS;
}

int removeListBack(List * list) {
	if (!list || list->length == 0) {
        return EXIT_FAILURE;
    }

    ListNode * temp = list->tail;
    list->head = temp->prev;
    if (list->tail) {
    	list->tail->next = NULL;
    }

    list->destroyData(temp->data);
    free(temp);
    temp = NULL;

    return EXIT_SUCCESS;
}

int removeFromList(List * list, void * data) {
    /*If the list does not exist, if the list is empty, or if the data to be deleted is NULL, then return 0*/
    if (!list || !data || list->length == 0) {
        return EXIT_FAILURE;
    }

    ListNode * temp = list->head;

    /*Loop through the list until the data in the current node matches the data to be deleted*/
    while (temp) {
        if (list->compareData(temp->data, data) == 0) {
            if (temp == list->head){
                list->head = temp->next;
                if (list->head) {
                    list->head->prev = NULL;
                }
            } else if (temp == list->tail) {
                list->tail = temp->prev;
                if (list->tail) {
                    list->tail->next = NULL;
                }
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            list->destroyData(temp->data);
            free(temp);
            temp = NULL;

            return EXIT_SUCCESS;
        }
        temp = temp->next;
    }

    return EXIT_FAILURE;
}

void * getFromListFront(List * list) {
    if (!list || list->length == 0) {
        return NULL;
    }

    return list->head->data;
}

void * getFromListBack(List * list) {
    if (!list || list->length == 0) {
        return NULL;
    }

    return list->tail->data;
}

size_t getListIndex(List * list, void * data) {
	if (!list || list->length == 0 || !data) {
        return -1;
    }

    ListNode * temp = list->head;
    size_t counter = 0;

    while (temp) {
    	if (list->compareData(temp->data, data) == 0) {
    		return counter;
    	}

    	counter++;
    	temp = temp->next;
    }

    return -1;
}

void * getListData(List * list, size_t index) {
	if (!list || list->length == 0 || index < 0) {
        return NULL;
    }

    ListNode * temp = list->head;
    size_t counter = 0;

    while (temp) {
    	if (counter == index) {
    		return temp->data;
    	}

    	counter++;
    	temp = temp->next;
    }


    return NULL;
}

bool listContains(List * list, void * data) {
	if (!list || list->length == 0 || !data) {
        return false;
    }

    ListNode * temp = list->head;
    while (temp) {
    	if (list->compareData(temp->data, data) == 0) {
    		return true;
    	}

    	temp = temp->next;
    }

    return false;
}

char * printList(List * list) {
	char * str = malloc(sizeof(char));
	if (!str) {
		return NULL;
	}
	strcpy(str, "");
	char * tempPtr, * tempStr;

	ListNode * temp = list->head;
	while(temp) {
		tempStr = list->printData(temp->data);

		tempPtr = realloc(str, sizeof(char) * (strlen(str) + strlen(tempStr)));
		if (!tempPtr) {
			free(str);
			return NULL;
		}
		str = tempPtr;

		strcat(str, tempStr);
		free(tempStr);

		temp = temp->next;
	}

	return str;
}

char * printListReverse(List * list) {
	char * str = malloc(sizeof(char));
	if (!str) {
		return NULL;
	}
	strcpy(str, "");
	char * tempPtr, * tempStr;

	ListNode * temp = list->tail;
	while(temp) {
		tempStr = list->printData(temp->data);

		tempPtr = realloc(str, sizeof(char) * (strlen(str) + strlen(tempStr)));
		if (!tempPtr) {
			free(str);
			return NULL;
		}
		str = tempPtr;

		strcat(str, tempStr);
		free(tempStr);

		temp = temp->prev;
	}

	return str;
}

ListIterator createListIterator(List * list) {
	ListIterator iterator;

	if (!list) {
		iterator.list = NULL;
		iterator.currentNode = NULL;
	} else {
		iterator.list = list;
		iterator.currentNode = list->head;
	}

	return iterator;
}

void * listIterateNext(ListIterator * iterator) {
	if (!iterator || !iterator->currentNode || !iterator->currentNode->next) {
		return NULL;
	}

	ListNode * temp = iterator->currentNode;
	iterator->currentNode = iterator->currentNode->next;
	return temp->data;
}

void * listIteratePrev(ListIterator * iterator) {
	if (!iterator || !iterator->currentNode || !iterator->currentNode->prev) {
		return NULL;
	}

	ListNode * temp = iterator->currentNode;
	iterator->currentNode = iterator->currentNode->prev;
	return temp->data;
}

int resetListIterator(ListIterator * iterator) {
	if (!iterator) {
		return EXIT_FAILURE;
	}

	iterator->currentNode = iterator->list->head;
	return EXIT_SUCCESS;
}
