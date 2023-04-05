#include <iostream>
#include "double_linked_list.h"
#include "input_parser.h"
#include "my_string.h"
#include "result_parser.h"
#include "structs.h"
using namespace std;

template <typename StructNode> void clear_list_memory(StructNode* headNode) {
    while (headNode != nullptr && headNode->next != nullptr) {
        StructNode* tempNode = headNode->next;
        delete headNode;
        headNode = tempNode;
    }
}

void clear_memory(DoubleLinkedList<BlockListNode>& blockList) {
    BlockListNode* currentNode = blockList.headNode;
    bool wasFirstBlockSkipped = false;
    while (currentNode != NULL && currentNode->next != NULL) {
        for (size_t i = 0; i < currentNode->amountOfSectionsWithoutDeletions; i++) {
            clear_list_memory<AttributeListNode>(currentNode->sections[i].attributeList->headNode);
            delete currentNode->sections[i].attributeList;

            clear_list_memory<SelectorListNode>(currentNode->sections[i].selectorList->headNode);
            delete currentNode->sections[i].selectorList;
        }
        delete currentNode->sections;

        BlockListNode* tempBlockListNode = currentNode->next;

        if(wasFirstBlockSkipped)
            delete currentNode;
            
        currentNode = tempBlockListNode;
        wasFirstBlockSkipped = true;
    }
}

int main() {
    DoubleLinkedList<BlockListNode> blockList;
    BlockListNode firstBlock;
    blockList.addNewBlockToList(&firstBlock);
    InputParser inputParser = { blockList };

    char character;
    myString input = { "" };

    inputParser.getCSSInput();
    while (cin >> character >> noskipws) {
        inputParser.parseCommands(character, input, false);
    }
    if (input.str() != "") 
        inputParser.parseCommands(character, input, true);

    inputParser.resultParser.printOutFinalResult();
    
    clear_memory(blockList);

	return 0;
}