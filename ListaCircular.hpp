#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

//! Classe CircularList
/*! A classe CircularList implementa uma lista circular genérica. */

template<typename T>
class CircularList {
 public:
    CircularList() = default;

    ~CircularList() {
        clear();
    }

    //! Método clear
    /*! O método clear apaga os dados da lista. */
    void clear() {
        head = nullptr;
        size_ = 0;
    }  // limpar lista

    //! Método push_back
    /*! O método push_back insere dados no fim da lista. */
    void push_back(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node *n = new Node(data, head);
            Node *last = head;
            for (int i = 0; i < size_-1; i++) {
                last = last->next();
            }
            last->next(n);
            size_++;
        }
    }  // inserir no fim

    //! Método push_front
    /*! O método push_front insere dados no começo da lista. */
    void push_front(const T& data) {
        if (empty()) {
            head = new Node{data};
            head->next(head);
        } else {
            Node *last = head;
            for (int i = 0; i < size_-1; i++) {
                last = last->next();
            }
            head = new Node(data, head);
        }
        size_++;
    }  // inserir no início

    //! Método insert
    /*! O método insert insere dados em uma posição da lista. */
    void insert(const T& data, std::size_t index) {
        if (index < 0 || index > size_) {
            throw(std::out_of_range("A posição não existe."));
        }
        if (index == 0) {
            push_front(data);
        } else if (index == size_) {
            push_back(data);
        } else {
            Node *n = new Node(data);
            Node *last = head;
            for (int i = 1; i < index; i++) {
                last = last->next();
            }
            n->next(last->next());
            last->next(n);
            size_++;
        }
    }  // inserir na posição

    //! Método insert_sorted
    /*! O método insert_sorted insere dados em ordem na lista. */
    void insert_sorted(const T& data) {
        if (empty() || (data < head->data())) {
            return push_front(data);
        } else {
            Node *n = head;
            int i = 0;
            while ((i < size_) && (data > n->data())) {
                i++;
                n = n->next();
            }
            insert(data, i);
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
    }  // acessar em um indice (com checagem de limites)

    //! Método at
    /*! O método at acessa um dado de um indice. */
    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw(std::out_of_range("A posição não existe."));
        }
        Node *n = head;
        for (int i = 0; i < index; i++) {
            n = n->next();
        }
        return n->data();
    }  // versão const do acesso ao indice

    //! Método pop
    /*! O método pop retira um dado de uma posição. */
    T pop(std::size_t index) {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        }
        if (index < 0 || index >= size_) {
            throw(std::out_of_range("A posição não existe."));
        }
        if (size_ == 1 || index == 0) {
            return pop_front();
        }
        if (index == size_-1) {
            return pop_back();
        }
        Node *previous = head;
        for (int i = 1; i < index; i++) {
            previous = previous->next();
        }
        auto old = previous->next();
        T back = old->data();
        previous->next(old->next());
        size_--;
        delete old;
        return back;
    }  // retirar da posição

    //! Método pop_back
    /*! O método pop_back retira dados do fim da lista. */
    T pop_back() {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        }
        if (size_ == 1) {
            return pop_front();
        }
        Node *n = head;
        for (int i = 2; i < size_; i++) {
            n = n->next();
        }
        auto old = n->next();
        T back = old->data();
        n->next(head);
        delete old;
        size_--;
        return back;
    }  // retirar do fim

    //! Método pop_front
    /*! O método pop_front remove dados do inicio da lista. */
    T pop_front() {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        }
        auto old = head;
        T back = old->data();
        head = old->next();
        Node *end = head;
        for (int i = 1; i < size_; i++) {
            end = end->next();
        }
        end = end->next();
        delete old;
        size_--;
        return back;
    }  // retirar do início

    //! Método remove
    /*! O método remove exclui um dado da lista. */
    void remove(const T& data) {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        } else {
            Node *n = head;
            for (int i = 0; i < size_; i++) {
                if (data == n->data()) {
                    pop(i);
                    return;
                }
                n = n->next();
            }
        }
    }  // remover dado específico

    //! Método empty
    /*! O método empty verifica se a lista está vazia. */
    bool empty() const {
        return (size_ == 0);
    }  // lista vazia

    //! Método contains
    /*! O método contains verifica se um dado está na lista. */
    bool contains(const T& data) const {
        return find(data) != size_;
    }  // lista contém determinado dado?

    //! Método find
    /*! O método find procura a posição de um dado na lista. */
    std::size_t find(const T& data) const {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        }
        Node *n = head;
        for (int i = 0; i < size_; i++) {
            if (data == n->data()) {
                return (i);
            }
            n = n->next();
        }
        return size_;
    }  // posição de um item na lista

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

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
