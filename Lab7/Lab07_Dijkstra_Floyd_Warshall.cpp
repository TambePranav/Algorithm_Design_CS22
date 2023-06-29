
// Pranav Tambe
// 2106339

#include <bits/stdc++.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define infinity INT_MAX / 2 // define infinity
struct neighborList          // structure of a node in the adjacency list
{
    int neighborIndex;         // index of the neighbor
    int weight;                // weight of the edge
    struct neighborList *next; // next pointer
};

class min_heap
{
    int size;            // variable to hold the current size of the heap
    int volume;          // variable to hold the maximum size of the heap
    pair<int, int> *arr; // pointer to an array of pairs of integers to hold the elements of the heap
public:
    min_heap(int volume);                   // constructor to initialize the heap with a given maximum size
    bool isempty() { return (size == 0); }  // function to check if the heap is empty
    void insert(pair<int, int> c);          // function to insert a new element into the heap
    void heapify(int idx);                  // function to adjust the heap to maintain the heap property after an element is removed
    pair<int, int> top() { return arr[0]; } // function to return the top element of the heap
    void pop();                             // function to remove the top element of the heap
};
void swap_pairs(pair<int, int> *t1, pair<int, int> *t2)
{
    pair<int, int> temp = *t2; // Create a temporary pair variable called "temp" and initialize it to the value of t2
    *t2 = *t1;                 // Set the value of t2 to the value of t1
    *t1 = temp;                // Set the value of t1 to the value of "temp" (which was previously t2)
}

// Constructor for the min_heap class
min_heap::min_heap(int v)
{
    volume = v;                  // Set the maximum size of the heap
    size = 0;                    // Set the current size of the heap to zero
    arr = new pair<int, int>[v]; // Allocate an array of pairs of integers on the heap
}

void min_heap::heapify(int idx)
{
    if (size == 0)
        return;              // If the heap is empty, there is nothing to heapify
    int smallest = idx;      // Start by assuming that the current index has the smallest value
    int left = 2 * idx + 1;  // Calculate the index of the left child
    int right = 2 * idx + 2; // Calculate the index of the right child
    if (left < size && arr[left].first < arr[idx].first)
        smallest = left; // If the left child is smaller than the current index, update the smallest index
    if (right < size && arr[right].first < arr[smallest].first)
        smallest = right; // If the right child is smaller than the smallest index, update the smallest index
    if (smallest != idx)  // If the smallest index is not the current index
    {
        swap_pairs(&arr[idx], &arr[smallest]); // swap the pairs
        heapify(smallest);                     // recursively call heapify on the new index
    }
}

// This function inserts a pair of integers into the min heap.

void min_heap::insert(pair<int, int> c)
{
    int idx = size;  // Initialize the index to the last position in the heap
    size++;          // Increment the size of the heap
    arr[idx] = c;    // Place the new element at the end of the heap
    while (idx != 0) // Continue while the current index is not the root of the heap
    {
        int parent = (idx - 1) / 2;             // Calculate the index of the parent node
        if (arr[parent].first > arr[idx].first) // If the parent node has a larger value than the current node
        {
            swap_pairs(&arr[parent], &arr[idx]); // Swap the parent and current nodes
            idx = parent;                        // Update the current index to the parent index
        }
        else
            break; // If the parent node is smaller or equal to the current node, break out of the loop
    }
}

void min_heap::pop()
{
    // If the size of the heap is less than or equal to 0, return immediately
    if (size <= 0)
        return;
    // If there's only one element in the heap, remove it and return
    if (size == 1)
    {
        size--;
        return;
    }
    // Otherwise, replace the root with the last element in the heap
    arr[0] = arr[size - 1];
    size--;
    heapify(0); // Then, restore the heap property by heapifying from the root
}

