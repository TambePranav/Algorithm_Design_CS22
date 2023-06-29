// Pranav Tambe
// 2106339

#include <iostream>
#include<ctime>
#include <fstream>
using namespace std;

int main() {
    string s;
    int n;
    float p;
    cout<<"Enter the file name"<<endl;
    cin>>s;
    cout<<"Enter the number of vertices"<<endl;
    cin>>n;
    cout<<"Enter the probability for Graph generation between 0 and 1"<<endl;
    cin>>p;
    // Create and open a text file
    ofstream MyFile(s);

    // Write to the file
    MyFile << n <<endl;
    srand( (unsigned) time( NULL ) );
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            float a = ((float) rand()/RAND_MAX );
            if(i==j){
                MyFile<<0<<" ";
            }
            
            else if(a<p){
                int b = rand()%1000;
                MyFile<<b<<" ";
            }
            else{
                MyFile<<0<<" ";
            }
        }
        MyFile<<"\n";
    }
    // Close the file
    MyFile.close();
}