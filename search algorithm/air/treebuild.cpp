#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;

vector<int> node[10];

vector<stack<int> > path;


int num=0;
int level=5;
int root=1;


stack<int> temp;
stack<int> sfsd;

void f3(){
    for(int i=0;i<sfsd.size();i++){
        cout<<sfsd.top()<<" ";sfsd.pop();

    }
    cout<<endl;
}

void f2(int u,int high)
{
    //cout<<u<<endl;
    //if(node[u].size()==0)return false;
    if(high==level){
        temp.push(u);
        
        path.push_back(temp);
        //sfsd=temp;
        //f3();
        temp.pop();
        return;
        //path[num].push(u);
        //num++;
        //return true;
    }
    //int flag=0;
    temp.push(u);
    for(int i=0;i<node[u].size();i++){
        int v=node[u][i];
        f2(v,high+1);
        //if(f2(v,high+1)){
            //path[num].push(u);
        //    flag=1;
        //}
    }
    temp.pop();
    //return flag;
}

void f1()
{
    temp.push(root);
    //cout<<temp.top()<<temp.size()<<endl;
    for(int i=0;i<node[root].size();i++){
        int u=node[root][i];
        f2(u,2);
        //cout<<temp.top()<<temp.size()<<endl;
        //if(f2(u,2)){
            //path[num].push(root);
        //}
    }
    temp.pop();
}


int main()
{
    //vector<int> temp;
    //temp.push_back(0);
    //temp.push_back(2);
    //temp.push_back(3);
    //node.push_back(temp);

    //temp.clear();
    //temp.push_back()
    node[1].push_back(2);
    node[1].push_back(3);
    node[2].push_back(4);
    node[2].push_back(5);
    node[5].push_back(6);
    node[5].push_back(7);
    node[5].push_back(8);
    node[7].push_back(9);
    node[8].push_back(10);
    node[8].push_back(11);
    //cout<<node[2].size();
    f1();
    //cout<<path.size();
    for(int i=0;i<path.size();i++){
        //cout<<path[i].size()<<' ';
        int num=path[i].size();
        for(int j=0;j<num;j++){
            
            cout<<path[i].top()<<' ';
            path[i].pop();
            //cout<<1<<endl;
        }
        //cout<<path[i].top()<<' ';
       //path[i].pop();
        //cout<<path[i].top()<<' ';
        //path[i].pop();
        //cout<<"df";
        cout<<endl;
    }
    system("pause");
}