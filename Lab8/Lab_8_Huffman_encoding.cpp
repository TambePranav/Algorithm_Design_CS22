/*
 Name-Pranav Tambe
Roll NO-2106339
*/

#include <bits/stdc++.h> // includes all the standard libraries
using namespace std;     // standard namespace
class TreeNode
{
public:
    int f;           // frequency of character
    char c;          // character
    TreeNode *left;  // pointer to the left child
    TreeNode *right; // pointer to the right child
                     // Constructor function with two arguments: frequency and character
    TreeNode(int fre, int ch)
    {
        c = ch;
        f = fre;
        left = NULL;  // initialize left child to NULL
        right = left; // initialize right child to left child (NULL)
    }

    // Constructor function with two arguments: left child and right child nodes
    TreeNode(TreeNode *l, TreeNode *r)
    {
        c = '#';         // '#' is used to represent a non-leaf node
        f = l->f + r->f; // frequency of the parent = frequencies of the left child + frequencies of the right child
        left = l;        // set left child
        right = r;       // set right child
    }

    // Constructor function with one argument: a node
    TreeNode(TreeNode *l)
    {
        c = l->c;         // copy character from the node
        f = l->f;         // copy frequency from the node
        left = l->left;   // copy left child node
        right = l->right; // copy right child node
    }
};
// Define a class named Compare
class Compare
{
public:
    // Define a boolean operator that takes two TreeNode pointers as input parameters
    bool operator()(TreeNode *a, TreeNode *b)
    {
        // Return true if the frequency value of node a is greater than the frequency value of node b
        return a->f > b->f;
    }
};

// This function takes a string 's' as input and returns a vector of pairs.
// Each pair contains a character and its frequency of occurrence in the string.

vector<pair<char, int>> countf(string s)
{
    vector<pair<char, int>> ans; // Create a vector to store the pairs.
    // Loop through the string 's' to count the frequency of each character.
    for (int i = 0; i < s.size(); i++)
    {
        bool f = 0;
        // Loop through the vector 'ans' to check if the character is already counted.
        for (auto &j : ans)
        {
            if (j.first == s[i])
            {
                j.second++; // Increment the frequency count of the character.
                f = 1;      // Set 'f' to true to indicate that the character is already counted.
            }
        }
        // If the character is not already counted, add a new pair to the vector.
        if (f == 0)
            ans.push_back({s[i], 1});
    }

    // Sort the vector 'ans' in ascending order of frequency counts using bubble sort algorithm.
    for (int i = 1; i < ans.size(); i++)
    {
        for (int j = 0; j < ans.size() - i; j++)
        {
            if (ans[j + 1].second < ans[j].second)
            {
                pair<char, int> temp = ans[j];
                ans[j] = ans[j + 1];
                ans[j + 1] = temp;
            }
        }
    }

    // Return the vector 'ans' containing pairs of characters and their frequency counts.
    return ans;
}

