#include<iostream>
using namespace std;
int main(){
    int n, j=0, count =0;
    int a[100], b[200];

    cout<<"Enter frame length:";
    cin>>n;

    cout<<"Enter the frame:";
    for(int i=0; i<n; i++){
        cin>>a[i];
    }

    for(int i=0; i<n; i++){
        b[j] = a[i];
    
    if(a[i]==1 )
        count++;
    else
        count=0;
    if(count==5){
        j++;
        b[j]=0;
        count=0;
    }

    j++;
    }
    cout<<"Frame after bit stuffing:";
    for(int i=0;i<j;i++){
        cout<<b[i];
    }

    return 0;
}