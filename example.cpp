#include "genericList.h"

int main(){

////Simple Use
    GenericList<int> gl1;

    gl1.insert(5);
    gl1.insert(10);
    gl1.insert(7);

    gl1.print();

////Changed Order of insert and remove

    GenericList<int> gl2;

    gl2.setInsert(gl2.ascendingInsert);
    gl2.setRemove(gl2.ascendingRemove);

    gl2.insert(5);
    gl2.insert(10);
    gl2.insert(7);

    gl2.print();

////Do something on each value

    gl2.forEach([](int* num){
        *num = *num + 1;
    });

////Set custom print

    gl2.setPrint([&gl2](){
        auto* runner = gl2.getHead();
        int counter = 0;
        while(runner){
            std::cout << "iteration[" << counter << "] = " << runner->value << std::endl;
            runner = runner->next;
            counter++;
        }
    });

    gl2.print();

////Use different types

    GenericList<std::string> glstring;
    glstring.insert("one");
    glstring.insert("two");
    glstring.insert("three");

    glstring.print();

////Working with pre/post condition
    
    GenericList<int> gl3;

    gl3.setRemovePre([&gl3](){
        if(gl3.getSize() < 1)std::cout << "Trying to remove from empty list" << std::endl;
    });

    gl3.remove(3);

    gl3.insert(3);
    gl3.insert(4);
    gl3.remove(4);
    gl3.print();
    gl3.remove(3);
    gl3.remove(6);

}