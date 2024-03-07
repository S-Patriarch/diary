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
   bool Diary::mode_check_files()
      // режим проверки служебных файлов
      // если какого-то файла не оказывается, то он создается
   {
      if (_f_diary_path!="") {
         const char* ps = _f_diary_path.c_str();
         mkdir(ps,0700);

         std::array<std::string,3> arr;
         arr[0] = _f_diary_path+_f_diary;
         arr[1] = _f_diary_path+_f_shadow;
         arr[2] = _f_diary_path+_f_rc;

         std::fstream fs;        
         for (const auto& s : arr) {
            fs.open(s, std::ios::in | std::ios::out | std::ios::app);       
            if (!fs.is_open()) return false;
            fs.close();
         }
      }
      return true;
   }
   //---------------------------------------------------------------------------
   bool Diary::open_file_diary() 
      // открытие файла дневника
   {
      std::string file_path = _f_diary_path+_f_diary;
      _fsd.open(file_path, std::ios::in | std::ios::out | std::ios::app);       
      if (!_fsd.is_open()) return false;
      return true;
   }     
   //---------------------------------------------------------------------------
   std::string Diary::mode_help()
      // вызов информации об управляющих командах дневника
      // возвращает введенную командную строку
   {
      std::cout << pl::mr::clrscr;
      info_logo();
      std::cout << '\n'
                << "Основные команды:\n";
      std::cout << "  h  - вызов информации об управляющих конандах\n"
                << "  q  - выход из дневника\n"
                << "  !q - выход без записи изменений\n"
                << "  wq - выход с записью изменений\n"
                << "  i  - режим ввода записей дневника\n"
                << "  w  - запись введенной информации\n"
                << "  dd - удаление последней введенной строки информации\n"
                << "  v  - режим просмотра записей дневника\n";
      std::cout << '\n'
                << "Настройки:\n";
      std::cout << "  set password - установка пароля\n";
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
      bool res {false};
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
         res = true;
      }
      return res; 
   }
   //---------------------------------------------------------------------------
   bool Diary::mode_input()
      // режим ввода записей дневника
   {
      bool res {false};
      if (_f_diary_path!="") {
         std::cout << pl::mr::clrscr;
         info_logo();

         res = true;
      }
      return res; 
   }
   //---------------------------------------------------------------------------
   bool Diary::mode_viewing()
      // режим просмотра записей дневника
   {
      bool res {false};
      if (_f_diary_path!="") {
         std::cout << pl::mr::clrscr;
         info_logo();

         res = true;
      }
      return res; 
   }
}

