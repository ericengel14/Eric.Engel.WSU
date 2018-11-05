/*
        Eric Engel
        CPTS 223
        Btree

        Header File containing class implementation of templated Btree
*/

#pragma once

#include <iostream>
#include <list>

using namespace std;

template <typename T>
class Node
{
public:
        Node(int mKey,T (*myFunc)(T*,T*));

        Node* prev;
        Node* lChild;
        int max;
        int min;

        int (*compareFunc)(T*,T*);

        class Key
        {
        public:
                Key();
                T data;
                Node<T>* rChild;
        };

        list<Key> first;

        int extra();
        bool youngerBrother(T *element);
        bool olderBrother(T *element);
        int checkEmpty();
        void deleteLeaf(T *deletion);
        Key* findMatch(T *search);
        int isMatch(T *search);
        int getMax() {return max;};
        Node* traverseLevel(T *add);
        void pushKey(Key *key);
        int checkFull();
        typename list<Key>::iterator iPosition(T *add);
        //int compareFunc(int *i,int *j);
        void addKey(T *add);

        typename list<Key>::iterator it1;
        typename Node<T>::Key* nRoot;

//friend class Btree;
};

template <typename T>
class Btree
{
public:
        Btree(int mKeys, T (*myFunc)(T*,T*));
        //~Btree();

        Node<T> *root;
        int keys;
        
        int (*compareFunction)(T*,T*);

        void mergeOlder(Node<T> *node, Node<T> *parent);
        void mergeYounger(Node<T> *node, Node<T> *parent);
        void marriage(Node<T> *node);
        void setTemp(typename Node<T>::Key *keyD);
        void swap(typename Node<T>::Key *keyD, typename Node<T>::Key *keyS, T *deletion);
        typename Node<T>::Key* successor(Node<T> *node, T *deletion);
        void theft(bool brother, Node<T> *node, Node<T> *parent);
        int caseJoint(Node<T> *node);
        void checkMin(Node<T> *temp);
        void deleteB(T *deletion);
        void search(T *search);
        void printTree();
        void checkBreak(Node<T> *temp);
        void breakRoot(Node<T> *node);
        void breakNode(Node<T> *node);
        Node<T>* iTraversal(T *add);
        void insert(T *add);
        int getKeys() {return keys;};

        Node<T>* temporary;
};

//Constructor for Btree class
template <typename T>
Btree<T>::Btree(int mKeys,T (*myFunc)(T*,T*))
{
        compareFunction = myFunc;
        root = NULL;
        temporary = NULL;
        keys = mKeys;
}

//Costructor for Node Class
template <typename T>
Node<T>::Node(int mKey,T (*myFunc)(T*,T*))
{
        compareFunc = myFunc;
        prev = NULL;
        lChild = NULL;
        it1 = first.begin();
        nRoot = NULL;
        max = mKey;
        min = max/2;
}

//Constructor for Key Class
template <typename T>
Node<T>::Key::Key()
{
        rChild = NULL;
}

//function to print out tree
template <typename T>
void Btree<T>::printTree()
{       
        Node<T> *node;
        Node<T> *temp;
        node = root;
        temp = root;
        node->it1 = node->first.begin();

        for(node->it1 = node->first.begin(); node->it1 != node->first.end(); ++node->it1){     //Counting how many elements are in the list
        cout << (*node->it1).data << ", ";
        }  
        cout << endl;

        while(temp->lChild != NULL)
        {
                temp = node->lChild;
                for(temp->it1 = temp->first.begin(); temp->it1 != temp->first.end(); ++temp->it1)
                {
                        cout << (*temp->it1).data << ", ";
                }
                cout << "    ";
                /*for(node->it1 = node->list.begin(); node->it1 != node->list.end(); ++node->it1)
                {
                        temp = (*temp->it1).rChild;
                        for(temp->it1 = temp->list.begin(); temp->it1 != temp->list.end(); ++temp->it1)
                        {
                                cout << (*temp->it1).data << ", ";
                        }
                        cout << "    ";
                }*/
        }
}

//Function to look for element inside Node
template <typename T>
int Node<T>::isMatch(T *search)
{
        //cout << "isMatch" << endl;
        int compare = 1;
        for(it1 = first.begin(); it1 != first.end(); ++it1)
        {
                cout << (*it1).data << ", ";
                compare = compareFunc(search, &(*it1).data);
                if(compare == 0)
                {
                        cout << endl << endl;
                        return compare;
                }
        }
        cout << endl;
        return compare;
}

