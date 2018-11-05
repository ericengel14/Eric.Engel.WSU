/*
        Eric Engel
        Cpts223
        Btree assignment

        driver program that takes in the BLOCK_SIZE during compile time and uses it to figure out the max number of keys that can 
        fit into that size, and passes that along with a function pointer for the comparison function to the Btree constructor.

        compile using 
        c++ Btree Btree.cpp -D BLOCK_SIZE=20    

        Driver program is set up to show the insertion of 15 items and then deletion of 3 items using the 
        block size of 20. Program will owrk correctly with other Block Sizes but the driver program
        will not demonstrate this.
*/

#include <iostream>
#include <list>
#include "Btree.h"
#include "compareFunc.h"

int main(int argc, char* argv[])
{
        int max;
        int (*myFunc)(int*,int*);

        max = BLOCK_SIZE/sizeof(int);

        //cout << "Max = " << max << endl;

        myFunc = &compareFunc;

        Btree <int>tree(max,myFunc);

        int a = 40;
        int b = 50;
        int c = 70;
        int d = 20;
        int e = 10;
        int f = 80;
        int g = 9;
        int h = 8;
        int i = 7;
        int j = 6;
        int k = 5;
        int l = 4;
        int m = 3;
        int n = 2;
        int o = 1;

        tree.insert(&a);
        tree.insert(&b);
        tree.insert(&c);
        tree.insert(&d);
        tree.insert(&e);
        tree.insert(&f);
        tree.insert(&g);
        tree.insert(&h);
        tree.insert(&i);
        tree.insert(&j);
        tree.insert(&k);
        tree.insert(&l);
        tree.insert(&m);
        tree.insert(&n);
        tree.insert(&o);

        cout << "Left most Node" << endl;
        tree.search(&m);
        cout << "Right node off of 4" << endl;
        tree.search(&i);
        cout << "Right node off of 8" << endl;
        tree.search(&d);
        cout << "Right node off of 40" << endl;
        tree.search(&f);

        tree.deleteB(&n);
        tree.deleteB(&o);
        tree.deleteB(&m);

        cout << endl;
        cout << "After Deletions" << endl;

        //tree.search(&a);
        //tree.search(&b);
        //tree.search(&c);
        cout << "Left most Node" << endl;
        tree.search(&d);
        //tree.search(&e);
        cout << "Right node off of 8" << endl;
        tree.search(&f);
        //tree.search(&g);
        //tree.search(&h);
        cout << "Right node off of 40" << endl;
        tree.search(&i);
        //tree.search(&j);
        //tree.search(&k);
        //tree.search(&l);
        //tree.search(&m);
        //tree.search(&n);
        //tree.search(&o);


        //tree.printTree();

        return 0;
}