#include "input_parser.h"
using namespace std;

InputParser::InputParser(DoubleLinkedList<BlockListNode>& newBlockList) {
    this->blockList = newBlockList;
    ResultParser newResultParser = { this->blockList };
    this->resultParser = newResultParser;
}

void InputParser::parseCommands(char& character, myString& input, bool flag) {
    //Flag is used to parse remaining characters, after main loop ends
    if ((character == '\n' || character == '\t' || character == EOF || flag)) {
        if (input == "????") {
            input = "";
        }
        else if (input == "****") {
            getCSSInput();
            input = "";
        }
        else if (input == "?") {
            this->resultParser.printOutAmountOfSections();
            input = "";
        }
        else if (input.amountOfComasInString() == 2) {
            input.removeSpacesFromBeginningAndEndFromString();
            myString firstParameter = { "" };
            myString secondParameter = { "" };
            myString thirdParameter = { "" };

            getCommandParameters(input, firstParameter, secondParameter, thirdParameter);

            bool isFirstParameterNumber = isCharArrayANumber(firstParameter.str());
            bool isThirdParameterNumber = isCharArrayANumber(thirdParameter.str());
            int sectionIndex;

            if (isFirstParameterNumber)
                sectionIndex = atoi(firstParameter.str()) - 1;

            if (secondParameter == "S") {
                if (thirdParameter == "?" && isFirstParameterNumber) {
                    this->resultParser.printOutAmountOfSelectorsOfSection(sectionIndex);
                }
                else if (isThirdParameterNumber && isFirstParameterNumber) {
                    int selectorIndex = atoi(thirdParameter.str()) - 1;
                    this->resultParser.printOutNSelectorOfSection(selectorIndex, sectionIndex);
                }
                else if (thirdParameter == "?" && !isFirstParameterNumber) {
                    this->resultParser.printOutAmountOfSelectorOccurences(firstParameter);
                }
            }
            else if (secondParameter == "A") {
                if (thirdParameter == "?" && isFirstParameterNumber) {
                    this->resultParser.printOutAmountOfAttributesOfSection(sectionIndex);
                }
                else if (isFirstParameterNumber && !isThirdParameterNumber) {
                    this->resultParser.printOutNAttributeOfSection(sectionIndex, thirdParameter);
                }
                else if (!isFirstParameterNumber && thirdParameter == "?") {
                    this->resultParser.printOutAmountOfAttributeOccurences(firstParameter);
                }
            }
            else if (secondParameter == "E") {
                if (!isFirstParameterNumber && !isThirdParameterNumber) {
                    this->resultParser.printOutValueOfAttributeWithNameNForSelectorZ(firstParameter, thirdParameter);
                }
            }
            else if (secondParameter == "D") {
                if (isFirstParameterNumber && thirdParameter == "*") {
                    this->resultParser.deleteSection(sectionIndex, true);
                }
                else if (isFirstParameterNumber) {
                    this->resultParser.deleteSectionWithProvidedAttributeName(sectionIndex, thirdParameter);
                }
            }
        }
        //output += '|';
        input = "";
    }
    else if (character != '\n' && character != '\t' && !flag) {
        input += character;
    }
}

