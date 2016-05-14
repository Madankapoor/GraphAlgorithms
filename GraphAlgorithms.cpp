#include <iostream>
#include <limits>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <functional>
#include <exception>
#include <algorithm>
#include <string.h>
#include <time.h>
#include <conio.h>
using namespace std;
#define INFINITY numeric_limits<double>::max()
//Gives the maximium value for Dist
//We need to max value to state that vertex is not reachable from some other vertex

struct vertex;
struct Edge //Basics info of a Edge
{
    //First Vertex is implict , why is it implict think on it ?
    vertex* second,*dest;//Second vertex in the Edge
    double cost;//Cost of the Edge

    Edge(vertex* s=NULL,double c=0):second(s),dest(s),cost(c)
    {}//default parametrised constructor for a edge
    bool operator> ( const Edge & rhs ) const
    { return cost > rhs.cost; }
    
    bool  operator< ( const Edge & rhs ) const
    { return cost < rhs.cost; }
};

struct vertex//basic info for vertex
{
    string name;//Denotes the name of the vertex
    vector<Edge> adj;//the list of adjacent vertices and cost
    double dist;//the distance + cost of the vertex from single source vertex
    int scrap;//Used for some Algorithm
    vertex * prev;//Used to keep track of prev visited vertex
    vertex(string n=""):name(n)
    {   reset();//Resets all distance from source and previous node travesed
    }
    void reset()
    {
        prev=NULL;
        dist=INFINITY ;
        scrap=0;
    }
    bool operator> ( const vertex & rhs ) const
    { return  dist > rhs.dist; }
    
    bool  operator< ( const vertex & rhs ) const
    { return  dist < rhs.dist; }
    
    
};


class Graph
{
public:
//functions
    Graph() // constructor
    {
        
        }
    ~Graph() // destructor
    {
        for(vmap::iterator it=vertexMap.begin();it!=vertexMap.end();it++)
            delete (*it).second;
    }
    
    void addEdge_directed(const string & srcname ,
                 const string & destname,
                 const double & cost) // Used to add a directed edge to graph
    {
        vertex * src=getvertex(srcname);
        vertex * dst=getvertex(destname);
        src->adj.push_back(Edge(dst,cost));
    }
    void addEdge_undirected(const string & srcname ,
                 const string & destname,
                 const double & cost)//Used to add a Undirected edge to graph
    {
        vertex * src=getvertex(srcname);
        vertex * dst=getvertex(destname);
        src->adj.push_back(Edge(dst,cost));
        dst->adj.push_back(Edge(src,cost));
    }
    void printpath(  const string&  destName ) // Used to print a path from one edge to another
    {

        if(!vertexMap.count(destName)) return;
        stack<vertex*> Stack;
        Stack.push(vertexMap[destName]);
        while(Stack.top()->prev!=NULL)
            Stack.push(Stack.top()->prev);
        while(!Stack.empty())
        {   if(Stack.top()->name==destName)
            cout << Stack.top()->name <<endl;
            else
            cout << Stack.top()->name << " to ";
            Stack.pop();
        }
    }
    void printvertex(ostream& cout=cout)
    {
        for(vmap::iterator itr=vertexMap.begin();itr!=vertexMap.end();itr++)
       { cout << (*itr).first  << "  :  "<< (*itr).second->dist  << " prev : ";
         if((*itr).second->prev!=NULL) cout << (*itr).second->prev->name <<  endl;
         else cout << "Null" << endl;
       }    
    }
   //Standard Algorithms Implementation
    void Min_span_tree_Krushkal();   
    void dijkstra( const string & startName );
    void Bellfordman(const string & startName);
    void acylic_topological_sorting(const string & startName);
    void Min_span_tree_Prim();
    void StronglyConnectedComponentes(Graph& graphrev);
    // random contraction min cut implemented separately
    double getcost(const string & dest)
    {   if(vertexMap.count(dest))

        return vertexMap[dest]->dist;
        else return 0.0;
    }
protected:
    void clearall()
    {
        for(vmap::iterator itr=vertexMap.begin();itr!=vertexMap.end();itr++)
            (*itr).second->reset();
    }

    typedef map<string,vertex*> vmap;
    /*
     * Vmap is is used map vertex name to struct vertex * pointer 
     * struct vertex holds all data nesssary for a shortest path algorithm
     * */
    
