// $Id: listmap.tcc,v 1.1 2014-04-24 18:02:55-07 - - $

#include "listmap.h"
#include "trace.h"

template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::node::node (const value_type& pair):
            pair(pair), prev(NULL), next(NULL) {
}

template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::listmap (): head(NULL), tail (NULL) {
}

template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::~listmap () {
   TRACE ('l', (void*) this);
}

template <typename Key, typename Value, class Less>
void listmap<Key,Value,Less>::insert (const xpair<Key,Value>& pair) {
   TRACE ('l', &pair << "->" << pair);
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::find (const key_type& that) const {
   TRACE ('l', that);
   return iterator();
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::begin () {
   return iterator (this, head);
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::end () {
   return iterator (this, NULL);
}

template <typename Key, typename Value, class Less>
bool listmap<Key,Value,Less>::empty () const {
   return head == NULL;
}


template <typename Key, typename Value, class Less>
xpair<Key,Value>& listmap<Key,Value,Less>::iterator::operator* () {
   TRACE ('l', where->pair);
   return where->pair;
}

template <typename Key, typename Value, class Less>
xpair<Key,Value> *listmap<Key,Value,Less>::iterator::operator-> () {
   TRACE ('l', where->pair);
   return &(where->pair);
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator++ () {
   TRACE ('l', "First: " << map << ", " << where);
   TRACE ('l', "Second: " << map->head << ", " << map->tail);
   where = where->next;
   return *this;
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator-- () {
   where = where->prev;
   return *this;
}

template <typename Key, typename Value, class Less>
bool listmap<Key,Value,Less>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::iterator::iterator (listmap *map,
            node *where): map (map), where (where){
}

template <typename Key, typename Value, class Less>
void listmap<Key,Value,Less>::iterator::erase () {
   TRACE ('l', "map = " << map << ", where = " << where << endl);
}