void InputParser::getCSSInput() {
    char character;
    myString selectorInput = { "" };
    myString attributeInput = { "" };
    myString input = { "" };
    bool wasNewSectionDetected = false;

    while (cin >> noskipws >> character) {
        if (character != '\n' && character != ' ' && character != '\t') input += character;
        if (character == EOF) return;
        if (character < ' ' || character == ENTER_BUTTON) continue;

        if (input == "????") {
            return;
        }
        if (character == '{') {
            wasNewSectionDetected = true;
        }
        else if (character == '}') {
            BlockListNode* currentBlock = blockList.getLastNode();
            if (currentBlock == nullptr) return;
            SectionNode currentSection = currentBlock->sections[currentBlock->amountOfSectionsWithoutDeletions];
            DoubleLinkedList<SelectorListNode>* selectorList = new DoubleLinkedList<SelectorListNode>;
            DoubleLinkedList<AttributeListNode>* attributeList = new DoubleLinkedList<AttributeListNode>;

            if (currentBlock->amountOfSectionsWithoutDeletions == AMOUNT_OF_BLOCKS_IN_BLOCK_LIST - 1) {
                BlockListNode* newBlockListNode = new BlockListNode;
                this->blockList.addNewBlockToList(newBlockListNode);
                currentBlock = newBlockListNode;
                currentSection = currentBlock->sections[currentBlock->amountOfSectionsWithoutDeletions];

            }

            addSelectors(selectorInput, selectorList);

            addAttributes(attributeInput, attributeList);

            input = "";
            currentSection.attributeList = attributeList;
            currentSection.selectorList = selectorList;
            currentBlock->sections[currentBlock->amountOfSectionsWithoutDeletions] = currentSection;
            currentBlock->currentAmountOfSections += 1;
            currentBlock->amountOfSectionsWithoutDeletions += 1;
            wasNewSectionDetected = false;
            selectorInput = "";
            attributeInput = "";
        }
        if (character != '}' && character != '{' && character != '\n' && character != '\t') {
            wasNewSectionDetected == false ? selectorInput += character : attributeInput += character;
        }
    }
}

bool InputParser::isCharArrayANumber(const char* arr) {
    const int string_len = strlen(arr);
    for (int i = 0; i < string_len; ++i) {
        if (!isdigit(arr[i]))
            return false;
    }
    return true;
}

void InputParser::addSelectors(myString& selectorInput, DoubleLinkedList<SelectorListNode>* selectorList) {
    myString temp = { "" };
    for (size_t i = 0; i < selectorInput.length(); i++) {
        if ((selectorInput[i] == ',' || (i == selectorInput.length() - 1))) {
            if (selectorInput.length() - 1 == i) temp += selectorInput[i];
            SelectorListNode* newNode = new SelectorListNode;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            temp.removeSpacesFromBeginningAndEndFromString();
            newNode->name = temp;
            selectorList->addNewBlockToList(newNode);
            temp = "";
        }
        else {
            temp += selectorInput[i];
        }
    }
}

void InputParser::addAttributes(myString& attributeInput, DoubleLinkedList<AttributeListNode>* attributeList) {
    myString temp = { "" };
    for (size_t i = 0; i < attributeInput.length(); i++) {
        if (attributeInput[i] == ';' || (i == attributeInput.length() - 1)) {
            if (i == attributeInput.length() - 1 && attributeInput[i] != ';') temp += attributeInput[i];
            AttributeListNode* newNode = new AttributeListNode;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            myString name = { "" };
            myString value = { "" };
            bool isNameInputFinished = false;

            for (size_t j = 0; j < temp.length(); j++) {
                if (temp[j] == ':') {
                    isNameInputFinished = true;
                }
                else {
                    if (temp[j] != ';')
                        isNameInputFinished == false ? name += temp[j] : value += temp[j];

                }
            }
            name.removeSpacesFromBeginningAndEndFromString();
            value.removeSpacesFromBeginningAndEndFromString();

            newNode->name = name;
            newNode->value = value;

            attributeList->addNewBlockToList(newNode);
            temp = "";
        }
        else {
            temp += attributeInput[i];
        }
    }
}

void InputParser::getCommandParameters(myString& input, myString& firstParameter, myString& secondParameter, myString& thirdParameter) {
    myString temp = { "" };
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == ',' || i == input.length() - 1) {
            if (i == input.length() - 1)
                temp += input[i];
            if (firstParameter == "") firstParameter = temp;
            else if (secondParameter == "") secondParameter = temp;
            else thirdParameter = temp;
            temp = "";
        }
        else {
            temp += input[i];
        }
    }
    firstParameter.removeSpacesFromBeginningAndEndFromString();
    secondParameter.removeSpacesFromBeginningAndEndFromString();
    thirdParameter.removeSpacesFromBeginningAndEndFromString();
}