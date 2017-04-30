#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

//! Classe LinkedStack
/*! A Classe LinkedStack é uma pilha de dados encadea. */

template<typename T>
class LinkedStack {
 public:
    LinkedStack() = default;

    ~LinkedStack() {
        Node *current, *previous;
        current = top_;
        while (current != nullptr) {
            previous = current;
            current = current->next();
            delete previous;
        }
    }

    //! Método clear
    /*! O método clear limpa a pilha. */
    void clear() {
        Node *previous = top_;
        while (previous != nullptr) {
            previous = previous->next();
            pop();
        }
        size_ = 0;
    }  // limpa pilha

    //! Método push
    /*! O metódo push empilha os dados na pilha. */
    void push(const T& data) {
        top_ = new Node(data, top_);
        size_++;
    }  // empilha

    //! Método pop
    /*! O método pop desempilha os dados até que a pilha fique vazia. */
    T pop() {
        T back;
        if (empty()) {
            throw(std::out_of_range("A pilha está vazia."));
        }
        Node *out = top_;
        back = out->data();
        top_= out->next();
        delete out;
        size_--;
        return back;
    }  // desempilha

    //! Método top
    /*! O método top retorna o dado que estiver no topo. */
    T& top() const {
        if (empty()) {
            throw(std::out_of_range("A pilha está vazia."));
        }
        return top_->data();
    }  // dado no topo

    //! Método empty
    /*! O método empty verifica se a pilha está vazia. */
    bool empty() const {
        return (size_ == 0);
    }  // pilha vazia

    //! Método size
    /*! O método size retorna o tamanho total da pilha. */
    std::size_t size() const {
        return size_;
    }  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data) {
            data_ = data;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        T& data() {
            return data_;
        }  // getter: info

        const T& data() const {
            return data_;
        }  // getter-constante: info

        Node* next() {
            return next_;
        }  // getter: próximo

        const Node* next() const {
            return next_;
        }  // getter-constante: próximo

        void next(Node* next) {
            next_ = next;
        }  // setter: próximo

     private:
        T data_;
        Node* next_;
    };

    Node* top_{nullptr};  // nodo-topo
    std::size_t size_{0u};  // tamanho
};

}  // namespace structures

#endif
