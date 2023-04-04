#include <iostream>
#include "double_linked_list.h"
#include "input_parser.h"
#include "my_string.h"
#include "result_parser.h"
#include "structs.h"
using namespace std;

int main() {
    DoubleLinkedList<BlockListNode> blockList;
    BlockListNode* firstBlock = new BlockListNode;
    firstBlock->next = nullptr;
    firstBlock->prev = nullptr;
    blockList.addNewBlockToList(firstBlock);

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
    
	return 0;
}