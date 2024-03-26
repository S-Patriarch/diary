//
// (c) 2024 S-Patriarch
//
#ifndef OTHER_HH
#define OTHER_HH

#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <iomanip>
#include <chrono>
#include <vector>
////////////////////////////////////////////////////////////////////////////////
namespace dr {
   void info_logo(); // выводит информационный логотип дневника
   std::string sha_256(const std::string&);
   std::string get_date(); // получает текущую дату
   std::string get_time(); // получает текущее время
   std::string encrypt(std::string); // шифрование строки
   std::string decrypt(std::string); // расшифровка шифрстроки
}
#endif // OTHER_HH

