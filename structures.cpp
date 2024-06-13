/**
  ** (_dsa_23)  **)

  C++ Custom Implementation Of Some Data Structures
  Namespaces: (_ags,ContagiousLists,LinkedLists,Queues,Stacks ...)
  This file is written in (c++ 11,12..23) because there's a lot of
  use of library functions in this file & some might may be deprecated
  so, it is accessible to everyone and for modification under the
  (GNU License)

  The algorithms that might be used in this file are out-dated or perhaps could
  be slower than expected, the file implements the commonly used algorithms
  having complexity O(log n) in many DS but could be optimised further, the file
  implements some algorithms like binary search,merge sort and quick sort as
  sorting algorithms and some data structures like stacks,linkedlist queues,and
  custom implemented lists, but this isn't the only thing in this file but there
  is a lot of modification in these data structures such as
  circularlinkeddequeue implementation etc.These data structures and algorithms
  are merely implemented as practice and can be further modified optimistically
  for better use cases.



*/
#include <algorithm>
#include <iostream>
#include <memory>
#include <regex>
#include <stdexcept>

#define DEF_DS_SIZE 0b101
using namespace std;

/*
Implementaion of some algorithms of complexity O(log n)
*/
namespace _ags {
int binary_s(int *ptr, unsigned int size, int key) {
  unsigned int s = 0;
  unsigned int e = size - 1;
  unsigned int mid;
  while (s <= e) {
    mid = s + (e - s) / 2;
    if (ptr[mid] == key)
      return mid;
    else if (key > ptr[mid])
      s = mid + 1;
    else
      e = mid - 1;
  }
  return -1;
}

int r_binary_s(int *ptr, int key, int s, int e) {
  if (s > e)
    return -1;
  int mid = s + (e - s) / 2;
  if (ptr[mid] == key)
    return mid;
  if (key > ptr[mid])
    return r_binary_s(ptr, key, mid + 1, e);
  return r_binary_s(ptr, key, s, mid - 1);
}

int f_i_sorted(int *ptr, int n, int k) {
  int s = 0;
  int e = n - 1;
  int mid;
  int ans = -1;
  while (s <= e) {
    mid = s + (e - s) / 2;
    if (ptr[mid] == k) {
      ans = mid;
      e = mid - 1;
    } else if (k > ptr[mid]) {
      s = mid + 1;
    } else {
      e = mid - 1;
    }
  }
  return ans;
}

int l_i_sorted(int *ptr, int n, int k) {
  int s = 0;
  int e = n - 1;
  int mid;
  int ans = -1;
  while (s <= e) {
    mid = s + (e - s) / 2;
    if (ptr[mid] == k) {
      ans = mid;
      s = mid + 1;
    } else if (k > ptr[mid]) {
      s = mid + 1;
    } else {
      e = mid - 1;
    }
  }
  return ans;
}

int count_occur_sorted(int *ptr, int n, int k) {
  int fi = f_i_sorted(ptr, n, k);
  int sec = l_i_sorted(ptr, n, k);
  return (sec - fi) + 1;
}

int max_array_sorted(int *ptr, int n) {
  int s = 0;
  int e = n - 1;
  while (s < e) {
    int mid = s + (e - s) / 2;
    if (ptr[mid] < ptr[mid + 1]) {
      s = mid + 1;
    } else {
      e = mid;
    }
  }
  return s;
}
int min_array_sorted(int *ptr, int n) {
  int s = 0;
  int e = n - 1;
  while (s < e) {
    int mid = s + (e - s) / 2;
    if (ptr[mid] < ptr[mid + 1]) {
      e = mid;
    } else {
      s = mid + 1;
    }
  }
  return e;
}

void merge(int *ptr, int s, int mid, int e, bool reverse) {
  int *a = new int[e - s + 1];
  int i = s, j = mid + 1, k = 0;
  while (i <= mid && j <= e) {
    if (reverse ? (ptr[i] > ptr[j]) : ptr[i] < ptr[j]) {
      a[k++] = ptr[i++];
    } else {
      a[k++] = ptr[j++];
    }
  }
  while (i <= mid)
    a[k++] = ptr[i++];
  while (j <= e)
    a[k++] = ptr[j++];

  for (int i = s; i <= e; i++) {
    ptr[i] = a[i - s];
  }
}
void m_sort(int *ptr, int s, int e, bool reverse) {
  if (s < e) {
    int mid = s + (e - s) / 2;
    m_sort(ptr, s, mid, reverse);
    m_sort(ptr, mid + 1, e, reverse);
    merge(ptr, s, mid, e, reverse);
  }
}
int _partition(int *ptr, int s, int e, bool reverse) {
  int pivot = ptr[s];
  int i = s;
  int j = e;
  while (i <= j) {
    while (reverse ? ptr[i] >= pivot : ptr[i] <= pivot)
      i++;
    while (reverse ? ptr[j] < pivot : ptr[j] > pivot)
      j--;
    if (i < j) {
      swap(ptr[i], ptr[j]);
    }
  }
  swap(ptr[s], ptr[j]);
  return j;
}
void _qsort(int *ptr, int s, int e, bool reverse) {
  if (s < e) {
    int i = _partition(ptr, s, e, reverse);
    _qsort(ptr, s, i, reverse);
    _qsort(ptr, i + 1, e, reverse);
  }
}

void reverse(int *ptr, int i, int j) {
  if (i > j)
    return;
  swap(ptr[i], ptr[j]);
  reverse(ptr, ++i, --j);
}
bool is_sorted(int *ptr, int n, int i = 0) {
  if (i == n - 1)
    return true;
  return (ptr[i] < ptr[i + 1]) && is_sorted(ptr, n, ++i);
}
void copy_array(int *src, int i, int elements, int *target) {
  std::copy_n(src + i, elements, target);
}
} // namespace _ags
// namespace ContagiousLists
namespace ContagiousLists {
// ListErrors
enum ListErrors { ListError, IndexError, OverflowError, MemoryAllocationError };
void throw_error(ListErrors) {
  if (ListErrors::IndexError) {
    throw runtime_error("IndexError(Out of Bounds)!");
  } else if (ListErrors::ListError) {
    throw runtime_error("ListError(Empty)!");
  } else if (ListErrors::OverflowError) {
    throw runtime_error("OverflowError(Max Size Reached)!");
  } else if (ListErrors::MemoryAllocationError) {
    throw runtime_error("MemoryAllocationError(Allocation Failure!)");
  }
}
class FixedArrayList {
private:
  int u_size = 0b0;
  int t_size;
  int *ptr;

public:
  FixedArrayList() {
    this->t_size = DEF_DS_SIZE;
    ptr = new int[DEF_DS_SIZE];
  }
  FixedArrayList(int size) {
    this->t_size = size;
    ptr = new int[size];
  }

