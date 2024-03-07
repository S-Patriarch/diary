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
////////////////////////////////////////////////////////////////////////////////
namespace dr {
   void info_logo(); // выводит информационный логотип дневника
   std::string sha_256(const std::string&);
   std::string get_date(); // получает текущую дату
   std::string get_time(); // получает текущее время
}
#endif // OTHER_HH

