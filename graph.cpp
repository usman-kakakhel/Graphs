/* *
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Mian Usman Naeem Kakakhel
* Description : description of your code
*/

/** @file graph.cpp
 * An adjacency list representation of an undirected weighted graph. 
*/

#include "graph.h"
/*Do not add new libraries or files*/

Graph::Graph()
{
}  // end constructor

void Graph::addAirport(const string& airportName)
{   /*YOUR IMPLEMENTATION*/
    if (adjList.find(airportName) == adjList.end()) //if the airport does not exist in the list already
    {
        list<node> myList;  //to insert this node in adjList
        adjList.insert(pair< string, list<node> >(airportName, myList));
    }
    
}  // end addPerformer

void Graph::addConnection(const string& airport1, const string& airport2, int numOfPassengers)
{   /*YOUR IMPLEMENTATION*/
    map<string, list<node> >::iterator it, it1; //make 2 iterators
    it = adjList.find(airport1); //get the iterator to the 2 cities in the adjList
    it1 = adjList.find(airport2);
    if (it != adjList.end() && it1 != adjList.end())//If both of the cities exist then
    {
        node a, b;
        a.airportName = airport1;
        a.numOfPassengers = numOfPassengers;
        b.airportName = airport2;
        b.numOfPassengers = numOfPassengers;

        it->second.push_back(b);//push both of the nodes in with the new data
        it1->second.push_back(a);
    }


}  // end addConnection

list<string> Graph::getAdjacentAirports(const string& airportName)
{   /*YOUR IMPLEMENTATION*/
    list<string> myList;

    map<string, list<node> >::iterator mapIT;//get an iterator
    mapIT = adjList.find(airportName); //find the city
    if (mapIT != adjList.end())//if city exists
    {
        for (list<node>::iterator listIT = (mapIT->second).begin(); listIT != (mapIT->second).end(); listIT++)//get the names of all the airports
        {
            myList.push_back((*listIT).airportName);
        }
    }
    return myList;//retirn those names

}  // end getAdjacentAirports

int Graph::getTotalPassengers(const string& airportName)
{   /*YOUR IMPLEMENTATION*/
    int sum = 0;

    map<string, list<node> >::iterator mapIT = adjList.find(airportName); //get an iterator
    if (mapIT != adjList.end())//if the city exists
    {
        for (list<node>::iterator listIT = (mapIT->second).begin(); listIT != (mapIT->second).end(); listIT++)//add all the ints in nodes to sum
            sum = sum + (*listIT).numOfPassengers;
    }

    return sum;

}  // end getTotalPassengers


list<string> Graph::findShortestPath(const string& airport1, const string& airport2)
{   /*YOUR IMPLEMENTATION*/
    list<string> myPathList; //the list to be returned
    map<string, string> visitedMap; //the map that has the already visited cities
    list<string> queue; //the queue which will help in breadth first traversal
    bool connection = false;

    if (adjList.find(airport1) != adjList.end() && adjList.find(airport2)!= adjList.end()) //if both cities exist
    {
        visitedMap.insert(pair<string, string>(airport1, ""));//mark the first city as visited
        queue.push_back(airport1);//push the airport in the queue

        while(!queue.empty()) //if the queue is not empty
        {
            string airport = queue.front(); // getthe airport at the top
            queue.pop_front();
            if (airport == airport2)//if required airport reached, then exit the while and mark found as true
            {
                connection = true;
                break;
            }

            map<string, list<node> >::iterator mapIT = adjList.find(airport); //get the iteratr to the city which was popped
            for (list<node>::iterator listIT = (mapIT->second).begin(); listIT != (mapIT->second).end(); listIT++)
            {
                string testAirport = listIT->airportName;
                if (visitedMap.find(testAirport) == visitedMap.end())//for every of its unvisited city, mark the cities as visited and insert in the queue.
                {
                    visitedMap.insert(pair<string, string>(testAirport, airport));
                    queue.push_back(testAirport);
                }
            }
        }

    }
    if (!connection)
        myPathList.clear();//if connection was not made, clear the list
    else
    {
        string testAirport = airport2;
        while (testAirport != "")//trace back the way to the original city from the path you came from as you have the name of the parent city as well
        {
            myPathList.push_front(testAirport);
            testAirport = visitedMap.find(testAirport)->second;
        }
    }
    
    
    return myPathList;//give back the new list

}  // end findShortestPath

list< pair<string, string> > Graph::findMST()
{   /*YOUR IMPLEMENTATION*/
    list<pair<string, string> > myTreeList; //the list with the MST
    map<string, string> visitedMap; //the map for visited nodes
    list<pair<string, node> > testPair;

    if (adjList.empty()) //is the Map is empty return an empty list
        return myTreeList;
    
    visitedMap.insert(pair<string, string>(adjList.begin()->first, "")); //mark a city at random as visited


    while(visitedMap.size() < adjList.size()) //while all of the cities have not been marked then
    {
        testPair.clear();
        node testNode;
        testNode.airportName = "";
        testNode.numOfPassengers = -1;
        testPair.push_front(pair<string, node>("", testNode)); //put the test nodes to the test values

        for (map<string, string>::iterator mapIT = visitedMap.begin(); mapIT != visitedMap.end(); mapIT++)
        {
            for (list<node>::iterator listIT = (adjList.find(mapIT->first))->second.begin(); listIT != (adjList.find(mapIT->first))->second.end(); listIT++)
            {
                if (visitedMap.find(listIT->airportName) == visitedMap.end()) // for every city in the visited map, find the smallest route to an unvisited city
                {
                    if (testPair.front().second.numOfPassengers == -1 || listIT->numOfPassengers < testPair.front().second.numOfPassengers)
                    {
                        testPair.clear();// if the path is shorter, or it is a test value in the test pair, change the test pair
                        testNode.airportName = mapIT->first;
                        testNode.numOfPassengers = listIT->numOfPassengers;
                        testPair.push_front(pair<string, node>(listIT->airportName, testNode));
                    }
                }
            }
        }

        visitedMap.insert(visitedMap.begin(), pair<string, string>(testPair.front().first, testPair.front().second.airportName));
        myTreeList.push_back(pair<string, string>(testPair.front().second.airportName, testPair.front().first));
    }
    return myTreeList;

}  // end findMST

void Graph::deleteAirport(const string& airportName)
{   /*YOUR IMPLEMENTATION*/
    map<string, list<node> >::iterator mapITT = adjList.find(airportName);
    bool del = false;
    list<node>::iterator a;

    adjList.erase(mapITT);
    for (map<string, list<node> >::iterator mapIT = adjList.begin(); mapIT != adjList.end(); mapIT++)
    {
        for (list<node>::iterator listIT = (mapIT->second).begin(); listIT != (mapIT->second).end(); listIT++)
        {
            if (listIT->airportName == airportName)
            {
                del = true;
                a = listIT;
            }
            
        }
        if (del)
        {
            (mapIT->second).erase(a);
            del = false;
        }
    }


}  // end deleteAirport

