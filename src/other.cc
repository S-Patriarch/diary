//
// (c) 2024 S-Patriarch
//
#ifndef OTHER_HH
#include "../include/other.hh"
#endif
////////////////////////////////////////////////////////////////////////////////
namespace dr {
   void info_logo()
      // выводит информационный логотип дневника
   {
      std::cout << "Электронный дневник. Версия 1.0.0\n"
                << "(c) 2024 S-Patriarch\n"; 
   }
   //---------------------------------------------------------------------------
   std::string sha_256(const std::string& s)
   {
      unsigned char hash_[SHA256_DIGEST_LENGTH];
      SHA256_CTX sha256;
      SHA256_Init(&sha256);
      SHA256_Update(&sha256,s.c_str(),s.size());
      SHA256_Final(hash_,&sha256);
      std::stringstream ss;
      for (int i=0; i<SHA256_DIGEST_LENGTH; ++i) 
         ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash_[i];
      return ss.str();
   }
   //---------------------------------------------------------------------------
   std::string get_date()
      // получает текущую дату и возвращает ее в виде строки
   {
      std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
      std::time_t t = std::chrono::system_clock::to_time_t(today);
      std::stringstream ss;
      ss << std::put_time(std::localtime(&t),"%d-%m-%Y");
      std::string res = ss.str();
      return res;
   }
   //---------------------------------------------------------------------------
   std::string get_time()
      // получает текущее время и возвращает его в виде строки
   {
      // получаем текущее время
      std::time_t now = std::time(nullptr);
      // преобразуем текущее время в локальное время
      std::tm* local_time = std::localtime(&now);
      // форматируем локальное время в строку
      char buffer[9];
      std::strftime(buffer,sizeof(buffer),"%H:%M:%S",local_time);
      // преобразуем buffer в std::string
      std::string res(buffer);
      return res;
   }
}