    vmap vertexMap ;//Adj_list
    vertex* getvertex(const string & s)
    {   if(!vertexMap.count(s))
        {
            vertexMap[s]=new vertex(s);
            return vertexMap[s];
        }
        else return vertexMap[s];
    }
    //methods and varaibles for scc
    stack< string > time_magical_order;
    vector< string > leaders;
    void dfs(vertex* src)
    {   
        stack<vertex*> st;
        st.push(src);
        int newcall=0;
        while(!st.empty())
         {  vertex *u=st.top();
             u->scrap=1;
             u->prev=src;
             newcall=0;
            for(vector<Edge>::iterator itr=u->adj.begin();itr!=u->adj.end();itr++)
            {
                if(itr->second->scrap!=1)
                {   newcall=1;
                    st.push(itr->second);
                    break;
                }
            }
            if(!newcall)
            {
                time_magical_order.push(u->name);
                 st.pop();   
            }
    
         }
    }
    
    void dfsLoop(stack<string>& ordering)
    {
        while(!ordering.empty())
        {
            string top=ordering.top();
                if(!vertexMap[top]->scrap)
                  {  leaders.push_back(top);
                      dfs(vertexMap[top]);
                  }
            ordering.pop();
        }
    }
};


void Graph::dijkstra(const string& startName)
{
    priority_queue< Edge,vector<Edge>,greater<Edge> > pq; 
    //This we use to get the min distance vertex 

    clearall();//We use to set our distance to INF 
    //and previous nodes path to NULL
    
    if(!vertexMap.count(startName)) 
    {
        cout << "Algorithm failed , Provided vertex not found in Graph " << endl;
        cout << "Please check Whether your input is correct " << endl;
        return;
    }

    vertex* start=vertexMap[startName];
    start->dist=0;//Source is at a distance 0 from it self
    start->scrap=0;//We used this to avoid taking the element twice on stack
    pq.push(Edge(start,0));

    Edge vrec;
 /*   for(int nodeseen=0;nodeseen <vertexMap.size();nodeseen++)
   {
        do
        {   if(pq.empty()) 
            // All entries are Know and thus we quit the Algorithm
                return;
            vrec = pq.top( );
            pq.pop();
        }while(vrec.dest->scrap!=0); 
//We do this while check inorder to avoiding selecting the vertex twice
*/ while(!pq.empty())
 {  vrec = pq.top();
    pq.pop();     
    vertex* v=vrec.dest;    
    
    v->scrap=1;
//v Has come from queue and set scrap is set this to 1 
// and hence it is not iterated again

        for(int i=0;i < v->adj.size();i++)
        {
            Edge e=v->adj[i];
            vertex * w=e.second;
            double cost=e.cost;
            if(v->dist + cost< w->dist)
            {
                w->dist=v->dist+cost;
                w->prev=v;
                pq.push(Edge(w,w->dist));
            } 
        }// end of for loop
    }
}

string intostring(int x)
{
    char s[100];
    int i=0;
    while(x)
    {
        s[i++]=x%10+'0';
        x/=10;
    }
    s[i]='\0';
    strrev(s);
    return string(s);
}
void Graph::Bellfordman(const string & startName)
{
    if(!vertexMap.count(startName)) {
        cout << "Algorithm failed because node not found " << endl;
        return; 
    }
     clearall();   
     vertex* start=vertexMap[startName];
     start->dist=0;
     queue<vertex*> q;
     q.push(start);
     while(!q.empty())
     {
         vertex* v=q.front();
         q.pop();
         if(v->scrap++ > 2*vertexMap.size()) // used to detect negative cycle
            {
                cout << "Negative cycle detected" << endl;
                return ;
            }
     
         for(int i=0;i<v->adj.size();i++)
         {
             Edge e=v->adj[i];
             vertex * w=e.second;
             double cost=e.cost;
             
             if(w->dist > v->dist + cost)
             {
                 w->dist=v->dist+cost;
                 w->prev=v;
                 // Enqueue only if not already on the queue
                  //if scrap is odd we assume vertex is already on queue 
                 if(w->scrap++%2==0)
                     q.push(w);
                 else 
                     w->scrap++;
             }
        }
    }
}

