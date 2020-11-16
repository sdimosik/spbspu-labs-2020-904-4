#include "factorialContainer.hpp"

FactorialContainer::Iterator FactorialContainer::begin()
{
  return Iterator(Iterator::MIN_IND_ELEM);
}

FactorialContainer::Iterator FactorialContainer::end()
{
  return Iterator(Iterator::MAX_IND_ELEM);
}


FactorialContainer::Iterator::Iterator() :
        ind_elem_(MIN_IND_ELEM),
        value_(MIN_IND_ELEM)
{}

FactorialContainer::Iterator::Iterator(size_t ind_elem) :
        ind_elem_(ind_elem),
        value_(getFactorial(ind_elem))
{
  if ((ind_elem < MIN_IND_ELEM) || (ind_elem > MAX_IND_ELEM))
  {
    throw std::out_of_range("Error: wrong order entered!\n");
  }
}

const size_t &FactorialContainer::Iterator::operator*() const noexcept
{
  return value_;
}

const size_t *FactorialContainer::Iterator::operator->() const noexcept
{
  return &value_;
}

FactorialContainer::Iterator &FactorialContainer::Iterator::operator++()
{
  if (ind_elem_ > MAX_IND_ELEM)
  {
    throw std::out_of_range("Error: the index of element is out of range (more then 11)!\n");
  }
  ++ind_elem_;
  value_ *= ind_elem_;
  return *this;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator++(int)
{
  const Iterator tempIter = *this;
  this->operator++();
  return tempIter;
}

FactorialContainer::Iterator &FactorialContainer::Iterator::operator--()
{
  if (ind_elem_ <= MIN_IND_ELEM)
  {
    throw std::out_of_range("Error: the index of element is out of range (less then 0)!\n");
  }
  value_ /= ind_elem_;
  ind_elem_--;
  return *this;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator--(int)
{
  const Iterator tempIter = *this;
  this->operator--();
  return tempIter;
}

bool FactorialContainer::Iterator::operator==(const Iterator &it) const
{
  return ind_elem_ == it.ind_elem_;
}

bool FactorialContainer::Iterator::operator!=(const Iterator &it) const
{
  return ind_elem_ != it.ind_elem_;
}

size_t FactorialContainer::Iterator::getFactorial(size_t index)
{
  size_t factorial = MIN_IND_ELEM;
  for (size_t i = MIN_IND_ELEM; i <= index; i++)
  {
    factorial *= i;
  }
  return factorial;
}

