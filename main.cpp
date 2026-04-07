#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

// Функция сжатия (базовый строковый RLE)
std::string encode_basic_rle(const std::string& text) {
    if (text.empty()) return "";
    
    std::string compressed = "";
    int count = 1;
    
    for (size_t i = 1; i < text.length(); ++i) {
        if (text[i] == text[i - 1]) {
            count++;
        } else {
            compressed += std::to_string(count) + text[i - 1];
            count = 1;
        }
    }
    // Добавляем последний блок
    compressed += std::to_string(count) + text.back();
    return compressed;
}

// Функция распаковки
std::string decode_basic_rle(const std::string& text) {
    std::string decoded = "";
    std::string count_str = "";
    
    for (char c : text) {
        if (std::isdigit(c)) {
            count_str += c;
        } else {
            if (!count_str.empty()) {
                int count = std::stoi(count_str);
                decoded.append(count, c); // Добавляем символ c нужное количество раз
                count_str = "";
            } else {
                decoded += c; // На случай непредвиденного формата
            }
        }
    }
    return decoded;
}

// Вспомогательная функция для чтения файла
std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Вспомогательная функция для записи файла
bool write_file(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::trunc); // trunc очищает файл перед записью
    if (!file.is_open()) {
        return false;
    }
    file << content;
    return true;
}

int main() {
    std::string choice;
    
    while (true) {
        std::cout << "\n--- RLE Архиватор (Перезапись файла на C++) ---\n";
        std::cout << "1. Encode (Сжать и перезаписать)\n";
        std::cout << "2. Decode (Распаковать и перезаписать)\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбери действие: ";
        std::cin >> choice;

        if (choice == "0") {
            break;
        } else if (choice == "1" || choice == "2") {
            std::string filename;
            std::cout << "Введи имя файла (например, input.txt): ";
            std::cin >> filename;

            std::string text = read_file(filename);
            if (text.empty()) {
                std::cout << "Ошибка: Файл " << filename << " не найден или пуст.\n";
                continue;
            }

            std::string result_text;
            std::string action;

            if (choice == "1") {
                result_text = encode_basic_rle(text);
                action = "Сжато";
            } else {
                result_text = decode_basic_rle(text);
                action = "Распаковано";
            }

            if (write_file(filename, result_text)) {
                std::cout << "Готово! Оригинал: " << text.length() 
                          << " симв. " << action << ": " << result_text.length() << " симв.\n";
                std::cout << "Файл " << filename << " перезаписан.\n";
            } else {
                std::cout << "Ошибка при записи в файл " << filename << ".\n";
            }
        } else {
            std::cout << "Неверный ввод.\n";
        }
    }

    return 0;
}