void Graph::Min_span_tree_Prim()
{  
    /*                          Aim
     * Input:    Graph-Adjaceny list
     * Ouput:    Minimum Spanning tree using prims Algorithm
     * Approach: Try to redesign with little considerations
     * 
     * Design and Anaylsis:
     *      Design:
     *      think over:(Refer wiki for solution)
     *       (memorize imp definitions for exam )   
     *          What is Spanning tree?
     *          What is Mst ?  
     *          what are the properties of a MST?
     *              Possible multiplicity
     *              Uniqueness (all edges are distinct,one unqiue spanning tree),
     *              Minimum-cost subgraph (weights are postive),
     *              Cycle property (for a cycle in graph,a larger weight edge is not in mst)
     *              Cut property  (cut smallest weight edge)
     *              minimumcost edge (a edge with min cost in G , is included in MST)
     *              contraction (contract a mst to a single vertex ,single index + mst = mst )
     *          What are the conditions that a graph must hold such that we can compute
     *          mst ?
     *          how can we get a mst from adj list alone ?
     *          what would be the representation or data structure of our Mst ?
     *           
     * 
     * 
     * 
     * 
     * 
     * 
     *  why must the give graph be 1:connected and 2:undirected graph ? 
     *  
     *  Mst is represented by array of vertices with prev nodes and distance from prev
     *  We use only a single class vertex to present vertex array with a linked list
     *  
     *  Algorithm:
     *      1.Create a data structure of vertices with a variable to hold distance 
     *          , prev node and set all distance varaibles to INF and prev node 
     *          varaibles to NULL in vertex array
     *      2.Pick a vertex at random from vertex array,set is distance to 0
     *              and push it in a queue with priorty queue with greater first
     *              (think how using priority queue improves the algorithm)                    
     *      3.while queue is not Empty:
     *          v=pop top of queue
     *          for w in Adj list of v:
     *              if vertex[w].distance > Edge_cost of v,w
     *                  vertex[w].distance=Edge_cost of v,w
     *                  vertex[w].pre=v
     *                  push w in queue
     */
      
    clearall();
    vertex *v=(*(vertexMap.begin())).second;
    priority_queue< Edge, vector<Edge> , greater<Edge> > pq;
    
    pq.push(Edge(v,0));
    
    while(!pq.empty())
    {
        Edge sw=pq.top();
        pq.pop();
        vertex *v=sw.dest;
        for(unsigned int i=0;i< v->adj.size();i++)
        {   vertex* w=v->adj[i].dest;
            double c=v->adj[i].cost;
            if(w->dist > c)
            {
                w->dist=c;
                w->prev=v;
                pq.push(Edge(w,c));
            }
        }
    }
    
}
void Graph::Min_span_tree_Krushkal()
{
    
    
    
    
    
    
    
    }



void Graph::acylic_topological_sorting(const string& startname)
{
    if(!vertexMap.count(startname)) 
    {
        cout << "Source not found "<< endl;
        return;
    }
    
    //intialising the graph
    clearall();
    
    // calculating the indegrees of all the vertices
    for(vmap::iterator itr=vertexMap.begin();itr!=vertexMap.end();itr++)
    {   vertex *v= (*itr).second;
        for(int i=0;i<v->adj.size();i++)
          v->adj[i].second->scrap++;
    }
    queue<vertex*> q;
    for(vmap::iterator itr=vertexMap.begin();itr!=vertexMap.end();itr++)
    {   vertex *v= (*itr).second;
        // enqueue all vertices with 0 indegree
        if(v->scrap==0)
            q.push(v);
    }
    cout << "Topological order is " << endl;
    int iteration=0;
    while(!q.empty())
    {   iteration++;
        vertex* v,*w;
        v=q.front();
        q.pop();
        cout << v->name << " to ";
        for(int i=0;i<v->adj.size();i++)
        {    
            w=v->adj[i].second;
            double c=v->adj[i].cost;
            if(--(w->scrap)==0)
                q.push(w);
             if(w->dist == INFINITY)   
                    continue;
            if(w->dist > v->dist + c)
               { w->dist=v->dist + c;
                  w->prev=v;
               }
        }
    }
    cout << endl;
    if(iteration !=vertexMap.size() )
        cout << "Cyles were present in graph";
    
}

void Graph::StronglyConnectedComponentes(Graph& graphrev)
{   
   stack<string> order;
   for(vmap::iterator itr=graphrev.vertexMap.begin();itr!=graphrev.vertexMap.end();itr++)
       order.push(itr->first);
    graphrev.dfsLoop(order);
    dfsLoop(graphrev.time_magical_order);
    map<string,int> scccounts;
    for(size_t  itr=0;itr<leaders.size();itr++)
    scccounts[leaders[itr]]=0;
    
    for(vmap::iterator itr=graphrev.vertexMap.begin();itr!=graphrev.vertexMap.end();itr++)
        scccounts[itr->second->prev->name]++;
    
    for(map<string,int>::iterator itr=scccounts.begin();itr!=scccounts.end();itr++)
            cout << "Leader of scc: " << itr->first << " count:" << itr->second << endl;
    
}

inline map< int,list<int> >::iterator & at(map< int,list<int> > & l,int i)
{
    map< int,list<int> >::iterator itr=l.begin();
    for(int src=0;itr!=l.end() && src<i;itr++,src++);
    if(itr==l.end()) throw "SIGEVt";
    return itr;
}
inline int at(list<int>& l,int i)
{
    list< int >::iterator itr=l.begin();
    for(int src=0;itr!=l.end() && src<i;itr++,src++);
    if(itr==l.end()) throw "SIGEVt";
    return *itr;
}
void contract_vertices(map<int ,list<int> > & adj_list,int u,int v)
{   list< int >::iterator itr=adj_list[v].begin();
    for(;itr!=adj_list[v].end();itr++)
    {   list< int >::iterator itr2=adj_list[*itr].begin();
        for(;itr2!=adj_list[*itr].end();itr2++)
            if(v==*itr2) *itr2=u;
        }
    adj_list[u].merge(adj_list[v]); // merging lists of u and v
    adj_list.erase(v); // removing v from map
    
    }
