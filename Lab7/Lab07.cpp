// Pranav Tambe
// 2106339
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
struct neighborList//structure of a node in the adjacency list
{
    int neighborIndex;//index of the neighbor
    int weight;//weight of the edge
    struct neighborList*next;//next pointer
};

class graph
{
    int vCount;//vertex count
    int**adjMatrix;//adjacency matrix
    neighborList**adjList;//adjacency list
    int edgeCount;//edge count
    int superSource;//source vertex for Dijkstra's Algorithm
    int*predListDijkstra;//predecessor list from Dijkstra's Algorithm
    int**predListFW;//predecessor list from Floyd-Warshall Algorithm

    int*distListDijkstra;//distance details from Dijkstra's Algorithm 
    int**distListFW;//distance details from FW Algorithm
    
    public:
    graph(int vertexCount)
    {
        vCount=vertexCount;
        edgeCount=0;
        allocateMem();
    }
    
    void allocateMem() //allocates memory for the necessary data structures
    {
        adjMatrix=new int*[vCount];
        adjList=new neighborList*[vCount];
        for(int i=0;i<vCount;i++)
        {
            adjMatrix[i]=new int[vCount];
            adjList[i]=NULL;
        }

        predListDijkstra=new int[vCount];
        distListDijkstra=new int[vCount];
        predListFW=new int*[vCount];
        distListFW=new int*[vCount];
        for(int i=0;i<vCount;i++)
        {
            predListFW[i]=new int[vCount];
            distListFW[i]=new int[vCount];
        }
    
    }
    void readAdjMatrix(FILE*fp)//reads adjacency matrix from the file
    {   
        for(int i=0;i<vCount;i++) 
            {for(int j=0;j<vCount;j++)
                {fscanf(fp,"%d",&adjMatrix[i][j]);}
            }
    }

    void printAdjMatrix()//prints adjacency matrix
    {
    //Iterate over adjacent matrix and print it
        for(int i=0;i<vCount;i++)
            {for(int j=0;j<vCount;j++)
                {printf("%-4d",adjMatrix[i][j]);}
                printf("\n");
            }
         

    }
    void loadAdjList()//set up the adjacency list 
    {   
    //Iterate over nodes 
        for(int i = 0; i<vCount; i++){
        //initialize the adjacency list
            neighborList* temp = new neighborList;
            temp->neighborIndex = i+1;
            temp->weight = 0;
            temp->next = NULL;
            adjList[i] = temp;
        }
//Iterate over nodes
        for(int i=0;i<vCount;i++)
        {
           
            
            for(int j=0;j<vCount;j++)
            {
                if(adjMatrix[i][j]!=0)
                {
                    //if weight is non zero add to adjacency list with neighbouring index and next pointer as null 
                    neighborList* temp = new neighborList;
                    temp->neighborIndex = j+1;
                    temp->next=NULL;
                    //add weights 
                    temp->weight = adjMatrix[i][j];
                    neighborList* it = adjList[i];
                    //Iterating till second last node
                    while(it->next != NULL){
                        it = it->next;
                    }
                    //set next of last node as null
                    it->next = temp;
                }
                
            }

         
        }


    }

    void printAdjList()//prints the adjacency list
    {
         for(int i=0;i<vCount;i++)
        {
             
            //take the head of each list 
            neighborList* temp = adjList[i];
            cout<<i+1<<"->";
           //iterate till it becomes equal to null pointer
            while(temp!=nullptr){
                if(temp->weight!=0 && temp->next!=nullptr)
                {
                cout<<temp->neighborIndex<<" "<<temp->weight<<"->";
                
                }
                if(temp->weight!=0 && temp->next==nullptr){
                	cout<<temp->neighborIndex<<"  "<<temp->weight;
                }
                temp = temp->next;
            }
            cout<<" NULL"<<endl;
             
        }

    }

    int countEdge()//count the number of edges in the graph
    {
//if adjacency matrix entry is non zero then there is a node
        for(int i=0;i<vCount;i++)
            {for(int j=0;j<vCount;j++)
                { if(adjMatrix[i][j]!=0)
                edgeCount++;}
                 
            }

        return edgeCount;
    }

    // void runDijkstra(int startVertex)// Run Dijkstra's Algorithm with the given startVertex and load the associated data structures with necessary information
    // {
    //  superSource=startVertex;
    // }    
    // void runFW()//Run Floyd-Warshall Algorithm and fill in the associated data structures with necessary information
    // {

    // }
    // void printDijkstraPathTo(int targetVertex)/*superSource->......->tergetVertex     lengthOfPath*/
    // {

    // }
    // void printFWPathBetween(int sourceVertex, int targetVertex)/*sourceVertex->......->targetVertex     lengthOfPath*/
    // {

    // } 

}*myGraph;


int main(int argc, char**argv)
{
    int vertexCount;
    int source;

    FILE*fp=fopen(argv[1],"r");
    fscanf(fp,"%d",&vertexCount);
    myGraph=new graph(vertexCount);//initialize vertex count from the file

    myGraph->readAdjMatrix(fp);
    fclose(fp);
    
    printf("\n There are %d edges in the graph ",myGraph->countEdge());

    myGraph->loadAdjList();

    myGraph->printAdjMatrix();
    myGraph->printAdjList();
  
  
    /* printf("\n Enter the super source vertex for Dijkstra's Algorithm:");
        scanf("%d",&source);     */
    /* runDijkstra(source);
    runFW();
    testDijkstra();
    testFW(); */


}


