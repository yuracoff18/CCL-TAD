#include "src/CCL.h"
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

vector<char> stringToVectorChar(string &s) {
    vector<char> ans;
    ans.push_back('-');
    for (int i = 0; i < s.size(); i++)
    {
        if (isalpha(s[i]))
        {
            ans.push_back(tolower(s[i]));
        }
        else
        {
            ans.push_back('-');
        }
        
    }
    ans.push_back('-');
    return ans;
}

void printVectorInt(vector<int> &in) {
    for (int i = 0; i < in.size(); i++)
    {
        printf("%d ", in[i]);
    }
    printf("\n");
}

int main()
{
    
    int k, e;

    while (cin >> k >> e)
    {
        vector<vector<char>> strange;
        vector<CCL> excuses;
        vector<string> originalExcuses;

        string aux;
        for (int i = 0; i < k; i++)
        {
            cin >> aux;
            strange.push_back(stringToVectorChar(aux));
        }

        cin.ignore();

        for (int i = 0; i < e; i++)
        {
            getline(cin , aux);
            excuses.push_back(CCL(stringToVectorChar(aux)));
            originalExcuses.push_back(aux);
        }

        vector<int> suspiciusEach(excuses.size(), 0);
        
        int max = 0;
        for (int i = 0; i < excuses.size(); i++)
        {
            for (int j = 0; j < strange.size(); j++)
            {
                suspiciusEach[i] += excuses[i].getConsecutiveOcurrences(strange[j]);
            }

            if (suspiciusEach[i] > max)
                max = suspiciusEach[i];
        }

        for (int i = 0; i < excuses.size(); i++)
        {
            if (suspiciusEach[i] == max)
            {
                printf("%s\n", originalExcuses[i].c_str());
            }
        }
        printf("\n");
    }
    
    return 0;
}
