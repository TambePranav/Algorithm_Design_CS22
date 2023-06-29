// Author - Pranav Tambe
// Roll No - 2106339

#include <bits/stdc++.h>
using namespace std;
// function to merge two subarrays
void merge(int *ar, int s, int e)
{
    // finding middle index for subarray
    int mid = (s + e) / 2;

    // lengths of the two subarrays
    int l1 = mid - s + 1;
    int l2 = e - mid;

    // creating new arrays to store values
    int *first = new int[l1];
    int *second = new int[l2];

    // copying values in two arrays (first and second)
    int k = s;

    // for loop - begin
    for (int i = 0; i < l1; i++)
    {
        first[i] = ar[k++];
    }
    // for loop - end

    k = mid + 1;

    // for loop - begin
    for (int i = 0; i < l2; i++)
    {
        second[i] = ar[k++];
    }
    // for loop - end

    // Merge two sorted array
    int index1 = 0, index2 = 0;
    k = s;

    // Checks entries of first and second array and store the smaller out of those in array ar[]
    // while loop - begin
    while (index1 < l1 && index2 < l2)
    {
        if (first[index1] <= second[index2])
        {
            ar[k++] = first[index1++];
        }
        else
            ar[k++] = second[index2++];
    }
    // while loop - end

    // while loop - begin
    while (index1 < l1)
    {
        ar[k++] = first[index1++];
    }
    // while loop - end

    // while loop - begin
    while (index2 < l2)
    {
        ar[k++] = second[index2++];
    }
    // while loop - end

    // freeing up memory allocated to arrays
    delete[] first;
    delete[] second;
}

// function to perform merge_sort
void merge_sort(int *ar, int s, int e)
{
    // Base case
    if (s >= e)
        return;
    // find the middle index
    int mid = (s + e) / 2;
    // sort left half
    merge_sort(ar, s, mid);
    // sort right half
    merge_sort(ar, mid + 1, e);

    // Merge
    merge(ar, s, e);
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
    cout << '(' << 'i' << ',' << "2^i" << ',' << "T(2^i)[in s]" << ',' << "i*2^i" << ',' << "ci" << ')' << endl;
    // Iterate over values of k
    // cout<<"Merge sort"<<endl;
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
        merge_sort(ar, 0, n - 1);

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