//Function to look for element inside Node and return an iterator to the found item
template <typename T>
typename Node<T>::Key* Node<T>::findMatch(T *search)
{
        int compare = 1;
        for(it1 = first.begin(); it1 != first.end(); ++it1)
        {
                compare = compareFunc(search, &(*it1).data);
                if(compare == 0)
                {
                        return &(*it1);
                }
        }
        return &(*it1);
}

//Function to search for an element in the Btree
template <typename T>
void Btree<T>::search(T *search)
{
        //cout << "Searching for " << *search << endl;
        Node<T> *temp = root;
        int compare = 1;

        while(compare != 0 && temp != NULL)
        {
                compare = temp->isMatch(search);                //Looking for element inside temp node
                if(compare != 0)
                {
                        temp = temp->traverseLevel(search);     //If element not found in node traverse to lower level to search again
                }             
        }
        if(temp == NULL)
        {
                cout << "Element to search for was not found" << endl;          //Element was not found in Btree
        }
        else if(compare == 0)
        {
                temporary = temp;               //Found Node containing searched for element and saving pointer to that node
        }
}

//Function to check if node is full
//Returns a 1 if full or a 0 if not
template <typename T>
int Node<T>::checkFull()
{
        //cout << "Calling check full" << endl;
        int isFull = 0;
        int count = 0;

        for(it1 = first.begin(); it1 != first.end(); ++it1, count++){     //Counting how many elements are in the list
        //cout << "Element " << (*it2).data << endl;
        }       

        //cout << "Count = " << count << endl;

        if(count > max)                         //If list is full
        {
                isFull = 1; 
        }

        return isFull;
}

//Function to call checkFull function and if it is full call function to break node
template <typename T>
void Btree<T>::checkBreak(Node<T> *temp)
{
        int isFull = 0;

        isFull = temp->checkFull();
        if(isFull == 1)
        {
                //cout << "Node is full" << endl;
                breakNode(temp);
        }
}

//Function to help traversal find which pointer to take to next node
template <typename T>
Node<T>* Node<T>::traverseLevel(T *add)
{
        int compare;
        it1 = first.begin();

        compare = compareFunc(add, &it1->data);
        if(compare == -1)
        {
                return lChild;
        } 

        for(it1 = first.begin(); it1 != first.end(); ++it1)
        {
                compare = compareFunc(add, &it1->data);
                if(compare == -1)
                {       
                        it1--;
                        return (*it1).rChild;
                }
        }
        it1--;
        return (*it1).rChild;
}


//Function to traverse through tree until the correct place to insert new element
template <typename T>
Node<T>* Btree<T>::iTraversal(T *add)
{
        Node<T> *temp = root;                                     //Pointer to use for iterating through tree

        while (temp->lChild != NULL)
        {
                temp = temp->traverseLevel(add);             //Create function for traversal position
                //Need to add to check to see if it is smaller then first element meaning we take Node->lChild
        }
        return temp;
}

//Function to find position to add new element into Node
//Return iterator pointer to position to be inserted into
template <typename T>
typename list<typename Node<T>::Key>::iterator Node<T>::iPosition(T *add)
{
        int compare;
        for(it1 = first.begin(); it1 != first.end(); ++it1)
        {
                compare = compareFunc(add, &it1->data);
                if(compare == -1)
                {
                        return it1;
                }
        }
        return it1;
}

//Function to break root node
template <typename T>
void Btree<T>::breakRoot(Node<T> *node)
{
        int count = 1;
        typename std::list<typename Node<T>::Key>::iterator it2 = node->first.begin();
        typename std::list<typename Node<T>::Key>::iterator it3;
        Node<T> *sibling = new typename Node<T>::Node(keys, compareFunction);
        Node<T> *parent  = new typename Node<T>::Node(keys, compareFunction);

        root = parent;
        parent->lChild = node;

        while(count <= node->min)
        {
                it2++;
                count++;
        }
        it3 = it2;

        sibling->lChild = (*it2).rChild;
        (*it2).rChild = sibling;
        sibling->prev = parent;
        node->prev = parent;
        parent->pushKey(&(*it2)); 
        it2++;                                  //Calling function to add middle object to parent node 
        for(it2; it2 != node->first.end(); ++it2)
        {
                sibling->pushKey(&(*it2));      //Adding all the rest of the elements to the right of the middle to the new node
        } 
        node->first.erase(it3, it2);
}

