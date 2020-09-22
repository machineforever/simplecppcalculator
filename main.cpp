#include <bits/stdc++.h>
using namespace std;

int end_check(string y){
    vector<string>s = {"QUIT","quit","EXIT","exit","END","end"};
    for (int i = 0 ; i <= 5 ; i++) {
        if (y == (s[i])) {
            return 1;
        }
    }
    return 0;
}

size_t find_op( string y){
    vector<string>s = {"+","-","*","/"};
    for (int i = 0 ; i <= 3 ; i++) {
        size_t found = y.find(s[i]);
        if (found != string::npos)
            return found;
    }
    return 1;
}
int string_to_int( string s){
    int n = s.length();
    char char_array[n + 1];
    strcpy(char_array, s.c_str());
    n =  atoi(char_array);
    return n;
}

int l_value(string b){
    string r = b.substr(0,find_op(b));
    return string_to_int(r);
}
int r_value(string b){
    string r = b.substr(find_op(b)+1,b.length() - find_op(b));
    return string_to_int(r);
}

double op_operation(int lvalue, char op, int rvalue) {
    if (op == '+')
        return lvalue + rvalue;
    if (op == '-')
        return lvalue - rvalue;
    if (op == '*')
        return lvalue * rvalue;
    if (op == '/') {
        if (rvalue == 0)
            return 999999;
        return double(lvalue) / double(rvalue);
    }
    return 0;
}
vector<size_t> index_of_ops(string s){
    vector<size_t> index;
    int total = 0;
    if (end_check(s) == 1)
        return index;
    for (size_t i = 0; i <= s.length(); i++){
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
            index.push_back(i);
            ++total;
        }
    }

    return index;
}
vector <string> op_parser(string s) { // first parse ops, then calculate them seperately from left to the right then add them up ( should work somehow?)
    string r;
    int j = 0;
    vector<string> parsed;
    if (end_check(s) == 1){
        parsed.push_back("Goodbye!");
        return parsed;
    }
    vector<size_t> index = index_of_ops(s); //
    int z = index[0];
    for (int i = 0; i <= index.size(); i++) {
        parsed.push_back(s.substr(j,z));
        j += z;
        z = index[i+1] - index[i];

    }
    return parsed;
}
// substring
int main(){
    string s;
    cin >> s;
    vector <string> str = op_parser(s);
    int rvalue;
    long long int total = 0;
    int l_int;
    for (auto x: str) {
        if (x == "Goodbye!"){
            cout << "Goodybe!";
            return 0;
        }
        char ar[2];
        if (find_op(x) == 1){
             l_int = string_to_int(x);
        }
        else {
            ar[1] = x.at(0);
            rvalue = r_value(x);
          //  cout << l_int << ar[1] << rvalue << endl;
            l_int = op_operation(l_int,ar[1],rvalue);
        }

        total = l_int;
    }
    cout << total;

    }
