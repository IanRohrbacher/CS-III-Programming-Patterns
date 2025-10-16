#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include "list.hpp"

// forward class declaration
template<typename T>
class Collection;

// forward function declaration
template<typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template<typename T>
class Collection{
    public:
        Collection() : collectionStart_(nullptr), size_(0) {};
        Collection(const Collection<T> &rhs);
        ~Collection();

        void add(T item);
        void remove(T item);
        T last();
        void print();

        void swap(Collection<T>&);

        Collection<T>& operator=(Collection<T> rhs) {swap(rhs); return *this;};

        friend bool equal<T>(const Collection &lhs, const Collection &rhs);
        
    private:
        node<T> *collectionStart_;
        int size_;
};

template<typename T>
Collection<T>::Collection(const Collection<T> &rhs) : collectionStart_(nullptr), size_(0) {
    if (rhs.collectionStart_ != nullptr) {
        collectionStart_ = new node<T>;
        node<T> *traversal = collectionStart_;
        node<T> *rhsTraversal = rhs.collectionStart_;
        while (rhsTraversal != nullptr) {
            traversal->setData(rhsTraversal->getData());
            if (rhsTraversal->getNext() != nullptr) {
                traversal->setNext(new node<T>);
                traversal = traversal->getNext();
            }
            rhsTraversal = rhsTraversal->getNext();
        }
        size_ = rhs.size_;
    }
}

template<typename T>
Collection<T>::~Collection(){
    node<T> *traversal = collectionStart_;
    while(traversal != nullptr) {
        node<T> *temp = traversal;
        traversal = traversal->getNext();
        delete temp;
    }
}

template<typename T>
void Collection<T>::add(T item){
    node<T> *newNode = new node<T>;
    newNode->setData(item);
    newNode->setNext(nullptr);
    if(size_ == 0) {
        collectionStart_ = newNode;
    } else {
        node<T> *traversal = collectionStart_;
        while(traversal->getNext() != nullptr) {
            traversal = traversal->getNext();
        }
        traversal->setNext(newNode);
    }
    size_++;
}

template<typename T>
void Collection<T>::remove(T item){
    node<T> *traversal = collectionStart_;
    node<T> *prev = nullptr;
    while(traversal != nullptr) {
        if(traversal->getData() == item) {
            if(prev == nullptr) {
                collectionStart_ = traversal->getNext();
            } else {
                prev->setNext(traversal->getNext());
            }
            node<T> *temp = traversal;
            traversal = traversal->getNext();
            delete temp;
            size_--;
        } else {
            prev = traversal;
            traversal = traversal->getNext();
        }
    }
}

template<typename T>
T Collection<T>::last(){
    node<T> *traversal = collectionStart_;
    while(traversal->getNext() != nullptr) {
        traversal = traversal->getNext();
    }
    return traversal->getData();
}

template<typename T>
void Collection<T>::print(){
    node<T> *traversal = collectionStart_;
    while(traversal != nullptr) {
        std::cout << traversal->getData() << (traversal->getNext() != nullptr  ? ", " : "");
        traversal = traversal->getNext();
    }
    std::cout << std::endl;
}

template<typename T>
void Collection<T>::swap(Collection<T> &rhs){
    node<T> *tempStart = collectionStart_;
    collectionStart_ = rhs.collectionStart_;
    rhs.collectionStart_ = tempStart;

    int tempSize = size_;
    size_ = rhs.size_;
    rhs.size_ = tempSize;
}

template <typename T> 
bool equal(const Collection<T> &lhs, const Collection<T> &rhs) {
    node<T> *lhsTraversal = lhs.collectionStart_;
    node<T> *rhsTraversal = rhs.collectionStart_;
    if(lhs.size_ != rhs.size_) {
        return false;
    }
    while(lhsTraversal != nullptr) {
        if(lhsTraversal->getData() != rhsTraversal->getData()) {
            return false;
        }
        lhsTraversal = lhsTraversal->getNext();
        rhsTraversal = rhsTraversal->getNext();
    }
    return true;
}

#endif // COLLECTION_HPP_
