#include <algorithm>
#include "library.h"
template <class T>
class AVLTree
{
private:
    AVLTree *left_tree;
    AVLTree *right_tree;
    AVLTree *father;
    AVLTree *first;
    int height;
    int balance;
    T data;

    /*
	* create new part in the tree
	*/
    AVLTree(T &element);
    /*
	* return the height of the left tree
	* if has no left return 0
	*/
    int getLeftHeight();
    /*
	* return the height of the right tree
	* if has no right return 0
	*/
    int getRightHeight();
    /*
	* return the height of the tree (H(left)+H(right)+1)
	*/
    int calculateHeight();
    /*
	* return the balance of the tree (H(left)-H(right))
	*/
    int calculateBalance();
    bool isLeaf();
    bool isRoot();
    void changetoRoot(AVLTree *v);
    bool isLeft();
    void switchPlaces(AVLTree *v);
    AVLTree *getNextInorder();
    AVLTree *calculateFirst();
    //_________________inserting element_________________
    /*
	* get the T element to insert
	* insert it to this part of the tree according to T order
	* return FAILURE if element alredy exists
	*       else return SECCESS
	*/
    StatusType insertElementAux(T &element);
    /*
	* get the T element to insert
	* insert it to the left tree
	* if there is no such left tree create new tree element of it and insert it
	* return FAILURE if element alredy exists
	*       else return SECCESS
	*/
    StatusType insertToLeft(T &element);
    /*
	* get the T element to insert
	* insert it to the right tree
	* if there is no such right tree create new tree element of it and insert it
	* return FAILURE if element alredy exists
	*       else return SECCESS
	*/
    StatusType insertToRight(T &element);

    //_________________AVL algorithems_________________
    void LL();
    void LR();
    void RL();
    void RR();
    /*
	* check which roll to do acording to avl algoritem
	*/
    void doRoll();

    //_________________delete element_________________
    template <class Id>
    StatusType deleteElementAux(Id &data);

    StatusType deleteThisElement(AVLTree *v);

    template <class Id>
    AVLTree<T> *getNodeAux(Id &data_in);
    template <class Id>
    AVLTree<T> *getNode(Id &data_in);

public:
    /*
	* create new tree
	*/
    AVLTree();
    ~AVLTree();
    AVLTree(AVLTree &tree_to_copy);
    AVLTree &operator=(AVLTree &tree_to_copy);
    /*
	* get the T element to insert to the tree
	* insert it to the tree according to T order
	* return FAILURE if element alredy exists
	*       else return SECCESS
	*/
    StatusType insertElement(T &element);
    template <class Id>
    StatusType deleteElement(Id &data);
    //template <class Id>
    //StatusType getElement(Id &data_in, T &element=T());
    template <class S>
    AVLTree<T> *getBestElements(int num_of_elements);

    //just for chacking:
    AVLTree *getLeftTree();
    AVLTree *getRightTree();
    T getData();
    AVLTree *getTree();
};

template <class T>
AVLTree<T>::AVLTree()
    : data(T()), height(-1), first(nullptr), balance(0), father(nullptr), left_tree(nullptr), right_tree(nullptr)
{
}

template <class T>
AVLTree<T>::AVLTree(T &element)
    : data(element), height(1), first(this), balance(0), father(nullptr), left_tree(nullptr), right_tree(nullptr)
{
}

template <class T>
AVLTree<T>::~AVLTree()
{
    if (left_tree != nullptr)
    {
        delete left_tree;
    }
    if (right_tree != nullptr)
    {
        delete right_tree;
    }
}

template <class T>
AVLTree<T>::AVLTree(AVLTree &tree_to_copy)
    : data(tree_to_copy.data), height(tree_to_copy.height), first(nullptr),
      balance(tree_to_copy.balance), father(nullptr), left_tree(nullptr), right_tree(nullptr)
{
}

template <class T>
AVLTree<T> &AVLTree<T>::operator=(AVLTree &tree_to_copy)
{
    data = tree_to_copy.data;
    height = tree_to_copy.height;
    balance = tree_to_copy.balance;
    first = nullptr;
    father = nullptr;
    left_tree = nullptr;
    right_tree = nullptr;
    return *this;
}

template <class T>
StatusType AVLTree<T>::insertElementAux(T &element)
{
    StatusType return_value = SUCCESS;
    if (data == element)
    {
        return FAILURE;
    }
    if (data > element)
    {
        return_value = insertToLeft(element);
    }
    else
    {
        return_value = insertToRight(element);
    }
    doRoll();
    return return_value;
}

template <class T>
StatusType AVLTree<T>::insertToLeft(T &element)
{
    StatusType return_value = SUCCESS;
    if (left_tree == nullptr)
    {
        left_tree = new AVLTree(element);
        left_tree->father = this;
    }
    else
    {
        return_value = left_tree->insertElementAux(element);
    }
    return return_value;
}

template <class T>
StatusType AVLTree<T>::insertToRight(T &element)
{
    StatusType return_value = SUCCESS;
    if (right_tree == nullptr)
    {
        right_tree = new AVLTree(element);
        right_tree->father = this;
    }
    else
    {
        return_value = right_tree->insertElementAux(element);
    }
    return return_value;
}

template <class T>
int AVLTree<T>::getLeftHeight()
{
    if (left_tree == nullptr)
    {
        return 0;
    }
    return left_tree->calculateHeight();
}

template <class T>
int AVLTree<T>::getRightHeight()
{
    if (right_tree == nullptr)
    {
        return 0;
    }
    return right_tree->calculateHeight();
}

template <class T>
int AVLTree<T>::calculateHeight()
{
    return 1 + std::max(getRightHeight(), getLeftHeight());
}

