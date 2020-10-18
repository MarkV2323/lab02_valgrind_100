#include "person.h"
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

Person::Person(char *name, Person* father, Person* mother){
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->father = father;
    this->mother = mother;
    capacity = 1;
    numChildren = 0;
    children = new Person*[capacity];
}

Person::~Person(){
    delete [] children;
    delete [] this->name;
}

void Person::addChild(Person *newChild){
    if(numChildren == capacity) expand(&children, &capacity);
    children[numChildren++] = newChild;
}

void Person::printAncestors(){
    cout << endl << "Ancestors of " << name << endl;
    printLineage('u', 0);
}

void Person::printDecendents(){
    cout << endl << "Decendents of " << name << endl;
    printLineage('d', 0);
}

void Person::printLineage(char dir, int level){
    char *temp = compute_relation(level);

    if(dir == 'd'){
        for(int i = 0; i < numChildren; i++){
            cout << temp << "child: " << children[i]->getName() << endl;
            children[i]->printLineage(dir, level + 1);
        }
    } else {
        if(mother){
            cout << temp << "mother: " << mother->getName() << endl;
            mother->printLineage(dir, level + 1);
        }
        if(father){
            cout << temp << "father: " << father->getName() << endl;
            father->printLineage(dir, level + 1);
        }
    }

    // frees temp
    delete [] temp;
}

/* helper function to compute the lineage
* if level = 0 then returns the empty string
* if level >= 1 then returns ("great ")^(level - 1) + "grand "
*/
char* Person::compute_relation(int level){

    if(level == 0) {
        char* temp = new char[2];
        memset(temp, '\0', 2);
        return strcpy(temp, "");
    }

    int tempCap = strlen("grand ") + 1;
    char* temp = new char[tempCap];
    memset(temp, '\0', tempCap);
    strcpy(temp, "grand ");
    
    for(int i = 2; i <= level; i++){
        char *temp2 = new char[strlen("great ") + strlen(temp) + 1];
        strcat(strcpy(temp2, "great "), temp);
        // free temp because we already copied it's data above
        delete [] temp;
        // reassign temp to be equal to temp2
        temp = temp2;
    }
    return temp;
}

/* non-member function which doubles the size of t
 * NOTE: t's type will be a pointer to an array of pointers
 */
void expand(Person ***t, int *MAX){
  Person **temp = new Person*[2 * *MAX]();
  // copies *t data into temp.
  memcpy(temp, *t, *MAX * sizeof(**t));
  // we've copied the data inside of *t to temp, its now time to free it.
  delete [] *t;
  *MAX *= 2;
  *t = temp;
}
