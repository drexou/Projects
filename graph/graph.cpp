#include "graph.hpp"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <deque>
using namespace std;



Graph::Graph(const std::string& filename)
{
    ifstream graphFile;
    graphFile.open(filename);
    string str;
    numEdges = 0;
    getline(graphFile, str); //stores whether this graph is weighted
    if(str == "Weighted")
    {
        currWeightStatus = isItWeighted::weighted;
    }
    else
    {
        currWeightStatus = isItWeighted::unweighted;
    }
    getline(graphFile, str); // " but for directed
    if(str == "Directed")
    {
        currDirectedStatus = isItDirected::directed;
    }
    else
    {
        currDirectedStatus = isItDirected::undirected;
    }
    getline(graphFile, str); // stores the format of the graph
    if(str == "AdjMatrix")
    {
        currFormat = format::AdjMatrix;
    }  
    else if(str == "AdjList")
    {
        currFormat = format::AdjList;
    }
    else
    {
        currFormat = format::ListEdges;
    }
    getline(graphFile, str);
    numNodes = stoi(str);
    int src = 0;
    int tempX = 0;
    //constructors for adjMatrix
    if(currFormat == format::AdjMatrix && currWeightStatus == isItWeighted::weighted && currDirectedStatus == isItDirected::directed)
    {
        while(getline(graphFile, str))
        {
            int dest = 0;
            stringstream iss(str);
            int number;
            vector<int> myNumbers;
            while (iss >> number)
                myNumbers.push_back(number); //creates a vector of ints that contains the data
            for(int i : myNumbers)
            {
                if(i != 0)
                {
                    //stores weights with their coordinates in a tuple
                    graphPoints.push_back(tuple<int,int,int>(src, dest, i));
                    numEdges += 1;
                }
                dest += 1;
            }
            src += 1;
        }
    }
    else if(currFormat == format::AdjMatrix && currWeightStatus == isItWeighted::weighted && currDirectedStatus == isItDirected::undirected)
    {
        while(getline(graphFile, str))
        {
            int dest = tempX;
            tempX += 1;
            stringstream iss(str);
            int number;
            vector<int> myNumbers;
            while (iss >> number)
                myNumbers.push_back(number); //creates a vector of ints that contains the data
            for(int i : myNumbers)
            {
                if(i != 0)
                {
                    //stores weights with their coordinates in a tuple
                    graphPoints.push_back(tuple<int,int,int>(src, dest, i));
                    numEdges += 1;
                }
                dest += 1;
            }
            src += 1;
        }
    }
    else if(currFormat == format::AdjMatrix && currWeightStatus == isItWeighted::unweighted && currDirectedStatus == isItDirected::directed)
    {
        while(getline(graphFile, str))
        {
            int dest = 0;
            stringstream iss(str);
            char value;
            vector<char> myValues;
            while (iss >> value)
                myValues.push_back(value); //creates a vector of ints that contains the data
            for(char i : myValues)
            {
                if(i == 'T')
                {
                    //stores weights with their coordinates in a tuple
                    graphPoints.push_back(tuple<int,int,int>(src, dest, 0));
                    numEdges += 1;
                }
                dest += 1;
            }
            src += 1;
        }
    }
    else if(currFormat == format::AdjMatrix && currWeightStatus == isItWeighted::unweighted && currDirectedStatus == isItDirected::undirected)
    {
        while(getline(graphFile, str))
        {
            int dest = tempX;
            tempX += 1;
            stringstream iss(str);
            char value;
            vector<char> myValues;
            while (iss >> value)
                myValues.push_back(value); //creates a vector of ints that contains the data
            for(int i : myValues)
            {
                if(i == 'T')
                {
                    //stores weights with their coordinates in a tuple
                    graphPoints.push_back(tuple<int,int,int>(src, dest, 0));
                    numEdges += 1;
                }
                dest += 1;
            }
            src += 1;
        }
    }
    //constructors for adjList
    else if(currFormat == format::AdjList)
    {
        int src = 0;
        while(getline(graphFile, str))
        {
            stringstream iss(str);
            int number;
            vector<int> myNumbers;
            while(iss >> number)
                myNumbers.push_back(number);
            int index = 0;
            if(currWeightStatus == isItWeighted::unweighted)
            {
                for(int dest : myNumbers)
                {
                    graphPoints.push_back(tuple<int,int,int>(src, dest, 0));
                    numEdges += 1;
                    index += 1;
                }
            }
            else
            {
                for(int dest : myNumbers)
                {
                    if (index % 2 == 0)
                    {
                        graphPoints.push_back(tuple<int,int,int>(src, dest, myNumbers[index+1]));
                        numEdges += 1;
                    }
                    index += 1;
                }
            }
            src += 1;
        }
    }
    //constructors for edgeList
    else if(currFormat == format::ListEdges)
    {
        while(getline(graphFile, str))
        {
            stringstream iss(str);
            int number;
            vector<int> myNumbers;
            while(iss >> number)
                myNumbers.push_back(number);
            if(currWeightStatus == isItWeighted::unweighted)
                graphPoints.push_back(tuple<int,int,int>(myNumbers[0], myNumbers[1], 0));
            else
                graphPoints.push_back(tuple<int,int,int>(myNumbers[0], myNumbers[1], myNumbers[2]));
            numEdges += 1;
        }
    }
    checkConditions(graphPoints);
}

