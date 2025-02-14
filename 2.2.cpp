#include <iostream>
#include <fstream>

using namespace std;

int getAnswer()
{
  ifstream answer("answer.txt");
  int debt;
  answer >> debt;
  if (debt == -1)
    {
      cout << "No answer";
      return -1;
    }
  double min;
  answer >> min;
  cout << "Debt: " << debt << endl;
  cout << "min: " << min << endl;
  answer.close();
  ofstream answer2("answer.txt");
  int temp = -1;
  answer2 << temp;
  if (min < 3)
  {
    cout << "No scholarship" << endl;
    return 0;
  }
  if (min < 5)
  {
    cout << "Base scholarship" << endl;
    return 0;
  }
  cout << "Elevated scholarship" << endl;

  return 0;
}

int main() {
  if (getAnswer() == -1)
  {
    return 0;
  }
  ofstream output("request.txt");
  if (!output.is_open())
  {
    cout << "File not opened" << endl;
    return -1;
  }
  string name;
  
  cout << "Input student's name: ";
  cin >> name;
  output << name << "\t";
  
  cout << "Input 4 grades: ";
  for (int i = 0; i < 4; i++) 
  {
    int grade;
    cin >> grade;
    output << grade << "\t";
  }

  output << endl;
  output.close();
  
  getAnswer();
  return 0;
}