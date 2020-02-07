#include "List.h"

using std::cout;
using std::endl;

int main() {

    List<int> list, list2, list3, list4;

    list.insertBack(2);
    list.insertBack(5);
    list.insertBack(3);
    list.insertBack(7);

    list.sort();

    cout << list << endl;

  return 0;
}