//second constructor: unweighted
Graph::Graph(unsigned numVertices, const std::vector<std::pair<unsigned, unsigned>>& edges, bool isDirected)
{
    numEdges = 0;
    currWeightStatus = isItWeighted::unweighted;
    if(isDirected == true)
        currDirectedStatus = isItDirected::directed;
    else
        currDirectedStatus = isItDirected::undirected;
    numNodes = (int) numVertices;

    for(pair<unsigned, unsigned> pair : edges)
    {
        graphPoints.push_back(tuple<int,int,int>((int)get<0>(pair),(int)get<1>(pair),0));
        numEdges += 1;
    }
    checkConditions(graphPoints);
}

//third constructor, weighted
Graph::Graph(unsigned numVertices, const std::vector<std::tuple<unsigned, unsigned, int>>& edges, bool isDirected)
{
    numEdges = 0;
    currWeightStatus = isItWeighted::weighted;
    if(isDirected == true)
        currDirectedStatus = isItDirected::directed;
    else
        currDirectedStatus = isItDirected::undirected;
    numNodes = (int) numVertices;

    for(tuple<unsigned, unsigned, int> tuples : edges)
    {
        if(get<2>(tuples) != 0)
        {
            graphPoints.push_back(tuple<int,int,int>((int)get<0>(tuples),(int)get<1>(tuples),get<2>(tuples)));
            numEdges += 1;
        }
        else
            throw std::logic_error{"Condition 4 not met"}; // condition 4
    }
    checkConditions(graphPoints);
}

/***********************************************
 accessor methods
 **********************************************/
bool Graph::isWeighted() const
{
    if(currWeightStatus == isItWeighted::weighted)
        return true;
    else
        return false;
}
bool Graph::isDirected() const
{
    if(currDirectedStatus == isItDirected::directed)
        return true;
    else
        return false;
}
unsigned Graph::getNumVertices() const
{
    return numNodes;
}
unsigned Graph::getNumEdges() const
{
    return numEdges;
}
vector<vector<int>> Graph::getAdjacencyMatrix() const
{
    vector<vector<int>> myMatrix;
    for(int i=0; i<numNodes; i++) //initialize a vector of 0's
    {
        vector<int> toPush;
        for(int j=0; j<numNodes; j++)
        {
            if(currWeightStatus == isItWeighted::weighted)
                toPush.push_back(0);
            else
                toPush.push_back(1); //initialize to 1's if unweighted
        }
        myMatrix.push_back(toPush);
    }

    for(int i=0; i<numEdges; i++) //find all values and add them into the matrix
    {
        myMatrix[get<0>(graphPoints[i])][get<1>(graphPoints[i])] = get<2>(graphPoints[i]);
        if(currDirectedStatus == isItDirected::undirected)
            myMatrix[get<1>(graphPoints[i])][get<0>(graphPoints[i])] = get<2>(graphPoints[i]);
    }
    /*
     * The reason I did this initializing in such a roundabout manner
     * is because in an unweighted graph, my values are all 0's, so
     * therefore I will just switch the values at the end of making my
     * adj matrix
    */
    if(currWeightStatus == isItWeighted::unweighted)
    {
        for(int i=0; i<numNodes; i++)
        {
            for(int j=0; j<numNodes; j++)
            {
                if(myMatrix[i][j] == 0)
                    myMatrix[i][j] = 1;
                else
                    myMatrix[i][j] = 0; // this segment flips the numbers if it is unweighted
            }
        }
    }
    return myMatrix;
}
vector<vector<pair<unsigned, int>>> Graph::getAdjacencyList() const
{
    vector<vector<pair<unsigned, int>>> myList(numNodes);
    for(int i=0; i<numEdges; i++)
    {
        int weight;
        if(currWeightStatus == isItWeighted::unweighted)
            weight = 1;
        else
            weight = get<2>(graphPoints[i]);
        myList[get<0>(graphPoints[i])].push_back(pair<unsigned, int> ((unsigned)get<1>(graphPoints[i]),weight));
        if(currDirectedStatus == isItDirected::undirected)
        {
            myList[get<1>(graphPoints[i])].push_back(pair<unsigned, int> ((unsigned)get<0>(graphPoints[i]),weight));
        }
    }
    return myList;
}
vector<unsigned> Graph::getBFSOrdering(unsigned start) const
{
    if((int) start >= numNodes)
        throw logic_error{"start too high"};
    vector<unsigned> myVector;
    deque<unsigned> q;
    unsigned currNode = start;

    vector<vector<pair<unsigned, int>>> myList(numNodes);
    for(int i=0; i<numEdges; i++)
    {
        int weight;
        if(currWeightStatus == isItWeighted::unweighted)
            weight = 1;
        else
            weight = get<2>(graphPoints[i]);
        myList[get<0>(graphPoints[i])].push_back(pair<unsigned, int> ((unsigned)get<1>(graphPoints[i]),weight));
        if(currDirectedStatus == isItDirected::undirected)
            myList[get<1>(graphPoints[i])].push_back(pair<unsigned, int> ((unsigned)get<0>(graphPoints[i]),weight));
    } // adjlist

    unsigned done = 0;
    while((int) myVector.size() < numNodes)
    {
        for(pair<unsigned,int> pair : myList[currNode])
        {
            for(unsigned item : myVector)
            {
                if(item == (unsigned)get<0>(pair))
                {
                    done = 1;
                }
            }
            for(unsigned item : q)
            {
                if(item == (unsigned)get<0>(pair))
                {
                    done = 1;
                }
            }
            if(done==0)
            {
                q.push_back((unsigned)get<0>(pair));
            }
            done = 0;
        }
        myVector.push_back(currNode);
        currNode = q.front();
        if(q.size() == 0)
            break;
        q.pop_front();
    }
    return myVector;
}
vector<unsigned> Graph::getDFSOrdering(unsigned start) const
{
    if((int) start >= numNodes)
        throw logic_error{"start too high"};
    vector<unsigned> myVector;
    deque<unsigned> q;
    unsigned currNode = start;

    vector<vector<pair<unsigned, int>>> myList(numNodes);
    for(int i=0; i<numEdges; i++)
    {
        int weight;
        if(currWeightStatus == isItWeighted::unweighted)
            weight = 1;
        else
            weight = get<2>(graphPoints[i]);
        myList[get<0>(graphPoints[i])].push_back(pair<unsigned, int> ((unsigned)get<1>(graphPoints[i]),weight));
        if(currDirectedStatus == isItDirected::undirected)
            myList[get<1>(graphPoints[i])].push_back(pair<unsigned, int> ((unsigned)get<0>(graphPoints[i]),weight));
    } // adjlist

    unsigned done = 0;
    while((int) myVector.size() < numNodes)
    {
        for(pair<unsigned,int> pair : myList[currNode])
        {
            for(unsigned i : myVector)
            {
                if(i == (unsigned)get<0>(pair))
                    done = 1;
            }
            if(done==0)
                q.push_back((unsigned)get<0>(pair));
            done = 0;
        }
        myVector.push_back(currNode);
        if(q.size() == 0)
            break;
        currNode = q.back();
        q.pop_back();
    }
    return myVector;
}