  // generals
  void show() const {
    if (u_size == 0) {
      cout << "[]\n";
      return;
    }
    int i = 0;
    while (i != u_size)
      cout << ptr[i++] << " ";
    cout << endl;
  }
  int length() const { return u_size; }
  bool is_empty() const { return u_size == 0; }
  bool is_full() const { return u_size >= t_size; }
  int at(int index) const {
    if (index >= u_size) {
      throw_error(ListError);
      return -1;
    }
    return ptr[index];
  }
  // main
  bool append(int n) {
    if (u_size >= t_size) {
      throw_error(OverflowError);
      return false;
    }
    ptr[u_size++] = n;
    return true;
  }
  bool insert(int index, int n) {
    if (u_size >= t_size) {
      throw_error(ListError);
      return false;
    }
    int i = u_size;
    while (i >= index) {
      ptr[i] = ptr[i - 1];
      i--;
    }
    ptr[index] = n;
    u_size++;
    return true;
  }
  int pop() {
    if (u_size == 0) {
      throw_error(ListError);
      return -1;
    }
    int copy = ptr[0];
    int i = 0;
    while (i != u_size) {
      ptr[i] = ptr[i + 1];
      i++;
    }
    u_size--;
    return copy;
  }

  int remove(int index) {
    if (u_size == 0) {
      throw_error(ListError);
      return -1;
    }
    int copy = ptr[index];
    while (index < u_size) {
      ptr[index] = ptr[index + 1];
      index++;
    }
    return copy;
  }
  bool set(int index, int element) {
    if (u_size == 0)
      return false;
    ptr[index] = element;
    return true;
  }
  /**
     @return Returns maximum element in sorted array O(log n)
  */
  int max() {
    int maxi = _ags::max_array_sorted(ptr, u_size);
    return maxi;
  }
  /**
     @return Returns mainimum element in sorted array O(log n)
  */
  int min() {
    int maxi = _ags::min_array_sorted(ptr, u_size);
    return maxi;
  }
  /**
     @param element of an sorted array
     @return Returns first index of element in sorted array O(log n)
     @return Returns -1 if element not found
  */
  int index_of(int element) { return _ags::f_i_sorted(ptr, u_size, element); }
  /**
     @param element of an sorted array
     @return Returns last index of element in sorted array O(log n)
     @return Returns -1 if element not found
  */
  int last_index_of(int element) {
    return _ags::l_i_sorted(ptr, u_size, element);
  }
  /**
     @param element of an sorted array
     @return Returns occurences of an element in sorted array O(log n)
  */
  int count(int element) {
    return _ags::count_occur_sorted(ptr, u_size, element);
  }
  /**
    @param reverse modifies order (true|false)
    Sorts an array in complexity of O(log n)
  */
  void sort(bool reverse = false) {
    if (u_size == 0 || u_size == 1)
      return;
    _ags::m_sort(ptr, 0, u_size - 1, reverse);
  }

  void extend(FixedArrayList *array) {
    if (u_size >= t_size) {
      throw_error(IndexError);
      return;
    }
    int remaining_size = t_size - u_size;
    for (int i = 0; i < remaining_size; i++) {
      append(array->at(i));
    }
  }
  void extend_array(int *array, int n) {
    if (u_size >= t_size) {
      throw_error(IndexError);
      return;
    }
    int remaining_size = t_size - u_size;
    for (int i = 0; i < remaining_size; i++) {
      append(array[i]);
    }
  }
  void reverse() {
    if (u_size == 0 || u_size == 1)
      return;
    _ags::reverse(ptr, 0, u_size);
  }
  /**
    @param n number to fill with
    Fills array using builting namespace std's fill function
  */
  void fill(int n) { std::fill(ptr, ptr + t_size, n); }
  void copy_into(int *dest, int n) {
    if (u_size == 0) {
      return;
    }
    for (int i = 0; i < n; i++) {
      dest[i] = ptr[i];
    }
  }
  void clear() {
    delete[] ptr;
    u_size = 0;
  }

