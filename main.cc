//
// (c) 2024 S-Patriarch
//
// Электронный дневник. Версия 1.0.0
// Данный проект реализуется под дивизом: "Слабоумие и Отвага".
//
#include "include/diary.hh"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
   std::vector<std::string> args(argv,argv+argc);

   dr::Diary dr;
   if (dr.open_file_diary()) {
      // ... режим авторизации пользователя
      // ...
      bool is = dr.mode_authorization();
      std::cout << is << '\n';
      /*
      for (;;) {
         std::string s = dr.mode_help();
         if (s=="q" || s=="!q" || s=="wq") {
            dr.mode_quit(s);
            break;
         }
      }*/
   }
   else std::cout << "E: Не могу открыть файл дневника.\n";
   return 0;
}

