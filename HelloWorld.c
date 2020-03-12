#include <iostream>
using namespace std;

class AAA
{
private:
  int num1;
public:
  AAA(int num1 = 0) : num1(num1) {}
  AAA operator+ (AAA& ref)
  {
    AAA num(num1 + ref.num1);
    return num;
  }
}

class BBB : public AAA
{
private:
  int num2;
public:
  BBB(int num1 = 0, int num2 = 0) : AAA(num1), num2(num2) {}
  BB

int main(void)
{
  cout<<"Hello world!"<<endl;
  return 0;
}
