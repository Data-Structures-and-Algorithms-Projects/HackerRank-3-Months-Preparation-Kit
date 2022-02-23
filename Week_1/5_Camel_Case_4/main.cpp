#include <bits/stdc++.h>
#include <vector>
#include <iostream>
using namespace std;

// utility function declarations
void split(string str, string *str_op);
void concat(string str, string *str_op);
void first_upper(string str, string *final_str, bool is_pascal_case);

int main()
{
    vector<string> vec;
    string line;

    // read inputs
    while (getline(cin, line))
    {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        vec.push_back(line);
    }

    for (int i = 0; i < vec.size(); i++)
    {
        string str = vec[i];
        char operation, type;

        while (getline(cin, str))
            ;
        operation = str[0], type = str[2];
        str.erase(0, 4);

        string final_str = str;

        // split the strings
        if (operation == 'S')
        {
            split(str, &final_str);

            if (type == 'M')
            {
                final_str.erase(final_str.end() - 2, final_str.end());
            }

            // concatinates the strings
        }
        else if (operation == 'C')
        {
            if (type == 'V')
            { // variable name
                first_upper(str, &final_str, false);
                // concat(str, &final_str);
            }
            else if (type == 'M')
            { // method name
                first_upper(str, &final_str, false);
                final_str += "()";
            }
            else if (type == 'C')
            { // class name
                first_upper(str, &final_str, true);
            }

            concat(str, &final_str);
        }

        // print the output strings
        cout << final_str << endl;
    }
    return 0;
}

// split the string based on the uppercase letters as the first letter of the owrd
void split(string str, string *str_op)
{
    *str_op = str;
    int num = 0;
    for (int i = 1; i < str.size(); i++)
    {
        if (isupper(str[i]))
        {
            str_op->insert(i + num, " ");
            num++;
        }
    }

    for (auto &c : *str_op)
        c = tolower(c);
}

// concatinate the strings based on ' ' || space
void concat(string str, string *str_op)
{
    string temp = *str_op;
    int num = 0;

    for (int i = 0; i < str.size(); i++)
    {
        if (isspace(str[i]))
        {
            temp.erase(i - num, 1);
            num++;
        }
    }

    *str_op = temp;
}

// convert the first letter of a word to uppercase
void first_upper(string str, string *str_op, bool is_pascal_case = false)
{
    *str_op = str;
    string temp = str;

    // for class variables i.e. PascalCase
    if (is_pascal_case)
    {
        if (islower(str[0]))
        {
            temp[0] = toupper(str[0]);
        }
    }

    // for camelCase
    for (int i = 1; i < str.size(); i++)
    {
        if (isspace(str[i]))
        {
            temp[i + 1] = toupper(str[i + 1]);
        }
    }

    *str_op = temp;
}
