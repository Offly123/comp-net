#include <iostream>
#include <string>

using namespace std;

int main() {
    string surname;
    int grades[4];
    int debt_count = 0;
    double average = 0.0;
    
    cout << "Введите фамилию студента: ";
    cin >> surname;
    
    cout << "Введите 4 оценки за сессию: ";
    for (int i = 0; i < 4; i++) {
        cin >> grades[i];
        if (grades[i] < 3) {
            debt_count++;
        }
        average += grades[i];
    }
    
    average /= 4;
    
    cout << "Студент " << surname << "\n";
    cout << "Количество задолженностей: " << debt_count << "\n";
    
    if (debt_count > 0) {
        cout << "Стипендия не выплачивается.\n";
    } else if (average == 5) {
        cout << "Повышенная стипендия.\n";
    } else if (average >= 4) {
        cout << "Обычная стипендия.\n";
    } else {
        cout << "Стипендия не выплачивается.\n";
    }
    
    return 0;
}