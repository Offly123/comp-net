#include <iostream>
#include <fstream>

using namespace std;

void getInfo(int mas[])
{
  int debt = 0;
  double min = 5;
  for (int i = 0; i < 4; i++)
  {
    debt += (mas[i] < 3);
    if (min > mas[i])
      min = mas[i];
  }
  ofstream answer("answer.txt");
  answer << debt << "\t" << min;
  answer.seekp(0);
}

int main() {
  ifstream request("request.txt");
  int grades[4];
  string name;

  request >> name;
  for (int i = 0; i < 4; i++) {
    request >> grades[i];
  }
  
  request.close();
  getInfo(grades);
  
  return 0;
}