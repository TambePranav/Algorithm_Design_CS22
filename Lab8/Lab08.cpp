// Pranav Tambe
// 2106339

#include <bits/stdc++.h> // includes all the standard libraries
using namespace std;     // standard namespace

string longestCommonSubsequence(string &text1, string &text2) // function declaration that takes two string inputs and returns a string
{
    vector<vector<int>> matrix(text1.size() + 1, vector<int>(text2.size() + 1, 0)); // initialize a 2D vector that stores the length of the longest common subsequence
    string s = "";                                                                  // initialize an empty string to store the longest common subsequence
    for (int i = 0; i < text1.size(); i++)                                          // loop through each character in the first string
    {
        for (int j = 0; j < text2.size(); j++) // loop through each character in the second string
        {

            if (text1[i] == text2[j]) // if the current characters match
            {
                matrix[i + 1][j + 1] = 1 + matrix[i][j]; // increment the length of the longest common subsequence by 1
            }
            else // if the current characters don't match
            {
                matrix[i + 1][j + 1] = max(matrix[i][j + 1], matrix[i + 1][j]); // set the length of the longest common subsequence to the maximum of the two values to the left and above
            }
        }
    }
    int i = text1.size(), j = text2.size(); // initialize two pointers to the end of each string
    while (i > 0 && j > 0)                  // while neither pointer has reached the beginning of its respective string
    {
        if (text1[i - 1] == text2[j - 1]) // if the current characters match
        {
            s += text1[i - 1]; // add the character to the longest common subsequence
            i--;               // move both pointers one character to the left
            j--;
        }
        else if (matrix[i - 1][j] > matrix[i][j - 1]) // if the value above is greater than the value to the left
            i--;                                      // move the pointer in the first string one character to the left
        else                                          // if the value to the left is greater than or equal to the value above
            j--;                                      // move the pointer in the second string one character to the left
    }
    reverse(s.begin(), s.end()); // reverse the longest common subsequence
    return s;                    // return the longest common subsequence
}

string shortestCommonSupersequence(string &text1, string &text2)
{
    // Initialize matrix with appropriate dimensions
    vector<vector<int>> matrix(text1.size() + 1, vector<int>(text2.size() + 1, 0));
    string s = "";

    // Initializing array for base case: when one string is empty, the length of the shortest common supersequence is the length of the other string
    for (int i = 1; i < text1.size() + 1; i++)
    {
        matrix[i][0] = i;
    }

    // Initializing array for base case: when one string is empty, the length of the shortest common supersequence is the length of the other string
    for (int i = 1; i < text2.size() + 1; i++)
    {
        matrix[0][i] = i;
    }

    // Entry for matrix to use Dynamic Programming
    for (int i = 0; i < text1.size(); i++)
    {
        for (int j = 0; j < text2.size(); j++)
        {
            // If characters match, add 1 to the length of shortest common supersequence
            if (text1[i] == text2[j])
            {
                matrix[i + 1][j + 1] = 1 + matrix[i][j];
            }
            // If characters don't match, take minimum of adding character to one of the strings
            else
            {
                matrix[i + 1][j + 1] = 1 + min(matrix[i][j + 1], matrix[i + 1][j]);
            }
        }
    }

    // Backtracking to construct the shortest common supersequence
    int i = text1.size(), j = text2.size();
    while (i > 0 && j > 0)
    {
        if (text1[i - 1] == text2[j - 1])
        {
            s += text1[i - 1];
            i--;
            j--;
        }
        else if (matrix[i - 1][j] > matrix[i][j - 1])
        {
            s += text2[j - 1];
            j--;
        }
        else
        {
            s += text1[i - 1];
            i--;
        }
    }

    // If one string is exhausted, append the remaining characters of the other string
    while (i > 0)
    {
        s += text1[i - 1];
        i--;
    }
    while (j > 0)
    {
        s += text2[j - 1];
        j--;
    }

    // Reverse the constructed string to get the correct order of characters
    reverse(s.begin(), s.end());
    return s;
}

int main()
{
    string s1, s2;
    cout << "Enter the first string :";
    cin >> s1;
    cout << "Enter the second string :";
    cin >> s2;
    cout << "Longest Common Subsequence is :" << longestCommonSubsequence(s1, s2) << endl;
    cout << "Shortest Common Supersequence is :" << shortestCommonSupersequence(s1, s2) << endl;
}