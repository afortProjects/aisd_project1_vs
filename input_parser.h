#pragma once
#include "result_parser.h"
#include "double_linked_list.h"
#include "structs.h"
#include "my_string.h"

class InputParser {
public:
	DoubleLinkedList<BlockListNode> blockList;
	ResultParser resultParser;
public:
	InputParser(DoubleLinkedList<BlockListNode>& newBlockList);

	void getCSSInput();

	void parseCommands(char& character, myString& input, bool flag);

	static bool isCharArrayANumber(const char* arr);

	static void addSelectors(myString& selectorInput, DoubleLinkedList<SelectorListNode>* selectorList);

	static void addAttributes(myString& attributeInput, DoubleLinkedList<AttributeListNode>* attributeList);

	static void getCommandParameters(myString& input, myString& firstParameter, myString& secondParameter, myString& thirdParameter);
};