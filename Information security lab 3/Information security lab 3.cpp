// Information security lab 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<fstream>
#include<list>
#include<math.h>
#include <vector>
#include<math.h>

using namespace std;


bool IsCompare(const string& text, const string& dict)
{
    int i = 0;
    int j = 0;
    int miss_text = 0;
    int miss_dict = 0;
    
    if(!(text.size() > 0 && dict.size() > 0)){
        return false;
    }

    while (i < text.size() && j < dict.size())
    {
        if (text.at(i) != dict.at(j))
        {
            if (j + 1 < dict.size()) {
                if (text.at(i) == dict.at(j + 1))
                {
                    miss_dict++;
                    j++;
                }
                else {
                    miss_text++;
                    i++;
                }
            } else {
                if(i + 1 < text.size()){
                        miss_text++;
                        i++;
                }
                else {
                    i++;
                    j++;
                    miss_dict++;
                    miss_text++;
                }
            }
        } else {
            i++;
            j++;
        }

        if (miss_dict > 1 || miss_text > 1)
            return false;

    }

        if(miss_text == 0){
            int test = text.size() - (dict.size() - miss_dict);
            miss_text = (test) > 0 ? 1 : 0;
        }
        if(miss_dict == 0){
            int test = dict.size() - (text.size() - miss_text);
            miss_dict = (test) > 0 ? 1 : 0;
         }

    return (text.size() - dict.size()) == (miss_text - miss_dict);
}

vector<string> Solution(vector<string> text, vector<string>dict)
{
    vector<string> solutions;
    for (int i = 0; i < text.size(); i++)
    {
        int count = 0;
        string lastMatch;
        for (int j = 0; j < dict.size(); j++)
        {
            if (IsCompare(text[i], dict[j]))
            {
                count++;
                lastMatch = dict[j];
            }
        }
        if (count > 0)
            if (count == 1)
                solutions.push_back(string(text[i] + " " + "1" + " " + lastMatch));
            else
                solutions.push_back(string(text[i]) + to_string(count));
    }
    return solutions;
}

vector<string> Split(string &s, char ch)
{
    vector<string> sol;
    string temp = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != ch)temp += s[i];
        else
        {
            sol.push_back(temp);
            temp = "";
        }
    }
    sol.push_back(temp);
    return sol;
}

int main() 
{
    fstream in("input.txt");
    string line;
    getline(in, line);
    
    int n = stoi(Split(line, ' ')[0]);
    int m = stoi(Split(line, ' ')[1]);

    vector<string> text;
    vector<string> dict;

    for (int i = 0; i < n; i++)
    {
        getline(in, line);
        dict.push_back(line);
    }
    for (int i = 0; i < m; i++)
    {
        getline(in, line);
        text.push_back(line);
    }

    vector<string> sol = Solution(text, dict);

    for (int i = 0; i < sol.size(); i++)
        cout << sol[i]<<endl;
    return 0;   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
