//
//  tests.cpp
//

#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_CONSOLE_WIDTH 150

#include <iostream>
#include "BinHeap.h"
#include "catch.hpp"


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing constructor", "[CONSTRUCTOR]") {
    BinHeap<int> heap;
    
    SECTION("constructor must initialize the maxSize") {
        INFO("maxSize should be initialized to 1");
        REQUIRE(heap.maxSize == 1);
    }
    
    SECTION("constructor must initialize the heapSize") {
        INFO("heapSize should be initialized to 0");
        REQUIRE(heap.heapSize == 0);
    }
    
    SECTION("constructor must initialize the heap's beacking array") {
        REQUIRE(heap.heapArray != nullptr);
    }
    
    SECTION("constructor must initialize index 0 of the heap's backing array") {
        INFO("index 0 of the heap's backing array should be initialized to -1");
        REQUIRE(heap.heapArray[0] == -1);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing isEmpty() method on an empty BinHeap", "[ISEMPTY]") {
    BinHeap<int> heap;
    
    INFO("heapSize of empty BinHeap should be 0");
    REQUIRE(heap.heapSize == 0);

    SECTION("verify return value of isEmpty()") {
        INFO("when empty, isEmpty() should return true");
        REQUIRE(heap.isEmpty() == true);
    }
}


TEST_CASE("testing isEmpty() method on a non-empty BinHeap", "[ISEMPTY]") {
    BinHeap<int> heap;
    heap.insert(5);
    
    INFO("inserted value 5");
    INFO("heapSize of BinHeap should be 1");
    REQUIRE(heap.heapSize == 1);
    INFO("value at index 1 of backing array should be 5");
    REQUIRE(heap.heapArray[1] == 5);
    
    SECTION("verify return value of isEmpty() after single insert") {
        INFO("when not empty, isEmpty() should return false");
        REQUIRE(heap.isEmpty() == false);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing makeEmpty() method on an empty BinHeap", "[MAKEEMPTY]") {
    BinHeap<int> heap;

    INFO("before calling makeEmpty(), BinHeap should be empty");
    REQUIRE(heap.maxSize == 1);
    REQUIRE(heap.heapSize == 0);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);
    
    SECTION("verify that makeEmpty() doesn't break anything when BinHeap is empty") {
        heap.makeEmpty();
        INFO("after calling makeEmpty(), BinHeap should still be empty");
        REQUIRE(heap.maxSize == 1);
        REQUIRE(heap.heapSize == 0);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);
    }
}


TEST_CASE("testing makeEmpty() method on a non-empty BinHeap", "[MAKEEMPTY]") {
    BinHeap<int> heap;
    heap.insert(6);
    heap.insert(12);
    heap.insert(8);
    heap.insert(18);
    heap.insert(16);
    heap.insert(10);
    heap.insert(14);
    heap.insert(20);
    heap.insert(2);
    
    INFO("inserted values 6, 12, 8, 18, 16, 10, 14, 20, 2");
    const char *heapString = "\n"
        "  Current array size: 16\n"
        "  Current heap size: 9\n"
        "  Heap Elements: 2 6 8 12 16 10 14 20 18\n";
    INFO("\nbefore calling makeEmpty(), BinHeap should be: " << heapString);
    REQUIRE(heap.maxSize == 16);        // check heap properties
    REQUIRE(heap.heapSize == 9);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);   // check heap contents
    REQUIRE(heap.heapArray[1] == 2);
    REQUIRE(heap.heapArray[2] == 6);
    REQUIRE(heap.heapArray[3] == 8);
    REQUIRE(heap.heapArray[4] == 12);
    REQUIRE(heap.heapArray[5] == 16);
    REQUIRE(heap.heapArray[6] == 10);
    REQUIRE(heap.heapArray[7] == 14);
    REQUIRE(heap.heapArray[8] == 20);
    REQUIRE(heap.heapArray[9] == 18);
    
    std::stringstream ss;
    heap.printHeapToStream(ss);
    INFO("before calling makeEmpty(), your BinHeap is: \n" << ss.str());

    SECTION("verify that makeEmpty() successfully empties BinHeap and properties are correct") {
        heap.makeEmpty();
        INFO("after calling makeEmpty(), BinHeap should be empty");
        REQUIRE(heap.maxSize == 1);
        REQUIRE(heap.heapSize == 0);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing resizeArray(newSize) method on an empty BinHeap", "[RESIZEARRAY]") {
    BinHeap<int> heap;
    
    INFO("before calling resizeArray(newSize), BinHeap should be empty");
    REQUIRE(heap.maxSize == 1);
    REQUIRE(heap.heapSize == 0);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);
    
    SECTION("verify that resizeArray(newSize) properly resizes the backing array (doubles its size)") {
        int * origHeapArrayPtr = heap.heapArray;
        heap.resizeArray(2 * heap.maxSize);
        INFO("after calling resizeArray(newSize), backing array should be double the size");
        REQUIRE(origHeapArrayPtr != heap.heapArray);  // make sure a new backing array was created
        REQUIRE(heap.maxSize == 2);
        REQUIRE(heap.heapSize == 0);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);
    }
    
    SECTION("verify that resizeArray(newSize) properly resizes the backing array (triples its size)") {
        int * origHeapArrayPtr = heap.heapArray;
        heap.resizeArray(3 * heap.maxSize);
        INFO("after calling resizeArray(newSize), backing array should be triple the size");
        REQUIRE(origHeapArrayPtr != heap.heapArray);  // make sure a new backing array was created
        REQUIRE(heap.maxSize == 3);
        REQUIRE(heap.heapSize == 0);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);
    }
}


