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

#include <openssl/sha.h>
#include <list>
//------------------------------------------------------------------------------
namespace dr {
   class Diary final {
      const char* _fshadow = "~/.diary/.shadow";
      const char* _fdiary = "~/.diary/diary.log";
      const char* _frc = "~/.diary/diaryrc";
      std::list<std::string> _buffer; // буффер записей дневника
      void buffer_write();  // пишет буффер записей дневника в файл
      void buffer_delete(); // удаляет последнию введенную строку буффера
   public:
      Diary() {}
      ~Diary() noexcept {}
      std::string mode_help();   // режим помощи
      void mode_check();         // режим проверки служебных файлов
      void mode_authorization(); // режим авторизации пользователя
      void mode_viewing();       // режим просмотра записей дневника
      void mode_input();         // режим ввода записей дневника
      void mode_quit();          // режим выхода
   };
}
#endif // DIARY_HH

