#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

int main()
{
    ifstream fin("In.txt");
    ofstream fout("Out.txt");
    regex reg(R"(^(https?:\/\/)?([0-9a-z-]+\.)+([a-z]{2,6})(\/[\w \.-]+)*\/?(\?[\w_]+=[\w_]+(&[\w_]+=[\w_]+)*)?(#[\w_]*)?$)");
    string s;
    while (fin >> s)
        {
        if (regex_match(s, reg))
        {
            fout << s << endl;
        }
    }
    return 0;
}