TEST_CASE("testing resizeArray(newSize) method on a non-empty BinHeap", "[RESIZEARRAY]") {
    BinHeap<int> heap;
    heap.insert(6);
    heap.insert(12);
    heap.insert(8);
    heap.insert(18);
    heap.insert(16);
    heap.insert(10);
    heap.insert(14);
    heap.insert(20);
    heap.insert(2);
    
    INFO("inserted values 6, 12, 8, 18, 16, 10, 14, 20, 2");
    const char *heapString = "\n"
        "  Current array size: 16\n"
        "  Current heap size: 9\n"
        "  Heap Elements: 2 6 8 12 16 10 14 20 18\n";
    INFO("\nbefore calling resizeArray(newSize), BinHeap should be: " << heapString);
    REQUIRE(heap.maxSize == 16);        // check heap properties
    REQUIRE(heap.heapSize == 9);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);   // check heap contents
    REQUIRE(heap.heapArray[1] == 2);
    REQUIRE(heap.heapArray[2] == 6);
    REQUIRE(heap.heapArray[3] == 8);
    REQUIRE(heap.heapArray[4] == 12);
    REQUIRE(heap.heapArray[5] == 16);
    REQUIRE(heap.heapArray[6] == 10);
    REQUIRE(heap.heapArray[7] == 14);
    REQUIRE(heap.heapArray[8] == 20);
    REQUIRE(heap.heapArray[9] == 18);
    
    std::stringstream ss;
    heap.printHeapToStream(ss);
    INFO("before calling resizeArray(newSize), your BinHeap is: \n" << ss.str());

    SECTION("verify that resizeArray(newSize) properly resizes the backing array (doubles its size)") {
        int * origHeapArrayPtr = heap.heapArray;
        heap.resizeArray(2 * heap.maxSize);
        INFO("after calling resizeArray(newSize), backing array should be double the size");
        REQUIRE(origHeapArrayPtr != heap.heapArray);  // make sure a new backing array was created
        REQUIRE(heap.maxSize == 32);
        REQUIRE(heap.heapSize == 9);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
    }
    
    SECTION("verify that resizeArray(newSize) properly resizes the backing array (triples its size)") {
        int * origHeapArrayPtr = heap.heapArray;
        heap.resizeArray(3 * heap.maxSize);
        INFO("after calling resizeArray(newSize), backing array should be triple the size");
        REQUIRE(origHeapArrayPtr != heap.heapArray);  // make sure a new backing array was created
        REQUIRE(heap.maxSize == 48);
        REQUIRE(heap.heapSize == 9);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
    }
    
    SECTION("verify that resizeArray(newSize) properly resizes the backing array (reduces its size)") {
        int * origHeapArrayPtr = heap.heapArray;
        heap.resizeArray(11);
        INFO("after calling resizeArray(newSize), backing array should have size of 11");
        REQUIRE(origHeapArrayPtr != heap.heapArray);  // make sure a new backing array was created
        REQUIRE(heap.maxSize == 11);
        REQUIRE(heap.heapSize == 9);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
    }
    
    SECTION("verify that resizeArray(newSize) properly resizes the backing array (reduces its to heapSize)") {
        int * origHeapArrayPtr = heap.heapArray;
        heap.resizeArray(9);
        INFO("after calling resizeArray(newSize), backing array should have size of 9");
        REQUIRE(origHeapArrayPtr != heap.heapArray);  // make sure a new backing array was created
        REQUIRE(heap.maxSize == 9);
        REQUIRE(heap.heapSize == 9);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing leftChildIndex(idx) method", "[LEFTCHILDINDEX]") {
    BinHeap<int> heap;
    REQUIRE(heap.leftChildIndex(1) == 2);
    REQUIRE(heap.leftChildIndex(2) == 4);
    REQUIRE(heap.leftChildIndex(3) == 6);
    REQUIRE(heap.leftChildIndex(4) == 8);
    REQUIRE(heap.leftChildIndex(5) == 10);
    REQUIRE(heap.leftChildIndex(6) == 12);
    REQUIRE(heap.leftChildIndex(7) == 14);
    REQUIRE(heap.leftChildIndex(8) == 16);
    REQUIRE(heap.leftChildIndex(9) == 18);
    REQUIRE(heap.leftChildIndex(10) == 20);
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing rightChildIndex(idx) method", "[RIGHTCHILDINDEX]") {
    BinHeap<int> heap;
    REQUIRE(heap.rightChildIndex(1) == 3);
    REQUIRE(heap.rightChildIndex(2) == 5);
    REQUIRE(heap.rightChildIndex(3) == 7);
    REQUIRE(heap.rightChildIndex(4) == 9);
    REQUIRE(heap.rightChildIndex(5) == 11);
    REQUIRE(heap.rightChildIndex(6) == 13);
    REQUIRE(heap.rightChildIndex(7) == 15);
    REQUIRE(heap.rightChildIndex(8) == 17);
    REQUIRE(heap.rightChildIndex(9) == 19);
    REQUIRE(heap.rightChildIndex(10) == 21);
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing parentIndex(idx) method", "[PARENTINDEX]") {
    BinHeap<int> heap;
    REQUIRE(heap.parentIndex(1) == 0);
    REQUIRE(heap.parentIndex(2) == 1);
    REQUIRE(heap.parentIndex(3) == 1);
    REQUIRE(heap.parentIndex(4) == 2);
    REQUIRE(heap.parentIndex(5) == 2);
    REQUIRE(heap.parentIndex(6) == 3);
    REQUIRE(heap.parentIndex(7) == 3);
    REQUIRE(heap.parentIndex(8) == 4);
    REQUIRE(heap.parentIndex(9) == 4);
    REQUIRE(heap.parentIndex(10) == 5);
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing minChild(idx) method on an empty BinHeap", "[MINCHILD]") {
    BinHeap<int> heap;
    
    INFO("before calling minChild(idx), BinHeap should be empty");
    REQUIRE(heap.maxSize == 1);
    REQUIRE(heap.heapSize == 0);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);
    
    SECTION("verify that minChild(idx) operates correctly after inserting single value into empty BinHeap") {
        heap.insert(6);
        int minChildMinResult = heap.minChild(1);
        INFO("inserted value 6");
        INFO("called minChild(idx) on index 1 (i.e. root node with no children)");
        REQUIRE(heap.maxSize == 1);
        REQUIRE(heap.heapSize == 1);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);
        REQUIRE(heap.heapArray[1] == 6);
        REQUIRE(minChildMinResult == -1);
    }
}


