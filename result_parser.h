#pragma once
#include "double_linked_list.h"
#include "consts.h"
#include "structs.h"
#include "my_string.h"
class ResultParser {
public:
	DoubleLinkedList<BlockListNode> blockList;
	myString output;

	SectionNode* getSectionFromIndex(int sectionIndex);
	BlockListNode* getBlockOfSection(int sectionIndex);

public:
	ResultParser();
	ResultParser(DoubleLinkedList<BlockListNode>& newBlockList);

	void const printOutFinalResult();

	void printOutAmountOfSections();

	void printOutAmountOfSelectorsOfSection(int sectionIndex);

	void printOutAmountOfAttributesOfSection(int sectionIndex);

	void printOutNSelectorOfSection(int selectorIndex, int sectionIndex);

	void printOutNAttributeOfSection(int sectionIndex, myString& attributeName);

	void printOutAmountOfAttributeOccurences(myString& attributeName);

	void printOutAmountOfSelectorOccurences(myString& selectorName);

	void printOutValueOfAttributeWithNameNForSelectorZ(myString& selectorName, myString& attributeName);

	void deleteSection(int sectionIndex, bool wantToAddToOutput);

	void deleteSectionWithProvidedAttributeName(int sectionIndex, myString& attributeName);

};