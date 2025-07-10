/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

int binsearch(int array[], int lo, int hi, int target)
{
    while(lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (array[mid] == target)
            return mid;
        if (array[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}
