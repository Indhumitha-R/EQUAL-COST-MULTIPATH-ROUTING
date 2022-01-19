#include <iostream>
#include <string>
#include <list>
#include <map>
#include <iterator>
#include <queue>
#include <climits>
using namespace std;

class Router
{
    int cost;
    string name;
    Router *next;

public:
    Router(int f, string n)
    {
        cost = f;
        name = n;
        next = NULL;
    }
    friend class Routing;
};
class Routing
{
    int n;
    list<Router> *RoutersList;
    map<string, int> hm;
public:
    vector<vector<string>> pathSeq;
    int min_path = INT_MAX;
    Routing(int num)
    {
        n = num;
        RoutersList = new list<Router>[n];
    }

    void vertexEdgeWt()
    {
        int choice = 1,edge;
        int dist = 0, j = 0;
        string name, source, destination;
        cout << "Names of all " << n << " router(s): \n";
        for (int i = 0; i < n; i++)
        {
            name='A'+i;
            cout<<name<<"  ";
            hm.insert(pair<string, int>(name, i));
        }
        cout << "\nEnter number of edges";
        cin>>edge;
        cout << "Enter all from vertex, to  vertex and cost of edge \n";
        for(int i=0;i<edge;i++)
        {  
            cin >> source >> destination >> dist;
            if (hm.find(source) == hm.end() || hm.find(destination) == hm.end())
            {
                cout << "Name of the router doesn’t match\n";
            }
            else
            {
                Router *endVertex = new Router(dist, destination);
                Router *startVertex = new Router(dist, source);

                map<string, int>::iterator itr;
                itr = hm.find(source);
                RoutersList[itr->second].push_back(*endVertex);
                itr = hm.find(destination);
                RoutersList[itr->second].push_back(*startVertex);
            }
        }
    }
    void allPathSrcToDest(string s, string d)
    {
        if (hm.find(s) == hm.end() || hm.find(d) == hm.end())
        {
            cout << " Name of the router doesn’t match\n ";
            return;
        }
        bool *visited = new bool[n];
        string *path = new string[n];
        int path_index = 0; // Initialize path[] as empty
        int path_cost = 0;
        for (int i = 0; i < n; i++)
            visited[i] = false;
        cout<< "Paths from router " << s << " to " << d << ": \n";
        pathSrcToDest(s, d, visited, path, path_index, path_cost;
    }
    void pathSrcToDest(string u,string d,bool visited[],
                        string path[],int &path_index,int path_cost)
    {  
        map<string, int>::iterator mapItrSrc, mapItrDest;
        mapItrSrc = hm.find(u);
        visited[mapItrSrc->second] = true;
        path[path_index] = u;
        path_index++;

        if (u == d)
        {
            if (path_cost <= min_path)
            {
                if (path_cost < min_path)
                {
                    pathSeq.clear();
                    min_path = path_cost;
                }
                vector<string> path_seq;
                for (int i = 0; i < path_index; i++)
                {
                    path_seq.push_back(path[i]);
                }
                pathSeq.push_back(path_seq);
            }

            for (int i = 0; i < path_index; i++)
            {
                cout << path[i] << " ";
            }
            cout << "Cost: " << path_cost << endl;
        }
        else
        {
            list<Router>::iterator i;
            for (i = RoutersList[mapItrSrc->second].begin();  
                 i != RoutersList[mapItrSrc->second].end(); ++i)
            {
              string num = i->name;
              mapItrDest = hm.find(num);
              int c = i->cost;
              path_cost += c;
              if (!visited[mapItrDest->second]){
              pathSrcToDest(num,d,visited,path,path_index,path_cost);
              }
              path_cost -= c;
            }
        }
        path_index--;
        visited[mapItrSrc->second] = false;
    }
    void printEqualCostPaths(int packet_num)
    {
        cout << "Minimium cost from source to destination is " << 
             min_path << endl;
        cout << "path(s) with least cost: \n";
        for (int i = 0; i < pathSeq.size(); i++)
        {
            for (int j = 0; j < pathSeq[i].size(); j++)
            {
                cout << pathSeq[i][j] << " ";
            }
            cout << endl;
        }
        if (pathSeq.size() > 1)
        {
            cout << "Balanced Round Robin algorithm is used for load balancing in case of multiple paths of equal cost \n";
            cout<< "Each packet will take a different path based on round robin algorithm \n";
            int pathIndex = 0;
            for (int i = 0; i < packet_num; i++)
            {
                pathIndex = (pathIndex + 1) % pathSeq.size();
                cout << "Packet "<<i+1;
                for (int j = 0; j < pathSeq[pathIndex].size(); j++)
                {
                    cout<<"---"<<pathSeq[pathIndex][j] << " ";
                }
                cout << endl;
            }
        }
        else
        {
            cout <<packet_num << " packets will take the above path as there is a single path with minimum cost\n";
        }
    }
};

int main()
{
    cout << "Enter the number of routers.";
    int n;
    string src, dest;
    cin >> n;
    Routing obj1(n);
    obj1.vertexEdgeWt();
    cout << "Enter name of source and destination routers: \n";
    cin >> src >> dest;
    cout << "Enter number of packets: \n";
    cin >> n;
    obj1.allPathSrcToDest(src, dest);
    obj1.printEqualCostPaths(n);
}
