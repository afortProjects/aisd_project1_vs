#pragma once
#include "double_linked_list.h"
#include "consts.h"
#include "my_string.h"

struct SelectorListNode {
    SelectorListNode* prev = nullptr;
    SelectorListNode* next = nullptr;
    myString name = { "" };
};

struct AttributeListNode {
    AttributeListNode* prev = nullptr;
    AttributeListNode* next = nullptr;
    myString name = { "" };
    myString value = { "" };
};

struct SectionNode {
    DoubleLinkedList<SelectorListNode>* selectorList = nullptr;
    DoubleLinkedList<AttributeListNode>* attributeList = nullptr;
    bool wasDeleted = false;
};

struct BlockListNode {
    BlockListNode* prev = nullptr;
    BlockListNode* next = nullptr;
    SectionNode* sections = new SectionNode[AMOUNT_OF_BLOCKS_IN_BLOCK_LIST];
    int currentAmountOfSections = 0;
    int amountOfSectionsWithoutDeletions = 0;
};


