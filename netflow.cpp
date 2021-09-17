#include "netflow.hpp"
#include <iostream>
#include <queue>
using namespace std;

#include <stdexcept>

/**
 * For your convenience (so that you do not have to type out all of these),
 * I provide the exception messages below.
 * FYI some may argue that const std::string objects are preferable over
 * macros here.
 */
#define ERR_NONEXISTENT_VERTEX "At least one edge is to a nonexistent vertex."
#define ERR_UNSORTED_NEIGHBORS "Found at least one unsorted neighbor list."
#define ERR_DISCONNECTED "Flow network is disconnected graph."
#define ERR_SRC "Flow network does not contain exactly one source."
#define ERR_SINK "Flow network does not contain exactly one sink."

void check1(const AdjList& flowNetwork, unsigned n)

{
    for(vector<NeighborEntry> neighbors: flowNetwork)
    {
        for(NeighborEntry neighbor: neighbors)
        {
            if(neighbor.neighbor >= n)
            {
                throw logic_error{ERR_NONEXISTENT_VERTEX};
            }
        }
    }
}
void check2(const AdjList& flowNetwork, unsigned n)
{
    for(vector<NeighborEntry> neighbors : flowNetwork)
    {
        unsigned m = neighbors.size(); //temp size of each neighbors vector
        for(unsigned i=0; i<m; i++)
        {
            if(i==0)
                continue;
            else if(neighbors[i].neighbor < neighbors[i-1].neighbor)
            {
                throw logic_error{ERR_UNSORTED_NEIGHBORS};
            }
        }
    }
}

vector<int> visit(const AdjList& flowNetwork, vector<int> visited, int currNode)
{
    visited[currNode] = 1; //marks visited
    vector<NeighborEntry> currVec = flowNetwork[currNode]; //initialies neighbors
    for(NeighborEntry neighbor : currVec)
    {
        if(visited[neighbor.neighbor] == 0)
        {
            visited = visit(flowNetwork, visited, neighbor.neighbor); //recurrsively marks if each node is visited
        }
    }
    return visited;
}
void check3(const AdjList& flowNetwork, unsigned n, unsigned source)
{
    vector<int> visited(n, source);
    visited = visit(flowNetwork, visited, 0);
    for(int num : visited)
    {
        if(num == 0)
        {
            throw logic_error{ERR_DISCONNECTED};
        }
    }
}

unsigned check4(const AdjList& flowNetwork, unsigned n)
{
    vector<unsigned> inDegree(n, 0);
    for(unsigned i=0; i<n; i++)
    {
        for(NeighborEntry neighbor : flowNetwork[i])
        {
            inDegree[neighbor.neighbor] = 1;
        }
    }
    for(unsigned i=0; i<n; i++)
    {
        if(inDegree[i] == 0) //check for 1 indegree of 0
        {
            for(unsigned j=0; j<n; j++)
            {
                if(inDegree[j] == 0 && i!=j) // check for more than 1 indegree of 0
                    throw logic_error{ERR_SRC};
            }
            return i;
        }
    }
    throw logic_error{ERR_SRC};
}

unsigned check5(const AdjList& flowNetwork, unsigned n)
{
    vector<unsigned> outDegree(n, 0);
    for(unsigned i=0; i<n; i++)
        outDegree[i] = flowNetwork[i].size();
    for(unsigned i=0; i<n; i++)
    {
        if(outDegree[i] == 0) //check for 1 indegree of 0
        {
            for(unsigned j=0; j<n; j++)
            {
                if(outDegree[j] == 0 && i!=j) // check for more than 1 indegree of 0
                    throw logic_error{ERR_SRC};
            }
            return i;
        }
    }
    throw logic_error{ERR_SRC};
}

void printList(const AdjList& flowNetwork)
{
    cout << "s d w" << endl;
    unsigned n = flowNetwork.size();
    for(unsigned i=0; i<n; i++)
    {
        for(NeighborEntry neighbor : flowNetwork[i])
            cout << i << " " << neighbor.neighbor << " " << neighbor.weight << endl;
    }
}

// function returns true if there is a path through the residual graph, and also a list for flows
bool bfs(vector<vector<int>>& resFlow, unsigned source, unsigned sink, vector<int>& path)
{
    unsigned n = resFlow[1].size();
    vector<unsigned> visited(n, 0);
    
    unsigned currNode = source;
    queue<unsigned> q;
    q.push(currNode);
    visited[currNode] = 1;

    while(q.size() > 0)
    {
        currNode = q.front();
        q.pop();
        for(unsigned i=0; i<n; i++)
        {
            if(resFlow[currNode][i] != 0 && visited[i] == 0 )
            {
                path[i] = currNode;
                visited[i] = 1;
                if(i == sink)
                    return true;
                q.push(i);
            }
        }
    }
    return false;
}

