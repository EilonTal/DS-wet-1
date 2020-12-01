#include <memory>
template<class T>
class AVLTreeNode
{
private:
    std::shared_ptr<AVLTreeNode> left;
    std::shared_ptr<AVLTreeNode> right;
    std::shared_ptr<AVLTreeNode> father;
    std::shared_ptr<AVLTreeNode> first;
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
    bool isLeaf();
    bool isRoot();
    template<class Data>
    StatusType insertElement(Data &data);
    template<class Id>
    StatusType deleteElement(Id &data);
    template<class S>
    std::shared_ptr<S> getBestElements(int num_of_elements);
};

