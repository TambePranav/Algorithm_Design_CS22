
// Pranav Tambe
// 2106339

#include <bits/stdc++.h> //bits header file to include inbuilt data structures
using namespace std;

int larger(vector<int> vec0, vector<int> vec1)
{
    // Check if the sizes of the two vectors are different
    if (vec0.size() != vec1.size())
    {
        // Return 0 if vec0 is larger, 1 if vec1 is larger
        return vec0.size() > vec1.size() ? 0 : 1;
    }

    // Iterate over the elements of the vectors
    for (unsigned long long int i = 0; i < vec0.size(); i++)
    {
        // Return 0 if vec0 is larger at the current position
        if (vec0[i] > vec1[i])
        {
            return 0;
        }
        // Return 1 if vec1 is larger at the current position
        if (vec0[i] < vec1[i])
        {
            return 1;
        }
    }

    // If the two vectors are equal, return -1
    return -1;
}
// template with number b
template <int b>
// class base b
class base_b
{
private:
    // private data vector
    vector<int> v;

public:
    // public functions
    //  base b  constructor with argument as vector
    base_b(vector<int> v1)
    {
        v = v1;
    }

    // base b  constructor with argument as  integer
    base_b(int n)
    {
        vector<int> vec;
        if (n == 0)
        {
            vec.push_back(0);
        }
        while (n > 0) // till n is greater than 0
        {
            vec.push_back(n % b); // find the mod add to last of vector
            n /= b;               // divide n by b
        }
        vec.push_back(0);                // pushing the sign bit
        reverse(vec.begin(), vec.end()); // reverse the vector
        *this = base_b(vec);             // store the vector in (*this)
    }
    /*  base_b(base_b&& a) noexcept
         : v(a.v)
     {
         delete &(a.v); // we'll talk more about this line below
     }

     base_b& operator=(base_b&& a) noexcept{
         // Self-assignment detection
         if (&a == this)
             return *this;

         // Release any resource we're holding
         delete &v;

         // Transfer ownership of a.m_ptr to m_ptr
         v = a.v;
         delete &(a.v); // we'll talk more about this line below

         return *this;
     } */

    void carrfnc()
    {
        for (unsigned long long int i = v.size(); i > 0; i--)
        { //
            if (v[i] < 0)
            { // If the ith element of the vector v is less than zero, this if statement will execute.
                v[i] += b;
                for (int j = i - 1; j > 0; j--)
                {
                    if (v[j] > 0) // This line subtracts 1 from the jth element of the vector v.
                    {
                        v[j] -= 1; // If the jth element of the vector v is not greater than zero, this else statement will execute
                    }
                    else
                    {
                        v[j] += b - 1; // This line adds b - 1 to the jth element of the vector v.
                    }
                }
            }
            (*this).remove(); // This line calls the remove method on the current object (*this). This line is likely removing an element from the vector, but the behavior is not specified in the code provided.
        }
    }
    base_b operator+(base_b y)
    {

        if (v[0] == y.v[0])
        {                                                               // if numbers are positive
            vector<int> ans;                                            // Vector ans of integers to store the answer
            int car = 0;                                                // variable car to store car initialized with 0
            unsigned long long int minsize = min(v.size(), y.v.size()); // To find the minimum size
            unsigned long long int vsize = v.size();                    // size of first number
            unsigned long long int ysize = y.v.size();                  // size of y

            for (unsigned long long int i = 1; i < minsize; i++)
            {
                int m = v[vsize - i] + y.v[ysize - i] + car; // add car with end  value from  vector v and vector y.v
                if (m < b)
                {
                    ans.push_back(m);
                    car = 0;
                } // if  the number is less than b push back in ans
                else
                {
                    ans.push_back(m % b);
                    car = m / b;
                } // else pushback mod of number m and store the value after division in car
            }

            for (unsigned long long int i = minsize; i < v.size(); i++)
            {
                int m = v[vsize - i] + car; // add car with end  value from  vector v
                if (m < b)
                {
                    ans.push_back(m);
                    car = 0;
                } // if  the number is less than b push back in ans
                else
                {
                    ans.push_back(m % b);
                    car = m / b;
                } // else pushback mod of number m and store the value after division in car
            }

            for (unsigned long long int i = minsize; i < y.v.size(); i++)
            {
                int m = y.v[ysize - i] + car; // add car with end  value from  vector y.v
                if (m < b)
                {
                    ans.push_back(m);
                    car = 0;
                } // if  the number is less than b push back in ans
                else
                {
                    ans.push_back(m % b);
                    car = m / b;
                } // else pushback mod of number m and store the value after division in car
            }
            if (car > 0)
                ans.push_back(car);          // If still carry remains  then push back
            ans.push_back(0);                // push the sign bit
            reverse(ans.begin(), ans.end()); // Reverse the vector
            base_b a(ans);                   // put this ans vector in base b and return
            return a;
        }

        else
        {
            // if first number is negative
            if (v[0] == 1)
            {
                // subtract first number from second
                base_b temp1(v);
                temp1.v[0] == 0;
                return y - temp1;
            }
            // else subtractb second number from first
            base_b temp1(y.v);
            temp1.v[0] = 0;
            return *this - temp1;
        }
    }

