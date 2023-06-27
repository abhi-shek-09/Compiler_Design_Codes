#include<iostream>
using namespace std;

//Remove comments
int main(){
    string st;
    getline(cin, st);
    int start = -1;
    int end = -1;
    for(int i =0; i<st.length(); i++){
        if(st[i] == '/' && st[i+1] == '*'){
            start = i;
        }

        if(st[i] == '*' && st[i+1] == '/'){
            end = i;
        }
    }

    if(start>=0 && end>=0){
        cout<<"It is a comment";
    }
    else{
        cout<<"It is not a comment";
    }
}