//
// (c) 2024 S-Patriarch
//
#include <chrono>
#ifndef DIARY_HH
#include "../include/diary.hh"
#endif
#ifndef OTHER_HH
#include "../include/other.hh"
#endif
////////////////////////////////////////////////////////////////////////////////
namespace dr {
   bool Diary::open_file_diary() 
      // открытие или создание файла дневника
   {
      bool res {true};
      if (_f_diary_path!="") {
         const char* sp = _f_diary_path.c_str();
         mkdir(sp,0700);
         std::string file_path = _f_diary_path+_f_diary;
         _fsd.open(file_path, std::ios::in | std::ios::out | std::ios::app);       
         if (!_fsd.is_open()) res = false;
      }
      else res = false;
      return res;
   }     
   //---------------------------------------------------------------------------
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
   //---------------------------------------------------------------------------
   void Diary::mode_quit(std::string& s)
      // режим выхода из дневника
   {
      std::cout << pl::mr::crsh << pl::mr::clrscr;
      info_logo();
      std::cout << '\n';
      if (s=="wq") {
         std::cout << _buffer.size() << " строк записано\n";
      }
      std::cout << "До новых встреч...\n";
      std::this_thread::sleep_for(std::chrono::seconds{1}); 
      std::cout << pl::mr::clrscr << pl::mr::crss;
      if (_fsd.is_open()) _fsd.close();
   }
   //---------------------------------------------------------------------------
   bool Diary::mode_authorization()
      // режим авторизации пользователя
   {
      bool res {true};
      if (_f_diary_path!="") {
         pl::Conio con; 
         std::cout << pl::mr::clrscr;
         info_logo();
         std::cout << '\n';
         std::cout << "Пароль: ";
         std::string s_pass = con.get_hidden_input();
         std::string s_pass_hash = sha_256(s_pass);

         std::string file_path = _f_diary_path+_f_shadow;
         std::ifstream in;
         in.open(file_path);
         std::string line {};
         in >> line;
         in.close();
         std::cout << '\n'
                   << "s_pass_hash " << s_pass_hash << '\n'
                   << "line        " << line << '\n';
      }
      else res = false; 
      return res; 
   }
}