TEST_CASE("testing minChild(idx) method on a non-empty BinHeap", "[MINCHILD]") {
    BinHeap<int> heap;
    heap.insert(6);
    heap.insert(12);
    heap.insert(8);
    heap.insert(18);
    heap.insert(16);
    heap.insert(10);
    heap.insert(14);
    heap.insert(20);
    heap.insert(2);
    heap.insert(24);
    
    INFO("inserted values 6, 12, 8, 18, 16, 10, 14, 20, 2, 24");
    const char *heapString = "\n"
        "  Current array size: 16\n"
        "  Current heap size: 10\n"
        "  Heap Elements: 2 6 8 12 16 10 14 20 18 24\n";
    INFO("\nbefore calling minChild(idx), BinHeap should be: " << heapString);
    REQUIRE(heap.maxSize == 16);        // check heap properties
    REQUIRE(heap.heapSize == 10);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);   // check heap contents
    REQUIRE(heap.heapArray[1] == 2);
    REQUIRE(heap.heapArray[2] == 6);
    REQUIRE(heap.heapArray[3] == 8);
    REQUIRE(heap.heapArray[4] == 12);
    REQUIRE(heap.heapArray[5] == 16);
    REQUIRE(heap.heapArray[6] == 10);
    REQUIRE(heap.heapArray[7] == 14);
    REQUIRE(heap.heapArray[8] == 20);
    REQUIRE(heap.heapArray[9] == 18);
    REQUIRE(heap.heapArray[10] == 24);
    
    std::stringstream ss;
    heap.printHeapToStream(ss);
    INFO("before calling minChild(idx), your BinHeap is: \n" << ss.str());
    
    SECTION("verify that minChild(idx) returns correct index for a node with no children") {
        INFO("minChild(idx) method should return -1 for a nodes with no children (e.g. nodes 10, 14, 20, 18)");
        REQUIRE(heap.minChild(6) == -1);  // node 10
        REQUIRE(heap.minChild(7) == -1);  // node 14
        REQUIRE(heap.minChild(8) == -1);  // node 20
        REQUIRE(heap.minChild(9) == -1);  // node 18
    }
    
    SECTION("verify that minChild(idx) returns correct value for a node with one child whose minChild is a left child") {
        INFO("minChild(idx) method should return index 10 as minChild of node 16");
        REQUIRE(heap.minChild(5) == 10);  // node 16
    }
    
    SECTION("verify that minChild(idx) returns correct value for a node with two children whose minChild is a left child") {
        INFO("minChild(idx) method should return index 2 as minChild of node 2");
        REQUIRE(heap.minChild(1) == 2);  // node 2
        INFO("minChild(idx) method should return index 4 as minChild of node 6");
        REQUIRE(heap.minChild(2) == 4);  // node 6
        INFO("minChild(idx) method should return index 6 as minChild of node 8");
        REQUIRE(heap.minChild(3) == 6);  // node 8
    }
    
    SECTION("verify that minChild(idx) returns correct value for a node with two children whose minChild is a right child") {
        INFO("minChild(idx) method should return index 9 as minChild of node 12");
        REQUIRE(heap.minChild(4) == 9);  // node 12
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing insert(x) method on an empty BinHeap", "[INSERT]") {
    BinHeap<int> heap;
    
    INFO("before calling insert(x), BinHeap should be empty");
    REQUIRE(heap.maxSize == 1);
    REQUIRE(heap.heapSize == 0);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);
    
    SECTION("verify structure of BinHeap after single insert into empty BinHeap") {
        int * origHeapArrayPtr = heap.heapArray;
        heap.insert(6);
        INFO("inserted value 6");
        INFO("after calling insert(x), heap should contain a single value");
        REQUIRE(heap.heapArray == origHeapArrayPtr); // no resizing should occur
        REQUIRE(heap.maxSize == 1);
        REQUIRE(heap.heapSize == 1);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);
        REQUIRE(heap.heapArray[1] == 6);
    }
}


