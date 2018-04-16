/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>

class Heap
{
  public:
  	Heap() : array(NULL), num(0) {}
  	Heap(T data[], int num);

  	~Heap() { delete[] array; }

  	T & getMax() throw (const char *) { return array[1]; }
  	T * getData() { return array; }
  	int getNum() { return num; }

  	void deleteMax() throw (const char *);

    // create a heap out of array
    void heapify(T* data, int n);

    // destructively sort
    void sort(T* a, int n);

private:
	// fix heap from index down
	void percolateDown(T * array, int index, int n);

	// swap two items
	void swap (int i1, int i2);

	T * array;
	int num;

};

/*****************************************************
* Swap
* Swap two items
****************************************************/
template <class T>
void Heap<T> :: swap (int i1, int i2)
{
	 T temp = array[i1];
     array[i1] = array[i2];
     array[i2] = temp;
}
/*****************************************************
* deleteMax
* Delete the top element
****************************************************/
template <class T>
void Heap<T> :: deleteMax() throw (const char *)
{
  array[1] = array[num];
  num--;
  percolateDown(array, 1, num);
}

/*****************************************************
* SORT
* Destructively sort
****************************************************/
template<class T>
void Heap<T> :: sort(T * a, int n)
{
   T tmp;

   // swaps then percolates
   for (int i = n; i >= 2; i--) {
      tmp = a[i];
      a[i] = a[1];
      a[1] = tmp;
      percolateDown(a, 1, i - 1);
   }
}

/*****************************************************
* HEAP(T, INT)
* Non-default constructor
****************************************************/
template<class T>
Heap<T>:: Heap(T data[], int num)
{
   // sets data
   this->num = num;
   array = new T[num + 1];

   // copy contents then heapify
   for (int i = 0; i <= num; i++)
   {
      array[i] = data[i];
   }
   heapify(array, num);
}

/*****************************************************
* HEAPIFY
* Creates heap
****************************************************/
template <class T>
void Heap<T> :: heapify(T* data, int n)
{
   // percolates all non-leaf nodes
   int i = n / 2;
   for (i; i >= 1; i--)
      percolateDown(data, i, n);
}
/*****************************************************
* PERCOLATE DOWN
* Fix heap order
****************************************************/
template <class T>
void Heap<T> :: percolateDown(T* array, int index, int n)
{
   T tmp = array[index];
   int j = 2 * index;

   // Percolates and fixes heap order
   while (j <= n)
   {
      // Compare left and rights, then head that direction
      if (j < n && array[j + 1] > array[j])
         j = j + 1;

      if (array[j] > tmp || array[j] == tmp)
      {
         array[j / 2] = array[j];
         j = j * 2;
      }
      else if (tmp > array[j])
         break;
   }
   array[j / 2] = tmp;
}
/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
   // Fix index and add an extra space
   T sortArray[num + 1];

   // Copy contents
   for (int i = 0; i < num; i++)
      sortArray[i + 1] = array[i];

   // Setup new heap, sort
   Heap<T>* heap = new Heap<T>(sortArray, num);
   heap->sort(heap->getData(), heap->getNum());

   // Fix again
   for (int i = 1; i <= num; i++) {
      array[i - 1] = heap->getData()[i];
   }
}

#endif // SORT_HEAP_H
