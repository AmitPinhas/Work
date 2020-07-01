#ifndef __BSTREE_H__ 
#define __BSTREE_H__

#include <stddef.h>  /* size_t */

/** 
 *  @file bstree.h
 *  @brief Generic Binary Search Tree
 *	
 *  @details  Implements a binary search tree(BST) container
 *  The BST will store pointers to any user defined opaque type
 *  The tree is implemented using a sentinel. 
 *  The first node in the tree is the sentinel left subtree.
 *
 *  @author Amit Pinhas  (amitenav@gmail.com)
 * 
 *  @bug No known bugs.
 */

typedef struct BSTree  BSTree;
typedef struct BSTreeItr*  BSTreeItr;

typedef int (*LessComparator)(void* _left, void* _right);

/** 
 * @brief Predicate function returns a none zero value if predicate holds for element
 *
 * @param _element : element to test
 * @param _context : context to be used
 * @return none zero if predicate holds
 */
typedef int (*PredicateFunction)(void * _element, void* _context);

/** 
 * @brief Action function to operate on an element
 *
 * @param _element : element to test
 * @param _context : context to be used
 * @return zero if action fails
 */
typedef int (*ActionFunction)(void* _element, void* _context);

typedef enum
{
    BSTREE_TRAVERSAL_PREORDER = 0,
    BSTREE_TRAVERSAL_INORDER,
    BSTREE_TRAVERSAL_POSTORDER,
    BSTREE_TRAVERSAL_DEPTH_FIRST,
    BSTREE_TRAVERSAL_BREADTH_FIRST
} TreeTraversalMode;

/** 
 * @brief Create a binary search tree
 * Creates an empty binary search tree with sentinel
 * 
 * @param _less: A comparison function 
 *				that returns true (none zero value) if x < y 
 *				and false (zero) otherwise.
 * @return a pointer to the newly created tree.
 * @retval NULL on failure due to allocation failure or NULL function pointer given
 */
BSTree* BSTreeCreate(LessComparator _less);

/** 
 * @brief Destroy tree
 * Destroys the tree, freeing the memory.
 * If supplied with non-NULL destroyer function, frees items in tree.
 * Average time complexity: O(1)..O(n) (depends on memory freeing)
 *
 * @params _tree : A previously created Tree ADT returned via BSTreeCreate
 * @params _destroyer : A function to destroy the data in the tree (may be NULL if unnecessary)
 */
void  BSTreeDestroy(BSTree* _tree, void (*_destroyer)(void*));

/** 
 * @brief Add an element to tree if it's not already there
 * Insert element to binary tree, using the tree's comparison function
 * Average time complexity O(log n).
 * Worst: O(n)
 *
 * @param _tree : A previously created Tree ADT returned via BSTreeCreate
 * @param _item: An item to add to the tree
 * @return iterator pointing to the item added or iterator to end on failure
 * @warning don't allow duplicates
 */
BSTreeItr BSTreeInsert(BSTree* _tree, void* _item);

/** 
 * @brief Get an in-order itertator to the tree's begin 
 *
 * @param _tree : tree to create iterator from
 * @return an iterator pointing at the tree's begin or end if tree is empty 
 */
BSTreeItr BSTreeItrBegin(const BSTree* _tree);

/** 
 * @brief Get itertator to the tree's end (in order)
 *
 * @param _tree : tree to create iterator from
 * @return an iterator pointing at the tree's end
 */
BSTreeItr BSTreeItrEnd(const BSTree* _tree);

/** 
 * @brief Compare two iterators
 *
 * @param _a, _b : Iterators to compare
 * @return : 0 if are not the same 
 *           any none zero value if iterators are the same
 */
int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b);


/** 
 * @brief Get element stored at tree position pointed to by iterator
 * time complexity O(1).
 * We do not provide a BSTreeItr_Put(it, data) function. Can you imagine why???
 * @param _it : A tree iterator
 * @return the item the iterator points at or null if _it as at end
 */
void* BSTreeItrGet(BSTreeItr _it);


/** 
 * @brief Get itertator to the next element from current iterator
 * complexity: O(?)
 *
 * @params _it : A tree iterator
 * @returns an iterator pointing at the next element after _it or end iterator.
 */
BSTreeItr BSTreeItrNext(BSTreeItr _it);

/** 
 * @brief Get itertator to the previous element from current iterator
 *
 * @param _it : A tree iterator
 * @return an iterator pointing at the previous element
 * or to the beginning if _it points to the beginning
 */
BSTreeItr BSTreeItrPrev(BSTreeItr _it);


/** 
 * @brief Search the first element for which the given predicate returns 0
 * iterating using in-order manner over elements
 * O(k * n) where O(k) is the time complexity of the predicate
 *
 * @param _tree : A previously created Tree ADT returned via BSTreeCreate
 * @param _predicate : Predicate function
 * @param _params : Predicate parameters
 * @return an iterator pointing to the first data found, to end of tree if not found or NULL on NULL input
 */
BSTreeItr BSTreeFindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context);


/** 
 * @brief Performs an action function on every element in tree, by given traversal mode
 * @details iteration will stop on the first element for which the action function returns a zero
 * or on reaching end of the conrainer
 *
 * @params _tree : tree to iterate over
 * @params _mode : Traversal mode - TREE_TRAVERSAL_PREORDER, TREE_TRAVERSAL_INORDER or TREE_TRAVERSAL_POSTORDER
 * @params _action : Action function to call for each element
 * @params _context : Context for the _action function
 * @return Iterator refering to the tree end or the element where iteration stopped
 */
BSTreeItr BSTreeForEach(const BSTree* _tree, TreeTraversalMode _mode, ActionFunction _action, void* _context);


#endif /* __BSTREE_H */
