#include <iostream>
#include <vector>
#include "print.cpp"

void  task_3()
{
  std::vector<int> array;

   int insert_number = 0;
   while(std::cin >> insert_number)
   {
     if(insert_number == 0)
     {
       break;
     }
     array.push_back(insert_number);
   }

   if((!std::cin.eof()) && (std::cin.fail()))
   {
     throw std::ios_base::failure("fail in reading stream \n");
   }

   if(array.empty())
   {
     return;
   }

   if(insert_number != 0)
   {
       throw std::invalid_argument(" the last number of array must be zero \n");
   }

   auto last_element = array.back();

   if(last_element == 1)
   {
     for(auto i = array.begin(); i != array.end();)
     {
       (*i % 2 == 0)? i = array.erase(i) : i++;
     }
   }
   else if(last_element == 2)
   {
     for(auto i = array.begin(); i != array.end();)
     {
       (*i % 3 == 0)? i = array.insert(i+1,3,1) : i++;
     }
   }

   print(array);
};
