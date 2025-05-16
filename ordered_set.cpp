#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

// ordered_set maintains sorted unique elements in ascending order using less comparison.
// ordered_multiset allows duplicates using a less_equal comparison, preserving the sorted order.

//Fucntions
//In addition to normal set operations, the ordered set supports:

//order_of_key(k): Gives the count of elements smaller than k. — O(log n)
//find_by_order(k): Returns the iterator for the kth element (use k = 0 for the first element). — O(log n)

//Deletion in Multiset
//To remove an element in a multiset, you must delete it using iterators:

ss.erase(ss.find_by_order(ss.order_of_key(x)));
