/*  Author: Alexandros Katsarakis
*   Creation Date: 30/4/2020
*   Last Modified: 05/5/2020 By Alexandros Katsarakis
*   Requirements for class T: operation overloading on <,<<
*/

#pragma once

#include <functional>
#include <iostream>
#include <cassert>


template<class T>
class GenericListNode {

    public:
    T value;
    GenericListNode* next;

    GenericListNode(T val):value(val){
      next = NULL;
    }
    
    void printValue(){
      std::cout << value;
    }

};

template<class T>
class GenericList {

  using Func = std::function<bool(T)>;
  using PrintFunc = std::function<void()>;
  using CondFunc = std::function<void()>;
  public:
  
  const Func simpleInsert = ([this](T val){
    auto* newNode = this->newNode(val);
    newNode->next = getHead();
    setHead(newNode);
    return true;
  });

  const Func simpleRemove = ([this](T val){
    auto* runner = getHead();
    auto* prev = runner;
    if(!runner)return false;
    if(!(runner->value < val) && !(val < runner->value)){
      setHead(runner->next);
      delete runner;
      return true;
    }
    while(runner){
      if(!(runner->value < val) && !(val < runner->value)){
        prev->next = runner->next;
        delete runner;
        return true;
      }
      prev = runner;
      runner = runner->next;
    }
    return false;
  });

  const Func simpleSearch = ([this](T val){
    auto* runner = getHead();
    if(!runner)return false;
    while(runner){
      if(!(runner->value < val) && !(val < runner->value))return true;
      runner = runner->next;
    }
    return false;
  });

  const PrintFunc simplePrint = ([this](){
    auto* runner = getHead();
    while(runner){
      runner->printValue();
      std::cout << ",";
      runner = runner->next;
    }
    std::cout << std::endl;
  });

  const CondFunc emptyCond = ([](){});

  const Func ascendingInsert = ([this](T val){
    auto* newNode = this->newNode(val);
    auto* runner = getHead();
    if(!runner){
      setHead(newNode);
      return true;
    }
    if(val < runner->value){
      newNode->next = runner;
      setHead(newNode);
      return true;
    }
    while(runner->next && runner->next->value < val){
      runner = runner->next;
    }
    newNode->next = runner->next;
    runner->next = newNode;
    return true;
  });

  const Func ascendingRemove = ([this](T val){
    auto* runner = getHead();
    auto* prev = runner;
    if(!runner)return false;
    if(!(runner->value < val) && !(val < runner->value)){
      setHead(runner->next);
      delete runner;
      return true;
    }
    while(runner && runner->value < val){
      if(!(runner->value < val) && !(val < runner->value)){
        prev->next = runner->next;
        delete runner;
        return true;
      }
      prev = runner;
      runner = runner->next;
    }
    return false;
  });

  const Func descendingInsert = ([this](T val){
    auto* newNode = this->newNode(val);
    auto* runner = getHead();
    if(!runner){
      setHead(newNode);
      return true;
    }
    if(runner->value < val){
      newNode->next = runner;
      setHead(newNode);
      return true;
    }
    while(runner->next && val < runner->next->value){
      runner = runner->next;
    }
    newNode->next = runner->next;
    runner->next = newNode;
    return true;
  });

  const Func descendingRemove = ([this](T val){
    auto* runner = getHead();
    auto* prev = runner;
    if(!runner)return false;
    if(!(runner->value < val) && !(val < runner->value)){
      setHead(runner->next);
      delete runner;
      return true;
    }
    while(runner){
      if(!(runner->value < val) && !(val < runner->value)){
        prev->next = runner->next;
        delete runner;
        return true;
      }
      if(runner->value < val){
        break;
      }
      prev = runner;
      runner = runner->next;
    }
    return false;
  });

  private:
  Func      insertLN,   removeLN,   searchLN;
  CondFunc  insertPre,  removePre,  searchPre;
  CondFunc  insertPost, removePost, searchPost;
  PrintFunc printL;

  GenericListNode<T>* head;
  size_t size;

  public:

  GenericList(){
    insertLN   = simpleInsert;
    removeLN   = simpleRemove;
    searchLN   = simpleSearch;
    insertPre  = emptyCond;
    insertPost = emptyCond;
    removePre  = emptyCond;
    removePost = emptyCond;
    searchPre  = emptyCond;
    searchPost = emptyCond;
    printL     = simplePrint;
    head       = NULL;
    size       = 0;
  }

  GenericListNode<T>* getHead(){
    return head;
  }

  void setHead(GenericListNode<T>* node){
    head = node;
  }

  size_t getSize(){
    return size;
  }

  bool insert(const T& val){
    insertPre();
    auto retVal = insertLN(val);
    if(retVal)size++;
    insertPost();
    return retVal;
  }

  bool remove(const T& val){
    removePre();
    auto retVal = removeLN(val);
    if(retVal)size--;
    removePost();
    return retVal;
  }

  bool search(const T& val){
    searchPre();
    auto retVal = searchLN(val);
    searchPost();
    return retVal;
  }

  void setInsert(const Func& f){
    insertLN = f;
  }

  void setInsertPre(const CondFunc& f){
    insertPre = f;
  }

  void setInsertPost(const CondFunc& f){
    insertPost = f;
  }

  void setRemove(const Func& f){
    removeLN = f;
  }

  void setRemovePre(const CondFunc& f){
    removePre = f;
  }

  void setRemovePost(const CondFunc& f){
    removePost = f;
  }

  void setSearch(const Func& f){
    searchLN = f;
  }

  void setSearchPre(const CondFunc& f){
    searchPre = f;
  }

  void setSearchPost(const CondFunc& f){
    searchPost = f;
  }

  void setPrint(const PrintFunc& f){
    printL = f;
  }

  void print(){
    printL();
  }

  GenericListNode<T>* newNode(const T& val){
    return new GenericListNode<T>(val);
  }

  void forEach(const std::function<void(T*)>& f){
    auto* runner = head;
    while(runner){
      f(&runner->value);
      runner = runner->next;
    }
  }

  const T& operator[] (size_t index){
    auto* runner = head;
    assert(index < this->size);
    while(index > 0){
      index--;
      runner = runner->next;
    }
    return runner->value;
  }

  void empty(){
    auto* runner = head;
    auto* prev = runner;
    for(size_t i = 0;i < size;++i){
      prev = runner;
      delete runner;
      runner = prev->next;
    }
    head = NULL;
    size = 0;
  }

  bool operator< (GenericList<T>& other){
    return size < other.getSize();
  }

  friend std::ostream& operator<< (std::ostream& os, const GenericList<T>& me){
    auto* runner = me.head;
    while(runner){
      os << runner->value << "->";
      runner = runner->next;
    }
    return os;
  }

  void operator+=(GenericList<T>& other){
    other.forEach([&](T* val){
      insert(*val);
    });
  }

  ~GenericList(){
    auto* runner = head;
    auto* prev = runner;
    for(size_t i = 0;i < size;++i){
      prev = runner;
      assert(runner);
      delete runner;
      runner = prev->next;
    }
  }

};