    base_b operator-(base_b y)
    {                                 //: This line declares a member function operator- for the class base_b that takes another base_b object y as input.
        vector<int> ans;              // This line declares a vector called ans to store the result of the subtraction operation.
        int compare = larger(v, y.v); // This line calls the larger function which compares the size of the two base_b objects and returns -1, 0, or 1 depending on the result of the comparison.
        if (compare == -1)
        { // If the comparison result is -1, it means that the second base_b object y is larger than the first one.
            base_b ans(0);
            return ans; // In this case, the function returns a base_b object with a value of 0.
        }

        if (compare == 1)
        { // If the comparison result is 1, it means that the first base_b object is larger than the second one.
            base_b temp(0);
            temp = y - (*this);
            temp.v[0] = 1; // In this case, the function performs subtraction in the opposite order and returns the result with a sign of positive.
            return temp;
        }
        int minsize = min(v.size(), y.v.size()); // This line calculates the size of the smaller base_b object and stores it in the minsize variable.
        // This line stores the size of both base_b objects in two separate variables vsize and ysize.
        int vsize = v.size();
        int ysize = y.v.size();

        // This loop starts from index 1 and continues until i is equal to minsize. For each iteration, the value of v[vsize-i]-y.v[ysize-i] is stored in the ans vector.
        for (int i = 1; i < minsize; i++)
        {
            ans.push_back(v[vsize - i] - y.v[ysize - i]);
        }

        // This loop starts from minsize and continues until i is equal to vsize. For each iteration, the value of v[vsize-i] is stored in the ans vector.
        for (int i = minsize; i < vsize; i++)
        {
            ans.push_back(v[vsize - i]);
        }
        // This line adds a 0 to the end of the ans vector.
        ans.push_back(0);
        reverse(ans.begin(), ans.end()); // This line reverses the elements in the ans vector.
        base_b a(ans);                   // This line creates a new base_b object a with the values stored in the ans vector.
        a.carrfnc();                     // This line calls the carrfnc function on the a object.
        return a.remove();               // This line returns the result of the subtraction operation after removing any leading zeros from the a object.
    }

