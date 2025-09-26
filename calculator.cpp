#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const double G = 9.81;
const double PI = 3.14159265358979323846;

// Функция вычисления высоты подъема
double calculate_height(double angle_deg, double initial_velocity) {
    double angle_rad = angle_deg * PI / 180.0;
    double vertical_velocity = initial_velocity * sin(angle_rad);
    return (vertical_velocity * vertical_velocity) / (2 * G);
}

// Функция вычисления дальности полета
double calculate_range(double angle_deg, double initial_velocity) {
    double angle_rad = angle_deg * PI / 180.0;
    return (initial_velocity * initial_velocity * sin(2 * angle_rad)) / G;
}

// Функция вычисления времени полета
double calculate_time(double angle_deg, double initial_velocity) {
    double angle_rad = angle_deg * PI / 180.0;
    double vertical_velocity = initial_velocity * sin(angle_rad);
    return (2 * vertical_velocity) / G;
}

void print_help() {
    cout << "Геометрический калькулятор - вычисление параметров движения тела\n";
    cout << "===============================================================\n\n";
    cout << "Использование:\n";
    cout << "  calculator -o <операция> <операнд1> <операнд2>\n";
    cout << "  calculator --operation <операция> <операнд1> <операнд2>\n\n";
    cout << "Доступные операции:\n";
    cout << "  height  - вычисление высоты подъема (угол, начальная скорость)\n";
    cout << "  range   - вычисление дальности полета (угол, начальная скорость)\n";
    cout << "  time    - вычисление времени полета (угол, начальная скорость)\n\n";
    cout << "Примеры:\n";
    cout << "  calculator -o height 45 20.0\n";
    cout << "  calculator --operation range 30 15.5\n";
    cout << "  calculator -o time 60 25.0\n\n";
    cout << "Единицы измерения:\n";
    cout << "  угол - градусы, скорость - м/с, результат - метры/секунды\n";
}

int main(int argc, char* argv[]) {
    // Если нет аргументов, выводим справку
    if (argc == 1) {
        print_help();
        return 0;
    }

    string operation;
    vector<double> operands;

    // Парсинг аргументов командной строки
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        
        if (arg == "-o" || arg == "--operation") {
            if (i + 1 < argc) {
                operation = argv[++i];
            } else {
                cerr << "Ошибка: после " << arg << " должно следовать название операции\n";
                return 1;
            }
        } else if (arg == "-h" || arg == "--help") {
            print_help();
            return 0;
        } else {
            // Пробуем преобразовать в число
            try {
                double value = stod(arg);
                operands.push_back(value);
            } catch (const exception& e) {
                cerr << "Ошибка: неверный формат числа: " << arg << "\n";
                return 1;
            }
        }
    }

    // Проверяем, что операция указана
    if (operation.empty()) {
        cerr << "Ошибка: не указана операция. Используйте -o или --operation\n";
        print_help();
        return 1;
    }

    // Проверяем количество операндов
    if (operands.size() != 2) {
        cerr << "Ошибка: требуется 2 числовых аргумента. Получено: " << operands.size() << "\n";
        return 1;
    }

    double angle = operands[0];
    double velocity = operands[1];

    // Выполняем операцию
    cout << fixed << setprecision(3);
    
    if (operation == "height") {
        double result = calculate_height(angle, velocity);
        cout << "Высота подъема: " << result << " м\n";
        
    } else if (operation == "range") {
        double result = calculate_range(angle, velocity);
        cout << "Дальность полета: " << result << " м\n";
        
    } else if (operation == "time") {
        double result = calculate_time(angle, velocity);
        cout << "Время полета: " << result << " с\n";
        
    } else {
        cerr << "Ошибка: неизвестная операция: " << operation << "\n";
        cerr << "Доступные операции: height, range, time\n";
        return 1;
    }

    return 0;
}
