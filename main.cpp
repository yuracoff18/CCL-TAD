#include "src/CCL.h"
#include <iostream>
#include <vector>

using namespace std;

vector<char> stringToVectorChar(string &s) {
    vector<char> ans;
    for (int i = 0; i < s.size(); i++)
    {
        ans.push_back(tolower(s[i]));
    }
    return ans;
}

void printListLikeString(List l) {
    for (int i = 0; i < l.size(); i++)
    {
        if (i == 0)
        {
            char aux = l.at(i);
            printf("%c", toupper(aux));
        }
        else
        {
           printf("%c", l.at(i)); 
        }
    }
    printf("\n");
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
                printListLikeString(excuses[i].expand()); 
            }
        }
        printf("\n");
    }
    
    return 0;
}
