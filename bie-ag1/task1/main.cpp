//
//  main.cpp
//  hw1
//
//  Created by Jamal Azizov on 18/10/2018.
//  Copyright © 2018 Jamal Azizov. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_set>


using namespace std;

struct City
{
    int foodId;
    int cityId;

};

class Graph
{
    int numVertices;
    bool* visited;
    list<int> *adjLists;

public:
    Graph(int vertices);
    int count;
    void addEdge(int src, int dest);
    void BFS(int startVertex,unsigned int q,vector<City *> &c, unordered_set<int> &foods, int &roads);
};

Graph::Graph(int vertices)
{
    numVertices = vertices;
    adjLists = new list<int>[vertices];
}

void Graph::addEdge(int src, int dest)
{
    adjLists[src].push_back(dest);
    adjLists[dest].push_back(src);
}


void Graph::BFS(int startVertex,unsigned int q,vector<City *> &c, unordered_set<int> &foods,int &roads)
{
    foods.clear();
    count = 0;
    visited = new bool[numVertices];
    for(int i = 0; i < numVertices; i++)
        visited[i] = false;
    
    list<int> queue;
    list<int> nextQueue;
    visited[startVertex] = true;
    queue.push_back(startVertex);
    
    list<int>::iterator i;
    
    while(!queue.empty())
    {
        if (foods.size() >= q){
            break;
        }
        int currVertex = queue.front();
//        cout << "Visited " << currVertex << " ";
        if (foods.size() < q) {
           if(foods.insert(c[currVertex]->foodId).second)
                roads+=count;
        }
        queue.pop_front();
        
        for(i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i)
        {
            int adjVertex = *i;
            if(visited[adjVertex])
                continue;
           
            visited[adjVertex] = true;
            nextQueue.push_back(adjVertex);

        }
        if (queue.empty() && !nextQueue.empty()) {
            queue.swap(nextQueue);
            ++count;
        }
    }
}


int main() {
    
    int N, M, P, Q;
    int foodType;
    int r1,r2;
    
    cin >> N >> M >> P >> Q;
   
    Graph graph = Graph(N);
    vector<City *> city(N);

    vector<unordered_set<int> > answer(N);
    vector<int> roads(N);
    
    
    
    for (int i = 0; i < N; i++) {
        cin >> foodType;
        City *c = new City;
        c->cityId = i;
        c->foodId = foodType;
        city[i] = c;

    }
    
    for (int i = 0; i < M; i++) {
        cin >> r1 >> r2;
        graph.addEdge(r1, r2);

    }

    for (int i = 0; i < N; i++) {
        graph.BFS(i, Q,city,answer[i],roads[i]);
    }
    
    
    int total = 0;
    
    for(const auto & p : roads)
        total += p;
    
    cout << total << endl;
    
    for (int i = 0; i < N; ++i) {
        cout << roads[i];
        for (unordered_set<int>::iterator iter=answer[i].begin();iter!=answer[i].end();iter++) {
            cout << " ";
            cout << *iter ;
        }
        cout << endl;
    }
    
}
