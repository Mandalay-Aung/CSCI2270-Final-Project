#include <gtest/gtest.h>
#include "PriorityQueue.hpp"
#include "enemy_graph.hpp"
#include "hash.hpp"
#include <string>
#include <vector>
using namespace std;

class CrawlTest : public ::testing::Test {
protected:
    EnemyGraph* graph1;
    
    void SetUp() override {
        // This runs before each test to instantiate 
            graph1 = new EnemyGraph();
        
    }
    void TearDown() override {
        // This runs after each test
        delete graph1;
    }
};

TEST_F(CrawlTest, searchgraphHappyPath) {

        //Given a graph with a vertex
        graph1->addVertex("fong");

        // When we search for that vertex
        Vertex* result = graph1->searchVertex("fong");

        //Then we expect the vertex return to Not equal a nullptr (EXPECT_NE means expect not equal)
        EXPECT_NE(result, nullptr);
        EXPECT_EQ(result->id, "fong");

}

TEST_F(CrawlTest, searchGraphErrorPath) {
    //Given an empty graph

    //When we try to search for a vertex
    //We expect an invalid argument error to be thrown
    EXPECT_THROW(graph1->searchVertex("doesnt exist"), std::invalid_argument);


}


// TODO Add an Edge Case test of the graph here
//////////////////////////////////////////////
TEST_F(CrawlTest, addedDuplicateVertex) { // My choice of edgecase is a duplicate vertex wanting to be added
    // GIVEN an empty graph
    // WHEN adding a preexisting vertex
    // THEN I should expect nullptr returned

    Vertex *a1 = graph1->addVertex("fart"); // adding first vertex

    ASSERT_NE(a1, nullptr); // expected results
    ASSERT_EQ(a1->id, "fart");

    Vertex *a2 = graph1->addVertex("fart"); // copy will be ignored
    EXPECT_EQ(a2, nullptr);
    //EXPECT_THROW(graph1->addVertex("fart"), std::invalid_argument);

    Vertex *found = graph1->searchVertex("fart"); // the original a1 of the same name can still be traced
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->id, "fart");
}
//////////////////////////////////////////////


//  ********   ******* PRIORITY QUEUE TESTS   ***** ****** *******
//When testing priority Queue you may wish to update line 63 to specify the capacity of the queue in the constructor

class PriorityTest : public ::testing::Test {
protected:

    PriorityQ* priority1;
    
    void SetUp() override {
        // This runs before each test to instantiate 
            priority1 = new PriorityQ();
        
    }
    
    void TearDown() override {
        // This runs after each test
        delete priority1;
    }
};


//////////////////////////////////////////////
TEST_F(PriorityTest, PriorityQueueInsertHappyPath) {
        // GIVEN: A priority queue with capacity
        // WHEN: We insert a valid item 
        // THEN: The item should be retrievable via peek 

        PriorityQ pq(2); // making capacity 2 items as that is the comparision I'm making for highest damage
        pq.insertElement({"Wiggly Wizard", "Staff of Immobility", 40, "Everybody freeze!"});
        pq.insertElement({"Frost Giant", "Blizzard Fist", 1500, "I never saw it coming!"});

        ItemInfo *frontItem = pq.peek(); // peek front of the queue
        ASSERT_NE(frontItem, nullptr);

        EXPECT_EQ(frontItem->itemName, "Blizzard Fist"); // expected result as Frost Giants damage 1500 is > 40 Wiggly Wizard
        EXPECT_EQ(frontItem->damage, 1500);
        
}
//////////////////////////////////////////////



// TO DO add more tests of your priority queue here
//////////////////////////////////////////////
TEST_F(PriorityTest, emptyPop) {
        // GIVEN: A empty queue
        // WHEN: pop the queue
        // THEN: throw an exception
        PriorityQ pq(2);
        pq.pop();                      // should do nothing
        EXPECT_EQ(pq.peek(), nullptr); // still empty

}

TEST_F(PriorityTest, emptyPeek) {
        // GIVEN an empty queue with capacity
        // WHEN peek the queue 
        // THEN peek should return nullptr as queue empty
        PriorityQ pq(2);
        ItemInfo *topItem = pq.peek();
        EXPECT_EQ(topItem, nullptr);

}
//////////////////////////////////////////////