  // operator_overloads
  int operator[](int index) {
    if (index >= u_size) {
      throw_error(ListErrors::OverflowError);
      return -1;
    }
    return ptr[index];
  }
  ~FixedArrayList() {
    delete[] ptr;
    u_size = 0;
  }
};
class DynamicArrayList : public FixedArrayList {
private:
  int *ptr;
  int u_size = 0b00;
  int t_size = DEF_DS_SIZE;

public:
  DynamicArrayList() { ptr = new int[t_size]; }
  DynamicArrayList(int size) {
    ptr = new int[size];
    t_size = size;
  }

  int length() const { return u_size; }
  bool is_empty() const { return u_size == 0; }

  void show() const {
    if (u_size == 0) {
      cout << "[]\n";
      return;
    }
    for (int i = 0; i < u_size; i++) {
      cout << ptr[i] << " ";
    }
    cout << '\n';
  }
  /**
  * @brief appends element to end of list
  * @param int element to be appended
  * @returns void

*/
  void append(int element) {
    if (u_size > t_size) {
      t_size *= 2;
      int *p = (int *)std::realloc(ptr, sizeof(int) * t_size);
      if (p == nullptr) {
        throw_error(MemoryAllocationError);
        return;
      }
      ptr = p;
    }
    ptr[u_size++] = element;
  }

  bool insert(int index, int n) {
    while (u_size >= t_size) {
      t_size *= 2;
      int *p = (int *)std::realloc(ptr, sizeof(int) * t_size);
      if (p == nullptr) {
        throw_error(MemoryAllocationError);
        return false;
      }
      ptr = p;
    }
    int i = u_size;
    while (i >= index) {
      ptr[i] = ptr[i - 1];
      i--;
    }
    ptr[index] = n;
    u_size++;
    return true;
  }
  int pop() {
    if (u_size == 0) {
      throw_error(ListError);
      return -1;
    }
    int copy = ptr[0];
    int i = 0;
    while (i != u_size) {
      ptr[i] = ptr[i + 1];
      i++;
    }
    u_size--;
    return copy;
  }

  int remove(int index) {
    if (u_size == 0) {
      throw_error(ListError);
      return -1;
    }
    int copy = ptr[index];
    while (index < u_size) {
      ptr[index] = ptr[index + 1];
      index++;
    }
    return copy;
  }

  /**
    * @brief extends the list by appending another list
    * @param DynamicArrayList* A DynamicArrayList
    * @returns void

  */
  void extend(DynamicArrayList *dal) {
    while (t_size <= dal->u_size) {
      t_size *= 2;
      int *p = (int *)std::realloc(ptr, sizeof(int) * t_size);
      if (p == nullptr) {
        throw_error(MemoryAllocationError);
        return;
      }
      ptr = p;
    }
    int j = 0;
    while (j < dal->u_size) {
      ptr[u_size++] = dal->ptr[j++];
    }
  }
  /**
   * @brief extends the list by appending array
   * @param int* array
   * @param int size
   * @returns void
   */
  void extend_array(int *array, int n) {
    while (t_size <= n) {
      t_size *= 2;
      int *p = (int *)std::realloc(ptr, sizeof(int) * t_size);
      if (p == nullptr) {
        throw_error(MemoryAllocationError);
        return;
      }
      ptr = p;
    }
    int j = 0;
    while (j < n) {
      ptr[u_size++] = array[j++];
    }
  }
  /**
   * @brief clears the memory for list
   * @returns void
   */
  void clear() {
    delete[] ptr;
    u_size = 0;
  }
  /**
   * @brief sets element for given index
   * @param index index of element in the list
   * @param element to replace with
   * @returns void
   */
  bool set(int index, int element) {
    if (u_size == 0) {
      return false;
    }
    ptr[index] = element;
    return true;
  }
  void reverse() {
    if (u_size == 0 || u_size == 1)
      return;
    _ags::reverse(ptr, 0, u_size);
  }
  /**
    @param n number to fill with
    Fills array using builting namespace std's fill function
  */
  void fill(int n) { std::fill(ptr, ptr + t_size, n); }
  void copy_into(int *dest, int n) {
    if (u_size == 0) {
      return;
    }
    for (int i = 0; i < n; i++) {
      dest[i] = ptr[i];
    }
  }
  /**
   @return Returns maximum element in sorted array O(log n)
*/
  int max() {
    int maxi = _ags::max_array_sorted(ptr, u_size);
    return maxi;
  }
  /**
     @return Returns mainimum element in sorted array O(log n)
  */
  int min() {
    int maxi = _ags::min_array_sorted(ptr, u_size);
    return maxi;
  }
  /**
     @param element of an sorted array
     @return Returns first index of element in sorted array O(log n)
     @return Returns -1 if element not found
  */
  int index_of(int element) { return _ags::f_i_sorted(ptr, u_size, element); }
  /**
     @param element of an sorted array
     @return Returns last index of element in sorted array O(log n)
     @return Returns -1 if element not found
  */
  int last_index_of(int element) {
    return _ags::l_i_sorted(ptr, u_size, element);
  }
  /**
     @param element of an sorted array
     @return Returns occurences of an element in sorted array O(log n)
  */
  int count(int element) {
    return _ags::count_occur_sorted(ptr, u_size, element);
  }
  /**
    @param reverse modifies order (true|false)
    Sorts an array in complexity of O(log n)
  */
  void sort(bool reverse = false) {
    if (u_size == 0 || u_size == 1)
      return;
    _ags::m_sort(ptr, 0, u_size - 1, reverse);
  }