    // Highh school method
    /*     base_b operator*(base_b y){
            int car=0; //initializes a variable "car" to 0 which will be used to keep track of the carry over during multiplication.
            int sign=0; // initializes a variable "sign" to 0 which will keep track of the sign of the result.
            if(v[0]^y.v[0]==1){sign=1;} //checks if the first elements of the two instances being multiplied have different signs and sets "sign" to 1 if true.
            v[0]=y.v[0]=0; //sets the first elements of both instances to 0 so that the sign does not affect the calculation.
            int l1=v.size(),l2=y.v.size(); //gets the lengths of the two instances.
            int k=0,l=0; // initializes two variables "k" and "l" to 0. They will be used in the calculation.
            vector<int>ans(l1+l2+1,0); // creates a vector "ans" with the length of "l1 + l2 + 1" and initializes all elements to 0. This will be used to store the result of the multiplication.

            //The for loop "for(int i=l1-1;i>=0;i--)" iterates through each element in the first instance from the end to the beginning.
            for(int i=l1-1;i>=0;i--)
            {
                l=0;
                for(int j=l2-1;j>=0;j--)
                {
                int s=v[i]*y.v[j]+ans[l+k]+car; //calculates the product of the two elements being multiplied, adds it to the current value in the "ans" vector, and adds the "car" value.
                ans[l+k]=s%b; //sets the value in the "ans" vector at index "l + k" to the remainder of "s" divided by "b"
                car=s/b; // sets the "car" value to the result of "s" divided by "b".
                    l++; //increments the "l" variable by 1.
                }
            if(car>0)ans[l+k]+=car; //checks if the "car" value is greater than 0 and adds it to the current value in the "ans" vector if true.
            car=0; // sets the "car" value back to 0 for the next iteration.
            k++; // increments the "k" variable by 1.
            }
            //while((ans.back()==0))" removes any 0 elements from the end of the "ans" vector
            while((ans.back()==0))
            {
                ans.pop_back();
            }
            ans.push_back(sign); //dds the "sign" value to the end of the "ans" vector.
            reverse(ans.begin(),ans.end()); // reverses the "ans" vector so that the elements are in the correct order.
            base_b temp(ans); // creates a temporary instance of the "base_b" class with the "ans" vector as its value.
            temp=temp.remove(); // removes any leading 0 elements from the "temp" instance.
            return temp; // returns the "temp" instance as the result of the multiplication

        } */

    base_b &operator++()
    {
        // prefix increment
        base_b one(1);
        *this = *this + one; // add one
        return *this;        // return new value by reference
    }

    // postfix increment
    base_b operator++(int)
    {
        base_b old(0);
        old.v = v;  // copy old value
        ++*this;    // prefix increment
        return old; // return old value
    }

    base_b leftshift()
    {
        base_b temp(0); // creates a temporary object temp of class base_b and initializes it to 0.
        temp.v = v;     // sets the v member of temp to be equal to the v member of the object the function is called on.
        base_b zero(0); // creates an object zero of class base_b and initializes it to 0.
        if (temp.v != zero.v)
        { // checks if the binary representation of temp is not equal to that of zero.
            temp.v.push_back(0);
        }
        temp = temp.remove();
        return temp;
    }

    base_b rightshift()
    {
        base_b temp(0);
        // The value of the current object is assigned to the temporary object
        temp.v = v;

        // The last element of the vector v is popped off
        temp.v.pop_back();

        // If the size of the vector v is 1 after popping off the last element, it pushes back 0 to the vector
        if (temp.v.size() == 1)
        {
            temp.v.push_back(0);
        }

        // The remove() function is called on the temporary object to remove leading zeros
        temp = temp.remove();

        // The modified temporary object is returned
        return temp;
    }
    base_b remove() // remove any unnecessary zeros from the answer base_b object
    {
        base_b temp(0);
        temp.v = v;
        int i = 0;
        if (temp.v.size() != 1)
        {
            while (temp.v[i] == 0)
            {
                i++;
            }
            i--;
            temp.v.erase(temp.v.begin(), temp.v.begin() + i);
        }
        // m.insert(m.begin(), 0);
        if (temp.v.size() == 1)
        {
            temp.v.push_back(0);
        }
        return (temp);
    }

