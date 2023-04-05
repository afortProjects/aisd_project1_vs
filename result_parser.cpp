#include "result_parser.h"
#include<iostream>
ResultParser::ResultParser() {}
ResultParser::ResultParser(DoubleLinkedList<BlockListNode>& newBlockList) : blockList(newBlockList), output(myString {""}) {}

SectionNode* ResultParser::getSectionFromIndex(int sectionIndex) {
    int counter = 0;
    BlockListNode* blockListTemp = this->blockList.headNode;
    SectionNode* desiredSection = new SectionNode;

    while (blockListTemp != nullptr) {
        for (int i = 0; i < blockListTemp->amountOfSectionsWithoutDeletions; i++) {
            if (blockListTemp->sections[i].wasDeleted == false) {
                if (sectionIndex == counter) {
                    desiredSection = &(blockListTemp->sections[i]);
                    return desiredSection;
                }
                counter++;
            }

        }
        blockListTemp = blockListTemp->next;
    }
    return nullptr;
}

void const ResultParser::printOutFinalResult() {
    //Flag is used to not write \n many times in a row
    bool flag = false;
    for (size_t i = 0; i < this->output.length(); i++) {
        if (this->output[i] != '\n' && this->output[i] != '|' && this->output[i] != '\t') {
            std::cout << this->output[i];
            flag = true;
        }
        else if (this->output[i] == '|' && i != 0 && flag) {
            std::cout << '\n';
            flag = false;
        }
    }
}

BlockListNode* ResultParser::getBlockOfSection(int sectionIndex) {
    int counter = 0;
    BlockListNode* blockListTemp = this->blockList.headNode;

    while (blockListTemp != NULL) {
        for (int i = 0; i < blockListTemp->amountOfSectionsWithoutDeletions; i++) {
            if (blockListTemp->sections[i].wasDeleted == false) {
                if (sectionIndex == counter) {
                    return blockListTemp;
                }
                counter++;
            }
        }
        blockListTemp = blockListTemp->next;
    }
    return nullptr;
}

void ResultParser::printOutAmountOfSections() {
    int counter = 0;
    BlockListNode* temp = blockList.headNode;
    
    while (temp != NULL) {
        counter += temp->currentAmountOfSections;
        temp = temp->next;
    }

    myString returnValue = { "? == " };
    returnValue += counter;
    this->output += returnValue;
    this->output += '|';
}

void ResultParser::printOutAmountOfSelectorsOfSection(int sectionIndex) {
    int counter = 0;
    SectionNode* tempSection = getSectionFromIndex(sectionIndex);

    myString defaultValue = { "" };
    defaultValue += sectionIndex+1;
    defaultValue += { ",S,? == 0" };

    if (tempSection == nullptr) return;
    if (tempSection->wasDeleted == true) return;

    DoubleLinkedList<SelectorListNode>* tempList = tempSection->selectorList;
    if (tempList == nullptr) {
        this->output += defaultValue;
        this->output += '|';
        return;
    }

    SelectorListNode* temp = tempList->headNode;
    if (temp == nullptr) {
        this->output += defaultValue;
        this->output += '|';
        return;
    }

    if (temp != NULL) {
        while (temp != NULL) {
            if (temp->name.length() != 0)
                counter++;
            temp = temp->next;
        }
    }

    myString returnValue = { "" };
    returnValue += sectionIndex + 1;
    returnValue += { ",S,? == " };
    returnValue += counter;

    this->output += returnValue;
    this->output += '|';
}

void ResultParser::printOutAmountOfAttributesOfSection(int sectionIndex) {
    int counter = 0;
    myString returnValue = { "" };
    SectionNode* tempSection = getSectionFromIndex(sectionIndex);

    if (tempSection == nullptr) return;
    if (tempSection->wasDeleted == true) return;

    DoubleLinkedList<AttributeListNode>* tempList = tempSection->attributeList;
    if (tempList == nullptr) return;

    tempList->removeDuplicates();

    AttributeListNode* temp = tempList->headNode;
    if (temp == nullptr) return;

    while (temp != NULL) {
        if (temp->name.length() != 0 || temp->value.length() != 0)
            counter++;
        temp = temp->next;
    }

    if (counter != 0) {
        returnValue += sectionIndex + 1;
        returnValue += { ",A,? == " };
        returnValue += counter;
        this->output += returnValue;
        this->output += '|';
    }
}