vector<vector<bool>> Graph::getTransitiveClosure() const
{
    vector<vector<bool>> myMatrix;
    vector<bool> myList;

    for(int i=0; i<numNodes; i++) //initialize a vector of 0's
    {
        vector<bool> toPush;
        for(int j=0; j<numNodes; j++)
            toPush.push_back(0);
        myMatrix.push_back(toPush);
    }
    for(int i=0; i<numNodes; i++)
        myMatrix[i][i] = 1;

    for(int i=0; i<numEdges; i++) //find all values and add them into the matrix
    {
        myMatrix[get<0>(graphPoints[i])][get<1>(graphPoints[i])] = 1;
        if(currDirectedStatus == isItDirected::undirected)
            myMatrix[get<1>(graphPoints[i])][get<0>(graphPoints[i])] = 1;
    }
    
    for(int i=0; i<numNodes; i++)
    {
        for(int j=0; j<numNodes; j++)
        {
            if(myMatrix[i][j] == 1)
            {
                for(int k=0; k<numNodes; k++)
                {
                    if(myMatrix[j][k] == 1)
                        myMatrix[i][k] = 1;
                }
            }
        }
    }



    return myMatrix;
}
/*
int main(int argc, char** argv)
{
    Graph g1(argv[1]);

    vector<vector<int>> m3 = g1.getAdjacencyMatrix();
    vector<vector<pair<unsigned,int>>> l3 = g1.getAdjacencyList();
    // vector<unsigned> v3 = g1.getBFSOrdering(stoi(argv[2]));
    vector<vector<bool>> m6 = g1.getTransitiveClosure();

    for(vector<bool> vector : m6)
    {
        for(bool value : vector)
        {
            cout << value << " ";
        }
        cout << endl;
    }
    // vector<unsigned> v4 = g1.getDFSOrdering(0);

    // cout << "============================" << endl;
    // for(unsigned i : v3)
    // {
    //     cout << i << endl;
    // }

    // int index = 0;
    // for(vector<pair<unsigned, int>> pairs : l3)
    // {
    //     for(pair<unsigned, int> pair : pairs)
    //     {
    //         cout << index << " " << get<0>(pair) << " " << get<1>(pair) << endl;
    //     }
    //     index += 1;
    // }

    // for(vector<int> vector : m3)
    // {
    //     for(int myInt : vector)
    //     {
    //         cout << myInt << " ";
    //     }
    //     cout << endl;
    // }

    return 1;
}*/