    // This function performs integer multiplication of two numbers represented in the base_b data structure.
    // It returns the product of the multiplication.
    base_b operator*(base_b y)
    {
        base_b zero(0); ////Declaring and initializing a base_b variable zero with value 0.
        // Checking if either of the two numbers is equal to zero.
        // If either is equal to zero, the result is returned as zero.
        if (y.v == zero.v)
        {
            return zero;
        }
        if (v == zero.v)
        {
            return zero;
        }
        // Declaring and initializing a base_b variable one with value
        base_b one(1);
        if (y.v.size() == 2) ////Checking if the size of the second parameter (y) is equal to 2.
        {
            base_b ans(0);                       // A variable ans of type base_b is declared and initialized with the value 0.
            for (int i = 0; i < y.v.back(); i++) // The current object is added to ans in each iteration of the loop.
            {
                ans = ans + (*this); //: The current object is added to ans in each iteration of the loop.
            }
            return ans; // The value of ans is returned as the result of the function.
        }

        else
        {
            base_b result(1);       // A variable result of type base_b is declared and initialized with the value 1.
            base_b mod(y.v.back()); // A variable mod of type base_b is declared and initialized with the value of the last element of y.v.

            // Shift the result of (*this) * (y.rightshift()) to the left by one position
            result = (*this) * (y.rightshift());
            result = result.leftshift();
            // Add the result of (*this) * mod to the result
            result = result + (*this) * mod;
            return result;
        }
    }

    // This function performs integer division of two numbers represented in the base_b data structure.
    // It returns the quotient of the division.
    /* base_b operator/(base_b b2) {
         //Declaring and initializing base_b variables zero and one with values 0 and 1 respectively.
            base_b zero(0);
            base_b one(1);

   //Checking if the numerator (v) is equal to zero.
//If it is, the result is returned as zero.

            if (v == zero.v) {
                return zero;
            }

            base_b r(0);
            base_b ans(0);
            base_b mod(v.back());
            base_b divb((((*this).rightshift()).remove()).v);
            //Calculating the first iteration of the quotient using the divb and the second parameter (b2).
            ans = divb / b2;
            ////Calculating the first iteration of the remainder using the divb, the second parameter (b2), and the calculated quotient (ans).
            r = divb - b2 * ans;
            //Shifting the result and the remainder to the left, removing any trailing zeros, and adding the modulus to the remainder.
            ans = ans.leftshift().remove();
            r = r.leftshift().remove() + mod;
            //Continuing to subtract b2 from the remainder until the remainder is no longer larger than b2.
//For each iteration, the quotient is incremented by 1.

            while (larger(r.v, b2.v) < 1) {
                r = r - b2;
                ans = ans + one;
            }
            //Removing any trailing zeros from the result.
            ans = ans.remove();
            //Returning the final result of the division.
            return ans;
            } */

    base_b operator/(base_b b2)
    {

        base_b one(1); // constructor to initialize the base_b object with the value of 1
        base_b ans(0); // constructor to initialize the base_b object with the value of 0

        while (larger(v, b2.v) != 1)
        {
            *this = *this - b2; // subtract the second base_b object from the current
                                // add 1 to the answer base_b object
            ans = ans + one;
        }
        // remove any unnecessary zeros from the answer base_b object
        ans = ans.remove();
        return ans; // return the final answer base_b object
    }

    void print() // function to print the number
    {
        for (unsigned long long int i = 0; i < v.size(); i++)
        {
            printf("%d ", v[i]);
        }
        printf("\n");
    }
};

int main()
{
    int x, y, z;
    cout << "Enter the space separsted x,y,z integers  :";
    cin >> x >> y >> z;
    base_b<37> integer1(x);
    base_b<37> integer2(y);
    base_b<37> integer3(z);
    base_b<37> integer4(z);
    base_b<37> remain(z);
    integer4 = (x + y) * z;
    cout << "(x+y)*z :";
    integer4.print();
    integer4 = x / y;
    cout << "(x/y) :";
    integer4.print();
    remain = integer1 - (integer4 * integer2);
    remain.print();
    cout << "(x/y) :";
    integer4.print();
    integer4 = x++;
    cout << "x++ :";
    integer4.print();
    integer4 = ++x;
    cout << "++x :";
    integer4.print();
}
