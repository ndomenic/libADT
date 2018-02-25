/**
 * @file HashTableAPI.c
 * @author Nicholas Domenichini <ndomenic@uoguelph.ca>
 * @brief Function implementations for a hash table
 **/

#include "HashTableAPI.h"

HTableNode * createHTableNode(int key, void * data) {
    HTableNode * node = malloc(sizeof(HTableNode));
    if (!node) {
    	return NULL;
    }

    node->next = NULL;
    node->key = key;
    node->data = data;

    return node;
}

HTable * createTable(size_t size, char * (*printData)(void * data), void (*destroyData)(void * data), int (*hashData)(size_t tableSize, int key)) {
    HTable * hTable = malloc(sizeof(HTable));
    if (!hTable) {
    	return NULL;
    }

    hTable->table = malloc(sizeof(HTableNode*) * size);
    if (!hTable->table) {
    	free(hTable);
    	return NULL;
    }

    for (int i = 0; i < hTable->size; ++i) {
    	hTable->table[i] = NULL;
    }

    assert(printData);
    assert(destroyData);
    assert(hashData);

    hTable->size = size;
    hTable->printData = printData;
    hTable->destroyData = destroyData;
    hTable->hashData = hashData;

    return hTable;
}

int insertData(HTable * hTable, int key, void * data) {
    if (!hTable) {
        return EXIT_FAILURE;
    }

    int index = hTable->hashData(hTable->size, key);

    if (hTable->table[index]) {
        HTableNode * temp = hTable->table[index];
        while (temp) {
            if (hTable->table[index]->key == key){
                hTable->destroyData(temp->data);
                temp->data = data;

                return EXIT_SUCCESS;
            }
            temp = temp->next;
        }
        temp->next = createHTableNode(key, data);
        return EXIT_SUCCESS;
    }

    hTable->table[index] = createHTableNode(key, data);
    return EXIT_SUCCESS;
}

int destroyTable(HTable * hTable) {
    if (!hTable) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < hTable->size; ++i) {
        HTableNode * temp = hTable->table[i];

        while (temp) {
            hTable->destroyData(temp->data);
            HTableNode * prev = temp;
            temp = temp->next;
            free(prev);
            prev = NULL;
        }
    }

    free(hTable->table);
    hTable->table = NULL;

    free(hTable);
    hTable = NULL;

    return EXIT_SUCCESS;
}

int removeData(HTable * hTable, int key) {
    if (!hTable) {
        return EXIT_FAILURE;
    }

    int index = hTable->hashData(hTable->size, key);

    if (hTable->table[index]) {
        HTableNode * temp = hTable->table[index];

        while (temp) {
            HTableNode * prev = temp;

            if (temp->key == key) {
                if (!prev) {
                    hTable->table[index] = temp->next;
                } else {
                    prev->next = temp->next;
                }

                hTable->destroyData(temp->data);
                free(temp);

                return EXIT_SUCCESS;
            }

            temp = temp->next;
        }
    }

    return EXIT_FAILURE;
}

void * lookupData(HTable * hTable, int key) {
    if (!hTable) {
        return NULL;
    }

    int index = hTable->hashData(hTable->size, key);

    if (!hTable->table[index]) {
        return NULL;
    }

    HTableNode * temp = hTable->table[index];

    while (temp) {
        if (temp->key == key) {
            return temp->data;
        }
        temp = temp->next;
    }

    return NULL;
}

char * printList(HTable * hTable) {
    char * str = malloc(sizeof(char));
    if (!str) {
        return NULL;
    }
    strcpy(str, "");
    char * tempPtr, * tempStr;

    for (int i = 0; i < hTable->size; ++i) {
        HTableNode * temp = hTable->table[i];

        while (temp) {
            tempStr = hTable->printData(temp->data);

            tempPtr = realloc(str, sizeof(char) * (strlen(str) + strlen(tempStr) + 2));
	        if (!tempPtr) {
	            free(str);
	            return NULL;
	        }
	        str = tempPtr;

	        strcat(str, tempStr);
	        free(tempStr);

	        temp = temp->next;
        }
    }

    return str;
}