//Function to preform addKey but taking a key as perameter not just the element to be added
template <typename T>
void Node<T>::pushKey(Key *key)
{
        int compare;

        it1 = iPosition(&key->data);          //Finding poisition inside node to add new element
        first.insert(it1, *key);        //Inserting Key into list 
}

//Function to break a node with too many elements
template <typename T>
void Btree<T>::breakNode(Node<T> *node)
{
        int count = 1;
        typename std::list<typename Node<T>::Key>::iterator it2 = node->first.begin();
        typename std::list<typename Node<T>::Key>::iterator it3;
        Node<T> *sibling = new typename Node<T>::Node(keys, compareFunction);
        Node<T> *parent  = node->prev; 

        if(node == root)
        {
                breakRoot(node);
        }
        else
        {
                while(count <= node->min)
                {
                        it2++;
                        count++;
                }
                it3 = it2;

                sibling->lChild = (*it2).rChild;
                (*it2).rChild = sibling;
                sibling->prev = parent;
                parent->pushKey(&(*it2));                 //Calling function to add middle object to parent node 
                checkBreak(parent);                 //Function to test if parent has to many memebers and call function to break if needed
                it2++;
                for(it2; it2 != node->first.end(); ++it2)
                {
                        sibling->pushKey(&(*it2));      //Adding all the rest of the elements to the right of the middle to the new node
                } 
                node->first.erase(it3, it2);
        }
}

//Function to addKey to node
template <typename T>
void Node<T>::addKey(T *add)
{
        Key *key = new Key();
        int compare;

        key->data = *add;

        if(nRoot == NULL)
        {
                first.insert(it1, *key);                //Since nRoot is NULL element must be first element into node
                nRoot = key;    
        }
        else
        {
                it1 = iPosition(add);          //Finding poisition inside node to add new element
                first.insert(it1, *key);        //Inserting Key into list 
        }

}

//Function to insert item into Btree
template <typename T>
void Btree<T>::insert(T *add)
{
        //cout << "Inserting " << *add << endl;

        Node<T> *temp;
        temp = root;

        if(root == NULL)                        //Fisrt element added to bTree
        {
                //cout << "a" << endl;
                Node<T> *node = new typename Node<T>::Node(keys,compareFunction);
                root = node;
                node->addKey(add);              //Call function to add element to tree
        }
        else if(temp->lChild == NULL)           //Root is only element in bTree
        {
                //cout << "b" << endl;
                temp->addKey(add);
                checkBreak(temp);
        }
        else
        {
                //cout << "c" << endl;
                temp = iTraversal(add);
                temp->addKey(add);
                checkBreak(temp);
        }

}

//Function to delete leaf level Key
template <typename T>
void Node<T>::deleteLeaf(T *deletion)
{
        cout << "Deleting element " << *deletion << endl;
        int compare = 1;
        for(it1 = first.begin(); it1 != first.end(); ++it1)
        {
                //cout << "Data = " << (*it1).data << endl;
                compare = compareFunc(deletion, &(*it1).data);
                if(compare == 0)
                {
                        first.erase(it1);
                        return;
                }
        }
        //cout << "Finished deleting leaf" << endl;
}

//function to check if current Node has an extra key
template <typename T>
int Node<T>::extra()
{
        int extra = 0;
        int count = 0;

        for(it1 = first.begin(); it1 != first.end(); ++it1, ++count){
        }     //Counting how many elements are in the list

        if(count > min)                         //If node has an extra key
        {
                extra = 1; 
        }

        return extra;
}

//Function to check if left sibling has an extra key to steal
//returns a 0 if theft is possible from youngerBrother
template <typename T>
bool Node<T>::youngerBrother(T *element)
{
        //cout << "youngerBrother" << endl;
        Node *node;
        bool freeStuff = 0;
        typename list<Key>::iterator it2;

        it1 = iPosition(element);
        it1--;
        it1--;
        node = (*it1).rChild;
        
        freeStuff = node->extra();                  //check if sibling has extra keys

        return !freeStuff;
}

