/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    T sum_ = 0;
    T top;

    if(s.empty())
        return 0;
    // if reachs here, it means s is not empty
        top = s.top();
        s.pop();
        sum_ = top + sum(s);
        s.push(top);
        return sum_;

}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> q)
{
    stack<char> s;
    int sz = q.size();
    char front;

    if(q.empty())
        return true;
    // when q is not empty
    for (int i = 0; i < sz; ++i){
        front = q.front();
        q.pop();
        q.push(front);
        // only push char "[" "]" to the stack
        if(front == ']' && s.empty()){
            return false;
        }else if(front == '['){
            s.push(front);
        }else if(front == ']' && !s.empty()){
            s.pop();
        }
    }

    return s.empty();

}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    T front; //do i need it?
    int sz = q.size();
    bool normal;
    int count = 1;
    int t = 1;
    int exceed;
    // decide how many times needed
    while(count < sz){
        ++t;
        count = count + t;
    }
    // decide which situation it is
    exceed = sz - (count - t);

    if(count == sz){
        normal = true;
    }else{
        normal = false;
    }
    // normal situation
    if(normal){
        for(int i = 1; i <= t; ++i){
                if(i % 2 == 1){
                    for(int j = 0; j < i; ++j){
                        front = q.front();
                        q.pop();
                        q.push(front);
                    }
                }else{
                    for(int j = 0; j < i; ++j){
                        front = q.front();
                        q.pop();
                        s.push(front);
                    }
                    for(int j = 0; j < i; ++j){
                        front = s.top();
                        s.pop();
                        q.push(front);
                    }
                }
            }
    }else{
        // abnormal situation
        for(int i = 1; i < t; ++i){
                if(i % 2 == 1){
                    for(int j = 0; j < i; ++j){
                        front = q.front();
                        q.pop();
                        q.push(front);
                    }
                }else{
                    for(int j = 0; j < i; ++j){
                        front = q.front();
                        q.pop();
                        s.push(front);
                    }
                    for(int j = 0; j < i; ++j){
                        front = s.top();
                        s.pop();
                        q.push(front);
                    }
                }
            }
        // last push
        if(t % 2 == 1){
            for(int j = 0; j < exceed; ++j){
                front = q.front();
                q.pop();
                q.push(front);
            }
        }else{
            for(int j = 0; j < exceed; ++j){
                front = q.front();
                q.pop();
                s.push(front);
            }
            for(int j = 0; j < exceed; ++j){
                front = s.top();
                s.pop();
                q.push(front);
            }
        }


    }
}

/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */

template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true;
    T top;
    T front;

    if (s.empty())
        return true;
    //
    top = s.top();
    s.pop();
    retval = verifySame(s, q);
    front = q.front();
    retval = retval * (front == top);

    q.pop();
    q.push(front);
    s.push(top);

    return retval;
    }
}