TEST_CASE("testing insert(x) method on a non-empty BinHeap (multiple inserts)", "[INSERT]") {
    BinHeap<int> heap;
    
    INFO("before calling insert(x), BinHeap should be empty");
    REQUIRE(heap.maxSize == 1);
    REQUIRE(heap.heapSize == 0);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);
    
    SECTION("verify structure of BinHeap after two inserts into empty BinHeap (1st val < 2nd val - no percolating)") {
        int * origHeapArrayPtr = heap.heapArray;
        heap.insert(6);
        heap.insert(12);
        std::stringstream ss;
        heap.printHeapToStream(ss);
        
        INFO("inserted values 6, 12");
        const char *heapString = "\n"
            "  Current array size: 2\n"
            "  Current heap size: 2\n"
            "  Heap Elements: 6 12\n";
        INFO("\nafter inserting two values (1st val < 2nd val), BinHeap should be: " << heapString);
        INFO("after inserting two values (1st val < 2nd val), your BinHeap is: \n" << ss.str());
        
        REQUIRE(heap.maxSize == 2);         // check heap properties
        REQUIRE(heap.heapSize == 2);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 6);
        REQUIRE(heap.heapArray[2] == 12);
    }
    
    SECTION("verify structure of BinHeap after two inserts into empty BinHeap (1st val > 2nd val - percolates)") {
        int * origHeapArrayPtr = heap.heapArray;
        heap.insert(6);
        heap.insert(2);
        std::stringstream ss;
        heap.printHeapToStream(ss);
        
        INFO("inserted values 6, 2");
        const char *heapString = "\n"
            "  Current array size: 2\n"
            "  Current heap size: 2\n"
            "  Heap Elements: 2 6\n";
        INFO("\nafter inserting two values (1st val > 2nd val), BinHeap should be: " << heapString);
        INFO("after inserting two values (1st val > 2nd val), your BinHeap is: \n" << ss.str());
        
        REQUIRE(heap.maxSize == 2);        // check heap properties
        REQUIRE(heap.heapSize == 2);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 6);
    }
    
    SECTION("verify structure of BinHeap after many inserts (requires resizing)") {
        int * origHeapArrayPtr = heap.heapArray;
        heap.insert(6);
        heap.insert(12);
        heap.insert(8);
        heap.insert(18);
        heap.insert(16);
        heap.insert(10);
        heap.insert(14);
        heap.insert(20);
        heap.insert(2);
        std::stringstream ss;
        heap.printHeapToStream(ss);
        
        INFO("inserted values 6, 12, 8, 18, 16, 10, 14, 20, 2");
        const char *heapString = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 9\n"
            "  Heap Elements: 2 6 8 12 16 10 14 20 18\n";
        INFO("\nafter inserting many values, BinHeap should be: " << heapString);
        INFO("after inserting many values, your BinHeap is: \n" << ss.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 9);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing removeMin() method on an empty BinHeap", "[REMOVEMIN]") {
    BinHeap<int> heap;
    
    INFO("before calling removeMin(), BinHeap should be empty");
    REQUIRE(heap.maxSize == 1);
    REQUIRE(heap.heapSize == 0);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);

    SECTION("verify that removeMin() returns the appropriate value when BinHeap is empty") {
        INFO("removeMin() should return -1 when called on an empty BinHeap");
        REQUIRE(heap.removeMin() == -1);
        INFO("the structure of the BinHeap should not change when removeMin() is called on empty BinHeap");
        REQUIRE(heap.maxSize == 1);
        REQUIRE(heap.heapSize == 0);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);
    }
}


