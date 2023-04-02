#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "string.h"
using namespace std;

#define AMOUNT_OF_BLOCKS_IN_BLOCK_LIST 8

struct BlockListNode;
struct SectionNode;
struct SelectorListNode;
struct AttributeListNode;
template<typename T> class DoubleLinkedList;



class myString
{
private:
    char* buffer = nullptr;
    unsigned int size = 0;
public:
    myString() : buffer(nullptr), size(0) {};

    myString(const char* newBuffer) {
        size = strlen(newBuffer);
        buffer = new char[size + 1];
        strcpy(buffer, newBuffer);
    };

    myString(const myString& stringObject)
    {
        size = stringObject.size;
        buffer = new char[size + 1];
        strcpy(buffer, stringObject.buffer);
    }

    myString(myString&& stringObject) noexcept
    {
        size = stringObject.size;
        buffer = stringObject.buffer;
        stringObject.buffer = nullptr;
        stringObject.size = 0;
    }


    myString& operator=(const myString& stringObject)
    {
        size = stringObject.size;
        buffer = new char[size + 1];
        strcpy(buffer, stringObject.buffer);
        return *this;
    }

    myString& operator=(myString&& stringObject) noexcept
    {
        size = stringObject.size;
        buffer = stringObject.buffer;
        stringObject.buffer = nullptr;
        stringObject.size = 0;
        return *this;
    }

    bool operator!=(myString& stringObject2) {
        return strcmp(buffer, stringObject2.buffer);
    }

    bool operator==(const char* arr) {
        return strcmp(buffer, arr) == 0;
    }

    bool operator==(myString& str) {
        return strcmp(buffer, str.buffer) == 0;
    }

    myString operator+(const char& character)
    {
        myString newString;
        newString.size = this->size + 1;
        newString.buffer = new char[newString.size + 1];

        strcpy(newString.buffer, this->buffer);
        newString.buffer[this->size] = character;
        newString.buffer[this->size + 1] = '\0';

        return newString;
    }

    myString operator+(const myString& stringToConcatenate)
    {
        myString newString;
        newString.size = this->size + stringToConcatenate.size;
        newString.buffer = new char[newString.size + 1];
        strcpy(newString.buffer, this->buffer);
        strcat(newString.buffer, stringToConcatenate.buffer);
        return newString;
    }

    myString& operator+=(const char& character)
    {
        myString newString;
        newString.size = this->size + 1;
        newString.buffer = new char[newString.size + 1];

        strcpy(newString.buffer, this->buffer);
        newString.buffer[this->size] = character;
        newString.buffer[this->size + 1] = '\0';

        if (buffer != nullptr)
            delete[] buffer;

        this->size = newString.size;
        this->buffer = new char[this->size + 1];
        strcpy(this->buffer, newString.buffer);
        return *this;
    }

    myString& operator+=(const myString& stringToConcatenate)
    {
        myString newString;
        newString.size = this->size + stringToConcatenate.size;
        newString.buffer = new char[newString.size + 1];
        strcpy(newString.buffer, this->buffer);
        strcat(newString.buffer, stringToConcatenate.buffer);

        if (buffer != nullptr)
            delete[] buffer;

        this->size = newString.size;
        this->buffer = new char[newString.size + 1];
        strcpy(this->buffer, newString.buffer);
        return *this;

    }

    char operator[](const int index) {
        return this->buffer[index];
    }

    unsigned int length() {
        return this->size;
    }
    const char* str() const {
        return this->buffer;
    }

    friend ostream& operator<<(std::ostream& cout, const myString& obj) {
        cout << obj.str();
        return cout;
    }


    ~myString() {
        if (buffer != nullptr) {
            delete[] buffer;
            size = 0;
        }
    }
};

struct SectionNode {
    DoubleLinkedList<SelectorListNode>* selectorList = NULL;
    DoubleLinkedList<AttributeListNode>* attributeList = NULL;
    bool wasDeleted = false;
    int counter = 0;
};

struct BlockListNode {
    BlockListNode* prev = NULL;
    BlockListNode* next = NULL;
    SectionNode* sections = new SectionNode[AMOUNT_OF_BLOCKS_IN_BLOCK_LIST];
    int currentAmountOfSections = 0;
    int amountOfSectionsWithoutDeletions = 0;
};


