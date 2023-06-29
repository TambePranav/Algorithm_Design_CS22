/* 
Name - Pranav Tambe
Roll No - 2106339 
*/

#include <bits/stdc++.h> //bits header file to include inbuilt data structures 
using namespace std; 

//Function to convert a number to base b
vector<int> Convert_to_base_b(int n,int b)
{
    vector<int>v; //Vector v of integers to store the ans
    int l=0, m=1; //  integer l to  keep track of places and integer m to raise b to the power l

    if(n<b) { v.push_back(n);  return v;} //if n<b pushback n and return

    while(n>0) //till n is greater than 0 
    {
      if(n/m<b) //if n/m is less than b
      {
        v.push_back(n/m); //then pushback n/m
        n-=(n/m)*m; // reduce  n by (n/m)*m
        m/=b; //reduce m by b
        l--; //reduce places by 1
      }
      else{m*=b;l++;}  //else increase m by b and palces by 1

      if(n<b)//if n<b pushback n and break
      {
        v.push_back(n);
        break;
      }  
    }

    if(l!=0) //if still some places in number are yet to fill,fill them with zeros
    {
      while(l--)v.push_back(0);
    }  
    return v; //return v

}

//Function to add two numbers to base b
vector<int> add_base_b(vector<int>x,vector<int>y,int b) 
{
  vector<int>ans;//Vector ans of integers to store the answer
  int carry=0; // variable carry to store carry initialized with 0
   while(x.size()!=0 && y.size()!=0) //till size of vector x or till size of vector y becomes 0 do
   {
    int m=x.back()+y.back()+carry; //get numbers from the end of two vectors and add them with carry and store in int m
    x.pop_back();y.pop_back(); //pop end values
    if(m<b){ans.push_back(m);carry=0;} //if  the number is less than b push back
    else  {ans.push_back(m%b);carry=m/b;} //else pushback mod of number m and store the value after division in carry
 
   }  
   //if  vector x or vector y is not empty yet
   while(x.size()!=0)
   {
    int m=x.back()+carry; //add carry with end  value from  vector x
    x.pop_back(); //pop out the  end value 
    if(m<b){ans.push_back(m);carry=0;} //if  the number is less than b push back in ans
    else  {ans.push_back(m%b);carry=m/b;} //else pushback mod of number m and store the value after division in carry

   }
    while( y.size()!=0)
   {
    int m=y.back()+carry; //add carry with end  value from  vector x
    y.pop_back(); //pop out the  end value 
    if(m<b){ans.push_back(m);carry=0;} //if  the number is less than b push back in ans
    else  {ans.push_back(m%b);carry=m/b;}  //else pushback mod of number m and store the value after division in carry

   }
   if(carry!=0) ans.push_back(carry); //if carry is non zero then push back it in ans
   reverse(ans.begin(),ans.end()); //function to reverse the ans vector

   return ans; //Return the ans
}

//Function to print the number in base b
void print(vector<int>v)
{
for(int i=0;i<v.size()-1;i++) //iterate through vector till (size-2)th index
{
  cout<<v[i]<<":"; 
}
cout<<v[v.size()-1]; //print (size-1)th index or the last entry
}

int main()
{
int x,y,b; //Variables to store numbers and the base 
//Take user inputs
cout<<"Enter the base: ";
cin>>b;
cout<<"Enter the first number: ";
cin>>x ;
cout<<"Enter the second number: ";
cin>>y;

//call the function and print the results
cout<<"First number to the base "<<b<<": "<<"(";print(Convert_to_base_b(x,b));cout<<")"<<"_"<<b<<endl;
cout<<"Second number to the base "<<b<<": "<<"(";print(Convert_to_base_b(y,b));cout<<")"<<"_"<<b<<endl;
cout<<"Sum of numbers to the base "<<b<<": "<<"(";print(add_base_b(Convert_to_base_b(x,b),Convert_to_base_b(y,b),b));cout<<")"<<"_"<<b<<endl;;;
 
}