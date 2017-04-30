#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

//! Classe LinkedQueue
/*! A Classe LinkedQueue é uma fila de dados encadeada. */

template<typename T>
class LinkedQueue {
 public:
    LinkedQueue() = default;

    ~LinkedQueue() {
        clear();
    }

    //! Método clear
    /*! O método clear limpa a fila. */
    void clear() {
        Node *previous = head;
        while (previous != nullptr) {
            previous = previous->next();
            dequeue();
        }
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    }  // limpar

    //! Método enqueue
    /*! O método enqueue insere dados na fila. */
    void enqueue(const T& data) {
        if (empty()) {
            head = new Node(data, nullptr);
            tail = head;
        } else {
            tail->next(new Node(data, nullptr));
            tail = tail->next();
        }
        // n->next(nullptr);
        // tail = new Node(data, nullptr);
        size_++;
    }  // enfilerar

    //! Método dequeue
    /*! O método dequeue retira dados da fila. */
    T dequeue() {
        if (empty()) {
            throw(std::out_of_range("A fila está vazia."));
        }
        Node *n = head;
        T back = n->data();
        head = head->next();
        delete n;
        size_--;
        return back;
    }  // desenfilerar

    //! Método front
    /*! O método front retorna o primeiro dado da fila. */
    T& front() const {
        if (empty()) {
            throw(std::out_of_range("A fila está vazia."));
        }
        return head->data();
    }  // primeiro dado

    //! Método back
    /*! O método back retorna o ultimo dado da fila. */
    T& back() const {
        if (empty()) {
            throw(std::out_of_range("A fila está vazia."));
        }
        return tail->data();
    }  // último dado

    //! Método empty
    /*! O método empty verifica se a fila está vazia. */
    bool empty() const {
        return (size_ == 0);
    }  // fila vazia

    //! Método size
    /*! O método size retorna o tamanho total da fila. */
    std::size_t size() const {
        return size_;
    }  // tamanho

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

    Node* head{nullptr};  // nodo-cabeça
    Node* tail{nullptr};  // nodo-fim
    std::size_t size_{0u};  // tamanho
};

}  // namespace structures

#endif