struct SelectorListNode {
    SelectorListNode* prev = nullptr;
    SelectorListNode* next = nullptr;
    myString name = { "" };
};


struct AttributeListNode {
    AttributeListNode* prev;
    AttributeListNode* next;
    myString name = { "" };
    myString value = { "" };
};



template<typename T> class DoubleLinkedList {
public:
    T* headNode = nullptr;
    int amountOfBlocks = 0;
    bool wasHeadNodeSet = false;
public:
    //TODO: Write destructor
    DoubleLinkedList() {
        T* head = new T;
        head->prev = NULL;
        head->next = NULL;
        wasHeadNodeSet = false;
        headNode = head;
    }

    int length() {
        return amountOfBlocks;
    }

    void addNewBlockToList(T* nextBlockListNode) {
        if (amountOfBlocks == 0) {
            headNode = nextBlockListNode;
            headNode->next = NULL;
            headNode->prev = NULL;

            amountOfBlocks++;

        }
        else {
            T* last = headNode;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = nextBlockListNode;
            nextBlockListNode->prev = last;
            amountOfBlocks++;
        }
    }


    T* getLastNode() {
        T* last = headNode;
        while (last->next != NULL) {
            last = last->next;
        }
        return last;
    }
    ~DoubleLinkedList() {
        T* temp = getLastNode();
        if (temp != NULL) {
            while (temp != NULL) {
                T* temp2 = temp->prev;
                delete temp;
                temp = temp2;
            }
            cout << endl;
        }

    }
};


template <class T> void printOutBlockList(T* blockList) {
    BlockListNode* temp = blockList->headNode;
    if (temp != NULL) {
        cout << "The list contains: ";
        while (temp != NULL) {
            cout << temp->currentAmountOfSections << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    else {
        cout << "The list is empty.\n";

    }
}

template <class T> void printAttributeList(T* attributeList) {
    AttributeListNode* temp = attributeList->headNode;
    myString output = { "" };
    if (temp != NULL) {
        while (temp != NULL) {
            output = output + temp->name;
            output = output + ":";
            output = output + temp->value;
            output = output + " ";
            temp = temp->next;
        }
    }
    else {
        cout << "The list is empty.\n";

    }
    cout << "Attributes: " << output << endl;
}

template <class T> void printSelectorList(T* selectorList) {
    SelectorListNode* temp = selectorList->headNode;
    myString output = { "" };
    if (temp != NULL) {
        while (temp != NULL) {
            output = output + temp->name;
            output = output + " ";
            temp = temp->next;
        }
    }
    else {
        cout << "The list is empty.\n";

    }
    cout << "Selectors: " << output << endl;
}

template<class T> void printOutSelectorsAndAttributes(T* blockList) {
    BlockListNode* temp = blockList->headNode;
    if (temp != NULL) {
        while (temp != NULL) {
            for (int i = 0; i < temp->amountOfSectionsWithoutDeletions; i++) {
                if (temp->sections[i].attributeList->headNode != nullptr && temp->sections[i].selectorList->headNode != nullptr) {
                    printSelectorList(temp->sections[i].selectorList);
                    printAttributeList(temp->sections[i].attributeList);

                }
            }
            temp = temp->next;
        }
    }
    else {
        cout << "The list is empty.\n";

    }
}

bool checkIfStringIsNotFullOfSpaces(myString str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') return false;
    }
    return true;
}

myString removeSpacesFromBeginningAndEndFromString(myString& str) {
    myString newStr = { "" };
    bool flag = false;
    int start=0, end=str.length()-1;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') { start = i; break; };
    }
    for (int i = str.length()-1; i >= 0; i--) {
        if (str[i] != ' ') { end = i; break; };
    }
    for (int i = start; i <= end; i++) {
        newStr += str[i];
    }
    return newStr;
}

