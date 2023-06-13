#include <iostream>
#include <stack>
#include <queue> // queue y priority queue
#include <type_traits>
using namespace std;

template <typename T, typename ...Params>
void show_stack(stack<T, Params...> s) {
    while (!s.empty()) {
        int value = s.top();
        cout << value << " ";
        s.pop();
    }
    cout << endl;
}

template<
        template<typename ...> class Adapter,
        typename T,
        typename ...Params,
        typename Callable>
void traverse_adapter(Adapter<T, Params...> adapter, Callable caller) {
    while(!adapter.empty()) {
        if constexpr (is_same_v<Adapter<T>, queue<T>>)
            caller(adapter.front());
        else
            caller(adapter.top());
        adapter.pop();
    }
}

void ejemplo_stack() {
    stack<int> s1;

    s1.push(10);
    s1.push(20);
    s1.push(30);
    s1.push(40);

    traverse_adapter(s1, [](auto value) {
        cout << value << " ";
    });
    cout << endl;

    deque deq = {10, 20, 30, 40, 50};
    stack<int> s2 (deq);
    show_stack(s2);

    vector vec = {10, 20, 30, 40, 50};
    stack<int, vector<int>> s3(vec);
    show_stack(s3);
}

void ejemplo_queue() {
    queue<int> q1;
    q1.push(10);
    q1.push(20);
    q1.push(30);;
    traverse_adapter(q1, [](auto value) {
        cout << value << " ";
    });
    cout << endl;

    deque deq = {10, 20, 30, 40, 50};
    queue<int> q2 (deq);
    traverse_adapter(q2, [](auto value) {
        cout << value << " ";
    });
    cout << endl;

    // No se puede usar un vector para generar un adaptador que queue
    /*
    vector vec = {10, 20, 30, 40, 50};
    queue<int, vector<int>> q3 (vec);
    traverse_adapter(q3, [](auto value) {
        cout << value << " ";
    });
    cout << endl;
    */
}

int main() {
    ejemplo_stack();
    ejemplo_queue();
    return 0;
}
