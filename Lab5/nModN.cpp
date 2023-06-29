
/*
Name - Pranav Tambe
Roll No - 2106339 */

/* This code defines a class named "noModN" which is used to perform operations like addition, subtraction, multiplication and increment/decrement on numbers.
The operations are performed on numbers modulo N where N is a template parameter. */

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
};
int main()
{
    // Output the string "N is 37" followed by a new line
    cout << "N is 37 " << endl;

    // Declare three integer variables `a`, `b`, and `c`
    int a, b, c;

    // Prompt the user to enter three integer values separated by a space
    cout << "Enter the space separated a,b,c integers  :";
    cin >> a >> b >> c;

    // Create instances of `noModN<37>` with the values of `a`, `b`, and `c`
    noModN<37> integer1(a);
    noModN<37> integer2(b);
    noModN<37> integer3(c);

    // Create an instance of `noModN<37>` with the value 1
    noModN<37> integer4(1);

    // Perform the operation `(a + b) * c` and store the result in `integer4`
    integer4 = (integer1 + integer2) * integer3;

    // Output the result of the calculation
    cout << "(a+b)*c :";
    integer4.print();

    // Perform the operation `a - b` and store the result in `integer4`
    integer4 = integer1 - integer2;

    // Output the result of the calculation
    cout << "a-b:";
    integer4.print();

    // Perform the operation `a++` and store the result in `integer4`
    integer4 = integer1++;

    // Output the result of the calculation
    cout << "a++:";
    integer4.print();

    // Perform the operation `++a` and store the result in `integer4`
    integer4 = ++integer1;

    // Output the result of the calculation
    cout << "++a:";
    integer4.print();
}
