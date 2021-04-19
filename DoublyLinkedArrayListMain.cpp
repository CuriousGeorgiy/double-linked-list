#include "DoublyLinkedArrayList.hpp"

int main()
{
    DoublyLinkedArrayList<int> doublyLinkedArrayList(1);

    size_t index1 = doublyLinkedArrayList.insertAfterPhysicalPos(0, 100);
    size_t index2 = doublyLinkedArrayList.insertAfterPhysicalPos(index1, 10);
    size_t index3 = doublyLinkedArrayList.insertAfterPhysicalPos(index2, 57);
    size_t index4 = doublyLinkedArrayList.insertAfterPhysicalPos(index3, 7);
    size_t index5 = doublyLinkedArrayList.insertAfterPhysicalPos(index4, 90);
    size_t index6 = doublyLinkedArrayList.insertAfterPhysicalPos(index3, 88);
    size_t index7 = doublyLinkedArrayList.insertBeforeTail(257);
    size_t index8 = doublyLinkedArrayList.insertAfterHead(1000);
    size_t index9 = doublyLinkedArrayList.insertBeforePhysicalPos(4, 500);
    size_t index10 = doublyLinkedArrayList.insertBeforePhysicalPos(5, 300);

    doublyLinkedArrayList.deleteHead();
    doublyLinkedArrayList.deleteTail();
    doublyLinkedArrayList.deleteFromPhysicalPos(index4);

    auto node1 = doublyLinkedArrayList.findNodeByLogicalPos(2);
    auto node2 = doublyLinkedArrayList.findNodeByValue(88);
    auto node3 = doublyLinkedArrayList.nodeBeforePhysicalPos(3);
    auto node4 = doublyLinkedArrayList.nodeAfterPhysicalPos(4);

    doublyLinkedArrayList.dump("Before sorting");
    doublyLinkedArrayList.sort();
    doublyLinkedArrayList.dump("After sorting");

    auto node5 = doublyLinkedArrayList.findNodeByLogicalPos(4);
    doublyLinkedArrayList.clear();
    doublyLinkedArrayList.dump("After clear");

    return 0;
}
