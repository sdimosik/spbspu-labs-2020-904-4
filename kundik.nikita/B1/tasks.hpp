#ifndef LABS_TASKS_HPP
#define LABS_TASKS_HPP
#include <cstddef>

#define UNKNOWN_ERROR "Something went wrong! The program stops working!"
#define BAD_INPUT_NUMBERS "Incorrect input! You can use only integer numbers and you cant use to large values!"

namespace task
{
  void doFirstTask(const char* sortDirection);
  void doSecondTask(const char* fileName);
  void doThirdTask();
  void doFourthTask(const char* sortDirection, size_t size);
}
#endif
