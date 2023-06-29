
/*
Name - Pranav Tambe
Roll No - 2106339 */

#include <bits/stdc++.h>
#include<chrono> //import chrono library for time calculation
using namespace std;
using namespace std::chrono;
#define ull unsigned long long //Macro defining unsigned long long integer as ull

//Function to  multiply given  two matrices and return the resultant matrix
//matrix multiplication
vector<vector<ull>> multiply(vector<vector<ull>> &a, vector<vector<ull>> &b)
{
    int l = a.size(); //Get size of matrix a
    vector<vector<ull>> m(l, vector<ull>(l, 0)); // matrix m  for storing value after multiplication ,initiated with all values as  0s
    //3 for loops for matrix multiplication
    for (int i = 0; i < l; i++) // to move along the rows of matrix a
    {
        for (int j = 0; j < l; j++) // to move along the columns of matrix b
        {
            for (int k = 0; k < l; k++)  //for row-column wise multiplication
            {
                m[i][j] += a[i][k] * b[k][j]; 
            }
        }
    }
    return m; //return the resultant matrix m  after multiplication
}

//Function to calculate nth fibonacci number by repeated squaring
vector<vector<ull>> fib_by_matrix(vector<vector<ull>> &a, int n)
{
    if (n == 0) //Base case
    {
        vector<vector<ull>> ans = {{1, 0}, {0, 1}}; //identity matrix 
        return ans; //For n==0 return identity matrix
    }

    if (n == 1) //Base case
    {
        return a;//For n==0 return identity matrix
    }
    vector<vector<ull>> temp = fib_by_matrix(a, n / 2); //Recurssive step with n/2 
    vector<vector<ull>> ans = multiply(temp, temp);  //Binary exponentiation 
    if (n & 1) //If n is odd multiply ans matix  with matrix a once again 
    {
        ans = multiply(ans, a);
    }
    return ans; //return ans matrix
}

//Function to give nth fibonacci number from the  obtained matrix
ull fib3(int n)
{
    vector<vector<ull>> a = {{1, 1}, {1, 0}}; //Matrix a is recurrence matrix  
    vector<vector<ull>> m; //matrix m to store value obtained by function fib by matrix
    m = fib_by_matrix(a, n); //Function call with matrix a and n
    return m[0][1]; //nth fibonacci number is present at the position [0][1]
}

int main()
{
    int n;
    ull Fn;
    //Taking user input for n 
    cout << "Enter the value of n: ";
    cin >> n;

    cout<<"n"<<" "<<"Fn"<<" "<<"log(Fn)"<<" "<<"log(Tn)"<<"\n";
    
    for(int i=0;i<=n;i++)
    {    
         // start time
        auto start=chrono::high_resolution_clock::now();

        Fn= fib3(i) ;

        // end time
        auto end=chrono::high_resolution_clock::now();
       
       //To convert into seconds from nanoseconds subtracted log2(1e-9)==29.8973
        double LTn=log2(chrono::duration_cast<chrono::nanoseconds>(end - start).count())-29.8973;
         
        
        cout<<i<<" "<<Fn<<" "<<log2(Fn)<<" "<<LTn<<"\n";
        //cout<<LTn<<"\n";
    }
     
}