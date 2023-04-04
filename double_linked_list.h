#pragma once
#include "consts.h"
#include<iostream>
using namespace std;
template<typename StructNode> class DoubleLinkedList {
public:
    StructNode* headNode;
    int amountOfBlocks = 0;
public:
    DoubleLinkedList() {
        StructNode* head = new StructNode;
        head->prev = nullptr;
        head->next = nullptr;
        this->headNode = head;
    }

    DoubleLinkedList& operator=(const DoubleLinkedList& other) {
        this->headNode = other.headNode;
        this->amountOfBlocks = other.amountOfBlocks;
        return *this;
    }

    StructNode* getLastNode() {
        StructNode* lastNode = this->headNode;
        while (lastNode != nullptr && lastNode->next != nullptr) {
            lastNode = lastNode->next;
        }
        return lastNode;
    }

    void addNewBlockToList(StructNode* nextBlockListNode) {
        if (amountOfBlocks == 0) {
            this->headNode = nextBlockListNode;
            this->headNode->next = nullptr;
            this->headNode->prev = nullptr;
        }
        else {
            StructNode* lastNode = getLastNode();
            lastNode->next = nextBlockListNode;
            nextBlockListNode->prev = lastNode;
            nextBlockListNode->next = nullptr;

        }
        (this->amountOfBlocks)++;
    }

    void removeDuplicates() {
        StructNode* head = this->headNode;
        StructNode* lastNode = getLastNode();
        while (lastNode != nullptr) {
            StructNode* headNode = this->headNode;
            while (headNode != nullptr && headNode->next != nullptr && headNode != lastNode) {
                if (headNode->name == lastNode->name) {
                    if (headNode->prev != nullptr)
                        headNode->prev->next = headNode->next;
                    if (headNode->next != nullptr) {
                        headNode->next->prev = headNode->prev;
                    }
                    if (headNode == head) {
                        this->headNode = headNode->next;
                    }
                    headNode = headNode->next;
                }
                else {
                    headNode = headNode->next;
                }

            }
            lastNode = lastNode->prev;
        }
    }

    bool checkIfListIsNotEmpty() {
        StructNode* temp = this->headNode;
        while (temp != NULL) {
            if (temp->name.length() != 0) {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }

    //~DoubleLinkedList() {
    //    StructNode* currentNode = this->headNode;
    //    while (currentNode != nullptr) {
    //        StructNode* tempNode = currentNode->next;
    //        delete currentNode;
    //        currentNode = tempNode;
    //    }
    //    //delete this->headNode;
    //}

};