void ResultParser::printOutNSelectorOfSection(int selectorIndex, int sectionIndex) {
    int counter = 0;
    myString returnValue = { "" };
    SectionNode* tempSection = getSectionFromIndex(sectionIndex);

    if (tempSection == nullptr) return;
    DoubleLinkedList < SelectorListNode >* tempList = tempSection->selectorList;

    if (tempList == nullptr) return;

    SelectorListNode* temp = tempList->headNode;
    if (temp == nullptr) return;

    if (temp != NULL) {
        while (temp != NULL && counter != selectorIndex) {
            temp = temp->next;
            counter++;
        }
    }

    if (counter == selectorIndex && temp != NULL && temp->name.length() != 0) {
        returnValue += sectionIndex+1;
        returnValue += { ",S," };
        returnValue += selectorIndex+1;
        returnValue += {" == "};
        returnValue += temp->name;
        this->output += returnValue;
        this->output += '|';

    }
}

void ResultParser::printOutNAttributeOfSection(int sectionIndex, myString& attributeName) {
    SectionNode* tempSection = getSectionFromIndex(sectionIndex);

    if (tempSection == nullptr) return;

    DoubleLinkedList<AttributeListNode>* tempList = tempSection->attributeList;
    if (tempList == nullptr) return;

    tempList->removeDuplicates();

    AttributeListNode* temp = tempList->headNode;
    if (temp == nullptr) return;

    if (temp != NULL) {
        while (temp != NULL && temp->name != attributeName) {
            temp = temp->next;
        }
    }

    if (temp != NULL && temp->name == attributeName && temp->value.length() != 0) {
        myString returnValue = { "" };
        returnValue += sectionIndex+1;
        returnValue += { ",A," };
        returnValue += attributeName;
        returnValue += {" == "};
        returnValue += temp->value.str();
        this->output += returnValue;
        this->output += '|';
    }
}

void ResultParser::printOutAmountOfAttributeOccurences(myString& attributeName) {
    int counter = 0;
    myString returnValue = { "" };
    BlockListNode* temp = this->blockList.headNode;

    while (temp != NULL) {
        for (int i = 0; i < temp->amountOfSectionsWithoutDeletions; i++) {
            SectionNode currentSection = temp->sections[i];
            if (currentSection.wasDeleted == false) {
                currentSection.attributeList->removeDuplicates();

                AttributeListNode* currentAttributeListTemp = currentSection.attributeList->getLastNode();
                while (currentAttributeListTemp != NULL) {
                    if (currentAttributeListTemp->name == attributeName) {
                        counter++;
                    };
                    currentAttributeListTemp = currentAttributeListTemp->prev;
                }
            }
        }
        temp = temp->next;
    }

    returnValue += attributeName;
    returnValue += { ",A,? == " };
    returnValue += counter;
    this->output += returnValue;
    this->output += '|';

}

void ResultParser::printOutAmountOfSelectorOccurences(myString& selectorName) {
    BlockListNode* temp = this->blockList.headNode;
    SectionNode currentSection;
    int counter = 0;

    while (temp != NULL) {
        for (int i = 0; i < temp->amountOfSectionsWithoutDeletions; i++) {
            currentSection = temp->sections[i];
            if (currentSection.wasDeleted == false) {
                SelectorListNode* currentSelectorListTemp = currentSection.selectorList->getLastNode();
                while (currentSelectorListTemp != NULL) {
                    if (currentSelectorListTemp->name == selectorName) { 
                        counter++; 
                        break; 
                    };
                    currentSelectorListTemp = currentSelectorListTemp->prev;
                }
            }

        }
        temp = temp->next;
    }

    myString returnValue = { "" };
    returnValue += selectorName;
    returnValue += { ",S,? == " };
    returnValue += counter;

    this->output += returnValue;
    this->output += '|';

}