class graph
{
    int vCount;             // vertex count
    int **adjMatrix;        // adjacency matrix
    neighborList **adjList; // adjacency list
    int edgeCount;          // edge count
    int superSource;        // source vertex for Dijkstra's Algorithm
    int *predListDijkstra;  // predecessor list from Dijkstra's Algorithm
    int **predListFW;       // predecessor list from Floyd-Warshall Algorithm
    int *distListDijkstra;  // first details from Dijkstra's Algorithm
    int **distListFW;       // first details from FW Algorithm
public:
    graph(int vertexCount)
    {
        vCount = vertexCount;
        edgeCount = 0;
        allocateMem();
    }

    void allocateMem() // allocates memory for the necessary data structures
    {
        adjMatrix = new int *[vCount];
        adjList = new neighborList *[vCount];
        for (int i = 0; i < vCount; i++)
        {
            adjMatrix[i] = new int[vCount];
            adjList[i] = NULL;
        }

        predListDijkstra = new int[vCount];
        distListDijkstra = new int[vCount];
        predListFW = new int *[vCount];
        distListFW = new int *[vCount];
        for (int i = 0; i < vCount; i++)
        {
            predListFW[i] = new int[vCount];
            distListFW[i] = new int[vCount];
        }
    }
    void readAdjMatrix(FILE *fp) // reads adjacency matrix from the file
    {
        for (int i = 0; i < vCount; i++)
        {
            for (int j = 0; j < vCount; j++)
            {
                fscanf(fp, "%d", &adjMatrix[i][j]);
            }
        }
    }

    void printAdjMatrix() // prints adjacency matrix
    {
        // Iterate over adjacent matrix and print it
        for (int i = 0; i < vCount; i++)
        {
            for (int j = 0; j < vCount; j++)
            {
                printf("%-4d", adjMatrix[i][j]);
            }
            printf("\n");
        }
    }
    void loadAdjList() // set up the adjacency list
    {
        // Iterate over nodes
        for (int i = 0; i < vCount; i++)
        {
            // initialize the adjacency list
            neighborList *temp = new neighborList;
            temp->neighborIndex = i + 1;
            temp->weight = 0;
            temp->next = NULL;
            adjList[i] = temp;
        }
        // Iterate over nodes
        for (int i = 0; i < vCount; i++)
        {

            for (int j = 0; j < vCount; j++)
            {
                if (adjMatrix[i][j] != 0)
                {
                    // if weight is non zero add to adjacency list with neighbouring index and next pointer as null
                    neighborList *temp = new neighborList;
                    temp->neighborIndex = j + 1;
                    temp->next = NULL;
                    // add weights
                    temp->weight = adjMatrix[i][j];
                    neighborList *it = adjList[i];
                    // Iterating till second last node
                    while (it->next != NULL)
                    {
                        it = it->next;
                    }
                    // set next of last node as null
                    it->next = temp;
                }
            }
        }
    }

    void printAdjList() // prints the adjacency list
    {
        for (int i = 0; i < vCount; i++)
        {

            // take the head of each list
            neighborList *temp = adjList[i];
            cout << i + 1 << "->";
            // iterate till it becomes equal to null pointer
            while (temp != nullptr)
            {
                if (temp->weight != 0 && temp->next != nullptr)
                {
                    cout << temp->neighborIndex << " " << temp->weight << "->";
                }
                if (temp->weight != 0 && temp->next == nullptr)
                {
                    cout << temp->neighborIndex << "  " << temp->weight;
                }
                temp = temp->next;
            }
            cout << " NULL" << endl;
        }
    }

    int countEdge() // count the number of edges in the graph
    {
        // if adjacency matrix entry is non zero then there is a node
        for (int i = 0; i < vCount; i++)
        {
            for (int j = 0; j < vCount; j++)
            {
                if (adjMatrix[i][j] != 0)
                    edgeCount++;
            }
        }

        return edgeCount;
    }

