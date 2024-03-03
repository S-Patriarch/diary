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
   std::string s = dr.mode_help();

   return 0;
}

