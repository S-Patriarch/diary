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
            dr.set_today();
            std::string s {};
            s = dr.mode_help();
            for (;;) {
               if (std::strncmp("i",s.c_str(),1)==0) dr.mode_input();
               else if (std::strncmp("q",s.c_str(),1)==0   
                        || std::strncmp("q!",s.c_str(),2)==0  
                        || std::strncmp("wq",s.c_str(),2)==0) {
                  dr.mode_quit(s);
                  break;
               }
               s = dr.mode_help();
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

