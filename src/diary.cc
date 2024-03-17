//
// (c) 2024 S-Patriarch
//
#include <chrono>
#include <pl/color.hh>
#ifndef DIARY_HH
#include "../include/diary.hh"
#endif
#ifndef OTHER_HH
#include "../include/other.hh"
#endif
////////////////////////////////////////////////////////////////////////////////
namespace dr {
   void Diary::set_today() {_today = get_date();}
   //---------------------------------------------------------------------------
   int Diary::get_size_buffer()
      // возвращает размер текущего буффера в байтах
   {
      int res {};
      std::string s {};
      for (const auto& lst : _buffer) {
         s = lst;
         res += s.size();
      }
      return res;
   }
   //---------------------------------------------------------------------------
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
   bool Diary::mode_authorization()
      // режим авторизации пользователя
   {
      bool res {false};
      
      pl::Conio con; 
      std::cout << pl::mr::clrscr;
      info_logo();
      std::cout << '\n';

      // открываем файл .shadow
      std::string file_path = _f_diary_path+_f_shadow;
      std::fstream file;
      file.open(file_path,std::ios::in | std::ios::out);
      // перемещаем указатель чтения в конец файла
      file.seekg(0,std::ios::end);
      // проверяем размер файла
      if (file.tellg()==0) {
         // файл пуст
         // проходим процедуру регисрации
         std::cout << "Процедура регистрации...\n";
         std::cout << "\nНовый пароль: ";
         std::string new_pass1 = con.get_hidden_input();
         std::cout << "\nПодтверждение пароля: ";
         std::string new_pass2 = con.get_hidden_input();
         if (new_pass1==new_pass2) {
            std::string new_pass_hash = sha_256(new_pass1);
            file.seekg(0,std::ios::beg);
            file << new_pass_hash;
            res = true;
         }
         else {
            std::cout << pl::mr::crsh;
            std::cout << "\n\nE: Сбой при проверке подтверждения пароля.\n";
            std::this_thread::sleep_for(std::chrono::seconds{3}); 
         }
      }
      else {
         // файл содержит данные
         std::cout << "Пароль: ";
         std::string s_pass = con.get_hidden_input();
         std::string s_pass_hash = sha_256(s_pass);
         std::string line {};
         // перемещаем указатель чтения в начало файла
         file.seekg(0,std::ios::beg);
         file >> line;
         if (s_pass_hash==line) res = true;
         else {
            std::cout << pl::mr::crsh;
            std::cout << "\n\nE: Сбой при проверке подлинности пароля.\n";
            std::this_thread::sleep_for(std::chrono::seconds{3}); 
         }
      }
      std::cout << pl::mr::crss;
      file.close();
      return res; 
   }
   //---------------------------------------------------------------------------
   void Diary::set_password()
      // установка (замена) пароля пользователя дневника
   {
      pl::Conio con; 
      std::cout << pl::mr::clrscr;
      info_logo();
      std::cout << '\n';
      std::cout << "Процедура установки пароля...\n";
      std::cout << "\nНовый пароль: ";
      std::string new_pass1 = con.get_hidden_input();
      std::cout << "\nПодтверждение пароля: ";
      std::string new_pass2 = con.get_hidden_input();

      if (new_pass1==new_pass2) {
         std::string new_pass_hash = sha_256(new_pass1);
         std::string file_path = _f_diary_path+_f_shadow;
         std::fstream file;
         file.open(file_path,std::ios::out);
         file << new_pass_hash;
         file.close();
      }
      else {
         std::cout << pl::mr::crsh;
         std::cout << "\n\nE: Сбой при проверке подтверждения пароля.\n";
         std::this_thread::sleep_for(std::chrono::seconds{3}); 
         std::cout << pl::mr::crss;
      }
   }
   //---------------------------------------------------------------------------
   std::string Diary::mode_help()
      // вызов информации об управляющих командах дневника
      // возвращает введенную командную строку
   {
      pl::Conio con;
      std::cout << pl::mr::clrscr;
      info_logo();
      std::cout << '\n'
                << "Основные команды:\n";
      std::cout << "  i  - режим ввода записей дневника\n"
                << "  v  - режим просмотра записей дневника\n"
                << "  d  - режим удаления записей дневника\n"
                << "  q  - выход из дневника\n"
                << "  q! - выход без записи изменений\n"
                << "  wq - выход с записью изменений\n";
      std::cout << '\n'
                << "Настройки:\n";
      std::cout << "  set password - установка пароля\n";
      std::cout << "\n:";
      std::string scom {};
      scom = con.get_line(160);
      return scom;
   }
   //---------------------------------------------------------------------------
   void Diary::mode_quit(std::string& s)
      // режим выхода из дневника
   {
      pl::Conio con;
      std::cout << pl::mr::clrscr;
      info_logo();
      std::cout << '\n';

      if (!_buffer.empty() && std::strncmp("q",s.c_str(),1)==0) {
         for (;;) {
            std::cout << pl::mr::bold << "W" << pl::mr::reset
                      << ": Изменения не сохранены "
                      << "(введите q!, чтобы обойти проверку).\n";
            std::string sq {};
            std::cout << ':';
            sq = con.get_line(160);
            if (std::strncmp("q!",sq.c_str(),2)==0) {
               _buffer.clear();
               std::cout << pl::mr::clrscr;
               info_logo();
               std::cout << '\n';
               break;
            }
            std::cout << pl::mr::clrscr;
            info_logo();
            std::cout << '\n';
         }
      }
      else if (!_buffer.empty() && std::strncmp("q!",s.c_str(),2)==0) {
         _buffer.clear();
      }
      else if (!_buffer.empty() && std::strncmp("wq",s.c_str(),2)==0) {
         if (open_file_diary()) {
            if (!_day_flag) {
               _fsd << _delimiter << '\n' << _today  << '\n';
               _day_flag = true;
            }
            for (const auto& lst : _buffer)  
               _fsd << lst;
            std::cout << pl::mr::bold << "W" << pl::mr::reset << ": " 
                      << _buffer.size() << "L, " 
                      << get_size_buffer() << "B записано.\n";
            _buffer.clear();
            _fsd.close();
         }
         else 
            std::cout << "E: Не могу открыть файл дневника.\n";
      }
      std::cout << "До новых встреч...\n\n";
   }
  //---------------------------------------------------------------------------
   void Diary::mode_input()
      // режим ввода записей дневника
   {
      pl::Conio con;
      std::cout << pl::mr::clrscr;
      info_logo();
      std::cout << '\n';
      std::cout << pl::mr::bold 
                << "-- ВСТАВКА --\n"
                << pl::mr::reset;
      std::cout << "Допустимые команды:\n"
                << "  dd   - удаление последней введенной строки\n"
                << "  ww   - запись введенной информации\n"
                << "  exit - выход из режима\n";
      std::cout << '\n';

      for (;;) {
         std::cout << "> ";
         std::string str {};
         str = con.get_line(160);
         _buffer.emplace_back(str);
         if (std::strncmp("exit",str.c_str(),4)==0) {
            _buffer.pop_back();
            break;
         }
         else if (std::strncmp("dd",str.c_str(),2)==0) {
            _buffer.pop_back();
            _buffer.pop_back();
            std::cout << pl::mr::bold << "W" << pl::mr::reset << ": "
                      << "1L удалена.\n";
         }
         else if (std::strncmp("ww",str.c_str(),2)==0) {
            _buffer.pop_back();
            if (open_file_diary()) {
               if (!_buffer.empty()) {
                  if (!_day_flag) {
                     _fsd << _delimiter << '\n' << _today  << '\n';
                     _day_flag = true;
                  }
                  for (const auto& lst : _buffer)  
                     _fsd << lst;
                  std::cout << pl::mr::bold << "W" << pl::mr::reset << ": " 
                            << _buffer.size() << "L, " 
                            << get_size_buffer() << "B записано.\n";
                  _buffer.clear();
               }
               _fsd.close();
            }
            else
               std::cout << "E: Не могу открыть файл дневника.\n";
         }
      }   
   }
   //---------------------------------------------------------------------------
   void Diary::mode_viewing()
      // режим просмотра записей дневника
   {
      pl::Conio con;
 
      if (!_buffer.empty()) {
         for (;;) {
            std::cout << pl::mr::clrscr;
            info_logo();
            std::cout << '\n';
            std::cout << pl::mr::bold << "W" << pl::mr::reset
                      << ": Изменения не сохранены, сохранить y/n: ";
            std::string yn = con.get_line(160);
            if (std::strncmp("n",yn.c_str(),1)==0) {
               _buffer.clear();
               break;
            }
            else if (std::strncmp("y",yn.c_str(),1)==0) {
               if (open_file_diary()) {
                  if (!_day_flag) {
                     _fsd << _delimiter << '\n' << _today  << '\n';
                     _day_flag = true;
                  }
                  for (const auto& lst : _buffer)  
                     _fsd << lst;
                  std::cout << pl::mr::bold << "W" << pl::mr::reset << ": " 
                            << _buffer.size() << "L, " 
                            << get_size_buffer() << "B записано.\n";
                  _buffer.clear();
                  _fsd.close();
               }
               else
                  std::cout << "E: Не могу открыть файл дневника.\n";
               break;
            }
         }
      }

      std::cout << pl::mr::clrscr;
      info_logo();
      std::cout << '\n';
      std::cout << pl::mr::bold 
                << "-- ПРОСМОТР --\n"
                << pl::mr::reset;
      std::cout << "Допустимые команды:\n"
                << "  дд-мм-гггг - дата просматриваемых записей\n"
                << "  exit       - выход из режима\n";
      std::cout << '\n';

      for (;;) {
         std::cout << ":";
         std::string str {};
         str = con.get_line(160);
         if (std::strncmp("exit",str.c_str(),4)==0) break;
         else if (str.size()==11) {
            if (!open_file_diary())
               std::cout << "E: Не могу открыть файл дневника.\n";
            else {
               std::string line {};
               while (std::getline(_fsd,line)) {
                  if (std::strncmp(str.c_str(),line.c_str(),10)==0) {
                     while (std::getline(_fsd,line)) {
                        if (std::strncmp(_delimiter.c_str(),line.c_str(),2)==0
                           || _fsd.eof()) break;
                        else {
                           std::string sl = std::string(line)+'\n';
                           _buffer.emplace_back(sl);
                        }
                     }
                  }
               }
               if (_buffer.empty()) {
                  std::cout << pl::mr::bold << "W" << pl::mr::reset
                            << ": Записи за искомый день отсутствуют.\n";
               } 
               else {
                  for (const auto& lst : _buffer)
                     std::cout << "> " << lst;
                  _buffer.clear();
               }
               _fsd.close();
            }
         }
      }
   }
   //---------------------------------------------------------------------------
   void Diary::mode_delete()
      // режим удаления записей дневника
   {
      pl::Conio con;
      std::cout << pl::mr::clrscr;
      info_logo();
      std::cout << '\n';
      std::cout << pl::mr::bold 
                << "-- УДАЛЕНИЕ --\n"
                << pl::mr::reset;
      std::cout << "Допустимые команды:\n"
                << "  дд-мм-гггг - дата удаляемых записей\n"
                << "  dd         - удаление всей истории дневника\n"
                << "  exit       - выход из режима\n";
      std::cout << '\n';

      for (;;) {
         std::cout << ":";
         std::string str {};
         str = con.get_line(160);
         if (std::strncmp("exit",str.c_str(),4)==0) break;
         else if (std::strncmp("dd",str.c_str(),2)==0) {
            std::string fpath = _f_diary_path+_f_diary;
            std::remove(fpath.c_str());
            std::cout << pl::mr::bold << "W" << pl::mr::reset << ": "
                      << "Вся история удалена.\n";
         }
         else if (str.size()==11) {
            std::string ifpath = _f_diary_path+_f_diary;
            std::string ofpath = _f_diary_path+_f_diary_temp;

            std::ifstream ifile(ifpath);
            std::ofstream ofile(ofpath);

            std::string line {};
            bool flag {false};
            while (std::getline(ifile,line)) {
               if (std::strncmp(str.c_str(),line.c_str(),10)==0) {
                  while (std::getline(ifile,line)) {
                     if (std::strncmp(_delimiter.c_str(),line.c_str(),2)==0
                        || _fsd.eof()) break;
                  }
                  flag = true;
               }
               else ofile << line << '\n';
            }
            if (flag) 
               std::cout << pl::mr::bold << "W" << pl::mr::reset << ": "
                         << "Записи за требуемый день удалены.\n";

            ifile.close();
            ofile.close();
            
            std::remove(ifpath.c_str());
            std::rename(ofpath.c_str(),ifpath.c_str());
         }
      } 
   } 
}

