/*
        Header File containing class implementation of templated Btree

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

        tree.deleteB(&m);

        tree.search(&a);
        tree.search(&b);
        tree.search(&c);
        tree.search(&d);
        tree.search(&e);
        tree.search(&f);
        tree.search(&g);
        tree.search(&h);
        tree.search(&i);
        tree.search(&j);
        tree.search(&k);
        tree.search(&l);
        tree.search(&m);
        tree.search(&n);
        //tree.search(&o);


        //tree.printTree();

        return 0;
}