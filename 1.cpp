#include <iostream>

using namespace std;

void getInfo(int mas[])
{
  int debt = 0;
  double average;
  for (int i = 0; i < 4; i++)
  {
    debt += 1 * (mas[i] < 3);
    average += mas[i] / 4.0;
  }
  
  cout << "Debt: " << debt << endl;
  cout << "Average: " << average << endl;
  if (average < 3 || debt)
  {
    cout << "No scholarship" << endl;
    return;
  }
  if (average < 5)
  {
    cout << "Base scholarship" << endl;
    return;
  }
  cout << "Elevated scholarship" << endl;
  return;
}

int main() {
  string name;
  int grades[4];
  
  cout << "Input student's name: ";
  cin >> name;
  
  cout << "Input 4 grades: ";
  for (int i = 0; i < 4; i++) {
      cin >> grades[i];
  }
  
  cout << "Student: " << name << endl;
  getInfo(grades);

  return 0;
}