void getCSSInput(DoubleLinkedList<BlockListNode>& blockList) {
    char character;
    myString emptyStringToClear("");
    myString selectorInput = { "" };
    myString attributeInput = { "" };
    myString input = { "" };
    bool wasNewSectionDetected = false;
    int wasNewAttributeDetected = 0;
    char spaceCharacter;
    int counter = 0;
    myString input2 = { "" };
    myString temp = { "" };

    while (cin >> noskipws >> character) {
        //cout << input;
        if (character != '\n' && character != ' ' && character != '\t') input += character;
        if (character == EOF) return;
        //input += character;
        if (input == "????") {
            return;
        }
        if (character == '{') {
            wasNewSectionDetected = true;
        }
        else if (character == '}') {
            BlockListNode* currentBlock = blockList.getLastNode();
            SectionNode currentSection = currentBlock->sections[currentBlock->amountOfSectionsWithoutDeletions];
            DoubleLinkedList<SelectorListNode>* selectorList = new DoubleLinkedList<SelectorListNode>;
            DoubleLinkedList<AttributeListNode>* attributeList = new DoubleLinkedList<AttributeListNode>;
            temp = "";

            if (currentBlock->amountOfSectionsWithoutDeletions == AMOUNT_OF_BLOCKS_IN_BLOCK_LIST - 1) {
                BlockListNode* newBlockListNode = new BlockListNode;
                blockList.addNewBlockToList(newBlockListNode);
                currentBlock = blockList.getLastNode();
                currentSection = currentBlock->sections[currentBlock->amountOfSectionsWithoutDeletions];

            }

            for (int i = 0; i < selectorInput.length(); i++) {
                //todo: add handling for example + in css
                if ((selectorInput[i] == ',' || (i == selectorInput.length() - 1 && temp.str() != ""))) {
                    if (selectorInput.length() - 1 == i) temp += selectorInput[i];
                    SelectorListNode* newNode = new SelectorListNode;
                    newNode->next = nullptr;
                    newNode->prev = nullptr;
                    newNode->name = removeSpacesFromBeginningAndEndFromString(temp);
                    selectorList->addNewBlockToList(newNode);
                    temp = "";
                }
                else {
                    temp += selectorInput[i];
                }
            }
            temp = "";

            for (int i = 0; i < attributeInput.length(); i++) {
                if (attributeInput[i] == ';' || (i == attributeInput.length() - 1 && temp.str() != "")) {
                    if (i == attributeInput.length() - 1 && attributeInput[i] != ';') temp += attributeInput[i];
                    AttributeListNode* newNode = new AttributeListNode;
                    newNode->next = nullptr;
                    newNode->prev = nullptr;
                    myString name = { "" };
                    myString value = { "" };
                    bool isNameInputFinished = false;

                    for (int j = 0; j < temp.length(); j++) {
                        if (temp[j] == ':') {
                            isNameInputFinished = true;
                        }
                        else {
                            if (temp[j] != ';')
                                isNameInputFinished == false ? name += temp[j] : value += temp[j];

                        }
                    }

                    newNode->name = removeSpacesFromBeginningAndEndFromString(name);
                    newNode->value = removeSpacesFromBeginningAndEndFromString(value);

                    attributeList->addNewBlockToList(newNode);
                    temp = "";

                }
                else {
                    temp += attributeInput[i];
                }
            }

            input = "";
            currentSection.attributeList = attributeList;
            currentSection.selectorList = selectorList;
            currentBlock->sections[currentBlock->amountOfSectionsWithoutDeletions] = currentSection;
            currentBlock->currentAmountOfSections += 1;
            currentBlock->amountOfSectionsWithoutDeletions += 1;

            wasNewAttributeDetected = false;
            wasNewSectionDetected = false;
            selectorInput = "";
            attributeInput = "";
            counter = 0;
        }
        if (character != '}' && character != '{' && character != '\n' && character != '\t') {
            if (wasNewSectionDetected == false) { //removed checking if character == ' '
                selectorInput += character;
            }
            else if (wasNewSectionDetected == true) {
                attributeInput += character;
            }
            //wasNewSectionDetected == false ? selectorInput += character : attributeInput += character;
        }


    }
    //printOutBlockList(&blockList);
}


