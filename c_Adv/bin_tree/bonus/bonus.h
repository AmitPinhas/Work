#ifndef __BONUS_H__
#define __BONUS_H__

/*
     Description : print the tree .
     Complexity : O(n) .
     Input : a)pointer to the tree .
             b)traverse Mode (PRE_ORDER / IN_ORDER / POST_ORDER) .  
     Output : no output . 
     Error : no error.
*/
void TreePrint(const BSTree* _tree , TreeTraversalMode _traverseMode);

/*
     Description : checks whether the tree is full or not.
     Complexity : O(n) .
     Input : a)pointer to the tree .  
     Output : TRUE / FALSE . 
     Error : TRUE - the tree is full or the tree is empty .
             FALSE - the tree is not full or the pointer sent is null .
*/
int IsFullTree(const BSTree* _tree);

/*
     Description : checks if the two trees have the same structure .
     Complexity : O(n) .
     Input : a) pointer to the tree number one .
             b) pointer to the tree number two . 
     Output : TRUE / FALSE . 
             FALSE - the trees are not the same , one of the pointers is null and the other not , the two pointers are null .
*/
int AreSimilar(const BSTree* _treeOne ,const BSTree* _treeTwo);

/*
     Description : check if the tree is perfect or not .
     Complexity : O(n) .
     Input : a)pointer to the tree .  
     Output : TRUE / FALSE . 
     Error : TRUE - the tree is perfect or the tree is empty .
             FALSE - the tree is not perfect or the pointer sent is null  .
*/
int IsPerfectTree(const BSTree* _tree);

/*
     Description : check if a tree is a binary search tree or not . 
     Complexity : O(n) .
     Input : a)pointer to the tree .  
     Output : TRUE / FALSE_BST . 
     Error : TRUE - the tree is binary search tree or the tree is empty .
             FALSE_BST - the tree is not binary search tree or the pointer sent is null .
*/
int IsBST(const BSTree* _tree);

#endif /* __BONUS_H__ */