  // operator_overloads
  int operator[](int index) {
    if (index >= u_size) {
      throw_error(ListErrors::OverflowError);
      return -1;
    }
    return ptr[index];
  }
  ~DynamicArrayList() {
    delete[] ptr;
    u_size = 0;
  }
};
} // namespace ContagiousLists
// namespace LinkedLists
namespace LinkedLists {
class Node {
public:
  int data;
  Node *next;
  Node(int value) : data(value), next(nullptr) {}
};
// Mother(base) virtual class for all other children
class AbstractList {
private:
  Node *head;
  Node *tail;
  int _size = 0;

public:
  AbstractList() : head(nullptr), tail(nullptr), _size(0){};

  // some pure and unpure virtual functions
  virtual void show() const = 0;
  virtual bool insert_start(int node) = 0;
  virtual bool insert_after(int node, int after) = 0;
  virtual bool insert_before(int node, int before) = 0;
  virtual bool insert_end(int node) = 0;
  virtual bool remove_start() = 0;
  virtual bool remove_end() = 0;
  virtual bool remove(int node) = 0;
  virtual bool set(int node, int new_node) = 0;
  virtual int size() const = 0;
  virtual void clear() = 0;
  virtual void reverse() = 0;
  virtual void to_array(int *ptr) const = 0;

  virtual ~AbstractList() {
    while (head != nullptr) {
      Node *tmp = head->next;
      delete head;
      head = tmp;
      _size--;
    }
  }
};

class SinglyLinkedList : public virtual AbstractList {
private:
  Node *head;
  Node *tail;
  int _size;

public:
  SinglyLinkedList() : head(nullptr), tail(nullptr), _size(0){};

  void show() const override {
    if (_size == 0) {
      cout << "[]\n";
      return;
    }
    Node *temp = head;
    while (temp != nullptr) {
      cout << temp->data << " -> ";
      temp = temp->next;
    }
    cout << "END\n";
  }
  Node *get_head() const { return head; };
  Node *get_tail() const { return tail; };
  int size() const override { return _size; };
  Node *search(int node) const {
    if (_size == 0) {
      return nullptr;
    }
    Node *tmp = head;
    while (tmp->data != node) {
      tmp = tmp->next;
    }
    return tmp;
  };
  bool insert_start(int node) override {
    Node *nd = new Node(node);
    if (nd == nullptr)
      return false;
    if (_size == 0) {
      head = nd;
      tail = nd;
    } else {
      Node *tmp = head;
      nd->next = tmp;
      head = nd;
    }
    _size++;
    return true;
  }
  bool insert_end(int node) override {
    Node *nd = new Node(node);
    if (nd == nullptr)
      return false;
    if (_size == 0) {
      return insert_start(node);
    } else {
      tail->next = nd;
      tail = nd;
    }
    _size++;
    return true;
  };
  bool insert_after(int node, int after) override {
    if (node == tail->data) {
      insert_end(node);
      return true;
    }
    if (_size == 0)
      return false;
    Node *new_node = new Node(after);
    if (new_node == nullptr)
      return false;
    Node *tmp = search(node);
    Node *next_node = tmp->next;
    tmp->next = new_node;
    new_node->next = next_node;
    _size++;
    return true;
  };
  bool insert_before(int node, int before) override {
    if (_size == 0)
      return false;
    if (node == head->data) {
      insert_end(node);
      return true;
    }
    Node *new_node = new Node(before);
    if (new_node == nullptr)
      return false;
    Node *tmp = head;
    while (tmp->next->data != node) {
      tmp = tmp->next;
    }
    Node *next_node = tmp->next;
    tmp->next = new_node;
    new_node->next = next_node;
    _size++;
    return true;
  };
  bool remove_end() override {
    if (_size == 0)
      return false;
    Node *tmp = head;
    while (tmp->next != tail) {
      tmp = tmp->next;
    }
    delete tmp->next;
    tmp->next = nullptr;
    tail = tmp;
    _size--;
    return true;
  };
  bool remove_start() override {
    if (_size == 0)
      return false;
    Node *new_head = head->next;
    delete head;
    head = new_head;
    _size--;
    return true;
  };
  void reverse() override {
    Node *prev = nullptr;
    Node *current = head;
    Node *temp = nullptr;
    while (current != nullptr) {
      temp = current->next;
      current->next = prev;
      prev = current;
      current = temp;
    }
    Node *t = head;
    head = tail;
    tail = t;
  };