TEST_CASE("testing removeMin() method on a non-empty BinHeap", "[REMOVEMIN]") {
    BinHeap<int> heap;
    heap.insert(6);
    heap.insert(12);
    heap.insert(8);
    heap.insert(18);
    heap.insert(16);
    heap.insert(10);
    heap.insert(14);
    heap.insert(20);
    heap.insert(2);
    heap.insert(24);
    
    INFO("inserted values 6, 12, 8, 18, 16, 10, 14, 20, 2, 24");
    const char *heapString = "\n"
        "  Current array size: 16\n"
        "  Current heap size: 10\n"
        "  Heap Elements: 2 6 8 12 16 10 14 20 18 24\n";
    INFO("\nbefore calling removeMin(), BinHeap should be: " << heapString);
    REQUIRE(heap.maxSize == 16);        // check heap properties
    REQUIRE(heap.heapSize == 10);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);   // check heap contents
    REQUIRE(heap.heapArray[1] == 2);
    REQUIRE(heap.heapArray[2] == 6);
    REQUIRE(heap.heapArray[3] == 8);
    REQUIRE(heap.heapArray[4] == 12);
    REQUIRE(heap.heapArray[5] == 16);
    REQUIRE(heap.heapArray[6] == 10);
    REQUIRE(heap.heapArray[7] == 14);
    REQUIRE(heap.heapArray[8] == 20);
    REQUIRE(heap.heapArray[9] == 18);
    REQUIRE(heap.heapArray[10] == 24);
    
    std::stringstream ss;
    heap.printHeapToStream(ss);
    INFO("before calling removeMin(), your BinHeap is: \n" << ss.str());
    
    SECTION("verify that removeMin() returns the appropriate value and updates the BinHeap (no resize required)") {
        int * origHeapArrayPtr = heap.heapArray;
        INFO("removeMin() should return 2 when called on existing BinHeap");
        REQUIRE(heap.removeMin() == 2);
        
        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 9\n"
            "  Heap Elements: 6 12 8 18 16 10 14 20 24\n";
        INFO("\nafter calling removeMin(), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling removeMin(), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 9);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray == origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 6);
        REQUIRE(heap.heapArray[2] == 12);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 18);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 24);
    }
    
    SECTION("verify that removeMin() returns the appropriate value and updates the BinHeap (resize required)") {
        int * origHeapArrayPtr = heap.heapArray;
        INFO("manually set heap's maxSize variable to 64 prior to calling removeMin()");
        heap.maxSize = 64;
        INFO("removeMin() should return 2 when called on existing BinHeap");
        REQUIRE(heap.removeMin() == 2);
        
        const char *heapString2 = "\n"
            "  Current array size: 32\n"
            "  Current heap size: 9\n"
            "  Heap Elements: 6 12 8 18 16 10 14 20 24\n";
        INFO("\nafter calling removeMin(), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling removeMin(), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 32);        // check heap properties
        REQUIRE(heap.heapSize == 9);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 6);
        REQUIRE(heap.heapArray[2] == 12);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 18);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 24);
    }
    
    SECTION("verify that removeMin() returns the appropriate values and updates the BinHeap on multiple calls to removeMin()") {
        int * origHeapArrayPtr = heap.heapArray;
        int removeMinResult;
        
        INFO("1st call to removeMin() should return 2 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("    Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == 2);      // call removeMin()
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 9);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray == origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 6);
        REQUIRE(heap.heapArray[2] == 12);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 18);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 24);
        
        INFO("2nd call to removeMin() should return 6 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("    Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == 6);      // call removeMin()
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 8);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray == origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 8);
        REQUIRE(heap.heapArray[2] == 12);
        REQUIRE(heap.heapArray[3] == 10);
        REQUIRE(heap.heapArray[4] == 18);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 24);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        
        INFO("3rd call to removeMin() should return 8 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("    Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == 8);      // call removeMin()
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 7);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray == origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 10);
        REQUIRE(heap.heapArray[2] == 12);
        REQUIRE(heap.heapArray[3] == 14);
        REQUIRE(heap.heapArray[4] == 18);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 24);
        REQUIRE(heap.heapArray[7] == 20);
        
        INFO("4th call to removeMin() should return 10 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("    Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == 10);     // call removeMin()
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 6);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray == origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 12);
        REQUIRE(heap.heapArray[2] == 16);
        REQUIRE(heap.heapArray[3] == 14);
        REQUIRE(heap.heapArray[4] == 18);
        REQUIRE(heap.heapArray[5] == 20);
        REQUIRE(heap.heapArray[6] == 24);
        
        INFO("4th call to removeMin() should return 12 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("    Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == 12);     // call removeMin()
        REQUIRE(heap.maxSize == 8);         // check heap properties
        REQUIRE(heap.heapSize == 5);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 14);
        REQUIRE(heap.heapArray[2] == 16);
        REQUIRE(heap.heapArray[3] == 24);
        REQUIRE(heap.heapArray[4] == 18);
        REQUIRE(heap.heapArray[5] == 20);

        INFO("5th call to removeMin() should return 14 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("    Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == 14);     // call removeMin()
        REQUIRE(heap.maxSize == 8);         // check heap properties
        REQUIRE(heap.heapSize == 4);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 16);
        REQUIRE(heap.heapArray[2] == 18);
        REQUIRE(heap.heapArray[3] == 24);
        REQUIRE(heap.heapArray[4] == 20);
        
        INFO("6th call to removeMin() should return 16 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("    Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == 16);     // call removeMin()
        REQUIRE(heap.maxSize == 8);         // check heap properties
        REQUIRE(heap.heapSize == 3);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 18);
        REQUIRE(heap.heapArray[2] == 20);
        REQUIRE(heap.heapArray[3] == 24);

        INFO("7th call to removeMin() should return 18 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("    Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == 18);     // call removeMin()
        REQUIRE(heap.maxSize == 4);         // check heap properties
        REQUIRE(heap.heapSize == 2);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 20);
        REQUIRE(heap.heapArray[2] == 24);
        
        INFO("8th call to removeMin() should return 20 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("    Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == 20);     // call removeMin()
        REQUIRE(heap.maxSize == 2);         // check heap properties
        REQUIRE(heap.heapSize == 1);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 24);

        INFO("9th call to removeMin() should return 24 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("    Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == 24);     // call removeMin()
        REQUIRE(heap.maxSize == 1);         // check heap properties
        REQUIRE(heap.heapSize == 0);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        
        INFO("10th call to removeMin() should return -1 when called on BinHeap");
        removeMinResult = heap.removeMin();
        INFO("     Your call to removeMin() returned " << removeMinResult);
        REQUIRE(removeMinResult == -1);     // call removeMin()
        REQUIRE(heap.maxSize == 1);         // check heap properties
        REQUIRE(heap.heapSize == 0);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing percolateUp(idx) method on an empty BinHeap", "[PERCOLATEUP]") {
    BinHeap<int> heap;
    
    INFO("before calling percolateUp(idx), BinHeap should be empty");
    REQUIRE(heap.maxSize == 1);
    REQUIRE(heap.heapSize == 0);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);
    
    SECTION("verify that percolateUp(idx) operates correctly when node is inserted into empty BinHeap") {
        heap.heapArray[1] = 6;  // manually inserting a value
        heap.heapSize++;
        heap.percolateUp(1);
        INFO("manually inserted value 6 into BinHeap at index 1 (did NOT use insert(x) method)");
        INFO("called percolateUp(idx) on index 1 (i.e. root node)");
        REQUIRE(heap.maxSize == 1);
        REQUIRE(heap.heapSize == 1);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);
        REQUIRE(heap.heapArray[1] == 6);
    }
}