//Function to check if right sibling has an extra key
//Returns a 1 if theft is possible from olderBrother
template <typename T>
bool Node<T>::olderBrother(T *element)
{
        //cout << "older Brother" << endl;
        Node *node;
        bool freeStuff = 0;

        it1 = iPosition(element);
        node = (*it1).rChild;
        
        freeStuff = node->extra();                  //check if sibling has extra keys

        return freeStuff;
}

//Function to check if you can steal a key from neighbor node
//Returns -1 if left sibling can be stolen from
//Returns 1 if right sibling can be stolen from
//Returns 0 if neither right or left sibling can be stolen from
template <typename T>
int Btree<T>::caseJoint(Node<T> *node)
{
        //cout << "casing the joint" << endl;
        bool sibling;
        int stealFrom = 0;

        Node<T> *parent = node->prev;
        for(parent->it1 = parent->first.begin(); parent->it1 != parent->first.end(); ++parent->it1){}
        parent->it1--;
        node->it1 = node->first.begin();

        if(parent->lChild == node)              //check if node is left child so it does not have a left sibling
        {
                //cout << "no left sibling" << endl;
                sibling = parent->olderBrother(&(*node->it1).data);       //check if sibling to the right has an extra key
                if (sibling == 1)
                {
                        stealFrom = 1;
                        theft(sibling, node, parent);
                }
        }
        else if((*parent->it1).rChild == node)          //Node has no right siblings
        {
                //cout << "no right sibling" << endl;
                sibling = parent->youngerBrother(&(*node->it1).data);
                if(sibling == 0)
                {
                        stealFrom = 1;
                        theft(sibling, node, parent);
                }
        }
        else
        {
                //cout << "2 siblings" << endl;
                sibling = parent->olderBrother(&(*node->it1).data);
                if(sibling == 1)
                {
                        theft(sibling, node, parent);
                        stealFrom = 1;
                }
                else
                {
                        sibling = parent->youngerBrother(&(*node->it1).data);
                        //cout << "sibling = " << sibling << endl;
                        if(sibling == 0)
                        {
                                stealFrom = 1;
                                theft(sibling, node, parent);
                        }
                }
        }
        //cout << "Steal From = " << stealFrom << endl;
        return stealFrom;
}

//Functino to steal key from neighbor node
//Takes a bool argument 0 if younger brother 1 if older brother
template <typename T>
void Btree<T>::theft(bool brother, Node<T> *node, Node<T> *parent)
{
        cout << "Stealing a node from sibling" << endl;
        Node<T> *sibling;
        typename Node<T>::Key *key = new typename Node<T>::Key;

        if (brother == 1)
        {
                //cout << "Stealing from older brother" << endl;
                node->it1 = node->first.begin();
                parent->it1 = parent->iPosition(&(*node->it1).data);
                key->data = ((*parent->it1).data);                     //Setting data of new key to equal parent data
                sibling = (*parent->it1).rChild;

                for(node->it1 = node->first.begin(); node->it1 != node->first.end(); ++node->it1){};    //Getting iterator to end of node
                node->first.insert(node->it1, *key);             //Inserting new key at end of node with data from parent key

                sibling->it1 = sibling->first.begin();
                ((*parent->it1).data) = ((*sibling->it1).data);        //Setting parent data to equal first element of sibling
                sibling->first.erase(sibling->it1);                                       //Deleting first element of sibling
        } 
}

//Function to marge with right sibling
template <typename T>
void Btree<T>::mergeOlder(Node<T> *node, Node<T> *parent)
{
        cout << "Merging Nodes" << endl;
        Node<T> *sibling;
        typename Node<T>::Key *key = new typename Node<T>::Key;
        typename list<typename Node<T>::Key>::iterator it2;

        node->it1 = node->first.begin();
        parent->it1 = parent->iPosition(&(*node->it1).data);
        sibling = (*parent->it1).rChild;                        //Setting sibling to older brother

        for(node->it1 = node->first.begin(); node->it1 != node->first.end(); ++node->it1){}     //set node iterator to end of node

        key->data = (*parent->it1).data;                        //Set key data to parent data
        node->first.insert(node->it1,*key);                      //Insert parent Key into node
        parent->first.erase(parent->it1);                         //Remove the key in parent

        for(sibling->it1 = sibling->first.begin(); sibling->it1 != sibling->first.end(); sibling->it1++)       //Iterate through each element in sibling
        {
                //node->it1++;
                key->data = (*sibling->it1).data;               
                node->first.insert(node->it1,*key);
        }

        it2 = sibling->first.end();
        sibling->first.erase(sibling->it1, it2);         //erase all the keys in sibling
}

