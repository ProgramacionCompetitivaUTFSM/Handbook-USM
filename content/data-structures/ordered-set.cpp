#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
  
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

ordered_set p;

p.insert(5); p.insert(2); p.insert(6); p.insert(4); // O(log n)
// value at 3rd index in sorted array. O(log n). Output: 6
cout << "Value at 3rd index: " << *p.find_by_order(3) << endl;

// index of number 6. O(log n). Output: 3
cout << "Index of number 6: " << p.order_of_key(6) << endl;

// number 7 not in the set but it will show the index 
// number if it was there in sorted array. Output: 4
cout << "Index of number 7:" << p.order_of_key(7) << endl;

// number of elements in the range [3, 10)
cout << p.order_of_key(10) - p.order_of_key(3) << endl;