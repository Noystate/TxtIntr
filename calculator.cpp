#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <locale>
#include <codecvt>

using namespace std;

// Константы для физических расчетов
const double G = 9.81;  // Ускорение свободного падения (м/с²)
const double PI = 3.14159265358979323846;  // Число Пи

// Функция для настройки русской локали
void setRussianLocale() {
    try {
        // Пробуем установить русскую локаль для Windows
        setlocale(LC_ALL, "ru_RU.UTF-8");
    } catch (...) {
        try {
            // Для Linux/Unix систем
            setlocale(LC_ALL, "ru_RU.utf8");
        } catch (...) {
            // Резервный вариант
            setlocale(LC_ALL, "");
        }
    }
}

/**
 * @brief Вычисляет максимальную высоту подъема тела, брошенного под углом к горизонту
 * @param angle_deg Угол броска в градусах
 * @param initial_velocity Начальная скорость (м/с)
 * @return Высота подъема в метрах
 */
double calculate_height(double angle_deg, double initial_velocity) {
    // Преобразуем угол из градусов в радианы
    double angle_rad = angle_deg * PI / 180.0;
    
    // Вычисляем вертикальную составляющую скорости
    double vertical_velocity = initial_velocity * sin(angle_rad);
    
    // Формула для максимальной высоты: H = (V_верт²) / (2 * g)
    return (vertical_velocity * vertical_velocity) / (2 * G);
}

/**
 * @brief Вычисляет дальность полета тела
 * @param angle_deg Угол броска в градусах
 * @param initial_velocity Начальная скорость (м/с)
 * @return Дальность полета в метрах
 */
double calculate_range(double angle_deg, double initial_velocity) {
    // Преобразуем угол из градусов в радианы
    double angle_rad = angle_deg * PI / 180.0;
    
    // Формула для дальности полета: L = (V₀² * sin(2α)) / g
    return (initial_velocity * initial_velocity * sin(2 * angle_rad)) / G;
}

/**
 * @brief Вычисляет полное время полета тела
 * @param angle_deg Угол броска в градусах
 * @param initial_velocity Начальная скорость (м/с)
 * @return Время полета в секундах
 */
double calculate_time(double angle_deg, double initial_velocity) {
    // Преобразуем угол из градусов в радианы
    double angle_rad = angle_deg * PI / 180.0;
    
    // Вычисляем вертикальную составляющую скорости
    double vertical_velocity = initial_velocity * sin(angle_rad);
    
    // Формула для времени полета: T = (2 * V_верт) / g
    return (2 * vertical_velocity) / G;
}

/**
 * @brief Выводит справочную информацию о программе на русском языке
 */
void print_help() {
    cout << "           ГЕОМЕТРИЧЕСКИЙ КАЛЬКУЛЯТОР (Вариант 15)\n";
    cout << "    Вычисление параметров движения тела под углом к горизонту\n";
    
    cout << "НАЗНАЧЕНИЕ:\n";
    cout << "  Программа рассчитывает параметры движения тела,\n";
    cout << "  брошенного под углом к горизонту с заданной начальной скоростью\n\n";
    
    cout << "СИНТАКСИС ИСПОЛЬЗОВАНИЯ:\n";
    cout << "  calculator -o <операция> <угол> <скорость>\n";
    cout << "  calculator --operation <операция> <угол> <скорость>\n\n";
    
    cout << "ДОСТУПНЫЕ ОПЕРАЦИИ:\n";
    cout << "  высота  - вычисление максимальной высоты подъема тела\n";
    cout << "  дальность - вычисление горизонтальной дальности полета\n";
    cout << "  время   - вычисление общего времени полета\n\n";
    
    cout << "ПАРАМЕТРЫ:\n";
    cout << "  <угол>     - угол броска к горизонту в градусах (0-90)\n";
    cout << "  <скорость> - начальная скорость тела в м/с\n\n";
    
    cout << "ПРИМЕРЫ ИСПОЛЬЗОВАНИЯ:\n";
    cout << "  calculator -o высота 45 20.0     # Высота для угла 45° и скорости 20 м/с\n";
    cout << "  calculator --operation дальность 30 15.5  # Дальность для угла 30° и скорости 15.5 м/с\n";
    cout << "  calculator -o время 60 25.0       # Время полета для угла 60° и скорости 25 м/с\n\n";
    
    cout << "СПРАВКА:\n";
    cout << "  calculator -h или calculator --help  - вывод этой справки\n";
    cout << "  calculator (без параметров)          - вывод справки\n\n";
    
    cout << "ФИЗИЧЕСКИЕ ФОРМУЛЫ:\n";
    cout << "  Высота:    H = (V₀² * sin²(α)) / (2g)\n";
    cout << "  Дальность: L = (V₀² * sin(2α)) / g\n";
    cout << "  Время:     T = (2 * V₀ * sin(α)) / g\n";
}

/**
 * @brief Проверяет корректность количества аргументов
 * @param expected Ожидаемое количество аргументов
 * @param actual Фактическое количество аргументов
 * @param operation_name Название операции для сообщения об ошибке
 * @return true если количество аргументов корректно, false в противном случае
 */
bool validate_arguments(int expected, int actual, const string& operation_name) {
    if (actual != expected) {
        cerr << "ОШИБКА: Операция '" << operation_name << "' требует " << expected 
             << " аргумента(ов), но получено " << actual << "\n";
        return false;
    }
    return true;
}

