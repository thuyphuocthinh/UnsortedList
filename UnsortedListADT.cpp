// Troy ID: 11629924
// Full name: Thinh, Thuy Phuoc

#include <bits/stdc++.h>

enum RelationType
{
    LESS,
    GREATER,
    EQUAL
};

class ItemType
{
public:
    ItemType() {}
    ItemType(int number) : value(number) {}
    RelationType CompareTo(ItemType otherItem)
    {
        if (value > otherItem.value)
            return GREATER;
        else if (value < otherItem.value)
            return LESS;
        else
            return EQUAL;
    }
    void Initialize(int number)
    {
        value = number;
    }
    int GetValue() const
    {
        return value;
    }

private:
    int value;
};

// NodeType represents a node of the linked-list based link data structure
// A NodeType contains 2 parts: an item and a next pointer
struct NodeType
{
    ItemType info;
    NodeType *next;
    NodeType() {}
    NodeType(ItemType data) : info(data), next(NULL) {}
};

class UnsortedType
{
public:
    // Constructor
    UnsortedType()
    {
        length = 0;
        head = NULL;
    }
    // MakeEmpty
    void MakeEmpty()
    {
        NodeType *tempPtr;
        while (head != NULL)
        {
            tempPtr = head;
            head = head->next;
            delete tempPtr;
        }
        currentPos = NULL;
        length = 0;
        std::cout << "List became empty" << "\n";
    };
    // CheckItem
    bool CheckItem(ItemType item)
    {
        NodeType *currentNode = head;
        while (currentNode != NULL)
        {
            if (currentNode->info.CompareTo(item) == EQUAL)
            {
                return true;
            }
            currentNode = currentNode->next;
        }
        return false;
    }
    // PutItem
    void PutItem(ItemType item)
    {
        // Check Item
        if (CheckItem(item))
        {
            std::cout << "Requested data " << item.GetValue() << " is in the list" << "\n";
            return;
        }
        NodeType *newNode = new NodeType(item);
        length++;
        if (head == NULL)
        {
            head = newNode;
            return;
        }
        NodeType *currentNode = head;
        while (currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
    // DeleteItem
    void DeleteItem(ItemType item)
    {
        if (!CheckItem(item))
        {
            std::cout << "Requested data " << item.GetValue() << " is not in the list" << "\n";
            return;
        }
        NodeType *prevNode = head;
        NodeType *currentNode = head->next;
        length--;
        while (currentNode != NULL)
        {
            if (currentNode->info.CompareTo(item) == EQUAL)
            {
                prevNode->next = currentNode->next;
                delete currentNode;
                break;
            }
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
    }
    // ResetList
    void ResetList()
    {
        currentPos = NULL;
        std::cout << "Current position has been reset." << "\n";
    }
    // GetNextItem
    NodeType *GetNextItem()
    {
        if (currentPos == NULL)
        {
            currentPos = head;
        }
        else
        {
            currentPos = currentPos->next;
        }
        return currentPos;
    }
    // PrintList
    void PrintList() const
    {
        if (length == 0)
        {
            std::cout << "List is empty"
                      << "\n";
            return;
        }
        NodeType *currentNode = head;
        while (currentNode != NULL)
        {
            std::cout << currentNode->info.GetValue() << " ";
            currentNode = currentNode->next;
        }
        std::cout << '\n';
    }
    // Destructor
    ~UnsortedType()
    {
        NodeType *tempPtr;
        while (head != NULL)
        {
            tempPtr = head;
            head = head->next;
            delete tempPtr;
        }
    }

    void SplitList(UnsortedType &list, ItemType item, UnsortedType &list1, UnsortedType &list2)
    {
        NodeType *currentNode = list.head;
        while (currentNode != NULL)
        {
            switch (currentNode->info.CompareTo(item))
            {
            case LESS:
            case EQUAL:
            {
                list1.PutItem(currentNode->info);
                break;
            }
            case GREATER:
            {
                list2.PutItem(currentNode->info);
                break;
            }
            default:
                break;
            }
            currentNode = currentNode->next;
        }
        std::cout << "List 1: ";
        list1.PrintList();
        std::cout << "List 2: ";
        list2.PrintList();
        list.PrintList();
    }

    int length;
    NodeType *head;
    NodeType *currentPos;
};

// App represents an app that runs the program
class App
{
public:
    App()
    {   
        // Mapping function name to integer value
        map["PutItem"] = 1;
        map["CheckItem"] = 2;
        map["DeleteItem"] = 3;
        map["MakeEmpty"] = 4;
        map["GetNextItem"] = 5;
        map["PrintList"] = 6;
        map["ResetList"] = 7;
        map["SplitList"] = 8;
    }
    // this function takes an input file as a parameter 
    // and read file to test each function of the UnsortedType class
    void process(std::ifstream &input)
    {
        if (input.is_open())
        {
            std::string functionName = "";
            int number;
            while (!input.eof())
            {
                input >> functionName;
                switch (map[functionName])
                {
                case 1:
                {
                    input >> number;
                    ItemType item(number);
                    std::cout << functionName << " " << number << "\n";
                    list.PutItem(item);
                    list.PrintList();
                    break;
                }
                case 2:
                {
                    input >> number;
                    ItemType item(number);
                    std::cout << functionName << " " << number << "\n";
                    if (list.CheckItem(item))
                    {
                        std::cout << "Requested data " << item.GetValue() << " is in the list" << "\n";
                    }
                    else
                    {
                        std::cout << "Requested data " << item.GetValue() << " is not in the list" << "\n";
                    }
                    list.PrintList();
                    break;
                }
                case 3:
                {
                    input >> number;
                    ItemType item(number);
                    std::cout << functionName << " " << number << "\n";
                    list.DeleteItem(number);
                    list.PrintList();
                    break;
                }
                case 4:
                {
                    std::cout << functionName << "\n";
                    list.MakeEmpty();
                    break;
                }
                case 5:
                {
                    std::cout << functionName << "\n";
                    std::cout << list.GetNextItem()->info.GetValue() << "\n";
                    list.PrintList();
                    break;
                }
                case 6:
                {
                    std::cout << functionName << "\n";
                    list.PrintList();
                    break;
                }
                case 7:
                {
                    std::cout << functionName << "\n";
                    list.ResetList();
                    list.PrintList();
                    break;
                }
                case 8:
                {
                    input >> number;
                    ItemType item(number);
                    UnsortedType list1, list2;
                    std::cout << functionName << " " << number << "\n";
                    list.SplitList(list, item, list1, list2);
                    break;
                }
                default:
                    break;
                }
                std::cout << "-------------------------" << "\n";
            }
            input.close();
        }
    }

private:
    UnsortedType list;
    std::map<std::string, int> map;
};

int main()
{
    std::string inputFile;
    std::cout << "Type your input file name: ";
    std::cin >> inputFile;
    std::ifstream input(inputFile);
    App app;
    app.process(input);
    return 0;
}