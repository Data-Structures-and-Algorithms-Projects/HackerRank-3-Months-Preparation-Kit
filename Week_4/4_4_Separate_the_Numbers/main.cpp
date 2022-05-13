#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'separateNumbers' function below.
 *
 * The function accepts STRING s as parameter.
 */

bool checkNext(const string &s, const string &val)
{
    if (s.size() >= val.size() && (s[0] != '0') && val == s.substr(0, val.size()))
    {
        return checkNext(s.substr(val.size()),
                         to_string(stoll(val) + 1UL));
    }
    return s.empty();
}

void separateNumbers(string s)
{
    for (int i = 0; i < s.size() / 2; ++i)
    {
        string val = s.substr(0, i + 1);
        if (checkNext(s.substr(val.size()),
                      to_string(stoll(val) + 1UL)))
        {
            cout << "YES " << val << endl;
            return;
        }
    }

    cout << "NO" << endl;
    return;
}

int main()
{
    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++)
    {
        string s;
        getline(cin, s);

        separateNumbers(s);
    }

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}