// This function calculates the edit distance between two input strings
string edit_distance(string str1, string str2)
{
    // Create a 2D vector of size (str2.size()+1)x(str1.size()+1) and initialize with 0
    vector<vector<int>> dp(str2.size() + 1, vector<int>(str1.size() + 1, 0));
    // Fill first column of the vector using dynamic programming
    for (int i = 1; i < dp.size(); i++)
        dp[i][0] = 3 + dp[i - 1][0];

    // Fill first row of the vector using dynamic programming
    for (int i = 1; i < dp[0].size(); i++)
        dp[0][i] = 1 + dp[0][i - 1];

    // Fill remaining cells of the vector using dynamic programming
    for (int i = 1; i <= str2.size(); i++)
    {
        for (int j = 1; j <= str1.size(); j++)
        {
            if (str2[i - 1] == str1[j - 1])                                                 // if the characters match
                dp[i][j] = dp[i - 1][j - 1];                                                // no operation required
            else                                                                            // if the characters do not match
                dp[i][j] = min({dp[i - 1][j] + 3, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 2}); // find minimum edit distance
        }
    }

    // Output the edit distance between the two strings
    cout << "Edit distance is :" << dp[str2.size()][str1.size()] << endl;
    cout << endl;

    int i = str2.size(), j = str1.size();
    string ans = str1;
    cout << "----------------------------------   Operations  --------------------------------" << endl;
    while (i > 0 && j > 0)
    {
        // If string charcters are equal reduce i and j
        if (j - 1 >= 0 && i - 1 >= 0 && str1[j - 1] == str2[i - 1])
        {
            i--;
            j--;
        }
        // if current value comes from diagonal value +2 we have replaced the character
        // reduce i and j
        else if (dp[i][j] == dp[i - 1][j - 1] + 2)
        {
            cout << "Replace " << j - 1 << " with " << str2[i - 1] << endl;
            ans += '2';
            ans += str2[i - 1];
            ans += to_string(j - 1);
            i--;
            j--;
        }
        // if current value comes from left value +1 we have deleted the character
        // reduce j
        else if (dp[i][j] == dp[i][j - 1] + 1)
        {
            cout << "Delete " << j - 1 << endl;
            ans += '1';
            ans += '@';
            ans += to_string(j - 1);
            j--;
        }
        // if current value comes from upward value +3 we have inserted the character
        // reduce i
        else if (dp[i][j] == dp[i - 1][j] + 3)
        {
            cout << "Insert " << str2[i - 1] << " at " << j << endl;
            ans += '0';
            ans += str2[i - 1];
            ans += to_string(j);
            i--;
        }
    }
    // if still j remains then we have to delete those characters from str1
    while (j != 0)
    {
        cout << "Delete " << j - 1 << endl;
        ans += '1';
        ans += '@';
        ans += to_string(j - 1);
        j--;
    }
    // if still i remains then we have to insert those characters of str2 in str1
    while (i != 0)
    {
        cout << "Insert " << str2[i - 1] << " at " << j << endl;
        ans += '0';
        ans += str2[i - 1];
        ans += to_string(j);
        i--;
    }
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << endl;
    // return ans string containing  str1 and operations
    return ans;
}
// This function generates a Huffman coding table for the given Huffman tree
void huffmanTable(TreeNode *root, unordered_map<char, string> &table, string encoding)
{
    // Base case
    // if the root is NULL, we have reached the end of the tree, so we return
    if (root == NULL)
        return;
    // Base case
    //  If the current node is a leaf node, we have found a character and its corresponding Huffman code
    if (root->left == NULL && root->right == NULL)
    {
        // Add the character and its code to the table
        table[root->c] = encoding;
    }
    else // If the current node is not a leaf node, we continue traversing the tree
    {

        // by recursively calling the function on its left and right subtrees
        huffmanTable(root->left, table, encoding + '0');
        huffmanTable(root->right, table, encoding + '1');
    }
}

// This function takes in a priority queue of TreeNode pointers and returns the root node of a Huffman tree.
TreeNode *huffmanTree(priority_queue<TreeNode *, vector<TreeNode *>, Compare> &pq)
{
    // If the priority queue only contains one node
    // return that node as the root of the Huffman tree.
    if (pq.size() == 1)
        return pq.top();
    // Otherwise, create new left and right child nodes using the top two nodes from the priority queue.
    TreeNode *l = new TreeNode(pq.top());
    pq.pop();
    TreeNode *r = new TreeNode(pq.top());
    pq.pop();
    // Create a new parent node using the left and right child nodes, and push it onto the priority queue.
    pq.push(new TreeNode(l, r));
    // Recursively call this function with the updated priority queue until only one node remains, which is the root of the Huffman tree.
    return huffmanTree(pq);
}

void huffmanEncoding(string str1, string str2)
{
    string s = edit_distance(str1, str2); // Get the edit distance of two strings
    cout << "Message before encoding :" << s << endl;
    cout << endl;
    vector<pair<char, int>> temp = countf(s);
    cout << "----------------------------------  Character Frequency --------------------------------" << endl;
    cout << "Character "
         << " Frequency " << endl;
    for (auto k : temp)
    {
        cout << k.first << "              " << k.second << endl;
    }
    // Make priority queue out of frequency and character
    priority_queue<TreeNode *, vector<TreeNode *>, Compare> pq;
    for (auto i : temp)
    {
        pq.push(new TreeNode(i.second, i.first));
    }
    // Get huffman Tree's root
    TreeNode *root = huffmanTree(pq);
    unordered_map<char, string> table;
    string sl = "";
    // Store encoding in an unordered map
    huffmanTable(root, table, sl);
    // cout<<"---------------------------------------------------------------------------------"<<endl;
    cout << endl;
    cout << "----------------------------------   Huffman Table  --------------------------------" << endl;
    cout << " Character "
         << " Encoding " << endl;
    for (auto i : table)
    {
        cout << i.first << "             " << i.second << endl;
    }
    // Make  encoded message using huffman table
    string message = "";
    for (auto i : s)
    {
        message += table[i];
    }
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Message before encoding :" << s << endl;
    cout << "The encoded message  :" << message << endl;
}

int main()
{
    // accept strings from user
    string str1, str2;
    cout << "Enter the  first string :";
    cin >> str1;
    cout << "Enter the  second string :";
    cin >> str2;
    cout << endl;
    huffmanEncoding(str1, str2);// call huffmancoding function
}