//Function to merge with left sibling if there is no left sibling
template <typename T>
void Btree<T>::mergeYounger(Node<T> *node, Node<T> *parent)
{
        //cout << "calling mergeYounger" << endl;
        node->it1 = node->first.begin();
        parent->it1 = parent->iPosition(&(*node->it1).data);
        parent->it1--;
        parent->it1--;

        node = (*parent->it1).rChild;           //set node to point to younger sibling

        mergeOlder(node, parent);               //Now call mergeOlder for the younger sibling
}

//Function to merge siblings into one family if no siblings have keys to share
template <typename T>
void Btree<T>::marriage(Node<T> *node)
{
        //cout << "Calling Marriage" << endl;
        Node<T> *parent = node->prev;
        
        for(parent->it1 = parent->first.begin(); parent->it1 != parent->first.end(); ++parent->it1){}
        parent->it1--;

        if((*parent->it1).rChild == node)
        {
                mergeYounger(node, parent);
        }
        else
        {
                mergeOlder(node, parent);
        }
}

//Function to perform check if Node is empty then call correct functino to fix problem
template <typename T>
void Btree<T>::checkMin(Node<T> *node)
{
        int isEmpty = 0;
        int surveilance = 0;

        isEmpty = node->checkEmpty();
        if(node == root){}
        else if(isEmpty == 1)
        {
                cout << "Node has too few elements" << endl;
                surveilance = caseJoint(node);
                if(surveilance == 0)
                {
                        marriage(node);
                }
        }
}

//Function to check if leaf node has too few elements after deletion
template <typename T>
int Node<T>::checkEmpty()
{
        //cout << "Calling check empty" << endl;
        int isEmpty = 0;
        int count = 0;

        for(it1 = first.begin(); it1 != first.end(); ++it1, count++){     //Counting how many elements are in the list
        //cout << "Element " << (*it2).data << endl;
        }       

        if(count < min)                         //If list is not full enough
        {
                isEmpty = 1; 
        }

        return isEmpty;
}

//Function to find immediate successor
template <typename T>
typename Node<T>::Key* Btree<T>::successor(Node<T> *node,T *deletion)
{
        typename Node<T>::Key *key;
        key = node->findMatch(deletion);
        node = key->rChild;
        while(node->lChild != NULL)
        {
                node = node->lChild;
        }
        node->it1 = node->first.begin();
        return &(*node->it1);
}

//Function to swap element to be deleted and its immediate successor and then call function to delete element
template <typename T>
void Btree<T>::swap(typename Node<T>::Key *keyD, typename Node<T>::Key *keyS, T *deletion)
{
        T tempD;
        tempD = keyS->data;
        keyS->data = keyD->data;
        keyD->data = tempD;
        
        temporary->deleteLeaf(deletion);
        checkMin(temporary);                    //call function to check if node is not full enough checkMin
}

//Function to set immediate to point at node containing immediate successor
template <typename T>
void Btree<T>::setTemp(typename Node<T>::Key *key)
{
        Node<T> *node;
        node = key->rChild;
        while(node->lChild != NULL)
        {
                node = node->lChild;
        }
        temporary = node;
}

//Function to delete item from Btree
template <typename T>
void Btree<T>::deleteB(T *deletion)
{
        int isEmpty = 0;
        typename Node<T>::Key *keyD;
        typename Node<T>::Key *keyS;

        search(deletion);
        if(temporary->lChild == NULL)
        {
                //cout << "Delete Leaf" << endl;
                temporary->deleteLeaf(deletion);
                checkMin(temporary);
        }
        else 
        {
                keyS = successor(temporary, deletion);          //functions to find immediate successor
                keyD = temporary->findMatch(deletion);          //Saving item to be deleted to a Key*      
                setTemp(keyD); //set temporary to point at node containing immediate successor 
                swap(keyD, keyS, deletion);                       //function to swap immediate successor and item to be deleted
        }
}