    void runDijkstra(int startVertex)
    {
        superSource = startVertex; // Set the superSource to the given startVertex
        for (int i = 0; i < vCount; i++)
        {
            distListDijkstra[i] = infinity; // Set the distance of each vertex to infinity
        }
        distListDijkstra[superSource - 1] = 0;           // Set the distance of the superSource vertex to 0
        predListDijkstra[superSource - 1] = superSource; // Set the predecessor of the superSource vertex to itself
        pair<int, int> p1 = make_pair(0, superSource);
        min_heap mh(vCount + 3);
        mh.insert(p1);
        // Loop until the minimum heap is empty
        while (!mh.isempty())
        {
            int node = mh.top().second;             // Get the node with minimum distance
            neighborList *temp = adjList[node - 1]; // Get the neighborList of the current node
            mh.pop();
            // Loop through all the neighbors of the current node
            while (temp != NULL)
            {
                int adjnode = temp->neighborIndex;                                     // Get the index of the neighbor node
                int cost = temp->weight;                                               // Get the weight of the edge between the current node and its neighbor
                if (distListDijkstra[adjnode - 1] > distListDijkstra[node - 1] + cost) // Check if a shorter path exists to the neighbor node through the current node
                {
                    distListDijkstra[adjnode - 1] = distListDijkstra[node - 1] + cost; // Update the distance of the neighbor node
                    mh.insert(make_pair(distListDijkstra[adjnode - 1], adjnode));      // Add the neighbor node to the minimum heap
                    predListDijkstra[adjnode - 1] = node;                              // Update the predecessor of the neighbor node
                }
                temp = temp->next; // Move to the next neighbor
            }
        }
    }

    void printDijkstraPathTo(int targetVertex)
    {
        if (targetVertex > vCount || targetVertex < 1)
        {
            cout << "Invalid Input" << endl;
            return;
        }
        if(distListDijkstra[targetVertex - 1]==infinity)
        {
            cout<<"Path between "<<superSource<<" to "<<targetVertex<<" doestn't exit"<<endl;
            return;
        }
        vector<int> ans(vCount); // Initialize a vector to store the path from targetVertex to superSource.
        cout << "The shortest path from " << superSource << " to " << targetVertex << " is of cost " << distListDijkstra[targetVertex - 1] << endl;
        int j = 0;
        for (int i = targetVertex; i != superSource; i = predListDijkstra[i - 1]) // Traverse through the predecessor list to find the path.
        {
            ans[j++] = i;
        }
        ans[j] = superSource; // Add the superSource vertex to the end of the path.
        cout << "The path is ";
        for (int i = j; i >= 0; i--)
        {
            cout << ans[i]; // Print the vertices in the path.
            if (i != 0)
                cout << "->"; // Print the arrow symbol to separate the vertices.
        }
        cout << endl;
    }
    void runFW() // Run Floyd-Warshall Algorithm and fill in the associated data structures with necessary information
    {
        for (int i = 0; i < vCount; i++)
        {
            for (int j = 0; j < vCount; j++)
            {
                if (i == j)
                {
                    predListFW[i][j] = i;
                }
                else
                {
                    predListFW[i][j] = i;
                }
            }
        }
        for (int i = 0; i < vCount; i++)
        {
            for (int j = 0; j < vCount; j++)
            {
                if (adjMatrix[i][j] == 0 && i != j)
                {
                    distListFW[i][j] = infinity;
                }
                else
                {
                    distListFW[i][j] = adjMatrix[i][j];
                }
            }
        }
        // update the distance and predecessor lists using the Floyd-Warshall Algorithm.
        for (int i = 0; i < vCount; i++)
        {
            for (int j = 0; j < vCount; j++)
            {
                for (int k = 0; k < vCount; k++)
                {

                    // if there is a shorter path through vertex, update the distance list and predecessor list
                    if (distListFW[i][j] > distListFW[i][k] + distListFW[k][j])
                    {
                        distListFW[i][j] = distListFW[i][k] + distListFW[k][j];
                        predListFW[i][j] = predListFW[k][j];
                    }
                }
            }
        }
    }

