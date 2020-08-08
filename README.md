# General List

General List Support so far:

  - Generic for every type using c++ templates (requirement: supporting "<" operator)
  - Add pre/post conditions on insert/remove/search
  - Use customized or existing insert/remove/search functions with c++ std::function model

Examples can be found [here](https://github.com/alexkatsarakis/genericList/example.cpp)

# API
##### General Purpose 
 - getHead() -> return the first item of the list
 - setHead() -> set the first item of the list. *!!used rarely*
 - getSize() -> return the size of the list
##### Main functionality
 - setInsert(std::function[&thelist](Type val){}) -> set the insert function that will be invoked to add the item to the list when using 
 - insert(Type val) -> insert an item to the list based on the function given by the user or the default
 - setRemove(std::function[&thelist](Type val){}) -> set the remove function that will be invoked to remove the item from the list when remove is being used
 - remove(Type val) -> remove the item with the value "val" from the list
 - setSearch(std::function[&thelist](Type val){}) -> set the search function that will be invoked to search for the item on the list when search is being used
 - search(Type val) -> search the item with value "val" on the list
 - setPrint(std::function[&thelist] (){}) -> set the print function that will be invoked when the print is being used.
 - print() -> print the list with default function or the one set by the user with setPrint
 - forEach(std::function[](Type* val){}) -> used to iterate through all the values on the list
 ##### Syntactic Sugar
 - list1 += list2 -> add all list2 items in list1
 - list[3] -> will return the 4th item on the list O(n)
 - list1 < list2 -> will return true if list1 has smaller size than list2
 - newNode(const Type& val) -> will return a new list node ready to be added to the list
 - empty() -> will empty the list 

# Usage

###### Fast usage without any configurations
```c++
#include "genericList.h"

int main(){
    GenericList<int> gl1;

    gl1.insert(5);
    gl1.insert(10);
    gl1.insert(7);

    gl1.print(); //Output 7,10,5
}
```

###### Used premade insert/remove functions
```c++
#include "genericList.h"

int main(){
    GenericList<int> gl2;

    gl2.setInsert(gl2.ascendingInsert);
    gl2.setRemove(gl2.ascendingRemove);

    gl2.insert(5);
    gl2.insert(10);
    gl2.insert(7);

    gl2.print(); //Output 5,7,10
}
```
###### Used premade insert/remove functions
```c++
#include "genericList.h"

int main(){
    GenericList<int> gl2;

    gl2.setInsert(gl2.ascendingInsert);
    gl2.setRemove(gl2.ascendingRemove);
    gl2.insert(5);
    gl2.insert(10);
    gl2.insert(7);

    gl2.forEach([](int* num){
        *num = *num + 1;
    });
    
    gl2.setPrint([&gl2](){
        auto* runner = gl2.getHead();
        int counter = 0;
        while(runner){
            std::cout << "iteration[" << counter << "] = " << runner->value << std::endl;
            runner = runner->next;
            counter++;
        }
    });

    gl2.print(); //iteration[0] = 6
                 //iteration[1] = 8
                 //iteration[2] = 11
}
```

###### Also use the pre/post conditions
```c++
#include "genericList.h"

int main(){
    GenericList<int> gl3;

    gl3.setRemovePre([&gl3](){
        if(gl3.getSize() < 1)std::cout << "Trying to remove from empty list" << std::endl;
    });

    gl3.remove(3); //Will print "Trying to remove from empty list" due to remove precondition (also can use assert for easier debug)

    gl3.insert(3);
    gl3.insert(4);
    gl3.remove(4);
    gl3.print(); //Will print "3," as it uses the default print function
    gl3.remove(3);
    gl3.remove(6); //Will print "Trying to remove from empty list" because list is now empty again
}
```

License
----

Apache License 2.0