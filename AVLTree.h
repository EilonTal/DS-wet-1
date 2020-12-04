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
    static const int height_of_queen = -1;
    int num_of_elements_in_tree;
    int height;
    int balance;
    T data;
    AVLTree(T &);
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
    void updateNumOfElements();
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
    AVLTree<T> *getNodeFromId(Id &data_in);

    void getBestElementsAux(T *&element, AVLTree<T> *v, int num_of_elements, int &i);
    

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

    template <class Id>
    T* getElement(Id &data_in);

    T *getBestElements(int num_of_elements, int &counter_of_elements);

    //just for chacking:
    AVLTree *getLeftTree();
    AVLTree *getRightTree();
    T& getData();
    AVLTree *getTree();
    T& getFirst()
    {
        return first->data;
    }
};

template <class T>
AVLTree<T>::AVLTree()
    : data(), height(height_of_queen), first(nullptr), balance(0),
      father(nullptr), left_tree(nullptr), right_tree(nullptr), num_of_elements_in_tree(0)
{
}

template <class T>
AVLTree<T>::AVLTree(T &element)
    : data(element), height(1), first(this), balance(0), father(nullptr),
      left_tree(nullptr), right_tree(nullptr), num_of_elements_in_tree(1)
{
}

template <class T>
AVLTree<T>::~AVLTree()
{
    if (left_tree != nullptr)
    {
        delete left_tree;
        left_tree = nullptr;
    }
    if (right_tree != nullptr)
    {
        delete right_tree;
        right_tree = nullptr;
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
        first = left_tree->first;
        updateNumOfElements();
    }
    else
    {
        return_value = insertToRight(element);
        updateNumOfElements();
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
        first = left_tree;
        num_of_elements_in_tree ++;
    }
    else
    {
        return_value = left_tree->insertElementAux(element);
        updateNumOfElements();
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
        num_of_elements_in_tree++;
    }
    else
    {
        return_value = right_tree->insertElementAux(element);
        updateNumOfElements();
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
    updateNumOfElements();
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

    //update first
    if (B->left_tree != nullptr)
    {
        B->first = B->left_tree->first;
    
    }
    else
    {
        B->first = B;
    }
    //update height and balance
    B->height = B->calculateHeight();
    B->balance = B->calculateBalance();
    A->height = A->calculateHeight();
    A->balance = A->calculateBalance();
    B->updateNumOfElements();
    A->updateNumOfElements();
    
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

    //update first
    A->first = B->first;

    //update height and balance
    B->height = B->calculateHeight();
    B->balance = B->calculateBalance();
    A->height = A->calculateHeight();
    A->balance = A->calculateBalance();
    B->updateNumOfElements();
    A->updateNumOfElements();
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

template <class T>
template <class Id>
StatusType AVLTree<T>::deleteElement(Id &data)
{
    if (left_tree != nullptr)
    {
        if (left_tree->data == data)
        {
            deleteThisElement(left_tree);
            updateNumOfElements();
            return SUCCESS;
        }
        else
        {
            StatusType retrun_val = left_tree->deleteElementAux(data);
            updateNumOfElements();
            return retrun_val;
        }
    }
    return FAILURE;
}

template <class T>
StatusType AVLTree<T>::deleteThisElement(AVLTree<T> *v)
{
    if (v->right_tree != nullptr && v->left_tree != nullptr)
    {
        AVLTree<T> *next = v->getNextInorder();
        v->switchPlaces(next);
        deleteThisElement(next);
        v->updateNumOfElements();
        updateNumOfElements();
    }
    else
    {
        if (v->isLeaf())
        {
            if (v->isLeft())
            {
                v->father->left_tree = nullptr;
                v->father->first = v->father;
                v->left_tree = nullptr;
                v->right_tree = nullptr;
                delete v;
                v = nullptr;
                num_of_elements_in_tree--;
            }
            else
            {
                v->father->right_tree = nullptr;
                v->left_tree = nullptr;
                v->right_tree = nullptr;
                delete v;
                v = nullptr;
                num_of_elements_in_tree--;
            }
            
        }
        else if (v->left_tree == nullptr)
        {
            v->changetoRoot(v->right_tree);
            v->left_tree = nullptr;
            v->right_tree = nullptr;
            delete v;
            v = nullptr;
            num_of_elements_in_tree--;
        }
        else
        {
            v->changetoRoot(v->left_tree);
            v->left_tree = nullptr;
            v->right_tree = nullptr;
            delete v;
            v = nullptr;
            num_of_elements_in_tree--;
        }
        
    }
    updateNumOfElements();
    return SUCCESS;
}

template <class T>
void AVLTree<T>::switchPlaces(AVLTree<T> *v)
{
    T tmp = v->data;
    v->data = data;
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
T& AVLTree<T>::getData()
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
        num_of_elements_in_tree++;
        return SUCCESS;
    }
    StatusType retrun_val = this->left_tree->insertElementAux(element);
    updateNumOfElements();
    return retrun_val;
}

template <class T>
AVLTree<T> *AVLTree<T>::getTree()
{
    return this->left_tree;
}

template <class T>
template <class Id>
AVLTree<T> *AVLTree<T>::getNodeFromId(Id &data_in)
{
    if (left_tree == nullptr)
    {
        return nullptr;
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
StatusType AVLTree<T>::deleteElementAux(Id &data_in)
{
    if (this == nullptr || isLeaf())
    {
        return FAILURE;
    }
    if (left_tree != nullptr && left_tree->data == data_in)
    {
        deleteThisElement(left_tree);
        updateNumOfElements();
        if (left_tree != nullptr) 
        {
            first = left_tree->first;
        }
        else
        {
            first = this;
        }
    }
    else if (right_tree != nullptr && right_tree->data == data_in)
    {
        deleteThisElement(right_tree);
        updateNumOfElements();
    }
    else if (data > data_in)
    {
        if (left_tree->deleteElementAux(data_in) == FAILURE)
        {
            return FAILURE;
        }
        first = left_tree->first;
        updateNumOfElements();
    }
    else
    {
        if (right_tree->deleteElementAux(data_in) == FAILURE)
        {
            return FAILURE;
        }
        updateNumOfElements();
    }
    doRoll();
    return SUCCESS;
}

template <class T>
T *AVLTree<T>::getBestElements(int num_of_elements, int &counter_of_elements)
{
    if (num_of_elements == 0)
    {
        return nullptr;
    }
    counter_of_elements = 0;
    T* arr_of_elements = new T[num_of_elements];
    getBestElementsAux(arr_of_elements, left_tree->first, num_of_elements, counter_of_elements);
    return arr_of_elements;
}

template <class T>
void AVLTree<T>::getBestElementsAux(T *&element, AVLTree<T>* v, int num_of_elements, int &i)
{
    if (v == nullptr || v->height == height_of_queen)
    {
        return;
    }
    if (num_of_elements == i || i == num_of_elements_in_tree)
    {
        return;
    }
    T new_element(v->data);
    element[i] = new_element;
    i++;
    if (v->right_tree != nullptr)
    {
        getBestElementsAux(element, v->right_tree->first, num_of_elements, i);
    }
    if (num_of_elements == i || i == num_of_elements_in_tree)
    {
        return;
    }
    getBestElementsAux(element, v->father, num_of_elements, i);
}

template <class T>
template <class Id>
T *AVLTree<T>::getElement(Id &data_in)
{
    AVLTree<T> *node = getNodeFromId(data_in);
    if (node == nullptr)
    {
        return nullptr;
    }
    return &(node->data);
}

template <class T>
void AVLTree<T>::updateNumOfElements()
{

    int num = 0;
    if (this->height != height_of_queen)
    {
        num++;
    }
    if (left_tree != nullptr)
    {
        num += left_tree->num_of_elements_in_tree;
    }
    if (right_tree != nullptr)
    {
        num += right_tree->num_of_elements_in_tree;
    }
    num_of_elements_in_tree = num;
}