  void clear() override {
    if (_size == 0)
      return;
    while (head != nullptr) {
      Node *temp = head->next;
      delete head;
      head = temp;
      _size--;
    }
    head = nullptr;
    tail = nullptr;
  };
  bool remove(int node) override {
    if (node == head->data) {
      return remove_start();
    }
    if (node == tail->data) {
      return remove_end();
    }
    if (_size == 0)
      return false;
    Node *tmp = head;
    while (tmp->next->data != node) {
      tmp = tmp->next;
    }
    Node *next_to_deleted = tmp->next->next;
    delete tmp->next;
    tmp->next = next_to_deleted;
    _size--;
    return true;
  };
  bool set(int node, int new_node) override {
    if (_size == 0)
      return false;
    Node *nd = search(node);
    nd->data = new_node;
    return true;
  };
  /**
  * @brief copies nodes to array provided (arraysize must == list size)
  * @param int* pointer to an array
  * @return void

  */
  void to_array(int *ptr) const override {
    int j = 0;
    Node *tmp = head;
    while (tmp != nullptr) {
      ptr[j++] = tmp->data;
      tmp = tmp->next;
    }
  };
  ~SinglyLinkedList() { clear(); }
};

class CircularLinkedList : public virtual AbstractList {
private:
  Node *head;
  Node *tail;
  int _size;

public:
  CircularLinkedList() : head(nullptr), tail(nullptr), _size(0){};

  void show() const override {
    if (_size == 0) {
      cout << "[]\n";
      return;
    }
    Node *temp = head;
    do {
      cout << temp->data << " -> ";
      temp = temp->next;
    } while (temp != head);
    cout << "END\n";
  }
  Node *get_head() const { return head; };
  Node *get_tail() const { return tail; };
  int size() const override { return _size; };
  Node *search(int node) const {
    if (_size == 0) {
      return nullptr;
    }
    Node *tmp = head;
    do {
      tmp = tmp->next;
    } while (tmp->data != node);
    return tmp;
  };
  bool insert_start(int node) override {
    Node *nd = new Node(node);
    if (nd == nullptr)
      return false;
    if (_size == 0) {
      head = nd;
      tail = nd;
    } else {

      Node *tmp = head;
      nd->next = tmp;
      head = nd;
      tail->next = head;
    }
    _size++;
    return true;
  }
  bool insert_end(int node) override {
    Node *nd = new Node(node);
    if (nd == nullptr)
      return false;
    if (_size == 0) {
      return insert_start(node);
    } else {
      tail->next = nd;
      tail = nd;
      tail->next = head;
    }
    _size++;
    return true;
  };
  bool insert_after(int node, int after) override {
    if (node == tail->data) {
      insert_end(node);
      return true;
    }
    if (_size == 0)
      return false;
    Node *new_node = new Node(after);
    if (new_node == nullptr)
      return false;
    Node *tmp = search(node);
    Node *next_node = tmp->next;
    tmp->next = new_node;
    new_node->next = next_node;
    _size++;
    return true;
  };
  bool insert_before(int node, int before) override {
    if (node == head->data) {
      insert_end(node);
      return true;
    }
    if (_size == 0)
      return false;
    Node *new_node = new Node(before);
    if (new_node == nullptr)
      return false;
    Node *tmp = head;
    do {
      tmp = tmp->next;
    } while (tmp->next->data != node);
    Node *next_node = tmp->next;
    tmp->next = new_node;
    new_node->next = next_node;
    _size++;
    return true;
  };
  bool remove_end() override {
    if (_size == 0)
      return false;
    Node *tmp = head;
    do {
      tmp = tmp->next;
    } while (tmp->next != tail);
    delete tmp->next;
    tmp->next = nullptr;
    tail = tmp;
    tail->next = head;
    _size--;
    return true;
  };
  bool remove_start() override {
    if (_size == 0)
      return false;
    Node *new_head = head->next;
    delete head;
    head = new_head;
    tail->next = head;
    _size--;
    return true;
  };
  void reverse() override {
    Node *prev = nullptr;
    Node *current = head;
    Node *temp = nullptr;
    do {
      temp = current->next;
      current->next = prev;
      prev = current;
      current = temp;
    } while (current != head);
    Node *t = head;
    head = tail;
    tail = t;
    tail->next = head;
  };

  void clear() override {
    if (_size == 0)
      return;
    Node *ptr = head->next;
    do {
      Node *tmp = ptr->next;
      delete ptr;
      ptr = tmp;
      _size--;
    } while (ptr != head);
    delete head;
    head = nullptr;
    tail = nullptr;
  };
  bool remove(int node) override {
    if (node == head->data) {
      return remove_start();
    }
    if (node == tail->data) {
      return remove_end();
    }
    if (_size == 0)
      return false;
    Node *tmp = head;
    do {
      tmp = tmp->next;
    } while (tmp->next->data != node);
    Node *next_to_deleted = tmp->next->next;
    delete tmp->next;
    tmp->next = next_to_deleted;
    _size--;
    return true;
  };
  bool set(int node, int new_node) override {
    if (_size == 0)
      return false;
    Node *nd = search(node);
    nd->data = new_node;
    return true;
  };
  /**
  * @brief copies nodes to array provided (arraysize must == list size)
  * @param int* pointer to an array
  * @return void

  */
  void to_array(int *ptr) const override {
    int j = 0;
    Node *tmp = head;
    do {
      ptr[j++] = tmp->data;
      tmp = tmp->next;
    } while (tmp != nullptr);
  };
  ~CircularLinkedList() { clear(); };
};
class DoublyLinkedList : public virtual AbstractList {
private:
  class Node {
  public:
    Node *prev;
    int data;
    Node *next;
    Node(int value) : prev(nullptr), data(value), next(nullptr){};
  };
  Node *head;
  Node *tail;
  int _size;

public:
  DoublyLinkedList() : head(nullptr), tail(nullptr), _size(0){};

