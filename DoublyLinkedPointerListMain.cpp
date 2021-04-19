#include "DoublyLinkedPointerList.hpp"

int main()
{
    DoublyLinkedPointerList<int> doublyLinkedPointerList;

    doublyLinkedPointerList.insertAfterLogicalPos(0, 100);
    doublyLinkedPointerList.insertAfterLogicalPos(1, 10);
    doublyLinkedPointerList.dump("After insert");
    doublyLinkedPointerList.insertAfterLogicalPos(2, 57);
    doublyLinkedPointerList.dump("After insert");
    doublyLinkedPointerList.insertAfterLogicalPos(3, 7);
    doublyLinkedPointerList.dump("After insert");
    doublyLinkedPointerList.insertAfterLogicalPos(4, 90);
    doublyLinkedPointerList.dump("After insert");
    doublyLinkedPointerList.insertAfterLogicalPos(3, 88);
    doublyLinkedPointerList.dump("After insert");
    doublyLinkedPointerList.insertBeforeTail(257);
    doublyLinkedPointerList.dump("After insert");
    doublyLinkedPointerList.insertAfterHead(1000);
    doublyLinkedPointerList.dump("After insert");
    doublyLinkedPointerList.insertBeforeLogicalPos(4, 500);
    doublyLinkedPointerList.dump("After insert");
    doublyLinkedPointerList.insertBeforeLogicalPos(5, 300);
    doublyLinkedPointerList.dump("After insert");

    doublyLinkedPointerList.deleteHead();
    doublyLinkedPointerList.deleteTail();
    doublyLinkedPointerList.deleteFromLogicalPos(3);

    doublyLinkedPointerList.dump("after deletes");
    auto node1 = doublyLinkedPointerList.nodeAtLogicalPos(2);
    auto node2 = doublyLinkedPointerList.findNodeByValue(88);

    doublyLinkedPointerList.dump("Before clear");
    doublyLinkedPointerList.clear();
    doublyLinkedPointerList.dump("After clear");

    return 0;
}
