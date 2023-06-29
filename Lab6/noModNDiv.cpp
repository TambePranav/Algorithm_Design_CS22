
/*
Name - Pranav Tambe
Roll No - 2106339 */

 

#include <bits/stdc++.h> // This line includes the standard C++ library.
using namespace std;     // This line uses the standard namespace.
vector<int> divide(int i, int j)
{
    // Check if j is 0
    if (j == 0)
    {
        // If j is 0, return a vector with -1 as the two elements
        return {-1, -1};
    }
    vector<int> ans; // Declare a vector to store the result
    // Check if i is 0
    if (i == 0)
    {
        // If i is 0, set the vector to {0, 0} and return
        ans = {0, 0};
        return ans;
    }
    // Perform a recursive call to divide with i and j as inputs
    ans = divide(i >> 1, j);
    // Shift the bits of the first element in the vector to the left by one place
    ans[0] = ans[0] << 1;
    // Shift the bits of the second element in the vector to the left by one place
    ans[1] = ans[1] << 1;
    // Check if the least significant bit of i is 1
    if (i & 1)
    {
        // If the least significant bit is 1, add 1 to the second element in the vector
        ans[1] += 1;
    }
    // Check if the second element in the vector is greater than or equal to j
    if (ans[1] >= j)
    {
        // If it is, subtract j from the second element and add 1 to the first element
        ans[1] -= j;
        ans[0] += 1;
    }
    // Return the result vector
    return ans;
}
   // This function uses the Extended Euclidean algorithm to find the coefficients of Bezout's identity
vector<int> Extended_Euclid(int a, int b)
{   
    // Base case: if b is 0, return {1, 0, a}
    if(b == 0) {
        vector<int> a1 = {1, 0, a};
        return a1;
    }
    
    // Recursively call the function with b and the remainder of a divided by b
    vector<int> ans = Extended_Euclid(b, divide(a, b)[1]);
    
    // Swap the elements in the ans vector to get the correct order of the coefficients
    int temp = ans[1];
    ans[1] = ans[0] - (divide(a, b)[0]) * temp;
    ans[0] = temp;
    
    // Return the coefficients of Bezout's identity
    return ans;  
}

template <int N> // define template with n
class noModN
{
private:
    int m; // private member m

public:

    // Constructor for the custom data type "noModN"
    noModN(int k)
    {
        // Set the value of "m" to the remainder of dividing "k" by "N"
        m = divide(k, N)[1];
    }

    noModN operator+(noModN num)
    {
        noModN ans(0); // Declare a noModN object to store the result
        // Check if the sum of the two noModN objects is greater than N-1
        if (m + num.m > N - 1)
        {
            // If it is, subtract N from the sum to keep it within the range [0, N-1]
            ans.m = m + num.m - N;
        }
        else
        {
            // If not, store the sum directly in the result object
            ans.m = m + num.m;
        }
        // Return the result object
        return ans;
    }

    // Define the negation operator for the custom data type "noModN"
    noModN operator-()
    {
        // Create a noModN object with initial value of 0
        noModN ans(0);
        // If m is equal to 0, return the ans object
        if (m == 0)
            return ans;
        // Otherwise, set the value of ans.m to N-m and return ans
        ans.m = N - m;
        return ans;
    }

    // Define the subtraction operator for the custom data type "noModN"
    noModN operator-(noModN num)
    {
        // Return the result of adding the negation of "num" to "this" object
        return (*this) + (-num);
    }

    // Define the pre-increment operator for the custom data type "noModN"
    noModN &operator++()
    {
        // Create a noModN object with value 1
        noModN one(1);
        // Increment the current object by adding "one" to it
        (*this) = (*this) + one;
        // Return a reference to the incremented object
        return *this;
    }

    // Define the post-increment operator for the custom data type "noModN"
    noModN operator++(int)
    {
        // Create a noModN object with value 0
        noModN old(0);
        // Store the current value of "this" object in "old"
        old = *this;
        // Use the pre-increment operator to increment "this" object
        ++(*this);
        // Return the old value of "this" object
        return old;
    }

    // Define the multiplication operator for the custom data type "noModN"
    noModN operator*(noModN num)
    {
        // Create a noModN object and store the result of the multiplication
        noModN ans(m * num.m);
        // Return the result
        return ans;
    }

    // Prints the value of member variable "m" of the "noModN" object
    void print()
    {
        // Use the "cout" function to output the value of "m"
        cout << m << endl;
    }

    // This function finds the inverse of m mod N
 noModN findInverse(){
    // Call the Extended_Euclid function to get the coefficients of Bezout's identity
    vector<int> ans = Extended_Euclid(m, N);

    // If the GCD is negative, add N to make it positive
    if(ans[0] < 0) {
        ans[0] += N;
    }

    // Create a noModN object with the inverse of m mod N
    noModN inv(ans[0]);
    if(ans[2] == 1)
     { // If the third element of the ans array is equal to 1
       return inv;   // return the value of inv
    }
 throw runtime_error("Divide by 0 error"); // Otherwise, throw a runtime error with the message "Divide by 0 error"

}
// Overloaded division operator for noModN objects
noModN operator/(noModN num)
{
    // Create a noModN object with a value of 1
    noModN ans1(1);
    
    // Find the inverse of the divisor
    ans1 = num.findInverse();
    
    // Multiply the dividend by the inverse of the divisor
    ans1 = ans1 * (*this);
    
    // Return the result of the division
    return ans1;
}



};
int main()
{
    // Declare variables a and b and get input from the user
    int a, b;
    cout << "Enter the space separated a,b integers  :";
    cin >> a >> b ;
    
    // Create noModN objects ans1, ans2, and ans3 
    noModN<60> ans1(a);
    noModN<60> ans2(b);
    noModN<60> ans3(b);
    
    // Perform modular division using the overloaded / operator for noModN objects
    ans3 = ans1 / ans2;
    
    // Print the result of the division in mod N
    cout << "a/b in mod N is: ";
    ans3.print();
 
    // Exit the program
    return 0;
}