  int size() const override { return _size; }
  Node *get_head() const { return head; }
  Node *get_tail() const { return tail; }
  void show() const override {
    Node *tmp = head;
    while (tmp != nullptr) {
      cout << tmp->data << " -> ";
      tmp = tmp->next;
    }
    cout << "END\n";
  }
  Node *search(int node) const {
    if (_size == 0)
      return nullptr;
    Node *tmp = head;
    while (tmp->data != node) {
      tmp = tmp->next;
    }
    return tmp;
  };

  bool insert_start(int node) override {
    Node *nd = new Node(node);
    if (nd == nullptr)
      return false;
    if (_size == 0) {
      head = nd;
      tail = nd;
      nd->prev = nd;
      nd->next = nd;
    } else {
      head->prev = nd;
      nd->next = head;
      nd = head;
    }
    _size++;
    return true;
  }
  bool insert_end(int node) override {
    Node *nd = new Node(node);
    if (nd == nullptr)
      return false;
    if (_size == 0) {
      return insert_start(node);
    } else {
      tail->next = nd;
      nd->prev = tail;
      tail = nd;
    }
    _size++;
    return true;
  };
  bool insert_after(int node, int after) override {
    if (node == tail->data) {
      insert_end(node);
      return true;
    }
    if (_size == 0)
      return false;
    Node *new_node = new Node(after);
    if (new_node == nullptr)
      return false;
    Node *tmp = search(node);
    Node *next_node = tmp->next;
    tmp->next = new_node;
    new_node->prev = tmp;
    new_node->next = next_node;
    next_node->prev = new_node;
    _size++;
    return true;
  };
  bool insert_before(int node, int before) override {
    if (_size == 0)
      return false;
    if (node == head->data) {
      insert_end(node);
      return true;
    }
    Node *new_node = new Node(before);
    if (new_node == nullptr)
      return false;
    Node *tmp = head;
    while (tmp->next->data != node) {
      tmp = tmp->next;
    }
    Node *next_node = tmp->next;
    tmp->next = new_node;
    new_node->prev = tmp;
    new_node->next = next_node;
    next_node->prev = new_node;
    _size++;
    return true;
  };
  bool remove_end() override {
    if (_size == 0)
      return false;

    Node *new_tail = tail->prev;
    delete tail;
    tail = new_tail;
    _size--;
    return true;
  };
  bool remove_start() override {
    if (_size == 0)
      return false;
    Node *new_head = head->next;
    delete head;
    new_head->prev = nullptr;
    head = new_head;
    _size--;
    return true;
  };
  /**
   * @brief reverses the list using (3 pointers approach) O(n)
   * @return void

  */
  void reverse() override {
    Node *prev = nullptr;
    Node *current = head;
    Node *next = nullptr;

    while (current != nullptr) {
      next = current->next;
      current->next = prev;
      if (prev) {
        prev->prev = current;
      }
      prev = current;
      current = next;
    }

    Node *tmp = head;
    head = tail;
    tail = tmp;
    head->prev = nullptr;
  };

  void clear() override {
    if (_size == 0)
      return;
    while (head != nullptr) {
      Node *temp = head->next;
      delete head;
      head = temp;
      _size--;
    }
    head = nullptr;
    tail = nullptr;
  };
  bool remove(int node) override {
    if (node == head->data) {
      return remove_start();
    }
    if (node == tail->data) {
      return remove_end();
    }
    if (_size == 0)
      return false;
    Node *tmp = head;
    while (tmp->next->data != node) {
      tmp = tmp->next;
    }
    Node *next_to_deleted = tmp->next->next;
    delete tmp->next;
    tmp->next = next_to_deleted;
    next_to_deleted->prev = tmp;
    _size--;
    return true;
  };
  bool set(int node, int new_node) override {
    if (_size == 0)
      return false;
    Node *nd = search(node);
    nd->data = new_node;
    return true;
  };
  /**
  * @brief copies nodes to array provided (arraysize must == list size)
  * @param int* pointer to an array
  * @return void

  */
  void to_array(int *ptr) const override {
    int j = 0;
    Node *tmp = head;
    while (tmp != nullptr) {
      ptr[j++] = tmp->data;
      tmp = tmp->next;
    }
  };
  ~DoublyLinkedList() { clear(); }
};
}; // namespace LinkedLists

namespace Queues {

class AbstractQueue {
private:
  int *ptr;
  int u_size;
  int t_size;

public:
  virtual void show() const = 0;
  virtual int front() const = 0;
  virtual int size() const = 0;
  virtual int rear() const = 0;
  virtual void enqueue(int item) = 0;
  virtual int dequeue() = 0;
  virtual bool is_empty() const = 0;
  virtual void clear() = 0;

  virtual ~AbstractQueue(){};
};

class ArrayQueue : public virtual AbstractQueue {
private:
  int *ptr;
  int u_size;
  int t_size;
  int _front;
  int _rear;

public:
  ArrayQueue(int size) : _front(-1), u_size(0), t_size(size), _rear(-1) {
    this->ptr = new int[size];
  };
  ArrayQueue() : _front(-1), u_size(0), t_size(DEF_DS_SIZE), _rear(-1) {
    this->ptr = new int[DEF_DS_SIZE];
  };
  int size() const override { return u_size; }
  void show() const override {
    if (u_size == 0) {
      cout << "END\n";
      return;
    }
    int i = _front;
    while (true) {
      cout << ptr[i] << " -> ";
      if (i == _rear)
        break;
      i = (i + 1) % t_size;
    }
    cout << "END\n";
  };
  int front() const override { return ptr[_front]; }
  int rear() const override { return ptr[_rear]; }
  bool is_empty() const override { return u_size == 0; }
  bool is_full() const { return u_size == t_size; }

