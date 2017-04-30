#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

//! Classe LinkedList
/*! A classe LinkedList implementa uma lista encadeada genérica. */

template<typename T>
class LinkedList {
 public:
    LinkedList() = default;  // construtor padrão

    ~LinkedList() {
        Node *current, *previous;
        current = head;
        while (current != nullptr) {
            previous = current;
            current = current->next();
            delete previous;
        }
    }  // destrutor

    //! Método clear
    /*! O método clear apaga os dados da lista. */
    void clear() {
        Node *previous = head;
        while (previous != nullptr) {
            previous = previous->next();
            pop_front();
        }
        size_ = 0;
    }  // limpar lista

    //! Método push_back
    /*! O método push_back insere dados no fim da lista. */
    void push_back(const T& data) {
        insert(data, size_);
    }  // inserir no fim

    //! Método push_front
    /*! O método push_front insere dados no começo da lista. */
    void push_front(const T& data) {
        head = new Node(data, head);
        size_++;
    }  // inserir no início

    //! Método insert
    /*! O método insert insere dados em uma posição da lista. */
    void insert(const T& data, std::size_t index) {
        if (index > size_) {
            throw(std::out_of_range("A posição não existe."));
        } else {
            if (index == 0) {
                push_front(data);
            } else {
                Node *n = new Node(data);
                Node *previous = head;
                for (auto i = 1u; i < index; ++i) {
                    previous = previous->next();
                }
                n->next(previous->next());
                previous->next(n);
                size_++;
            }
        }
    }  // inserir na posição

    //! Método insert_sorted
    /*! O método insert_sorted insere dados em ordem na lista. */
    void insert_sorted(const T& data) {
        if (empty() || head->data() > data) {
            push_front(data);
        } else {
            Node *current = head;
            while ((current != nullptr) && (current->next() != nullptr)
                   && (data > current->next()->data())) {
                current = current->next();
            }
            current->next(new Node(data, current->next()));
            size_++;
        }
    }  // inserir em ordem

    //! Método at
    /*! O método at acessa um dado de um indice. */
    T& at(std::size_t index) {
        if (index >= size_) {
            throw(std::out_of_range("A posição não existe."));
        }
        Node *n = head;
        for (int i = 0; i < index; i++) {
            n = n->next();
        }
        return n->data();
    }  // acessar um elemento na posição index

    //! Método pop
    /*! O método pop remove um dado de uma posição. */
    T pop(std::size_t index) {
        T back;
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        }
        if (index >= size_) {
            throw(std::out_of_range("A posição não existe."));
        }
        if (index == 0) {
            back = pop_front();
        } else {
            Node *previous = head;
            for (int i = 1; i < index; i++) {
                previous = previous->next();
            }
            Node *del = previous->next();
            back = del->data();
            previous->next(del->next());
            size_--;
            delete del;
        }
        return back;
    }  // retirar da posição

    //! Método pop_back
    /*! O método pop_back remove dados do fim da lista. */
    T pop_back() {
        return pop(size_-1);
    }  // retirar do fim

    //! Método pop_front
    /*! O método pop_front remove dados do inicio da lista. */
    T pop_front() {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        }
        Node *out = head;
        T back = out->data();
        head = out->next();
        size_--;
        delete out;
        return back;
    }  // retirar do início

    //! Método remove
    /*! O método remove exclui um dado da lista. */
    void remove(const T& data) {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        } else {
            Node *previous = head;
            Node *current = head->next();
            if (data == previous->data()) {
                head = previous->next();
                size_--;
                delete previous;
            } else {
                for (int i = 0; i < size_; i++) {
                    if (data == current->data()) {
                        previous->next(current->next());
                        size_--;
                        delete current;
                        return;
                    }
                    previous = previous->next();
                    current = current->next();
                }
            }
        }
    }  // remover específico

    //! Método empty
    /*! O método empty verifica se a lista está vazia. */
    bool empty() const {
        return (size_ == 0);
    }  // lista vazia

    //! Método contains
    /*! O método contains verifica se um dado está na lista. */
    bool contains(const T& data) const {
        Node *n = head;
        for (int i = 0; i < size_; i++) {
            if (data == n->data()) {
                return true;
            }
            n = n->next();
        }
        return false;
    }  // contém

    //! Método find
    /*! O método find procura a posição de um dado na lista. */
    std::size_t find(const T& data) const {
        Node *n = head;
        for (int i = 0; i < size_; i++) {
            if (data == n->data()) {
                return (i);
            }
            n = n->next();
        }
        return size_;
    }  // posição do dado

    //! Método size
    /*! O método size retorna o tamanho da lista. */
    std::size_t size() const {
        return size_;
    }  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
