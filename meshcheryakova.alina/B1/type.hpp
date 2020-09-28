#ifndef B1_TYPE_HPP
#define B1_TYPE_HPP

#include <iostream>

template<typename T>
struct type_bracket{

  using index = size_t;
  static index begin(const T&)
  {
    return 0;
  }

  static index end(const T& collection)
  {
    return collection.size();
  }

  static typename T::reference get_element(T& collection, index i)
  {
    return collection[i];
  }

};

template<typename T>
struct type_at{

  using index = size_t ;
  static index begin(const T&)
  {
    return 0;
  }

  static index end(const T& collection)
  {
    return collection.size();
  }

  static typename T::reference get_element(T& collection, index i)
  {
    return collection.at(i);
  }

};

template<typename T>
struct type_iter{

  using index = typename T::iterator;
  static index begin(T& collection)
  {
    return collection.begin();
  }

  static index end(T& collection)
  {
    return collection.end();
  }

  static typename T::reference get_element(T&, index i)
  {
    return *i;
  }

};

#endif //B1_TYPE_HPP