/**
 * @brief Проверяет физическую корректность входных данных
 * @param angle Угол броска в градусах
 * @param velocity Начальная скорость в м/с
 * @return true если данные корректны, false в противном случае
 */
bool validate_physics(double angle, double velocity) {
    bool valid = true;
    
    // Проверяем корректность угла (должен быть между 0 и 90 градусами)
    if (angle < 0 || angle > 90) {
        cerr << "ПРЕДУПРЕЖДЕНИЕ: Угол " << angle << "° выходит за рекомендуемые пределы (0-90°)\n";
    }
    
    // Проверяем корректность скорости (должна быть положительной)
    if (velocity <= 0) {
        cerr << "ОШИБКА: Скорость должна быть положительным числом\n";
        valid = false;
    }
    
    return valid;
}

/**
 * @brief Преобразует английское название операции в русское для вывода
 * @param operation Английское название операции
 * @return Русское название операции
 */
string get_russian_operation_name(const string& operation) {
    if (operation == "высота") return "вычисление высоты подъема";
    if (operation == "дальность") return "вычисление дальности полета";
    if (operation == "время") return "вычисление времени полета";
    return operation;
}

/**
 * @brief Главная функция программы
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return Код завершения программы (0 - успех, 1 - ошибка)
 */
int main(int argc, char* argv[]) {
    // Устанавливаем русскую локаль
    setRussianLocale();
    
    // Если программа запущена без параметров, выводим справку
    if (argc == 1) {
        print_help();
        return 0;
    }

    // Переменные для хранения параметров командной строки
    string operation;          // Название операции (высота, дальность, время)
    vector<double> operands;   // Числовые аргументы (угол, скорость)

    for (int i = 1; i < argc; i++) {
        string current_arg = argv[i];  // Текущий аргумент
        
        // Обработка именованных параметров
        if (current_arg == "-o" || current_arg == "--operation") {
            // Следующий аргумент после -o/--operation должен быть названием операции
            if (i + 1 < argc) {
                operation = argv[++i];  // Получаем название операции
            } else {
                cerr << "ОШИБКА: После параметра " << current_arg << " должно следовать название операции\n";
                return 1;
            }
        }
        // Обработка запроса справки
        else if (current_arg == "-h" || current_arg == "--help") {
            print_help();
            return 0;
        }
        // Обработка числовых аргументов
        else {
            try {
                // Пытаемся преобразовать аргумент в число
                double numeric_value = stod(current_arg);
                operands.push_back(numeric_value);
            } catch (const exception& e) {
                // Обработка ошибки преобразования строки в число
                cerr << "ОШИБКА: Неверный формат числового аргумента: '" << current_arg << "'\n";
                cerr << "        Аргумент должен быть числом (например: 45.5 или 30)\n";
                return 1;
            }
        }
    }
 
    // Проверяем, что операция была указана
    if (operation.empty()) {
        cerr << "ОШИБКА: Не указана операция для выполнения\n";
        cerr << "Используйте параметр -o или --operation для указания операции\n\n";
        print_help();
        return 1;
    }
    
    // Проверяем количество числовых аргументов
    if (!validate_arguments(2, operands.size(), operation)) {
        cerr << "\nПравильный формат: calculator -o " << operation << " <угол> <скорость>\n";
        return 1;
    }
    
    // Извлекаем числовые параметры
    double angle = operands[0];     // Угол броска в градусах
    double velocity = operands[1];  // Начальная скорость в м/с
    
    // Проверяем физическую корректность параметров
    if (!validate_physics(angle, velocity)) {
        return 1;
    }

    // Устанавливаем формат вывода чисел (3 знака после запятой)
    cout << fixed << setprecision(3);
    
    // Получаем русское название операции для вывода
    string russian_operation = get_russian_operation_name(operation);
    
    // Выполняем запрошенную операцию
    if (operation == "высота") {
        // Вычисление высоты подъема
        double result = calculate_height(angle, velocity);
        cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЙ:\n";
        cout << "Операция:    " << russian_operation << "\n";
        cout << "Угол броска: " << angle << "°\n";
        cout << "Скорость:    " << velocity << " м/с\n";
        cout << "Высота:      " << result << " м\n";
        
    } else if (operation == "дальность") {
        // Вычисление дальности полета
        double result = calculate_range(angle, velocity);
        cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЙ:\n";
        cout << "Операция:    " << russian_operation << "\n";
        cout << "Угол броска: " << angle << "°\n";
        cout << "Скорость:    " << velocity << " м/с\n";
        cout << "Дальность:   " << result << " м\n";
        
    } else if (operation == "время") {
        // Вычисление времени полета
        double result = calculate_time(angle, velocity);
        cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЙ:\n";
        cout << "Операция:    " << russian_operation << "\n";
        cout << "Угол броска: " << angle << "°\n";
        cout << "Скорость:    " << velocity << " м/с\n";
        cout << "Время:       " << result << " с\n";
        
    } else {
        // Обработка неизвестной операции
        cerr << "ОШИБКА: Неизвестная операция: '" << operation << "'\n";
        cerr << "Доступные операции: высота, дальность, время\n\n";
        print_help();
        return 1;
    }
    return 0;
}
