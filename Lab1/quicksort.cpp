// Author - Pranav Tambe
// Roll No - 2106339

#include <bits/stdc++.h>
using namespace std;

// Partition function
int partition(int *ar, int s, int e)
{

    // Place pivot at its right position and then take care of left and right of pivot
    int pivot = ar[s];

    // Count numbers lesser than pivot
    int cnt = 0;

    // for loop - begin
    for (int i = s + 1; i <= e; i++)
    {

        // counting amount of entries smaller than pivot
        if (ar[i] <= pivot)
            cnt++;
    }
    // for loop - end

    // Place pivot at its correct position based on amount calculated above
    int pivotIndex = s + cnt;
    swap(ar[pivotIndex], ar[s]);

    // Left and right part of pivot
    int i = s, j = e;

    // fixing the values around pivot such that pivot has lower values to left, higher values to right
    // while loop - begin
    while (i < pivotIndex && j > pivotIndex)
    {

        // traversing from start till pivot while entries are
        while (ar[i] < pivot)
            i++;

        // traversing from end till pivot while entries are
        while (ar[j] > pivot)
            j--;

        // swapping values and traversing
        if (i < pivotIndex && j > pivotIndex)
            swap(ar[i++], ar[j--]);
    }
    // while loop - end

    // returning the value of the pivot
    return pivotIndex;
}

// Function to perform quicksort on an array
void quick_sort(int *ar, int s, int e)
{

    // Base case
    if (s >= e)
        return;

    // partition the array
    int p = partition(ar, s, e);

    // recursively call quicksort on the 2 partitions created to sort the array
    quick_sort(ar, s, p - 1);
    quick_sort(ar, p + 1, e);
}

// function to calculate expectation of an array
double expectationArr(double *ar, int len)
{
    double sum = 0;
    // Iterate over array to sum all values
    for (int i = 0; i < len; i++)
    {
        sum += ar[i];
    }
    // divide total sum by size of the array
    return sum / len;
}

// function to calculate variance of an array
double varianceArr(double *ar, int len)
{
    double sum = 0;
    // Store expected value
    double exp = expectationArr(ar, len);
    // Find square of deviation from the mean for each entry and store in sum
    for (int i = 0; i < len; i++)
    {
        sum += ((ar[i] - exp) * (ar[i] - exp));
    }
    // Divide sum by size of the array
    return sum / len;
}

int main()
{
    // srand() sets the seed which is used by rand to generate “random” numbers
    time_t seed_t = time(NULL);
    srand(int(seed_t));
    // taking input of k from user via prompt
    int k;
    cout << "Enter the value of K: ";
    cin >> k;

    // Dynamiclly allocate memory for storing values of ci
    double *ar_c = new double[k];

    cout << "Quick sort" << endl;
    cout << '(' << 'i' << ',' << "2^i" << ',' << "T(2^i)[in s]" << ',' << "i*2^i" << ',' << "ci" << ')' << endl;
    // Iterate over values of k
    for (int i = 5; i < k + 1; i++)
    {
        // pow to find the ith power of 2
        int n = pow(2, i);

        // Dynamiclly allocate memory for storing random integer values
        int *ar = new int[n];

        // for loop - begin
        for (int j = 0; j < n; j++)
        {
            ar[j] = rand(); // rand() function uniformly returns random integer value
        }

        // start time
        auto start = clock();

        // performing quicksort on array
        quick_sort(ar, 0, n - 1);

        // end time
        auto end = clock();

        // difference time as the execution time
        double Execution_time = double(end - start) / CLOCKS_PER_SEC;

        // calculating c_i as given in problem
        double c_i = Execution_time / (n * i); // i==log2(n)

        // Printing the sorted array
        // for loop - begin
        /*  cout<<'('<<i<<','<<n<<')'<<" " <<endl;
        cout<<"sorted array"<<" ";
        for(int j=0;j<n;j++)
        {
            cout<<ar[j]<<" ";
        }
        //for loop - end

        cout<<endl; */

        // Print the required tuple
        cout << '(' << i << ',' << n << ',' << Execution_time << ',' << n * i << ',' << c_i << ')' << endl;
        // Store ci value in array ar_c
        ar_c[i - 1] = c_i;
        // Free the assigned memory for array ar
        delete[] ar;
    }

    // Printing the expected value and variance
    cout << "Expected Value :" << expectationArr(ar_c, k) << endl;
    ;
    cout << "Variance :" << varianceArr(ar_c, k) << endl;

    // freeing up memory
    delete[] ar_c;
}