#include"Executive.cpp"
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

int main()
{

  menu RunningBack; //initial the Executive object
  string fil = "running-back-data.txt";
  RunningBack.setfilepath( fil );
  RunningBack.readfile();
  //cout<<RunningBack.records.size()<<endl;
  RunningBack.run(); //
  return(0);
}
