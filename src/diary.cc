//
// (c) 2024 S-Patriarch
//
#ifndef DIARY_HH
#include "../include/diary.hh"
#endif
#ifndef OTHER_HH
#include "../include/other.hh"
#endif
//------------------------------------------------------------------------------
namespace dr {
   std::string Diary::mode_help()
      // вызов информации об управляющих командах дневника
      // возвращает введенную командную строку
   {
      std::cout << pl::mr::clrscr;
      info_logo();
      std::cout << '\n';
      std::cout << "h   вызов информации об управляющих конандах\n"
                << "q   выход из дневника\n"
                << "!q  выход без записи изменений\n"
                << "wq  выход с записью изменений\n"
                << "i   режим ввода записей дневника\n"
                << "w   запись введенной информации\n"
                << "dd  удаление последней введенной строки информации\n"
                << "v   режим просмотра записей дневника\n";
      std::cout << "\n:";
      std::string scom {};
      std::cin >> scom;
      return scom;
   }
}

