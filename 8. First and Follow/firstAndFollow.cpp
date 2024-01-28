#include <iostream>
#include <string.h>
#define max 20
#define MAX_SYMBOLS 20

using namespace std;

// Declarations of arrays to store production rules, terminals, non-terminals, first sets, and follow sets.
char prod[max][10];
char terminal[10], non_terminal[10];
char first[10][10], follow[10][10];
int epsilon[10];
int count_variable = 0;

// Function to find the position of a character in the non-terminal array.
int find_position(char ch)
{
    int n;
    for (n = 0; non_terminal[n] != '\0'; n++)
        if (non_terminal[n] == ch)
            break;
    if (non_terminal[n] == '\0')
        return 1;
    return n;
}

// Function to check if a character is a capital letter.
int IsCapital(char c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

// Function to add a character to an array if it doesn't exist already.
void add(char *arr, char c)
{
    int i, flag = 0;
    for (i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] == c)
        {
            flag = 1;
            break;
        }
    }
    if (flag != 1)
        arr[strlen(arr)] = c;
}

// Function to add elements from one array to another without duplicating.
void add_array(char *s1, char *s2)
{
    int i, j, flag = 99;
    for (i = 0; s2[i] != '\0'; i++)
    {
        flag = 0;
        for (j = 0;; j++)
        {
            if (s2[i] == s1[j])
            {
                flag = 1;
                break;
            }
            if (j == strlen(s1) && flag != 1)
            {
                s1[strlen(s1)] = s2[i];
                break;
            }
        }
    }
}

// Function to add a production rule to the arrays.
void add_production(char *s)
{
    int i;
    prod[count_variable][0] = s[0];
    for (i = 3; s[i] != '\0'; i++)
    {
        if (!IsCapital(s[i]))
            add(terminal, s[i]);
        prod[count_variable][i - 2] = s[i];
    }
    prod[count_variable][i - 2] = '\0';
    add(non_terminal, s[0]);
    count_variable++;
}

// Function to find the first sets for non-terminals.
void findfirst()
{
    int i, j, n, k, e, n1;
    for (i = 0; i < count_variable; i++)
    {
        for (j = 0; j < count_variable; j++)
        {
            n = find_position(prod[j][0]);
            if (prod[j][1] == (char)238) // If the production has epsilon (empty string)
                epsilon[n] = 1;
            else
            {
                for (k = 1, e = 1; prod[j][k] != '\0' && e == 1; k++)
                {
                    if (!IsCapital(prod[j][k]))
                    {
                        e = 0;
                        add(first[n], prod[j][k]);
                    }
                    else
                    {
                        n1 = find_position(prod[j][k]);
                        add_array(first[n], first[n1]);
                        if (epsilon[n1] == 0)
                            e = 0;
                    }
                }
                if (e == 1)
                    epsilon[n] = 1;
            }
        }
    }
}

// Function to find the follow sets for non-terminals.
void findfollow()
{
    int i, j, k, n, e, n1;
    n = find_position(prod[0][0]);
    add(follow[n], '$'); // $ represents the end of the input string.
    for (i = 0; i < count_variable; i++)
    {
        for (j = 0; j < count_variable; j++)
        {
            k = strlen(prod[j]) - 1;
            for (; k > 0; k--)
            {
                if (IsCapital(prod[j][k]))
                {
                    n = find_position(prod[j][k]);
                    if (prod[j][k + 1] == '\0') // If the non-terminal is at the end of the production
                    {
                        n1 = find_position(prod[j][0]);
                        add_array(follow[n], follow[n1]);
                    }
                    if (IsCapital(prod[j][k + 1]))
                    {
                        n1 = find_position(prod[j][k + 1]);
                        add_array(follow[n], first[n1]);
                        if (epsilon[n1] == 1)
                        {
                            n1 = find_position(prod[j][0]);
                            add_array(follow[n], follow[n1]);
                        }
                    }
                    else if (prod[j][k + 1] != '\0')
                        add(follow[n], prod[j][k + 1]);
                }
            }
        }
    }
}

int main()
{
    char epsilonSymbol = 238; // Representation of epsilon (empty string)

    freopen("sample.txt", "r", stdin); // Redirecting input to read from a file.

    char production[MAX_SYMBOLS];

    // Reading production rules from input file and adding them to the arrays.
    while (cin >> production)
    {
        add_production(production);
    }
    
    // Finding first and follow sets.
    findfirst();
    findfollow();
    
    // Displaying the results.
    cout << endl;
    cout << endl;
    cout << "Non-Terminal\tFIRST\tFOLLOW\n";
    cout << "======================================\n";
    for (int i = 0; i < strlen(non_terminal); i++)
    {
        cout << "\t" << non_terminal[i] << "\t";
        cout << first[i];
        if (epsilon[i] == 1)
            cout << epsilonSymbol << "\t";
        else
            cout << "\t";
        cout << follow[i] << "\n";
    }
    cout << endl;

    return 0;
}
