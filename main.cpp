/* *
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Mian Usman Naeem Kakakhel
* Description : description of your code
*/

/**
 * CS 202 - HW 4
 * A main file
 * Please make sure that your code compiles and runs with this main file
 */
#include "graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
/*You can add additional libraries here to read and process the dataset*/

using namespace std;

int main() {
    /*YOUR IMPLEMENTATION*/
    Graph myGraph;
    
    ifstream myFile;
    myFile.open ("flightDataset.txt");

    string myLine;

    while ( getline (myFile,myLine) )
    {
        int loc1 = myLine.find(";");//find the first city
        string remain = myLine.substr(loc1 + 1);
        string airport1 = myLine.substr(0,myLine.length() - remain.length() - 1);

        int loc2 = remain.find(";");// find the second city
        string num = remain.substr(loc2 + 1);//find the passengers
        string airport2 = remain.substr(0,remain.length() - num.length() - 1);

        myGraph.addAirport(airport1);//add both the airports to teh graph
        myGraph.addAirport(airport2);
        int number;
        std::istringstream iss (num);
        iss >> number;
        myGraph.addConnection(airport1, airport2, number);//add the connection to both the cities
    }

    myFile.close();



    //testing

    cout << endl << "Adjacent Airports to Norwich!" << endl;
    list<string > d = myGraph.getAdjacentAirports("NORWICH");
    for (list<string>::iterator listIT = d.begin(); listIT != d.end(); listIT++)
    {
        cout << *listIT << endl;
    }

    cout << endl << "Total passengers Kirkwall" << endl;
    cout << myGraph.getTotalPassengers("KIRKWALL") << endl;
    
    cout << endl << "minimum spanning tree!" << endl;
    list<pair <string, string> > b = myGraph.findMST();
    for (list<pair <string, string> >::iterator listIT = b.begin(); listIT != b.end(); listIT++)
    {
        cout << listIT->first << "-" << listIT->second << endl;
    }

    cout << endl << "shortest path between kirkwall and jersey!" << endl;
    list<string> a = myGraph.findShortestPath("KIRKWALL", "JERSEY");
    for (list<string>::iterator listIT = a.begin(); listIT != a.end(); listIT++)
    {
        cout << *listIT << endl;
    }

    cout << endl << "Deleting Edinburgh now!" << endl;
    myGraph.deleteAirport("EDINBURGH");
    
    cout << endl << "shortest path between kirkwall and jersey again to see if edinburgh is deleted!" << endl;
    list<string> c = myGraph.findShortestPath("KIRKWALL", "JERSEY");
    for (list<string>::iterator listIT = c.begin(); listIT != c.end(); listIT++)
    {
        cout << *listIT << endl;
    }

	return 0;
}
// End of main file