void ResultParser::printOutValueOfAttributeWithNameNForSelectorZ(myString& selectorName, myString& attributeName) {
    BlockListNode* temp = blockList.getLastNode();

    while (temp != NULL) {
        for (int i = temp->amountOfSectionsWithoutDeletions - 1; i >= 0; i--) {
            if (temp->sections[i].wasDeleted == false) {
                SelectorListNode* currentSelectorListTemp = temp->sections[i].selectorList->getLastNode();
                temp->sections[i].attributeList->removeDuplicates();
                AttributeListNode* currentAttributeListTemp = temp->sections[i].attributeList->getLastNode();

                bool selectorFlag = false;
                while (currentSelectorListTemp != NULL) {
                    if (currentSelectorListTemp->name == selectorName) {
                        selectorFlag = true;
                        break;
                    }
                    currentSelectorListTemp = currentSelectorListTemp->prev;
                }

                bool attributeFlag = false;

                while (currentAttributeListTemp != NULL) {
                    if (currentAttributeListTemp->name == attributeName) { attributeFlag = true; break; };
                    currentAttributeListTemp = currentAttributeListTemp->prev;
                }

                if (selectorFlag && attributeFlag && currentAttributeListTemp != NULL && currentAttributeListTemp->value.str() != "") {
                    myString returnValue = { "" };
                    returnValue += selectorName;
                    returnValue += { ",E," };
                    returnValue += attributeName;
                    returnValue += { " == " };
                    returnValue += currentAttributeListTemp->value;
                    this->output += returnValue;
                    this->output += '|';
                    return;
                }
            }
        }
        temp = temp->prev;
    }
}


void ResultParser::deleteSection(int sectionIndex, bool wantToAddToOutput) {
    SectionNode* temp = getSectionFromIndex(sectionIndex);
    BlockListNode* tempBlock = getBlockOfSection(sectionIndex);
    myString returnValue = { "" };

    if (temp != nullptr && tempBlock != nullptr) {
        delete temp->attributeList;
        delete temp->selectorList;
        temp->attributeList = new DoubleLinkedList<AttributeListNode>;
        temp->selectorList = new DoubleLinkedList<SelectorListNode>;
        temp->attributeList->headNode = NULL;
        temp->selectorList->headNode = NULL;
        temp->wasDeleted = true;

        if (tempBlock->currentAmountOfSections == 0) {
            return;
        }
        tempBlock->currentAmountOfSections -= 1;

        returnValue += sectionIndex+1;
        returnValue += { ",D,* == deleted" };

        if (wantToAddToOutput) {
            this->output += returnValue;
            this->output += '|';
        }
    }
}

void ResultParser::deleteSectionWithProvidedAttributeName(int sectionIndex, myString& attributeName) {
    SectionNode* temp = getSectionFromIndex(sectionIndex);
    bool wasThereDeletion = false;
    myString returnValue = { "" };

    if (temp == nullptr) return;

    DoubleLinkedList<AttributeListNode>* tempAttrList = temp->attributeList;
    if (tempAttrList == nullptr) return;

    tempAttrList->removeDuplicates();

    AttributeListNode* tempAttrListHeadNode = tempAttrList->headNode;
    if (tempAttrListHeadNode == nullptr) return;

    while (tempAttrListHeadNode != NULL) {
        if (tempAttrListHeadNode->name == attributeName) {
            tempAttrListHeadNode->name = "";
            tempAttrListHeadNode->value = "";
            if (tempAttrListHeadNode->prev != nullptr)
                tempAttrListHeadNode->prev->next = tempAttrListHeadNode->next;
            if (tempAttrListHeadNode->next != nullptr)
                tempAttrListHeadNode->next->prev = tempAttrListHeadNode->prev;
            tempAttrListHeadNode = nullptr;

            wasThereDeletion = true;
            break;
        }
        else {
            tempAttrListHeadNode = tempAttrListHeadNode->next;
        }
    }

    if (tempAttrList->checkIfListIsNotEmpty()) {
        deleteSection(sectionIndex, false);
    }

    if (wasThereDeletion) {
        returnValue += sectionIndex + 1;
        returnValue += { ",D," };
        returnValue += attributeName;
        returnValue += {" == deleted"};
        this->output += returnValue;
        this->output += '|';

    }
}