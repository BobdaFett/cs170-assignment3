#include <iostream>
using namespace std;

#pragma warning(disable : 4996)

int main()
{
    char str[] = "Something to type";
    char* pch;
    printf("Splitting string \"%s\" into tokens:\n", str);
    pch = strtok(str, " ,.-");
    while (pch != NULL)
    {
        printf("%s\n", pch);
        pch = strtok(NULL, " ,.-");
    }
    return 0;
}