    void printFWPathBetween(int sourceVertex, int targetVertex) /*sourceVertex->......->targetVertex     lengthOfPath*/
    {
        sourceVertex--;
        targetVertex--;
        // If either of the input vertices are out of range, print an error message and return.
        if (sourceVertex > vCount || targetVertex > vCount || sourceVertex < 1 || targetVertex < 1)
        {
            cout << "Invalid Input" << endl;
            return;
        }
         if(distListFW[sourceVertex][targetVertex]==infinity)
        {
            cout<<"Path between "<<sourceVertex+1<<" to "<<targetVertex+1<<" doestn't exit"<<endl;
            return;
        }

        // Get the predecessor list for the source vertex.
        int *arr = predListFW[sourceVertex];

        // Initialize an output array and counter variables.
        int output[vCount];
        int count = 0;

        // Traverse the predecessor list to get the shortest path between the source and target vertices.
        int temp = arr[targetVertex];
        while (temp != sourceVertex)
        {
            output[count] = temp;
            temp = arr[temp];
            count++;
        }

        // Add the source vertex to the output array and print the shortest path in reverse order.
        output[count] = sourceVertex;
        cout << "The shortest path from " <<sourceVertex+1 << " to " << targetVertex +1<< " is of cost " << distListFW[sourceVertex][targetVertex] << endl;
        cout << "The path is ";
        for (count = count; count >= 0; count--)
        {
            cout << output[count] + 1 << "->";
        }
        cout << targetVertex + 1 << endl;
    }
} *myGraph;
void testDijkstra()
{
    /*Write the function that would keep on reading intended target vertices from the user and print the corresponding path  (using the printDijkstraPathTo function) unless the user decides to terminate*/
    // Infinite loop until user terminates
    while (true)
    {
        char i;
        // Prompt the user to quit or enter input
        cout << "Press b for back or any key to proceed" << endl;

        // Input
        cin >> i;

        // if Input is 'q' or 'Q' break to quit
        if (i == 'b')
        {
            cout << "Dijkstra closing" << endl;
            break;
        }

        // else get input from user for source and target vertex
        else
        {
            int target;
            // prompt user for source target input
            cout << "Enter target vertex " << endl;
            // input
            cin >> target;
            // print path between source and target using printFWPathbetween()
            myGraph->printDijkstraPathTo(target);
        }
    }
}

void testFW()
{
    // Infinite loop until user terminates
    while (true)
    {
        char i;
        int j, k;

        // Prompt the user to quit or enter input
        cout << "Press b for back or any key to proceed" << endl;
        // Input
        cin >> i;

        // if Input is 'q' or 'Q' break to quit
        if (i == 'b')
        {
            cout << "Floyd Warshall closing" << endl;
            break;
        }

        // else get input from user for source and target vertex
        else
        {

            // prompt user for source target input
            cout << "Enter source vertex followed by target vertex (space separated)" << endl;

            // input
            cin >> j >> k;

            // print path between source and target using printFWPathbetween()
            myGraph->printFWPathBetween(j, k);
        }
    }
    /*Write the function that would keep on reading intended source and target vertices from the user and print the corresponding path (using printFWPathBetween function) unless the user decides to terminate*/
}
int main(int argc, char **argv)
{
    int vertexCount;
    int source;
    int target;
    FILE *fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &vertexCount);
    myGraph = new graph(vertexCount); // initialize vertex count from the file

    myGraph->readAdjMatrix(fp);
    fclose(fp);

    printf("\n There are %d edges in the graph ", myGraph->countEdge());
    cout << endl;

    myGraph->loadAdjList();

    myGraph->printAdjMatrix();
    myGraph->printAdjList();

    myGraph->runFW();
    while (true)
    {
        int i;
        int j, k;

        // Prompt the user to quit or enter input
        cout << "Press 1 for Dijkstra, 2 for FW, 3 to quit" << endl;

        // Input
        cin >> i;

        if (i == 1)
        {
            printf("Enter the super source vertex for Dijkstra's Algorithm:");
            scanf("%d", &source);
            myGraph->runDijkstra(source);
             testDijkstra();
        }
        if (i == 2)
            testFW();
        if (i == 3)
            break;
    }
}
