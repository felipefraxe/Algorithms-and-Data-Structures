/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

int linear_search(int array[], size_t length, int target)
{
    for (int i = 0; i < length; i++)
    {
        if(array[i] == target)
            return i;
    }
    return -1;
}