SectionNode* getSectionAsAPointer(int sectionIndex, DoubleLinkedList<BlockListNode>& blockList) {
    int counter = 0;
    BlockListNode* blockListTemp = blockList.headNode;
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

myString printOutAmmountOfSections(DoubleLinkedList<BlockListNode>& blockList) {
    BlockListNode* temp = blockList.headNode;
    int counter = 0;
    while (temp != NULL) {
        counter += temp->currentAmountOfSections;
        temp = temp->next;
    }

    char counterInChar[512];
    sprintf(counterInChar, "%d", counter);
    myString returnValue = { "? == " };
    returnValue += counterInChar;
    return returnValue;
}

myString printOutAmountOfSelectorsOfSection(int sectionIndex, DoubleLinkedList<BlockListNode>& blockList) {
    //todo: fix
    SectionNode* tempSection = getSectionAsAPointer(sectionIndex, blockList);

    myString defaultValue = { "" };
    char sectionIndexInCharDefault[512];
    sprintf(sectionIndexInCharDefault, "%d", sectionIndex + 1);

    defaultValue += sectionIndexInCharDefault;
    defaultValue += { ",S,? == 0" };

    if (tempSection == nullptr) return myString{ "" };
    if (tempSection->wasDeleted == true) return myString{ "" };

    DoubleLinkedList<SelectorListNode>* tempList = tempSection->selectorList;
    if (tempList == nullptr) return defaultValue;

    SelectorListNode* temp = tempList->headNode;
    if (temp == nullptr) return defaultValue;

    int counter = 0;
    if (temp != NULL) {
        while (temp != NULL) {
            if (temp->name.length() != 0)
                counter++;
            temp = temp->next;
        }
    }

    char sectionIndexInChar[512];
    sprintf(sectionIndexInChar, "%d", sectionIndex + 1);

    char counterInChar[512];
    sprintf(counterInChar, "%d", counter);

    myString returnValue = { "" };
    returnValue += sectionIndexInChar;
    returnValue += { ",S,? == " };
    returnValue += counterInChar;
    return returnValue;

    return myString{ "" };
}

void removeDuplicates(DoubleLinkedList<AttributeListNode>* attributeList) {
    AttributeListNode* head = attributeList->headNode;
    AttributeListNode* lastNode = attributeList->getLastNode();
    while (lastNode != nullptr) {
        AttributeListNode* headNode = attributeList->headNode;
        while (headNode != nullptr && headNode->next != nullptr && headNode != lastNode) {
            if (headNode->name == lastNode->name) {
                if (headNode == head) {
                    if (headNode->prev != nullptr)
                        headNode->prev->next = headNode->next;
                    if (headNode->next != nullptr) {
                        headNode->next->prev = headNode->prev;
                    }
                    attributeList->headNode = headNode->next;
                    headNode = headNode->next;
                }
                else {
                    if (headNode->prev != nullptr)
                        headNode->prev->next = headNode->next;
                    if (headNode->next != nullptr) {
                        headNode->next->prev = headNode->prev;
                    }
                    headNode = headNode->next;
                }

            }
            else
                headNode = headNode->next;
        }
        lastNode = lastNode->prev;
    }
}

myString printOutAmountOfAttributesOfSection(int sectionIndex, DoubleLinkedList<BlockListNode>& blockList) {
    int counter = 0;
    SectionNode* tempSection = getSectionAsAPointer(sectionIndex, blockList);
    if (tempSection == nullptr) return myString{ "" };
    if (tempSection->wasDeleted == true) return myString{ "" };

    DoubleLinkedList<AttributeListNode>* tempList = tempSection->attributeList;
    if (tempList == nullptr) return myString{ "" };

    removeDuplicates(tempList);

    AttributeListNode* temp = tempList->headNode;
    if (temp == nullptr) return myString{ "" };

    myString emptyString = { "" };
    if (temp != NULL) {
        while (temp != NULL) {
            if (temp->name.length() != 0 || temp->value.length() != 0)
                counter++;
            temp = temp->next;
        }
    }

    char sectionIndexInChar[512];
    sprintf(sectionIndexInChar, "%d", sectionIndex + 1);

    char counterInChar[512];
    sprintf(counterInChar, "%d", counter);

    if (counter != 0) {
        myString returnValue = { "" };
        returnValue += sectionIndexInChar;
        returnValue += { ",A,? == " };
        returnValue += counterInChar;
        return returnValue;
    }
    return myString{ "" };
}

myString printOutNSelectorOfSection(int selectorIndex, int sectionIndex, DoubleLinkedList<BlockListNode>& blockList) {
    int counter = 0;
    SectionNode* tempSection = getSectionAsAPointer(sectionIndex, blockList);

    if (tempSection == nullptr) return myString{ "" };
    DoubleLinkedList < SelectorListNode >* tempList = tempSection->selectorList;
    if (tempList == nullptr) return myString{ "" };
    SelectorListNode* temp = tempList->headNode;
    if (temp == nullptr) return myString{ "" };

    if (temp != NULL) {
        while (temp != NULL && counter != selectorIndex) {
            temp = temp->next;
            counter++;
        }
    }

    char sectionIndexInChar[512];
    sprintf(sectionIndexInChar, "%d", sectionIndex + 1);

    char selectorIndexInChar[512];
    sprintf(selectorIndexInChar, "%d", selectorIndex + 1);

    if (counter == selectorIndex && temp != NULL && temp->name.length() != 0) {
        myString returnValue = { "" };
        returnValue += sectionIndexInChar;
        returnValue += { ",S," };
        returnValue += selectorIndexInChar;
        returnValue += {" == "};
        returnValue += temp->name;
        return returnValue;
    }
    return myString{ "" };
}

myString printOutNAttributeOfSection(int sectionIndex, myString attributeName, DoubleLinkedList<BlockListNode>& blockList) {
    // need to delete duplicates
    int counter = 0;
    SectionNode* tempSection = getSectionAsAPointer(sectionIndex, blockList);
    if (tempSection == nullptr) return myString{ "" };

    DoubleLinkedList<AttributeListNode>* tempList = tempSection->attributeList;
    if (tempList == nullptr) return myString{ "" };

    removeDuplicates(tempList);

    AttributeListNode* temp = tempList->headNode;
    if (temp == nullptr) return myString{ "" };

    if (temp != NULL) {
        while (temp != NULL && temp->name != attributeName) {
            temp = temp->next;
        }
    }

    char sectionIndexInChar[512];
    sprintf(sectionIndexInChar, "%d", sectionIndex + 1);
    if (temp != NULL && temp->name == attributeName && temp->value.length() != 0) {
        myString returnValue = { "" };
        returnValue += sectionIndexInChar;
        returnValue += { ",A," };
        returnValue += attributeName;
        returnValue += {" == "};
        returnValue += temp->value.str();
        return returnValue;
    }
    return myString{ "" };
}

myString printOutAmountOfAttributeOccurences(myString attributeName, DoubleLinkedList<BlockListNode>& blockList) {
    BlockListNode* temp = blockList.headNode;
    int counter = 0;
    while (temp != NULL) {
        for (int i = 0; i < temp->amountOfSectionsWithoutDeletions; i++) {
            SectionNode currentSection = temp->sections[i];
            if (currentSection.wasDeleted == false) {
                removeDuplicates(currentSection.attributeList);

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



    char counterInChar[512];
    sprintf(counterInChar, "%d", counter);

    myString returnValue = { "" };
    returnValue += attributeName;
    returnValue += { ",A,? == " };
    returnValue += counterInChar;
    return returnValue;
}

myString printOutAmountOfSelectorOccurences(myString selectorName, DoubleLinkedList<BlockListNode>& blockList) {
    BlockListNode* temp = blockList.headNode;
    SectionNode currentSection;
    int counter = 0;
    while (temp != NULL) {
        for (int i = 0; i < temp->amountOfSectionsWithoutDeletions; i++) {
            currentSection = temp->sections[i];
            if (currentSection.wasDeleted == false) {
                SelectorListNode* currentSelectorListTemp = currentSection.selectorList->getLastNode();
                while (currentSelectorListTemp != NULL) {
                    if (currentSelectorListTemp->name == selectorName) { counter++; break; };
                    currentSelectorListTemp = currentSelectorListTemp->prev;
                }
            }

        }
        temp = temp->next;
    }

    char counterInChar[512];
    sprintf(counterInChar, "%d", counter);

    myString returnValue = { "" };
    returnValue += selectorName;
    returnValue += { ",S,? == " };
    returnValue += counterInChar;
    return returnValue;
}

myString printOutValueOfAttributeWithNameNForSelectorZ(myString selectorName, myString attributeName, DoubleLinkedList<BlockListNode>& blockList) {
    BlockListNode* temp = blockList.getLastNode();
    int counter = 0;
    while (temp != NULL) {
        for (int i = temp->amountOfSectionsWithoutDeletions - 1; i >= 0; i--) {
            if (temp->sections[i].wasDeleted == false) {
                SelectorListNode* currentSelectorListTemp = temp->sections[i].selectorList->getLastNode();
                removeDuplicates(temp->sections[i].attributeList);
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
                    return returnValue;
                }
            }
        }
        temp = temp->prev;
    }

    myString emptyString{ "" };
    return emptyString;
}

BlockListNode* getBlockInSectionIndex(int sectionIndex, DoubleLinkedList<BlockListNode>& blockList) {
    int counter = 0;
    BlockListNode* blockListTemp = blockList.headNode;
    SectionNode* desiredSection = new SectionNode;
    while (blockListTemp != NULL) {
        for (int i = 0; i < blockListTemp->amountOfSectionsWithoutDeletions; i++) { //blockListTemp->currentAmountOfSections
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

myString deleteSection(int sectionIndex, DoubleLinkedList<BlockListNode>& blockList) {
    SectionNode* temp = getSectionAsAPointer(sectionIndex, blockList);
    BlockListNode* tempBlock = getBlockInSectionIndex(sectionIndex, blockList);
    if (temp != nullptr && tempBlock != nullptr) {
        //If section exists
        delete temp->attributeList;
        delete temp->selectorList;
        temp->attributeList = new DoubleLinkedList<AttributeListNode>;
        temp->selectorList = new DoubleLinkedList<SelectorListNode>;
        temp->attributeList->headNode = NULL;
        temp->selectorList->headNode = NULL;
        temp->wasDeleted = true;

        if (tempBlock->currentAmountOfSections == 0) {
            return myString{ "" };
        }
        tempBlock->currentAmountOfSections -= 1;

        char sectionIndexInChar[512];
        sprintf(sectionIndexInChar, "%d", sectionIndex + 1);
        myString returnValue = { "" };
        returnValue += sectionIndexInChar;
        returnValue += { ",D,* == deleted" };

        return returnValue;
    }
    else return myString{ "" };

}

bool checkIfAttributeListIsNotEmpty(DoubleLinkedList<AttributeListNode>* attributeList) {
    int counter = 0;
    AttributeListNode* temp = attributeList->headNode;
    while (temp != NULL) {
        if (temp->name.length() != 0) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

myString deleteSectionWithProvidedAttributeName(int sectionIndex, myString attributeName, DoubleLinkedList<BlockListNode>& blockList) {
    SectionNode* temp = getSectionAsAPointer(sectionIndex, blockList);
    bool flag = false;
    if (temp == nullptr) return myString{ "" };
    DoubleLinkedList<AttributeListNode>* tempAttrList = temp->attributeList;
    if (tempAttrList == nullptr) return myString{ " " };

    removeDuplicates(tempAttrList);

    AttributeListNode* tempAttrListHeadNode = tempAttrList->headNode;
    if (tempAttrListHeadNode == nullptr) return myString{ "" };

    while (tempAttrListHeadNode != NULL) {
        if (tempAttrListHeadNode->name == attributeName) {
            tempAttrListHeadNode->name = "";
            tempAttrListHeadNode->value = "";
            if (tempAttrListHeadNode->prev != nullptr)
                tempAttrListHeadNode->prev->next = tempAttrListHeadNode->next;
            if (tempAttrListHeadNode->next != nullptr)
                tempAttrListHeadNode->next->prev = tempAttrListHeadNode->prev;
            tempAttrListHeadNode = nullptr;
            flag = true;
            break;
        }
        else {
            tempAttrListHeadNode = tempAttrListHeadNode->next;
        }
    }

    if (checkIfAttributeListIsNotEmpty(tempAttrList)) {
        deleteSection(sectionIndex, blockList);
    }
    if (flag) {
        char sectionIndexInChar[512];
        sprintf(sectionIndexInChar, "%d", sectionIndex + 1);
        myString returnValue = { "" };
        returnValue += sectionIndexInChar;
        returnValue += { ",D," };
        returnValue += attributeName;
        returnValue += {" == deleted"};
        return returnValue;
    }
    else {
        return myString{ "" };
    }


}

bool isCharArrayANumber(const char* arr) {
    const int string_len = strlen(arr);
    for (int i = 0; i < string_len; ++i) {
        if (!isdigit(arr[i]))
            return false;
    }
    return true;
}

void parseCommands(char& character, myString& output, myString& input, DoubleLinkedList<BlockListNode>& blockList, bool flag) {
    if ((character == '\n' || character == ' ' || character == '\t' || character == EOF || flag)) {
        if (input == "????") {
            input = "";
        }
        else if (input == "****") {
            getCSSInput(blockList);
            //po tym nie wraca program
            input = "";
        }
        else if (input == "?") {
            output += printOutAmmountOfSections(blockList);
            input = "";
        }
        else {
            myString firstParameter = { "" };
            myString secondParameter = { "" };
            myString thirdParameter = { "" };
            myString temp = { "" };
            for (int i = 0; i < input.length(); i++) {
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
            firstParameter = removeSpacesFromBeginningAndEndFromString(firstParameter);
            secondParameter = removeSpacesFromBeginningAndEndFromString(secondParameter);
            thirdParameter = removeSpacesFromBeginningAndEndFromString(thirdParameter);

            bool isFirstParameterNumber = isCharArrayANumber(firstParameter.str());
            bool isThirdParameterNumber = isCharArrayANumber(thirdParameter.str());
            int sectionIndex;
            if (isFirstParameterNumber)
                sectionIndex = atoi(firstParameter.str()) - 1;

            if (secondParameter == "S") {
                if (thirdParameter == "?" && isFirstParameterNumber) {
                    output += printOutAmountOfSelectorsOfSection(sectionIndex, blockList);
                }
                else if (isThirdParameterNumber && isFirstParameterNumber) {
                    int selectorIndex = atoi(thirdParameter.str()) - 1;
                    output += printOutNSelectorOfSection(selectorIndex, sectionIndex, blockList);
                }
                else if (thirdParameter == "?" && !isFirstParameterNumber) {
                    output += printOutAmountOfSelectorOccurences(firstParameter, blockList);
                }
            }
            else if (secondParameter == "A") {
                if (thirdParameter == "?" && isFirstParameterNumber) {
                    output += printOutAmountOfAttributesOfSection(sectionIndex, blockList);
                }
                else if (isFirstParameterNumber && !isThirdParameterNumber) {

                    output += printOutNAttributeOfSection(sectionIndex, thirdParameter, blockList);
                }
                else if (!isFirstParameterNumber && thirdParameter == "?") {
                    output += printOutAmountOfAttributeOccurences(firstParameter, blockList);

                }
            }
            else if (secondParameter == "E") {
                if (!isFirstParameterNumber && !isThirdParameterNumber) {
                    output += printOutValueOfAttributeWithNameNForSelectorZ(firstParameter, thirdParameter, blockList);
                }
            }
            else if (secondParameter == "D") {
                if (isFirstParameterNumber && thirdParameter == "*") {
                    output += deleteSection(sectionIndex, blockList);
                }
                else if (isFirstParameterNumber) {
                    output += deleteSectionWithProvidedAttributeName(sectionIndex, thirdParameter, blockList);
                }
            }

        }
        output += '|';
        input = "";
    }
    else if (character != '\n' && character != ' ' && character != '\t' && !flag) {
        input += character;
    }
}

int main() {
    DoubleLinkedList<BlockListNode> blockList;
    BlockListNode* firstBlock = new BlockListNode;
    blockList.addNewBlockToList(firstBlock);
    char character;
    myString input = { "" };
    myString output = { "" };
    getCSSInput(blockList);
    //printOutSelectorsAndAttributes(&blockList);

    while (cin >> character >> noskipws) {
        parseCommands(character, output, input, blockList, false);
    }
    if (input.str() != "")
        parseCommands(character, output, input, blockList, true);
    bool flag = false;
    //Flag is used to not write \n many times in a row
    for (int i = 0; i < output.length(); i++) {
        if (output[i] != '\n' && output[i] != '|' && output[i] != '/' && output[i] != '\t') {
            cout << output[i];
            flag = true;
        }
        else if (output[i] == '|' && i != 0 && flag) {
            cout << '\n';
            flag = false;
        }
    }
    return 0;
}