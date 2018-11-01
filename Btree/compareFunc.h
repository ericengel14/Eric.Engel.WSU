//Function to be passed as functino pointer to Btree

//Compare Func to decide whether child is left or right child
//Return -1 if left child 
//Return 1 if right child
//Return 0 if they are equal

#pragma once

template <typename T>
T compareFunc(T *i,T *j)
{	
	if (*i < *j)
	{
		return -1;
	}
	if (*i > *j)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}