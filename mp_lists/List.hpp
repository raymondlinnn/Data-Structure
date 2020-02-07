/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator();
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if (head_ != NULL) {
      ListNode *curr = head_;
      ListNode *prev;
      while (curr != NULL) {
          prev = curr;
          curr = curr->next;
          delete prev;
      }
  }
  // are these necessary?
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->next = head_;
  newNode->prev = NULL;

  // if head points to something, then update it
  if (head_ != NULL) {
      head_->prev = newNode;
      head_ = newNode;
    }

  // if tail points to nothing, update it
  if (tail_ == NULL) {
      head_ = newNode;
      tail_ = newNode;
    }

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
    ListNode* seeker = head_;
    ListNode* newNode = new ListNode(ndata);
    newNode->next = NULL;
    newNode->prev = tail_;
    // the order is very important in these two chunks
    if (tail_ != NULL) {
        tail_->next = newNode;
        tail_ = newNode;
    }

    if (head_ == NULL) {
        head_ = newNode;
        tail_ = newNode;
    }

    length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
  /// @todo Graded in MP3.1
    if (splitPoint == 0)
        return start;

    ListNode * curr = start;
    for (int i = 0; i < splitPoint && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr != NULL) {
        curr->prev->next = NULL;
        curr->prev = NULL;
    }

    start = curr;
    return start;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  int count = 0;
  ListNode* curr = head_;
  ListNode* prev;

  while (curr != tail_ && curr != NULL) {
      // in the even turn, only record
      if (count % 2 == 0){
          prev = curr;
          curr = curr->next;
          ++count;
    }else{
        // connect the previous node and next node
        prev->next = curr->next;
        curr->next->prev = prev;
        // connect the curr node to the tail
        curr->next = tail_->next;
        tail_->next = curr;
        curr->prev = tail_;
        // correct the tail
        tail_ = curr;
        // continue moving
        curr = prev->next;
        ++count;
    }
  }

}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
    if (startPoint == endPoint)
        return;
    if (startPoint == NULL || endPoint == NULL)
        return;

        int count = 0;
        for (List<T>::ListIterator it = List<T>::ListIterator(startPoint); it != List<T>::ListIterator(endPoint); ++it)
            ++count;

        ListNode* s1 = startPoint;
        ListNode* s2 = endPoint;

        ListNode* temp_n;
        ListNode* temp_p;
        // add count one more time
        ++count;
        count = count / 2;
        for (int i = 0; i < count; ++i) {
            // store the node previous and next to startPoint
            // temp_p and s2->next might be NULL
            if (head_ == startPoint)
                head_ = endPoint;
            if (tail_ == endPoint)
                tail_ = startPoint;       // reset the head and tail

            temp_n = s1->next;
            temp_p = s1->prev;
            // the edge case  : s1->s2
            if (s1->next == s2) {
                s1->next = s2->next;
                if (s2->next != NULL)
                    s2->next->prev = s1;

                s2->next = s1;
                s1->prev = s2;

                if (temp_p != NULL)
                    temp_p->next = s2;
                s2->prev = temp_p;
                return;
            }
            // normal condition
            s1->next = s2->next;
            s1->prev = s2->prev;

            s2->prev->next = s1;
            if (s2->next != NULL)
                s2->next->prev = s1;

            if (temp_p != NULL)
                temp_p->next = s2;
            s2->prev = temp_p;

            s2->next = temp_n;
            temp_n->prev = s2;

            s2 = s1->prev;
            s1 = temp_n;
        }


}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n < 0 || length_ == 0)
    return;

  if (n > length_){
      reverse();
      return;
  }

  ListNode *curr = head_;
  ListNode *prev;

  while (curr != NULL) {
      prev = curr;
      // set i to the tail of the current chunk
      for (int i = 0; i < n - 1; ++i) {
          if (curr != NULL) {
              curr = curr->next;
          }else{
              curr = tail_;
              break;
          }
      }
      reverse(prev, curr);
      curr = prev;
      // move to the next chunk
      if (curr != NULL) {
          curr = curr->next;
      }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {

    if (first == NULL)
        return second;
    if (second == NULL)
        return first;
    if (first == NULL && second == NULL)
        return NULL;

    ListNode* s1 = first;
    ListNode* s1_p = first;
    ListNode* s2 = second;
    ListNode* s2_n;

    while (s2 != NULL) {
        // store the next node in second list
        s2_n = s2->next;
        // use s1 to search where to store s2
        while (s1 != NULL && s1->data < s2->data) {
            s1_p = s1;
            s1 = s1->next;
        }
        // when s1 stops, insert s2, s1 and s1->prev might be null
        // edge case 1: s1 = NULL (insertback)
        if (s1 == NULL) {
            s2->prev = s1_p;
            s2->next = s1;
            s1_p->next = s2;
        }else{
            // normal condition: s1 not NULL
            if (s1->prev != NULL) {
                s1->prev->next = s2;
            }else{
                // s1->prev == NULL means insert at front, need to update head
                first = s2;
            }
            s2->next = s1;
            s2->prev = s1->prev;
            s1->prev = s2;
        }
        // reset seekers
        s1 = s2;
        s2 = s2_n;
    }
    // when s2 == NULL, means second list clear
    return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
    if (start == NULL)
        return NULL;

    if (chainLength <= 1)
        return start;

    ListNode* secondhead = NULL;

    if (chainLength > 1) {
        secondhead = split(start, chainLength / 2);
    }

    return merge(mergesort(start, chainLength / 2), mergesort(secondhead, chainLength - chainLength / 2));
}
