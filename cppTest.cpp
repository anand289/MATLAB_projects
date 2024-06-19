#include <iostream>
#include <string>
using namespace std;

struct student {
  string name;
  int roll_no;
};

int add(int a, int b){
    return a+b;
}

int main() {

  student anand = {"anand",42};

  string my_name = anand.name;
  int my_roll = anand.roll_no;

  cout<<my_name<<"\n"<<my_roll<<"\n";


  string str = "AnandSingh in singapore";
  int count = 0;

  cout<<str[0]<<"\n";

  for(int i = 0;i<10;i++){
    if (str[i]=='n'){
      count = count + 1;
    }
  }

  cout << "This is Cpp!\n";

  int i = 0;

  for(i=0;i<10;i++){
    cout<<i ;
  }

  count = 0;
  cout<<"\n"<<add(7,8)<<"\n";

  for (int i=1; i < str.length() -1 ; i ++){
    if ((str[i]=='n')&&(str[i-1]=='i'))
      count += 1;
  }

  cout<<"Number of ISs are "<<count<<"\n";
  cout<<str.length();
}
