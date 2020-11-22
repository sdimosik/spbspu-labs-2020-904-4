#include "get-partition.hpp"
#include "shape.hpp"
#include "base-types.hpp"

unzhakov::Matrix unzhakov::getPartition(const unzhakov::Shape::SharedPtr *elem, size_t size)
{
  unzhakov::Matrix tempMatrix;
  tempMatrix.addLayer();
  for (size_t k = 0; k < size; k++)
  {
    size_t i = 0;
    size_t j = 0;
    size_t rows = tempMatrix.getRow();
    size_t columns = tempMatrix[0].getSize();
    while ((i < rows) && (j < columns))
    {
      columns = tempMatrix[i].getSize();
      if (isIntersect(elem[k]->getFrameRect(), tempMatrix[i][j]->getFrameRect()))
      {
        i++;
        j = 0;
        continue;
      }
      j++;
    }
    if (i == rows)
    {
      tempMatrix.addLayer();
    }
    tempMatrix[i].add(elem[k]);
  }
  return tempMatrix;
}