TEST_CASE("testing percolateUp(idx) method on a non-empty BinHeap", "[PERCOLATEUP]") {
    BinHeap<int> heap;
    heap.insert(6);
    heap.insert(12);
    heap.insert(8);
    heap.insert(18);
    heap.insert(16);
    heap.insert(10);
    heap.insert(14);
    heap.insert(20);
    heap.insert(2);
    heap.insert(24);
    
    INFO("inserted values 6, 12, 8, 18, 16, 10, 14, 20, 2, 24");
    const char *heapString = "\n"
        "  Current array size: 16\n"
        "  Current heap size: 10\n"
        "  Heap Elements: 2 6 8 12 16 10 14 20 18 24\n";
    INFO("\nbefore calling percolateUp(idx), BinHeap should be: " << heapString);
    REQUIRE(heap.maxSize == 16);        // check heap properties
    REQUIRE(heap.heapSize == 10);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);   // check heap contents
    REQUIRE(heap.heapArray[1] == 2);
    REQUIRE(heap.heapArray[2] == 6);
    REQUIRE(heap.heapArray[3] == 8);
    REQUIRE(heap.heapArray[4] == 12);
    REQUIRE(heap.heapArray[5] == 16);
    REQUIRE(heap.heapArray[6] == 10);
    REQUIRE(heap.heapArray[7] == 14);
    REQUIRE(heap.heapArray[8] == 20);
    REQUIRE(heap.heapArray[9] == 18);
    REQUIRE(heap.heapArray[10] == 24);
    
    std::stringstream ss;
    heap.printHeapToStream(ss);
    INFO("before calling percolateUp(idx), your BinHeap is: \n" << ss.str());
    
    SECTION("verify that percolateUp(idx) operates correctly when called on the root node") {
        heap.heapArray[1] = 1;
        heap.percolateUp(1);
        INFO("manually modified the root node data value from 2 to 1");
        INFO("called percolateUp(idx) on index 1 (i.e. root node)");
        
        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 1 6 8 12 16 10 14 20 18 24\n";
        INFO("\nafter calling percolateUp(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateUp(idx), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 1);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateUp(idx) operates correctly when called on a middle node that does not move") {
        heap.heapArray[4] = 9;
        heap.percolateUp(4);
        INFO("manually modified value in index 4, changed data value from 12 to 9");
        INFO("called percolateUp(idx) on index 4 (i.e. now node 9)");
        INFO("node 9 should not move");
        
        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 2 6 8 9 16 10 14 20 18 24\n";
        INFO("\nafter calling percolateUp(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateUp(idx), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 9);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateUp(idx) operates correctly when called on a middle node that moves up slightly") {
        heap.heapArray[4] = 5;
        heap.percolateUp(4);
        INFO("manually modified value in index 4, changed data value from 12 to 5");
        INFO("called percolateUp(idx) on index 4 (i.e. now node 5)");
        
        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 2 5 8 6 16 10 14 20 18 24\n";
        INFO("\nafter calling percolateUp(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateUp(idx), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 5);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 6);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateUp(idx) operates correctly when called on a middle node that moves up to the root") {
        heap.heapArray[4] = 1;
        heap.percolateUp(4);
        INFO("manually modified value in index 4, changed data value from 12 to 1");
        INFO("called percolateUp(idx) on index 4 (i.e. now node 1)");
        
        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 1 2 8 6 16 10 14 20 18 24\n";
        INFO("\nafter calling percolateUp(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateUp(idx), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 1);
        REQUIRE(heap.heapArray[2] == 2);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 6);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateUp(idx) operates correctly when called on a leaf node that does not move") {
        heap.heapArray[10] = 20;
        heap.percolateUp(10);
        INFO("manually modified value in index 10, changed data value from 24 to 20");
        INFO("called percolateUp(idx) on index 10 (i.e. now node 20)");
        INFO("node 20 should not move");
        
        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 2 6 8 12 16 10 14 20 18 20\n";
        INFO("\nafter calling percolateUp(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateUp(idx), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
        REQUIRE(heap.heapArray[10] == 20);
    }
    
    SECTION("verify that percolateUp(idx) operates correctly when called on a leaf node that moves up to a middle node") {
        heap.heapArray[9] = 5;
        heap.percolateUp(9);
        INFO("manually modified value in index 9, changed data value from 18 to 5");
        INFO("called percolateUp(idx) on index 9 (i.e. now node 5)");

        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 2 5 8 6 16 10 14 20 12 24\n";
        INFO("\nafter calling percolateUp(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateUp(idx), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 5);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 6);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 12);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateUp(idx) operates correctly when called on a leaf node that moves up to the root") {
        heap.heapArray[7] = 1;
        heap.percolateUp(7);
        INFO("manually modified value in index 7, changed data value from 14 to 1");
        INFO("called percolateUp(idx) on index 7 (i.e. now node 1)");
        
        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 1 6 2 12 16 10 8 20 18 24\n";
        INFO("\nafter calling percolateUp(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateUp(idx), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 1);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 2);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 8);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
        REQUIRE(heap.heapArray[10] == 24);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing percolateDown(idx) method on an empty BinHeap", "[PERCOLATEDOWN]") {
    BinHeap<int> heap;
    
    INFO("before calling percolateDown(idx), BinHeap should be empty");
    REQUIRE(heap.maxSize == 1);
    REQUIRE(heap.heapSize == 0);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);
    
    SECTION("verify that percolateDown(idx) operates correctly when node is inserted into empty BinHeap") {
        heap.heapArray[1] = 6;  // manually inserting a value
        heap.heapSize++;
        heap.percolateDown(1);
        INFO("manually inserted value 6 into BinHeap at index 1 (did NOT use insert(x) method)");
        INFO("called percolateDown(idx) on index 1 (i.e. root node)");
        REQUIRE(heap.maxSize == 1);
        REQUIRE(heap.heapSize == 1);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);
        REQUIRE(heap.heapArray[1] == 6);
    }
}


TEST_CASE("testing percolateDown(idx) method on a non-empty BinHeap", "[PERCOLATEDOWN]") {
    BinHeap<int> heap;
    heap.insert(6);
    heap.insert(12);
    heap.insert(8);
    heap.insert(18);
    heap.insert(16);
    heap.insert(10);
    heap.insert(14);
    heap.insert(20);
    heap.insert(2);
    heap.insert(24);
    
    INFO("inserted values 6, 12, 8, 18, 16, 10, 14, 20, 2, 24");
    const char *heapString = "\n"
        "  Current array size: 16\n"
        "  Current heap size: 10\n"
        "  Heap Elements: 2 6 8 12 16 10 14 20 18 24\n";
    INFO("\nbefore calling percolateDown(idx), BinHeap should be: " << heapString);
    REQUIRE(heap.maxSize == 16);        // check heap properties
    REQUIRE(heap.heapSize == 10);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);   // check heap contents
    REQUIRE(heap.heapArray[1] == 2);
    REQUIRE(heap.heapArray[2] == 6);
    REQUIRE(heap.heapArray[3] == 8);
    REQUIRE(heap.heapArray[4] == 12);
    REQUIRE(heap.heapArray[5] == 16);
    REQUIRE(heap.heapArray[6] == 10);
    REQUIRE(heap.heapArray[7] == 14);
    REQUIRE(heap.heapArray[8] == 20);
    REQUIRE(heap.heapArray[9] == 18);
    REQUIRE(heap.heapArray[10] == 24);
    
    std::stringstream ss;
    heap.printHeapToStream(ss);
    INFO("before calling percolateDown(idx), your BinHeap is: \n" << ss.str());
    
    SECTION("verify that percolateDown(idx) operates correctly when called on a root node that does not move") {
        heap.heapArray[1] = 1;
        heap.percolateDown(1);
        INFO("manually modified the root node data value from 2 to 1");
        INFO("called percolateDown(idx) on index 1 (i.e. root node)");
        
        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 1 6 8 12 16 10 14 20 18 24\n";
        INFO("\nafter calling percolateDown(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateDown(idx), your BinHeap is: \n" << ss2.str());

        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 1);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateDown(idx) operates correctly when called on a root node that moves down slightly") {
        heap.heapArray[1] = 13;
        heap.percolateDown(1);
        INFO("manually modified the root node data value from 2 to 13");
        INFO("called percolateDown(idx) on index 1 (i.e. root node)");
        
        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 6 12 8 13 16 10 14 20 18 24\n";
        INFO("\nafter calling percolateDown(idx), BinHeap should now be: " << heapString2);

        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateDown(idx), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 6);
        REQUIRE(heap.heapArray[2] == 12);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 13);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateDown(idx) operates correctly when called on a root node that moves down to a leaf") {
        heap.heapArray[1] = 99;
        heap.percolateDown(1);
        INFO("manually modified the root node data value from 2 to 99");
        INFO("called percolateDown(idx) on index 1 (i.e. root node)");

        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 6 12 8 18 16 10 14 20 99 24\n";
        INFO("\nafter calling percolateDown(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateDown(idx), your BinHeap is: \n" << ss2.str());

        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 6);
        REQUIRE(heap.heapArray[2] == 12);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 18);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 99);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateDown(idx) operates correctly when called on a middle node that does not move") {
        heap.heapArray[2] = 11;
        heap.percolateDown(2);
        INFO("manually modified value in index 2, changed data value from 6 to 11");
        INFO("called percolateDown(idx) on index 2 (i.e. now node 11)");
        INFO("node 11 should not move");

        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 2 11 8 12 16 10 14 20 18 24\n";
        INFO("\nafter calling percolateDown(idx), BinHeap should now be: " << heapString2);

        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateDown(idx), your BinHeap is: \n" << ss2.str());

        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 11);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateDown(idx) operates correctly when called on a middle node that moves down slightly") {
        heap.heapArray[2] = 15;
        heap.percolateDown(2);
        INFO("manually modified value in index 2, changed data value from 6 to 15");
        INFO("called percolateDown(idx) on index 2 (i.e. now node 15)");
        
        const char *heapString2 = "\n"
        "  Current array size: 16\n"
        "  Current heap size: 10\n"
        "  Heap Elements: 2 12 8 15 16 10 14 20 18 24\n";
        INFO("\nafter calling percolateDown(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateDown(idx), your BinHeap is: \n" << ss2.str());

        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 12);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 15);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 18);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateDown(idx) operates correctly when called on a middle node that moves down to a leaf") {
        heap.heapArray[2] = 99;
        heap.percolateDown(2);
        INFO("manually modified value in index 2, changed data value from 6 to 99");
        INFO("called percolateDown(idx) on index 2 (i.e. now node 99)");

        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 2 12 8 18 16 10 14 20 99 24\n";
        INFO("\nafter calling percolateDown(idx), BinHeap should now be: " << heapString2);

        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateDown(idx), your BinHeap is: \n" << ss2.str());
        
        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 12);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 18);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 99);
        REQUIRE(heap.heapArray[10] == 24);
    }
    
    SECTION("verify that percolateDown(idx) operates correctly when called on a leaf node that does not move") {
        heap.heapArray[9] = 99;
        heap.percolateDown(9);
        INFO("manually modified value in index 9, changed data value from 18 to 99");
        INFO("called percolateDown(idx) on index 9 (i.e. now node 99)");
        INFO("node 99 should not move");
        
        const char *heapString2 = "\n"
            "  Current array size: 16\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 2 6 8 12 16 10 14 20 99 24\n";
        INFO("\nafter calling percolateDown(idx), BinHeap should now be: " << heapString2);
        
        std::stringstream ss2;
        heap.printHeapToStream(ss2);
        INFO("after calling percolateDown(idx), your BinHeap is: \n" << ss2.str());

        REQUIRE(heap.maxSize == 16);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 8);
        REQUIRE(heap.heapArray[4] == 12);
        REQUIRE(heap.heapArray[5] == 16);
        REQUIRE(heap.heapArray[6] == 10);
        REQUIRE(heap.heapArray[7] == 14);
        REQUIRE(heap.heapArray[8] == 20);
        REQUIRE(heap.heapArray[9] == 99);
        REQUIRE(heap.heapArray[10] == 24);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing buildHeap(arr, arrSize) method on a BinHeap", "[BUILDHEAP]") {
    BinHeap<int> heap;
    
    INFO("before calling buildHeap(arr, arrSize), BinHeap should be empty");
    REQUIRE(heap.maxSize == 1);
    REQUIRE(heap.heapSize == 0);
    REQUIRE(heap.heapArray != nullptr);
    REQUIRE(heap.heapArray[0] == -1);
    
    SECTION("verify that buildHeap(arr, arrSize) operates correctly when input array contains a single value") {
        int arr[] = { 6 };
        int * origHeapArrayPtr = heap.heapArray;
        heap.buildHeap(arr, 1);
        
        INFO("created the following array: [ 6 ]");
        INFO("called buildHeap(arr, arrSize) with the newly created array");
        const char *heapString = "\n"
            "  Current array size: 1\n"
            "  Current heap size: 1\n"
            "  Heap Elements: 6\n";
        INFO("\nafter calling buildHeap(arr, arrSize), BinHeap should be: " << heapString);
        
        std::stringstream ss;
        heap.printHeapToStream(ss);
        INFO("after calling buildHeap(arr, arrSize), your BinHeap is: \n" << ss.str());
        
        REQUIRE(heap.maxSize == 1);         // check heap properties
        REQUIRE(heap.heapSize == 1);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);  // buildHeap should be creating a new backing array
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 6);
    }
    
    SECTION("verify that buildHeap(arr, arrSize) operates correctly when input array contains many value") {
        int arr[] = { 24, 20, 18, 16, 14, 12, 10, 8, 6, 2 };
        int * origHeapArrayPtr = heap.heapArray;
        heap.buildHeap(arr, 10);
        INFO("created the following array: [ 24, 20, 18, 16, 14, 12, 10, 8, 6, 2 ]");
        INFO("called buildHeap(arr, arrSize) with the newly created array");
        const char *heapString = "\n"
            "  Current array size: 10\n"
            "  Current heap size: 10\n"
            "  Heap Elements: 2 6 10 8 14 12 18 24 16 20\n";
        INFO("\nafter calling buildHeap(arr, arrSize), BinHeap should be: " << heapString);
        
        std::stringstream ss;
        heap.printHeapToStream(ss);
        INFO("after calling buildHeap(arr, arrSize), your BinHeap is: \n" << ss.str());
        
        REQUIRE(heap.maxSize == 10);        // check heap properties
        REQUIRE(heap.heapSize == 10);
        REQUIRE(heap.heapArray != nullptr);
        REQUIRE(heap.heapArray != origHeapArrayPtr);  // buildHeap should be creating a new backing array
        REQUIRE(heap.heapArray[0] == -1);   // check heap contents
        REQUIRE(heap.heapArray[1] == 2);
        REQUIRE(heap.heapArray[2] == 6);
        REQUIRE(heap.heapArray[3] == 10);
        REQUIRE(heap.heapArray[4] == 8);
        REQUIRE(heap.heapArray[5] == 14);
        REQUIRE(heap.heapArray[6] == 12);
        REQUIRE(heap.heapArray[7] == 18);
        REQUIRE(heap.heapArray[8] == 24);
        REQUIRE(heap.heapArray[9] == 16);
        REQUIRE(heap.heapArray[10] == 20);
    }
}


/* **************************************************************** */
/* **************************************************************** */



/* **************************************************************** */
/* **************************************************************** */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
/* **************************************************************** */
/* **************************************************************** */


int main( int argc, char const* const* const argv )
{
    // global setup...
    std::cout << BOLDCYAN << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << "############################# Running Unit Tests ##############################" << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << RESET << std::endl;

    int result = Catch::Session().run( argc, argv );

    // global clean-up...
    std::cout << BOLDCYAN << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << "########################### Done Running Unit Tests ###########################" << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << RESET << std::endl;

    return result;
}
