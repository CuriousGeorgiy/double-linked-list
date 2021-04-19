#ifndef DOUBLYLINKEDPOINTERLIST_HPP
#define DOUBLYLINKEDPOINTERLIST_HPP

#include <cstdlib>
#include <cstdio>
#include <memory.h>

#ifndef NDEBUG
#define VALIDATE_LIST validate()
#else
#define VALIDATE_LIST
#endif

template<typename T>
class DoublyLinkedPointerList {
public:
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };

    Node *tail;
    Node *head;

    size_t size;

    explicit DoublyLinkedPointerList();

    DoublyLinkedPointerList(const DoublyLinkedPointerList<T> &) = delete;
    DoublyLinkedPointerList(DoublyLinkedPointerList<T> &&) = delete;

    DoublyLinkedPointerList<T> &operator=(const DoublyLinkedPointerList<T> &) = delete;
    DoublyLinkedPointerList<T> &operator=(DoublyLinkedPointerList<T> &&) = delete;

    ~DoublyLinkedPointerList();

    Node *insertAfterLogicalPos(size_t logicalPos, T val);
    Node *insertBeforeLogicalPos(size_t logicalPos, T val);
    Node *insertBeforeTail(T val);
    Node *insertAfterHead(T val);

    void deleteFromLogicalPos(size_t logicalPos);
    void deleteHead();
    void deleteTail();

    Node *nodeAtLogicalPos(size_t logicalPos) const;

    void dump(const char *msg) const;
    bool isValid() const;
    void validate() const;
    void clear();

    Node *findNodeByValue(T val) const;

private:
    bool checkInsertLogicalPosCorrectness(size_t logicalPos) const;
    bool checkDeleteLogicalPosCorrectness(size_t logicalPos) const;
    bool checkFindLogicalPosCorrectness(size_t logicalPos) const;
};

template<typename T>
DoublyLinkedPointerList<T>::DoublyLinkedPointerList()
: tail(nullptr), head(nullptr), size(0)
{
    VALIDATE_LIST;
}

template<typename T>
DoublyLinkedPointerList<T>::~DoublyLinkedPointerList()
{
    VALIDATE_LIST;

    clear();
}

template<typename T>
typename DoublyLinkedPointerList<T>::Node *DoublyLinkedPointerList<T>::insertAfterLogicalPos(size_t logicalPos, T val)
{
    if (!checkInsertLogicalPosCorrectness(logicalPos)) return nullptr;

    if (logicalPos == size) {
        VALIDATE_LIST;
        return insertAfterHead(val);
    }

    Node *node = nodeAtLogicalPos(logicalPos);

    Node *newNode = new Node;

    newNode->next = node->next;
    node->next = newNode;
    newNode->next->prev = newNode;
    newNode->prev = node;
    newNode->data = val;
    ++size;

    VALIDATE_LIST;
    return newNode;
}

template<typename T>
typename DoublyLinkedPointerList<T>::Node *DoublyLinkedPointerList<T>::insertBeforeLogicalPos(size_t logicalPos, T val)
{
    if (!checkInsertLogicalPosCorrectness(logicalPos)) return nullptr;

    if (logicalPos <= 1) {
        VALIDATE_LIST;
        return insertBeforeTail(val);
    }

    Node *node = nodeAtLogicalPos(logicalPos);

    Node *newNode = new Node;

    newNode->next = node;
    newNode->prev = node->prev;
    node->prev = newNode;
    newNode->prev->next = newNode;
    newNode->data = val;
    ++size;

    VALIDATE_LIST;
    return newNode;
}

template<typename T>
typename DoublyLinkedPointerList<T>::Node *DoublyLinkedPointerList<T>::insertBeforeTail(T val)
{
    VALIDATE_LIST;

    Node *newNode = new Node;

    if (tail != nullptr) {
        tail->prev = newNode;
    } else {
        head = tail;
    }

    newNode->next = tail;
    newNode->prev = nullptr;
    newNode->data = val;
    tail = newNode;
    ++size;

    VALIDATE_LIST;
    return newNode;
}

template<typename T>
typename DoublyLinkedPointerList<T>::Node *DoublyLinkedPointerList<T>::insertAfterHead(T val)
{
    VALIDATE_LIST;

    Node *newNode = new Node;

    if (head != nullptr) {
        head->next = newNode;
    } else {
        tail = newNode;
    }

    newNode->next = nullptr;
    newNode->prev = head;
    newNode->data = val;
    head = newNode;
    ++size;

    VALIDATE_LIST;
    return newNode;
}

template<typename T>
void DoublyLinkedPointerList<T>::deleteFromLogicalPos(size_t logicalPos)
{
    VALIDATE_LIST;

    if (!checkDeleteLogicalPosCorrectness(logicalPos)) return;

    if (logicalPos == size) {
        deleteHead();
        VALIDATE_LIST;
        return;
    }

    if (logicalPos == 1) {
        deleteTail();
        VALIDATE_LIST;
        return;
    }

    Node *node = nodeAtLogicalPos(logicalPos);

    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node;
    --size;

    VALIDATE_LIST;
}