template <class T>
int AVLTree<T>::calculateBalance()
{
    return getLeftHeight() - getRightHeight();
}

template <class T>
void AVLTree<T>::doRoll()
{
    if (this == nullptr)
    {
        return;
    }
    height = calculateHeight();
    balance = calculateBalance();
    if (balance > 1)
    {
        if (left_tree->balance >= 0)
        {
            LL();
        }
        else
        {
            LR();
        }
    }
    else if (balance < -1)
    {
        if (right_tree->balance <= 0)
        {
            RR();
        }
        else
        {
            RL();
        }
    }
}

template <class T>
void AVLTree<T>::changetoRoot(AVLTree *v)
{
    if (isLeft())
    {
        if (father->left_tree != v)
        {
            father->left_tree = v;
            v->father = father;
        }
    }
    else
    {
        if (father->right_tree != v)
        {
            father->right_tree = v;
            v->father = father;
        }
    }
}

template <class T>
bool AVLTree<T>::isLeft()
{
    return father->left_tree == this;
}

template <class T>
void AVLTree<T>::LL()
{
    AVLTree<T> *A = this->left_tree, *B = this;
    AVLTree<T> *AR_temp = A->right_tree;
    // changing A to be root
    changetoRoot(A);

    // changing B to right son of A
    A->right_tree = B;
    B->father = A;
    
    //make A right tree to B left
    B->left_tree = AR_temp;
    if (AR_temp != nullptr)
    {
        AR_temp->father = B;
    }    

    //update height and balance
    B->height = B->calculateHeight();
    B->balance = B->calculateBalance();
    A->height = A->calculateHeight();
    A->balance = A->calculateBalance();
}

template <class T>
void AVLTree<T>::RR()
{
    AVLTree<T> *A = this->right_tree, *B = this;
    AVLTree<T> *AL_temp = A->left_tree;
    // changing A to be root
    changetoRoot(A);

    // changing B to left son of A
    A->left_tree = B;
    B->father = A;

    //make A left tree to B right
    B->right_tree = AL_temp;
    if (AL_temp != nullptr)
    {
        AL_temp->father = B;
    }

    //update height and balance
    B->height = B->calculateHeight();
    B->balance = B->calculateBalance();
    A->height = A->calculateHeight();
    A->balance = A->calculateBalance();
}


template <class T>
void AVLTree<T>::LR()
{
    this->left_tree->RR();
    LL();
}

template <class T>
void AVLTree<T>::RL()
{
    this->right_tree->LL();
    RR();
}

template <class Id>
StatusType deleteElement(Id &data)
{
    AVLTree<T> *element_ptr = getNode(data);
    if (element_ptr == nullptr)
    {
        return FAILURE;
    }
    deleteThisElement(element_ptr);

}

template <class T>
StatusType AVLTree<T>::deleteThisElement(AVLTree<T> *v)
{
    if (v->right_tree != nullptr && v->left_tree != nullptr)
    {
        AVLTree<T> *next = getNextInorder();
        switchPlaces(next);
        deleteThisElement(next);

    }
    else
    {
        if (isLeaf())
        {
            if (isLeft())
            {
                v->father->left_tree = nullptr;
                delete v;
            }
            else
            {
                v->father->right_tree = nullptr;
                delete v;
            }
            
        }
        else if (left_tree == nullptr)
        {
            v->changetoRoot(right_tree);
            delete v;
        }
        else
        {
            v->changetoRoot(left_tree);
            delete v;
        }
        
    }
    return SUCCESS;
}

template <class T>
void AVLTree<T>::switchPlaces(AVLTree<T> *v)
{
    T tmp = v.data;
    v.data = data;
    data = tmp;
}

template <class T>
bool AVLTree<T>::isLeaf()
{
    return right_tree == nullptr && left_tree == nullptr;
}

template <class T>
bool AVLTree<T>::isRoot()
{
    return father.height == -1;
}

template <class T>
AVLTree<T> *AVLTree<T>::getLeftTree()
{
    return left_tree;
}

template <class T>
AVLTree<T> *AVLTree<T>::getRightTree()
{
    return right_tree;
}

template <class T>
T AVLTree<T>::getData()
{
    return data;
}

template <class T>
AVLTree<T> *AVLTree<T>::getNextInorder()
{
    return right_tree->first;
}

template <class T>
StatusType AVLTree<T>::insertElement(T &element)
{
    if (this->left_tree == nullptr)
    {
        left_tree = new AVLTree(element);
        left_tree->father = this;
        return SUCCESS;
    }
    return this->left_tree->insertElementAux(element);
}

template <class T>
AVLTree<T> *AVLTree<T>::getTree()
{
    return this->left_tree;
}

template <class T>
template <class Id>
AVLTree<T> *AVLTree<T>::getNode(Id &data_in)
{
    if (left_tree == nullptr)
    {
        return FAILURE;
    }
    return left_tree->getNodeAux(data_in);
}

template <class T>
template <class Id>
AVLTree<T> *AVLTree<T>::getNodeAux(Id &data_in)
{
    if (this == nullptr || data == data_in)
    {
        return this;
    }
    if (data > data_in)
    {
        return left_tree->getNodeAux(data_in);
    }
    return right_tree->getNodeAux(data_in);
}

template <class T>
template <class Id>
AVLTree<T> *AVLTree<T>::getNodeAux(Id &data_in)
{
    if (this == nullptr || isLeaf())
    {
        return nullptr;
    }
    if (left_tree != nullptr && left_tree->data == data_in)
    {
        deleteThisElement(left_tree);
    }
    if (right_tree != nullptr && right_tree->data == data_in)
    {
        deleteThisElement(right_tree);
    }
    if (data > data_in)
    {
        return left_tree->getNodeAux(data_in);
    }
    return right_tree->getNodeAux(data_in);
}