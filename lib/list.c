/**
 * @file Implementation of list's API functions.
 */

#include "list.h"




list *list_create()
{
    list * l = (list *)malloc(sizeof(list));

    l->front = NULL;
    l->back = NULL;
    l->size = 0;

    return l;
}


inline __attribute__ ((always_inline)) dptr list_back(const list *l)
{
    return do_node_get(l->back);
}


inline __attribute__ ((always_inline)) list_iterator list_begin(const list *l)
{
    return l->front;
}


void list_clear(list *l)
{
    struct lnode *tmp = l->front;
    
    /* Deleting all nodes. */
    while(tmp)
    {
        struct lnode *tmp_next = tmp->next;
        __do_node_destroy(tmp);
        tmp = tmp_next;
    }

    /* Set starting values. */
    l->size = 0;
    l->front = NULL;
    l->back = NULL; 
}


list *list_copy(const list *l)
{
    /* Creating dest list. */
    list * other = list_create();
    /* Copy values to dest list. */
    struct lnode *cur = l->front;

    while(cur)
    {
        list_push_back(other, cur);
        cur = cur->next;
    }

    other->size = l->size;

    return other;
}


size_t list_count(const list *l, constdptr data, bool (*cmp)(constdptr first, constdptr second))
{
    size_t res = 0;
    struct lnode *cur = l->front;

    /* Goes through list one by one and count res. */
    while(cur)
    {
        if(cmp(data, cur))
            res++;
        cur = cur->next;
    }

    return res;
}


size_t list_count_if(const list *l, bool (*predicate)(constdptr data))
{
    size_t res = 0;
    struct lnode *cur = l->front;

    /* Goes through list one by one and count res. */
    while(cur)
    {
        if(predicate(cur))
            res++;
        cur = cur->next;
    }

    return res;
}


inline void list_destroy(list *l)
{
    /* Deleting all nodes. */
    list_clear(l);
    /* Frees the memory for struct list. */
    free(l);
}


inline __attribute__ ((always_inline)) list_iterator list_end()
{
    return NULL;
}


inline void list_emplace(list *l, list_iterator where, constdptr data)
{
    list_insert(l, where, data);
}


inline void list_emplace_front(list *l, constdptr data)
{
    list_push_front(l, data);
}


inline void list_emplace_back(list *l, constdptr data)
{
    list_push_back(l, data);
}


inline __attribute__ ((always_inline)) bool list_empty(const list *l)
{   
    return l->size == 0;
}

void list_erase(list *l, list_iterator where);

void list_erase_range(list *l, list_iterator first, list_iterator last);


inline __attribute__ ((always_inline)) dptr list_front(const list *l)
{
    return do_node_get(l->front);
}


list_iterator list_find(const list *l, constdptr data, bool (*cmp)(constdptr first, constdptr second))
{
    struct lnode *cur = l->front;

    /* Find first occurence, that cmp() return true. */
    while(cur)
    {
        if(cmp(data, cur))
            return cur;
        cur = cur->next;
    }

    return NULL;
}


list_iterator list_find_if(const list *l, bool (*predicate)(constdptr data))
{
    struct lnode *cur = l->front;

    /* Find first occurence, that predicate() return true. */
    while(cur)
    {
        if(predicate(cur))
            return cur;
        cur = cur->next;
    }

    return NULL;
}


list_iterator list_rfind(const list *l, constdptr data, bool (*cmp)(constdptr first, constdptr second))
{
    struct lnode *cur = l->back;

    /* Find first occurence in reverse order, that cmp() return true. */
    while(cur)
    {
        if(cmp(data, cur))
            return cur;
        cur = cur->prev;
    }

    return NULL;
}


list_iterator list_rfind_if(const list *l, bool (*predicate)(constdptr data))
{
    struct lnode *cur = l->back;

    /* Find first occurence in reverse order, that predicate() return true. */
    while(cur)
    {
        if(predicate(cur))
            return cur;
        cur = cur->prev;
    }

    return NULL;    
}


list_iterator list_insert(list *l, list_iterator where, constdptr data)
{
    /* New element goes to the end if !where. */
    if(!where)
        list_push_back(l, data);
    else if(where->prev)
        list_push_front(l, data);

    /* If new element going to the middle. */
    if(where->prev)
        where->prev->next = __do_node_create(data, where, where->prev);
    where->prev = where->prev->next;
    
    l->size++;

    return (where ? where->prev : l->front);
}


list_iterator list_insert_many(list *l, list_iterator where, size_t count, ...)
{
    list_iterator res = NULL;
    /* Using va_list to implement any count of arguments to insert. */
    va_list args;
    /* Count is number of elements. */
    va_start(args, count);

    /* Inserting all elements one by one. */
    for(size_t i = 0; i < count; i++)
    {
        dptr cur = va_arg(args, dptr);
        struct lnode *tmp = list_insert(l, where, cur);

        /* Writing result list_iterator. */
        if(i == 0)
            res = tmp;
    }

    /* Ending work with va_list. */
    va_end(args);

    return res;
}


void list_pop_back(list *l)
{
    if(!l->back)
        return;
    
    /* Saving ref to old back element. */
    struct lnode *tmp = l->back;

    /* Changing back element */
    l->back = l->back->prev;
    
    /* Deleting next reference of new l->back. */
    l->back->next = NULL;
    l->size--;
    /* Deleting old front element. */
    __do_node_destroy(tmp);
}


void list_pop_front(list *l)
{
    if(!l->front)
        return;
    
    /* Saving ref to old front element. */
    struct lnode *tmp = l->front;

    /* Changing front element */
    l->front = l->front->next;
    
    /* Deleting prev reference of new l->front. */
    l->front->prev = NULL;
    l->size--;
    /* Deleting old front element. */
    __do_node_destroy(tmp);
}


void list_push_back(list *l, constdptr data)
{
    /* Saving former last element. */
    struct lnode *tmp = l->back;

    /* Creating new last element. */
    l->back = __do_node_create(data, NULL, l->back);

    /* If l->front was exist => tmp != NULL, so making ref to the next
        Esle new element is front element too. */
    if(l->front)
        tmp->next = l->back;
    else
        l->front = l->back;

    l->size++;
}


void list_push_front(list *l, constdptr data)
{
    /* Saving format first element. */
    struct lnode *tmp = l->front;

    /* Creating new first element. */
    l->front = __do_node_create(data, l->front, NULL);

    /* If l->back was exist => tmp != NULL, so making ref to the prev
        Esle new element is back element too. */
    if(l->back)
        tmp->prev = l->front;
    else
        l->back = l->front;

    l->size++;
}


void list_remove(list *l, dptr data, bool (*cmp)(constdptr first, constdptr second))
{
    struct lnode *cur = l->front;

    /* Deleting all nodes if <cmp> returns true. */
    while(cur)
    {
        if(cmp(data, cur))
            list_erase(l, cur);
        cur = cur->next;
    }
}


void list_remove_if(list *l, bool (*predicate)(constdptr data))
{
    struct lnode *cur = l->front;

    /* Deleting all nodes if <predicate> returns true. */
    while(cur)
    {
        if(predicate(cur))
            list_erase(l, cur);
        cur = cur->next;
    }
}


void list_reverse(list *l);


inline __attribute__ ((always_inline)) size_t list_size(const list *l)
{
    return l->size;
}


void list_sort(list *l, int (*cmp)(constdptr first, constdptr second));


void list_unique(list *l, bool (*predicate)(constdptr first, constdptr second));