template<typename T>
void DoublyLinkedPointerList<T>::deleteHead()
{
    VALIDATE_LIST;

    head->prev->next = nullptr;
    Node *deletedHead = head;
    head = head->prev;
    delete deletedHead;
    --size;

    VALIDATE_LIST;
}

template<typename T>
void DoublyLinkedPointerList<T>::deleteTail()
{
    VALIDATE_LIST;

    tail->next->prev = nullptr;
    Node *deletedTail = tail;
    tail = tail->next;
    delete deletedTail;
    --size;

    VALIDATE_LIST;
}

template<typename T>
void DoublyLinkedPointerList<T>::dump(const char *msg) const
{
    std::FILE *dumpFile = std::fopen("DoublyLinkedPointerList.dot", "w");
    std::fprintf(dumpFile, "digraph G {\n"
                           "\trankdir=LR\n");

    size_t i = 1;
    for (Node *node = tail; node != nullptr; node = node->next, ++i) {
        std::fprintf(dumpFile, "\t%zu[", i);

        if ((i == 1) || (i == size)) {
            std::fprintf(dumpFile, R"(fillcolor="#ffc0cb", color="#462759", fontcolor="#462759", label=")");
        } else {
            std::fprintf(dumpFile, R"(fillcolor="#add8e6", color="#00008b", fontcolor="#00008b", label=")");
        }

        std::fprintf(dumpFile,
                     "<data> data\\n %d\", style=filled, "
                     "shape=record];\n",
                     node->data);
    }

    for (i = 1; i < size; ++i) {
        std::fprintf(dumpFile, "\t%zu->%zu;\n", i, i + 1);
    }

    for (i = size; i > 1; --i) {
        std::fprintf(dumpFile, "\t%zu->%zu;\n", i, i - 1);
    }

    std::fprintf(dumpFile, "\tlabelloc=\"t\"\n"
                           "\tlabel=\"%s\"\n", msg);

    std::fprintf(dumpFile, "}\n");
    std::fclose(dumpFile);

    std::system("dot -Tpng DoublyLinkedPointerList.dot > DoublyLinkedPointerList.png");
    std::system("start DoublyLinkedPointerList.png");
    std::system("pause");
}

template<typename T>
bool DoublyLinkedPointerList<T>::checkInsertLogicalPosCorrectness(size_t logicalPos) const
{
    VALIDATE_LIST;

    return ((logicalPos != 0) || ((tail == nullptr) && (head == nullptr))) && (logicalPos <= size);
}

template<typename T>
bool DoublyLinkedPointerList<T>::checkDeleteLogicalPosCorrectness(size_t logicalPos) const
{
    VALIDATE_LIST;

    return (logicalPos != 0) && (logicalPos <= size);
}

template<typename T>
bool DoublyLinkedPointerList<T>::checkFindLogicalPosCorrectness(size_t logicalPos) const
{
    VALIDATE_LIST;

    return checkDeleteLogicalPosCorrectness(logicalPos);
}

template<typename T>
typename DoublyLinkedPointerList<T>::Node *DoublyLinkedPointerList<T>::nodeAtLogicalPos(size_t logicalPos) const
{
    VALIDATE_LIST;

    if (!checkFindLogicalPosCorrectness(logicalPos)) return nullptr;

    Node *node = tail;
    while (--logicalPos > 0) {
        node = node->next;
    }

    return node;
}

template<typename T>
typename DoublyLinkedPointerList<T>::Node *DoublyLinkedPointerList<T>::findNodeByValue(T val) const
{
    VALIDATE_LIST;

    for (Node *node = tail; node != nullptr; node = node->next) {
        if (node->data == val) {
            return node;
        }
    }

    return nullptr;
}

template<typename T>
void DoublyLinkedPointerList<T>::clear()
{
    VALIDATE_LIST;

    Node *node = tail;
    while (node != nullptr) {
        Node *nextNode = node->next;
        delete node;
        node = nextNode;
    }
    size = 0;
    tail = nullptr;
    head = nullptr;

    VALIDATE_LIST;
}

template<typename T>
bool DoublyLinkedPointerList<T>::isValid() const
{
    if (size == 0) {
        if ((tail != nullptr) || (head != nullptr)) return false;

        return true;
    }

    if ((tail == nullptr) || (head == nullptr) || (tail->prev != nullptr) || (head->next != nullptr)) return false;

    Node *node = tail;
    for (size_t i = 0; i < size; node = node->next, ++i) {
        if ((node->prev == nullptr) && (node != tail)) return false;
    }
    if (node != nullptr) return false;

    node = head;
    for (size_t i = size; i > 0; node = node->prev, --i);
    if (node != nullptr) return false;

    return true;
}

template<typename T>
void DoublyLinkedPointerList<T>::validate() const
{
    if (!isValid()) {
        dump("Invalid list");
        exit(EXIT_FAILURE);
    }
}

#undef VALIDATE_LIST
#endif /* DOUBLYLINKEDPOINTERLIST_HPP */
