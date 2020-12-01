#include <memory>
#include "library.h"
template<class T>
class AVLTree
{
private:
    std::shared_ptr<AVLTree> left_tree;
    std::shared_ptr<AVLTree> right_tree;
    std::shared_ptr<AVLTree> father;
    std::shared_ptr<AVLTree> first;
    int hight;
    int balance;
    T data;
    /*
    * return the hight of the left tree
    * if has no left return 0
    */
    int getLeftHight();
    /*
    * return the hight of the right tree
    * if has no right return 0
    */
    int getRightHight();
    /*
    * return the hight of the tree (H(left)+H(right)+1)
    */
    int calculateHight();
    /*
    * return the balance of the tree (H(left)-H(right))
    */
    int calculateBalance();
    //?
    bool isLeaf();
    bool isRoot();
    std::shared_ptr<AVLTree> getLeftTree();
    std::shared_ptr<AVLTree> getRightTree();
    std::shared_ptr<AVLTree> getFather();
    StatusType setFather(std::shared_ptr<AVLTree>  element);
    std::shared_ptr<AVLTree> getFirst();
    //?
    template<class Id>
    std::shared_ptr<AVLTree> getElementPointer(Id &data);
    void setFather(T& data);
    /*
    * get the T element to insert 
    * insert it to the left tree 
    * if there is no such left tree create new tree element of it and insert it
    * return FAILURE if element alredy exists
    *       else return SECCESS 
    */
    StatusType insertToLeft(T& element);
    /*
    * get the T element to insert 
    * insert it to the right tree 
    * if there is no such right tree create new tree element of it and insert it
    * return FAILURE if element alredy exists
    *       else return SECCESS 
    */
    StatusType insertToRight(T& element);

    StatusType deleteThisElement(std::shared_ptr<AVLTree> v);
    void LL();
    void LR();
    void RL();
    void RR();
    /*
    * check which roll to do acording to avl algoritem
    */
    void doRoll();

public:
    AVLTree(T& data);
    ~AVLTree() = default;
    AVLTree(AVLTree& element) = default;
    AVLTree& operator=(AVLTree& element) = default;
    /*
    * get the T element to insert 
    * insert it to the tree according to T order
    * return FAILURE if element alredy exists
    *       else return SECCESS 
    */
    StatusType insertElement(T &element);
    template<class Id>
    StatusType deleteElement(Id &data);
    template<class Id>
    StatusType getElement(Id &data);
    template<class S>
    std::shared_ptr<S> getBestElements(int num_of_elements);
    std::shared_ptr<AVLTree> getPointer();
};