AdjList solveNetworkFlow(const AdjList& flowNetwork)
{
    unsigned source, sink;
    // input validation
    unsigned n = flowNetwork.size();
    // condition 1
    check1(flowNetwork, n);
    // condition 2
    check2(flowNetwork, n);

    // condition 4
    source = check4(flowNetwork, n);
    // condition 5
    sink = check5(flowNetwork, n);
    // condition 3
    check3(flowNetwork, n, source);

    // init maxflow list
    AdjList maxFlow{n};
    for(unsigned i=0; i<n; i++)
    {
        for(NeighborEntry neighbor : flowNetwork[i])
            maxFlow[i].push_back({neighbor.neighbor, 0});
    }

    // init residual flow graph
    vector<vector<int>> resFlow(n, vector<int>(n, 0));
    for(unsigned i=0; i<n; i++)
    {
        for(NeighborEntry neighbor : flowNetwork[i])
            resFlow[i][neighbor.neighbor] = neighbor.weight;
    }
    vector<int> path(n, -1);

    while(bfs(resFlow, source, sink, path))
    {
        // find bottleneck
        // for(unsigned i=0; i<n; i++)
        // {
        //     for(unsigned j=0; j<n; j++)
        //         cout << resFlow[i][j] << " ";
        //     cout << endl;
        // }
        // cout << endl;
        unsigned currNode = sink;
        unsigned parentNode = path[currNode];
        int minFlow = 10000; //weight of bottleneck
        while(currNode != source)
        {
            if(resFlow[parentNode][currNode] < minFlow)
                minFlow = resFlow[parentNode][currNode];
            currNode = parentNode;
            parentNode = path[currNode];
        }

        //subtract from resFlow, add to back edges
        currNode = sink;
        parentNode = path[currNode];
        while(currNode != source)
        {
            resFlow[parentNode][currNode] -= minFlow;
            resFlow[currNode][parentNode] += minFlow;

            for(unsigned i=0; i<maxFlow[parentNode].size(); i++)
            {
                if(maxFlow[parentNode][i].neighbor == currNode)
                {
                    maxFlow[parentNode][i].weight += minFlow;
                }
            }
            currNode = parentNode;
            parentNode = path[currNode];
        }
    }
    return maxFlow;
}

int findIndex(const string target, const vector<string>& offered)
{
    unsigned m = offered.size();
    for(unsigned i=0; i<m; i++)
    {
        if(offered[i] == target)
            return i;
    }
    return -1;
}

vector<string> assignTutoring(const vector<vector<string>>& preferences,const vector<string>& offered)
{
    unsigned n = preferences.size();
    unsigned m = offered.size();

    AdjList assignments{n+m+2}; //create m+n + source and sink nodes
    for(unsigned i=0; i<(n+m); i++)
    {
        if(i<n) // 0->n are for tutor nodes, n->n+m are for classes nodes, n+m->n+m+2 are for sink and source nodes
        {
            assignments[n+m].push_back({i, 1}); //add edge to source
            for(string cls: preferences[i])
            {
                int index = findIndex(cls, offered);
                assignments[i].push_back({(unsigned)index+n, 1});
            }
        }
        else if (i>=n && i<n+m) //n+m is source, n+m+1 is sink
            assignments[i].push_back({n+m+1, 1}); // add edge to sink
    }

    AdjList final = solveNetworkFlow(assignments);

    vector<string> v{n};

    for(unsigned i=0; i<n; i++)
    {
        for(NeighborEntry neighbor : final[i])
        {
            if(neighbor.weight == 1)
            {
                v[i] = offered[neighbor.neighbor-n];
            }
        }
    }

    // for(unsigned i=0; i<n; i++)
    // {
    //     cout << v[i] << endl;
    // }

    return v;
}


// int main()
// {
//     vector<vector<string>> prefs{5};
//     prefs.at(0).insert(prefs[0].begin(), {"ECS 20", "ECS 36A"});
//     prefs.at(1).insert(prefs[1].begin(), {"ECS 20", "ECS 36B", "ECS 36C"});
//     prefs.at(2).insert(prefs[2].begin(), {"ECS 36B", "ECS 36C"});
//     prefs.at(3).insert(prefs[3].begin(), {"ECS 20", "ECS 36C"});
//     prefs.at(4).insert(prefs[4].begin(), {"ECS 36C"});

//     assignTutoring(prefs, {"ECS 20", "ECS 36A", "ECS 36B", "ECS 36C"});
// }