void remove_self_loops(map<int ,list<int> > &  adj_list,int u,int v)
{   list< int >::iterator itr=adj_list[u].begin();
    for(;itr!=adj_list[u].end();)
       if( *itr==u || *itr == v) 
            itr=adj_list[u].erase(itr);
        else itr++;
}
int Random_contraction_min_cut(map<int ,list<int> >   adj_list)
{   int i=1;
      while( adj_list.size() >2)
    {
        int u,v;
        u=at(adj_list, rand()%adj_list.size() )->first; //selecting randomly u
        v=at(adj_list[u],rand()%adj_list[u].size()); // selecting randomly v
        cout << u << ":" << v << endl;
        contract_vertices(adj_list,u,v);
        remove_self_loops(adj_list,u,v);
    }   
    return adj_list.begin()->second.size();
}
void testDijkstra()
{
    Graph G;

    ifstream Edge_file("D:\\dijkstraData.txt");

    if(Edge_file.bad())
    {
        cout << "Error opening file" << endl;
        return ;
    }

    while(Edge_file)
    {
        string str;
        getline(Edge_file,str);
        stringstream stdd(str);
        int src;
        stdd >> src;
        while(stdd)
        {
            int dest;
            double cost;
            stdd >> dest >> cost ;

            string srcstr=intostring(src),deststr=intostring(dest);
            G.addEdge_directed(srcstr,deststr,cost);
        }
    }

    Edge_file.close();
    string start("1");
    G.dijkstra(start);
    string strs[]={"7","37","59","82","99","115","133","165","188","197"};

    cout << "Solution to Coursea programming assignment for dijkatra's algorithm" << endl;
    for(int i=0;i<10;i++)
     cout << G.getcost(strs[i]) << endl;

    }

void test_toplogicalsort()
{
    Graph G;
    int edges;
    cout << "Enter the no of edges";
    cin >> edges;
    while(edges--)
    {   string src,dest;
        double cost;
        cout << "Enter the Edge" << endl;
        cin >> src >> dest >> cost;
        G.addEdge_directed(src,dest,cost);
    }
    cout << "Enter the starting node " << endl;
    string start;
    cin >> start;
    G.acylic_topological_sorting(start); 
}
void test_prim()
{   Graph G;
    string a,b;
    double cost;
    ifstream Edge_file("D:\\MIMtest.txt");

    if(Edge_file.bad())
    {
        cout << "Error opening file" << endl;
        return ;
    }
    int n=1;
    while(Edge_file)
    {
       cout << n++ << endl;
       Edge_file >> a >> b >> cost;
        G.addEdge_undirected(a,b,cost);
    }
    Edge_file.close();
    G.Min_span_tree_Prim();
    G.printvertex();
}

void test_random_contration()
{   
    int mincuts=100000,i=1;
    
    map<int ,list<int> >  adj_list;
    
    
    ifstream Edge_file("D:\\kargerMinCut.txt");
    
    if(Edge_file.bad())
    {
        cout << "Error opening file" << endl;
        return ;
    }
    while(Edge_file)
    {
        string str;
        getline(Edge_file,str);
        stringstream stdd(str);
        int src;
        stdd >> src;
        if(str.length() ==0) break;
        adj_list[src]=list<int>();
        while(stdd)
        {
            int dest;
            stdd >> dest ;
            adj_list[src].push_back(dest);
        }
    }

    Edge_file.close();     
    srand(876123465);
    for(int i=0;i<10000;i++)
        cout << ( mincuts=min(Random_contraction_min_cut(adj_list),mincuts) )<< endl;
    getch();
    cout << "min cut" << mincuts;
} 

void test_Stronglyconnectedcomponenets()
{
    ifstream input("D:\\scc.txt");
    Graph g;
    Graph gr;
    
    while(input)
    {
        string dst,src;
        input >> src >> dst ;
        if(src == "" || dst == "") break;
        
        g.addEdge_directed(src,dst,1);
        gr.addEdge_directed(dst,src,1);
    }
    input.close();  
    g.StronglyConnectedComponentes(gr);
      
}
    
    
int main(int argc, char **argv)
{
  testDijkstra();
  //test_toplogicalsort();
  //test_prim();
  //test_random_contration();
  //test_Stronglyconnectedcomponenets();
  return 0;
}