  void reverse() { std::reverse(this->ptr, this->ptr + u_size); };

  void enqueue(int item) override {
    if (u_size >= t_size) {
      return;
    }
    if (u_size == 0) {
      _front++;
    }
    _rear = (_rear + 1) % t_size;
    ptr[_rear] = item;
    u_size++;
  }
  int search(int item) const {
    int i = 0;
    while (i < u_size) {
      if (ptr[i] == item)
        return i;
      i = (i + 1) % t_size;
    }
    return -1;
  }
  void sort() {
    _ags::m_sort(ptr, 0, u_size - 1, false);
    _front = 0;
    _rear = u_size - 1;
  }
  int dequeue() override {
    if (u_size == 0)
      return -1;
    int cpy;
    if (_front == _rear) {
      cpy = ptr[_front];
      _front = -1;
      _rear = -1;
      return cpy;
    }
    cpy = ptr[_front];
    _front = (_front + 1) % t_size;
    u_size--;
    return cpy;
  }
  void clear() override {
    u_size = 0;
    _front = -1, _rear = -1;
    delete[] ptr;
  }
  ~ArrayQueue() {
    u_size = 0;
    delete[] ptr;
  }
};

class LinkedQueue : public virtual AbstractQueue {
private:
  class Node {
  public:
    int data;
    Node *next;
    Node(int value) : data(value), next(nullptr){};
  };
  Node *head;
  Node *tail;
  int u_size;

  void show(Node *head) const {
    if (head == nullptr)
      return;
    cout << head->data << " -> ";
    show(head->next);
  }

  void enqueue(Node *&head, Node *&node) {
    if (head == nullptr) {
      head = node;
      tail = node;
      return;
    }
    if (head->next == nullptr) {
      head->next = node;
      tail = node;
      return;
    }
    enqueue(head->next, node);
  }
  void clear(Node *&head) {
    if (head == nullptr)
      return;
    Node *&temp = head->next;
    delete head;
    clear(temp);
  }
  void reverse(Node *&head, Node *prev = nullptr) {
    if (head == nullptr)
      return;
    Node *next = head->next;
    head->next = prev;
    prev = head;
    reverse(next, prev);
  }

public:
  LinkedQueue() : head(nullptr), tail(nullptr), u_size(0){};
  void show() const override {
    show(head);
    cout << "END\n";
  };
  int front() const override { return head->data; }
  int rear() const override { return tail->data; }
  bool is_empty() const override { return u_size == 0; }
  void enqueue(int item) override {
    Node *node = new Node(item);
    enqueue(head, node);
    u_size++;
  }
  int dequeue() override {
    if (u_size == 0) {
      return -1;
    }
    Node *temp = head->next;
    int cpy = head->data;
    delete head;
    head = temp;
    u_size--;
    return cpy;
  }
  void reverse() {
    reverse(head);
    Node *temp = head;
    head = tail;
    tail = temp;
  }
  int size() const override { return u_size; }
  void clear() override {
    clear(head);
    u_size = 0;
  }

  ~LinkedQueue() { clear(); }
};

class Deque : public virtual AbstractQueue {
private:
  int *ptr;
  int u_size;
  int t_size;

public:
  Deque(int size) : u_size(0), t_size(size) { this->ptr = new int[size]; }
  Deque() : u_size(0), t_size(DEF_DS_SIZE) { this->ptr = new int[DEF_DS_SIZE]; }

  int front() const override { return ptr[0]; }
  int rear() const override { return ptr[u_size - 1]; }
  int size() const override { return u_size; }
  bool is_empty() const override { return u_size == 0; }

  void show() const override {
    if (u_size == 0) {
      cout << "[]\n";
      return;
    }
    for (int i = 0; i < u_size; i++) {
      cout << ptr[i] << " -> ";
    }
    cout << "END\n";
  }

  void enqueue(int item) override {
    if (u_size >= t_size)
      return;
    ptr[u_size++] = item;
  }

  int dequeue() override {
    if (u_size == 0)
      return -1;
    int cpy = ptr[0];
    for (int i = 0; i < u_size; i++) {
      ptr[i] = ptr[i + 1];
    }
    u_size--;
    return cpy;
  }
  void enqueue_start(int item) {
    if (u_size >= t_size)
      return;
    for (int i = u_size; i >= 0; i--) {
      ptr[i] = ptr[i - 1];
    }
    ptr[0] = item;
    u_size++;
  }

  int dequeue_end() {
    if (u_size == 0)
      return -1;
    int cpy = ptr[u_size - 1];
    u_size--;
    return cpy;
  }

  void sort(int reverse=false) {
     if(u_size == 0 || u_size == 1) return;
     _ags::m_sort(ptr, 0, u_size-1, reverse);
  }

  void clear() override {
    u_size = 0;
    delete[] ptr;
  }

  ~Deque() { clear(); }
};

}; // namespace Queues

