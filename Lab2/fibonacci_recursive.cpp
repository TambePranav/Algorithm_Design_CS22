
/* 
Name - Pranav Tambe
Roll No - 2106339 */

#include <bits/stdc++.h>
#include<chrono> //import chrono library for time calculation
using namespace std;
using namespace std::chrono;
#define ull unsigned long long //Macro defining unsigned long long integer as ull

// function to calculate nth fibonacci number recursively
int fib1(int n) 
{
    if (n == 0) //Base case F0=0
        return 0;
    if (n == 1) //Base case F1=1
        return 1;
    return fib1(n - 1) + fib1(n - 2); //Recursive  step Fn=Fn-1+Fn-2
}

int main()
{
    int n,Fn;
    //Taking user input for n 
    cout << "Enter the value of n: ";
    cin >> n;

    cout<<"n"<<" "<<"Fn"<<" "<<"log(Fn)"<<" "<<"log(Tn)"<<"\n";
    
    for(int i=0;i<=n;i++)
    {    
         // start time
        auto start=chrono::high_resolution_clock::now();

        Fn= fib1(i) ;

        // end time
        auto end=chrono::high_resolution_clock::now();

      //To convert into seconds from nanoseconds subtracted log2(1e-9)==29.8973
        double LTn=log2(chrono::duration_cast<chrono::nanoseconds>(end - start).count())-29.8973;
         
        
        cout<<i<<" "<<Fn<<" "<<log2(Fn)<<" "<<LTn<<"\n";
        //cout<<LTn<<"\n";
    }
     
}