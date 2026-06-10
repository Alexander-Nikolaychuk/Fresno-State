/*
    CSci114_P5.cpp

    How to compile and run:
        g++ CSci114_P5.cpp -o P5.exe
        ./P5.exe

    The program expects an input file named requests.txt in the same folder.
    It writes the final free-memory block sizes to final_size.txt.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct FreeNode {
    int blockId;
    int size;
    FreeNode* next;

    FreeNode(int id, int s) {
        blockId = id;
        size = s;
        next = NULL;
    }
};

struct AllocNode {
    int requestId;
    int blockId;
    int size;
    AllocNode* next;

    AllocNode(int r, int b, int s) {
        requestId = r;
        blockId = b;
        size = s;
        next = NULL;
    }
};

void insertFreeSorted(FreeNode*& head, FreeNode* node) {
    if (node == NULL) return;
    node->next = NULL;

    if (head == NULL || node->size < head->size ||
        (node->size == head->size && node->blockId < head->blockId)) {
        node->next = head;
        head = node;
        return;
    }

    FreeNode* current = head;
    while (current->next != NULL &&
           (current->next->size < node->size ||
           (current->next->size == node->size && current->next->blockId < node->blockId))) {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
}

FreeNode* removeFreeByBlockId(FreeNode*& head, int blockId) {
    FreeNode* previous = NULL;
    FreeNode* current = head;

    while (current != NULL && current->blockId != blockId) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) return NULL;

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    current->next = NULL;
    return current;
}

FreeNode* removeBestFitBlock(FreeNode*& head, int requestedSize) {
    FreeNode* previous = NULL;
    FreeNode* current = head;

    while (current != NULL && current->size < requestedSize) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) return NULL;

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    current->next = NULL;
    return current;
}

void insertAllocationSorted(AllocNode*& head, AllocNode* node) {
    if (node == NULL) return;
    node->next = NULL;

    if (head == NULL || node->requestId < head->requestId) {
        node->next = head;
        head = node;
        return;
    }

    AllocNode* current = head;
    while (current->next != NULL && current->next->requestId < node->requestId) {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
}

AllocNode* removeAllocationByRequestId(AllocNode*& head, int requestId) {
    AllocNode* previous = NULL;
    AllocNode* current = head;

    while (current != NULL && current->requestId != requestId) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) return NULL;

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    current->next = NULL;
    return current;
}

void writeFinalSizes(FreeNode* freeHead) {
    ofstream outputFile("final_size.txt");
    if (!outputFile) {
        cout << "Unable to open final_size.txt for writing." << endl;
        return;
    }

    FreeNode* current = freeHead;
    while (current != NULL) {
        outputFile << current->size << endl;
        current = current->next;
    }

    outputFile.close();
}

void deleteFreeList(FreeNode*& head) {
    while (head != NULL) {
        FreeNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void deleteAllocList(AllocNode*& head) {
    while (head != NULL) {
        AllocNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    FreeNode* freeHead = NULL;
    AllocNode* allocHead = NULL;

    for (int i = 1; i <= 1024; i++) {
        insertFreeSorted(freeHead, new FreeNode(i, 1024));
    }

    ifstream inputFile("requests.txt");
    if (!inputFile) {
        cout << "Unable to open requests.txt." << endl;
        writeFinalSizes(freeHead);
        deleteFreeList(freeHead);
        deleteAllocList(allocHead);
        return 0;
    }

    char requestType;
    while (inputFile >> requestType) {
        if (requestType == 'A' || requestType == 'a') {
            int requestId, requestedSize;
            inputFile >> requestId >> requestedSize;

            if (requestedSize <= 0) {
                cout << "Request " << requestId << " cannot be served because the requested size is invalid." << endl;
                continue;
            }

            FreeNode* block = removeBestFitBlock(freeHead, requestedSize);
            if (block == NULL) {
                cout << "Request " << requestId << " cannot be served because no free block has enough memory." << endl;
                continue;
            }

            int blockId = block->blockId;
            block->size -= requestedSize;
            insertFreeSorted(freeHead, block);
            insertAllocationSorted(allocHead, new AllocNode(requestId, blockId, requestedSize));

            cout << requestedSize << " bytes have been allocated at block "
                 << blockId << " for request " << requestId << endl;
        } else if (requestType == 'R' || requestType == 'r') {
            int requestId;
            inputFile >> requestId;

            AllocNode* allocation = removeAllocationByRequestId(allocHead, requestId);
            if (allocation == NULL) {
                cout << "Request " << requestId << " cannot be released because it was not found." << endl;
                continue;
            }

            FreeNode* block = removeFreeByBlockId(freeHead, allocation->blockId);
            if (block == NULL) {
                cout << "Request " << requestId << " cannot be released because block "
                     << allocation->blockId << " was not found." << endl;
                delete allocation;
                continue;
            }

            block->size += allocation->size;
            insertFreeSorted(freeHead, block);

            cout << allocation->size << " bytes have been returned backed to block "
                 << allocation->blockId << " for request " << allocation->requestId << endl;

            delete allocation;
        } else {
            string restOfLine;
            getline(inputFile, restOfLine);
            cout << "Unknown request type " << requestType << ". Request skipped." << endl;
        }
    }

    inputFile.close();
    writeFinalSizes(freeHead);
    deleteFreeList(freeHead);
    deleteAllocList(allocHead);

    return 0;
}
