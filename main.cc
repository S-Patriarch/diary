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
   if (!dr.mode_check_files()) 
      std::cout << "E: Сбой при проверке служебных файлов.\n";
   else {
      if (dr.mode_authorization()) {
         if (dr.open_file_diary()) {
            dr.mode_input(); // ---debug---
            std::string s = dr.mode_help();
            for (;;) {
               if (s=="h") s = dr.mode_help();
               if (s=="q" || s=="q!" || s=="wq") {
                  dr.mode_quit(s);
                  break;
               }
            }
         }
         else std::cout << "E: Не могу открыть файл дневника.\n";
      }
      else {
         std::string s {"q"};
         dr.mode_quit(s);
      }
   }
   return 0;
}