namespace Stacks {
class AbstractStack {
private:
  int *ptr;
  int u_size;
  int t_size;

public:
  AbstractStack() : ptr(nullptr), u_size(0), t_size(DEF_DS_SIZE){};
  AbstractStack(int size) : ptr(nullptr), u_size(0), t_size(size){};

  virtual void show() const = 0;
  virtual bool is_empty() const = 0;
  virtual int top() const = 0;
  virtual int bottom() const = 0;
  virtual int size() const = 0;
  virtual int search(int item) const = 0;
  virtual void reverse() = 0;
  virtual void push(int item) = 0;
  virtual int pop() = 0;
  virtual void clear() = 0;

  virtual ~AbstractStack() {
    u_size = 0;
    delete[] ptr;
  }
};

class ArrayStack : public virtual AbstractStack {
private:
  int *ptr;
  int u_size;
  int t_size;

public:
  ArrayStack() : ptr(nullptr), u_size(0), t_size(DEF_DS_SIZE) {
    this->ptr = new int[DEF_DS_SIZE];
  };
  ArrayStack(int size) : ptr(nullptr), u_size(0), t_size(size) {
    this->ptr = new int[size];
  };

  int size() const override { return u_size; }
  void show() const override {
    if (u_size == 0) {
      cout << "[]\n";
      return;
    }
    for (int i = u_size - 1; i >= 0; i--) {
      cout << ptr[i] << " -> ";
    }
    cout << "END\n";
  };

  bool is_empty() const override { return u_size == 0; };
  bool is_full() const { return u_size == t_size; };
  int top() const override { return ptr[u_size - 1]; };
  int bottom() const override { return ptr[0]; };
  void push(int item) override {
    if (u_size == t_size)
      return;
    ptr[u_size++] = item;
  };
  int pop() override {
    if (u_size == 0)
      return -1;
    int cp = ptr[0];
    for (int i = 0; i < u_size; i++) {
      ptr[i] = ptr[i + 1];
    }
    u_size--;
    return cp;
  };
  void reverse() override { std::reverse(ptr, ptr + u_size); }
  int search(int item) const override {
    if (u_size == 0)
      return -1;
    return _ags::binary_s(ptr, u_size, item);
  };
  void clear() override {
    u_size = 0;
    delete[] ptr;
  }

  ~ArrayStack() {
    u_size = 0;
    delete[] ptr;
  }
};
class LinkedStack : public virtual AbstractStack {
private:
  class Node {
  public:
    Node *prev;
    int data;

    Node *next;

    Node(int value) : prev(nullptr), data(value), next(nullptr){};
  };
  Node *head;
  Node *tail;
  int u_size;

public:
  LinkedStack() : u_size(0), head(nullptr), tail(nullptr){};

private:
  void show(Node *node) const {
    if (node == nullptr)
      return;
    show(node->next);
    cout << node->data << " -> ";
  };
  void linked_reverse(Node *node, Node *&prev) {
    if (node == nullptr)
      return;
    Node *next = node->next;
    node->next = prev;
    prev = node;
    linked_reverse(next, prev);
  }
  void push(Node *node, int item) {
    if (node == nullptr) {
      Node *n = new Node(item);
      head = n;
      tail = n;
      return;
    }
    if (node->next == nullptr) {
      Node *pushed = new Node(item);
      node->next = pushed;
      pushed->prev = node;
      tail = pushed;
      return;
    }
    push(node->next, item);
  }
  Node *search(Node *node, int target) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->data == target) {
      return node;
    }
    return search(node->next, target);
  }
  void clear(Node *&node) {
    if (node == nullptr) {
      return;
    }
    Node *&nxt = node->next;
    delete node;
    clear(nxt);
  }

public:
  int size() const override { return u_size; }
  bool is_empty() const override { return u_size == 0; }
  int top() const override { return tail->data; };
  int bottom() const override { return head->data; }

  void show() const override {
    if (u_size == 0) {
      cout << "[]\n";
      return;
    }
    show(head);
    cout << "END\n";
  };

  void push(int data) override {
    push(head, data);
    u_size++;
  }
  int pop() override {
    if (u_size == 0)
      return -1;
    Node *temp = tail->prev;
    int cpy = tail->data;
    delete tail;
    tail = temp;
    tail->next = nullptr;
    u_size--;
    return cpy;
  }

  int search(int item) const override {
    Node *target = search(head, item);
    return target != nullptr ? target->data : -1;
  }

  void reverse() override {
    Node *new_head = nullptr;
    linked_reverse(head, new_head);
    Node *tmp = head;
    head = tail;
    tail = tmp;
  }

  void clear() override {
    clear(head);
    u_size = 0;
  }

  ~LinkedStack() { clear(); }
};
class QueueStack : public virtual AbstractStack {
private:
  Queues::ArrayQueue q;

public:
  QueueStack(int size) { q = Queues::ArrayQueue(size); }
  void show() const override { q.show(); }
  int bottom() const override { return q.front(); }
  int top() const override { return q.rear(); }
  bool is_empty() const override { return q.is_empty(); }
  int size() const override { return q.size(); }
  int pop() override { return q.dequeue(); }
  void push(int item) override { q.enqueue(item); }
  int search(int item) const override { return q.search(item); }
  void reverse() override { q.reverse(); }
  void clear() override { q.clear(); }
  ~QueueStack() { q.clear(); }
};
// namespace Array
} // namespace Stacks

// TODO: Implement Various Queues

int main(void) {

  return 0;
}