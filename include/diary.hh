//
// (c) 2024 S-Patriarch
//
#ifndef DIARY_HH
#define DIARY_HH

#ifndef PL_CONIO_HH
#include "pl/conio.hh"
#endif 
#ifndef PL_COLOR_HH
#include "pl/color.hh"
#endif
#ifndef PL_BAR_HH
#include "pl/bar.hh"
#endif

#include <list>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <sys/stat.h>
#include <array>
////////////////////////////////////////////////////////////////////////////////
namespace dr {
   class Diary final {
      std::string _f_diary = "/diary.log";
      std::string _f_shadow = "/shadow";
      std::string _f_rc = "/diaryrc";
      std::string _f_diary_path;
      std::string _delimiter {"##"}; // разделитель дней дневника
      std::string _today {}; // дата текущего дня
      std::fstream _fsd; // файловый поток дневника
      std::list<std::string> _buffer; // буффер записей дневника
      bool _day_flag {false}; // флаг записи дня
   public:
      Diary() 
      {
         const char* sh = "HOME";
         char* dir_home = std::getenv(sh);
         if (dir_home==nullptr) 
            _f_diary_path = "";
         else 
            _f_diary_path = std::string(dir_home)+"/.diary";
      }
      ~Diary() noexcept = default;
      void set_today();
      bool mode_check_files();      // режим проверки служебных файлов
      bool open_file_diary();       // открытие файла дневника
      std::string mode_help();      // режим помощи
      void mode_quit(std::string&); // режим выхода
      bool mode_authorization();    // режим авторизации пользователя
      void mode_input();            // режим ввода записей дневника
      void mode_viewing();          // режим просмотра записей дневника
      void set_password();          // установка пароля
   };
}
#endif // DIARY_HH

