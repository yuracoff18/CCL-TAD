#include "src/CCL.h"
#include <vector>
#include <iostream>

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

int main(int argc, char const *argv[])
{
    
    vector<char> test = {'a', 'a', 'a', 'b', 'c', 'd', 'd', 'a'};
    vector<char> findA = {'a', 'a', 'a'};

    CCL JK(test);

    printListLikeString(JK.expand());

    JK.insertElement(1, 'b');

    printListLikeString(JK.expand());

    return 0;
}
