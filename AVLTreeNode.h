#include <memory>
template<class T>
class AVLTreeNode
{
private:
    std::shared_ptr<AVLTreeNode> left;
    std::shared_ptr<AVLTreeNode> right;
    std::shared_ptr<AVLTreeNode> father;
    std::shared_ptr<AVLTreeNode> first, root;
    int hight;
    int balance;
    T data;

public:
    AVLTreeNode(T& data);
    ~AVLTreeNode() = default;
    AVLTreeNode(AVLTreeNode element);
    AVLTreeNode& operator=(AVLTreeNode& element);
    std::shared_ptr<AVLTreeNode> getLeft();
    std::shared_ptr<AVLTreeNode> getRight();
    std::shared_ptr<AVLTreeNode> getFather();
    void setLeft(std::shared_ptr<AVLTreeNode>  node);
    void setRight(std::shared_ptr<AVLTreeNode>  node);
    void setFather(std::shared_ptr<AVLTreeNode>  node);
    void setLeft(T& data);
    void setRight(T& data);
    void setFather(T& data);
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
    //?
    bool isLeaf();
    bool isRoot();
    /*
    template<class Data>
    StatusType insertElement(Data &data);
    template<class Id>
    StatusType deleteElement(Id &data);
    template<class S>
    std::shared_ptr<S> getBestElements(int num_of_elements);*/
    
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
};

