//
//  main.cpp
//  TestTrueConf
//
//  Created by Артем on 05.10.17.
//  Copyright © 2017 Артем. All rights reserved.
//
/*

TASK:

1.заполнить случайными числами от 1 до 9 значения контейнеров vector[i] и map[i];
2.удалить случайное число элементов (не более 15) в каждом контейнере;
3.после этого провести синхронизацию контейнеров, чтобы в vector и map остались
только имеющиеся в обоих контейнерах элементы (дубликаты не удалять).

 SOLUTION:
 
 1.void fill(vector<int>&, map<int,int>&);
 
 2.void erase(vector<int>&, map<int,int>&);
 
 3.void sync(vector<int>&, map<int,int>&);
 
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

const int ContainerSize = 20;

//Function prototypes
void fill(vector<int>&, map<int,int>&);
void erase(vector<int>&, map<int,int>&);
void sync(vector<int>&, map<int,int>&);

void show(vector<int>&, map<int,int>&);

void show(vector<int>&);

int get_second( pair<int, int> i ){ return i.second; }


int main(int argc, const char * argv[])
{
    srand((unsigned int) time(NULL));
    
    vector<int> vec1(ContainerSize);
    map<int,int> map1;
    
    fill(vec1,map1);
    
    cout<<"\nContainers with random numbers from 1 to 9"<<endl;
    show(vec1,map1);
    
    erase(vec1,map1);
    
    cout<<"\nContainers after erase"<<endl;
    show(vec1,map1);
    
    sync(vec1,map1);
    
    cout<<"\nContainers after synchronizing"<<endl;
    show(vec1,map1);
    
    return 0;
}

void fill(vector<int>& vec1, map<int,int>& map1)
{
    //Fill vector&map with random numbers 1 to 9
    for (int i = 0;i < ContainerSize;i++)
    {
        vec1[i]=rand()%9+1;
        map1[i]=rand()%9+1;
    }
    
}
void erase(vector<int>& vec1, map<int,int>& map1)
{
    //Erase vector by random number of elements <=15
    
    int temp = rand()%15+1;
    cout<<"\nRandom number:"<<temp<<endl;
    vec1.erase(vec1.begin(),vec1.begin()+temp);
    
    
    //Erase map by random number of elements <=15
    do
    {
        map1.erase(map1.begin());
        temp--;
    }
    while(temp!=0);
    
}
void sync(vector<int>& containerFirst, map<int,int>& containerSecond)
{
    //Sync containers
    
    vector<int> tempVec(containerFirst);
    
    sort(tempVec.begin(), tempVec.end());
    
    vector<int> mapTransform(containerSecond.size());
    
    transform( containerSecond.begin(), containerSecond.end(), mapTransform.begin(), get_second );
    
    sort( mapTransform.begin(), mapTransform.end() );
    
    cout<<"\nSorted map:";
    show(mapTransform);
    
    vector<int> intersectionElements;
    
    set_intersection(tempVec.begin(), tempVec.end(), mapTransform.begin(), mapTransform.end(), back_inserter(intersectionElements));
    
    
    cout << "\nIntersection elements: ";
    show(intersectionElements);
    
    auto predVector =
    [&](int value) -> bool {
        for (auto &i : intersectionElements) { if (value == i) { return false; }}
        return true;
    };
    
    containerFirst.erase(
                         remove_if(containerFirst.begin(), containerFirst.end(), predVector),
                         containerFirst.end());
    
    auto predMap =
    [&](map<int, int>::value_type valueType) -> bool {
        for (auto &i : intersectionElements) { if (i == valueType.second) { return false; }}
        return true;
    };
    
    auto it = containerSecond.begin();
    while ((it = find_if(it, containerSecond.end(), predMap)) != containerSecond.end()) {
        containerSecond.erase(it++);
    }
    
}
void show(vector<int>& vec1,map<int,int>& map1)
{
    //Print vector
    cout<<"Vector:";
    for (int val : vec1)
        cout << val << ' ';
    cout<< '\n';
    //Print map
    cout<<"Map:"<<endl;
    for(map<int,int>::iterator iter=map1.begin();iter != map1.end();iter++)
        cout<< (*iter).first<< ' '<<(*iter).second<<'\n';
}
void show(vector<int>& vec1)
{
    //Print vector
    cout<<"Vector:";
    for (int val : vec1)
        cout << val << ' ';
    cout<< '\n';
}


