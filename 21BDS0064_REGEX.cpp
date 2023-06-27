#include<bits/stdc++.h>
using namespace std;

bool regex1(string s){
    string s1(s);
    if (s1 == "a") {
        return true;
    }
    return false;
}

bool checkForChange(const char* s,int i, int n){
    for(int j=i; j<n; j++){
        if(s[j] == 'a'){
            return false;
        }
    }
    return true;
}
bool regex2(string s1){
    const char* s = s1.c_str();
    int n = sizeof(s)/sizeof(s[0]);
    bool flag = false;

    int breakArr = -1;
    if(s[0] == 'b'){
        return checkForChange(s, 0, n);
    }
    int i;
    for(i=0; i<n; i++){
        if(s[i] == 'b'){
            flag = true;
            break;
        }
    }
    if(flag==false){
        return flag;
    }
    return checkForChange(s, i, n);
}


bool regex3(string s){
    string s1(s);
    if (s1 == "abb") {
        return true;
    }
    return false;
}

int main(){
    ifstream myfile;
    myfile.open("regex_test.txt");
    string myline;
    if ( myfile.is_open() ) {
        while ( myfile ) { 
            getline (myfile, myline);
            cout<<myline<<" is:";
            if(regex1(myline) == 1){
                cout<<"Accepted by regex 'a' "<<endl;
            }

            else if(regex2(myline) == 1){
                cout<<"Accepted by regex 'a*b+' "<<endl;
            }

            else if(regex3(myline) == 1){
                cout<<"Accepted by regex 'abb' "<<endl;
            }

            else if(regex1(myline) == 0 && regex2(myline) == 0 && regex3(myline) == 0){
                cout<<"Not accepted by any of the expressions"<<endl;
            }
            cout<<endl<<endl;
        }
    }
    else {
        cout << "Couldn't open file\n";
    }
    return 0;
}
