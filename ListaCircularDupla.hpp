#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
// #include <memory>  // Memória dinâmica

namespace structures {

//! Classe DoublyCircularList
/*! A classe DoublyCircularList implementa uma lista dupla circular. */

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList() = default;

    ~DoublyCircularList() {
        Node *current, *previous;
        current = head;
        while (current != nullptr) {
            previous = current;
            current = current->next();
            delete previous;
        }
    }

    //! Método clear
    /*! O método clear apaga os dados da lista. */
    void clear() {
        Node *previous = head;
        while (previous != nullptr) {
            previous = previous->next();
            pop_front();
        }
        size_ = 0;
    }

    //! Método push_back
    /*! O método push_back insere dados no fim da lista. */
    void push_back(const T& data) {
        insert(data, size_);
    }  // insere no fim

    //! Método push_front
    /*! O método push_front insere dados no começo da lista. */
    void push_front(const T& data) {
        Node *n = new Node(data);
        n->next(head);
        n->prev(nullptr);
        head = n;
        size_++;
    }  // insere no início

    //! Método insert
    /*! O método insert insere dados em uma posição da lista. */
    void insert(const T& data, std::size_t index) {
        if (index > size_) {
            throw(std::out_of_range("A posição não existe."));
        } else {
            if (index == 0) {
                return push_front(data);
            }
            Node *n = new Node(data, head);
            Node *previous = head;
            for (int i = 0; i < index-1; i++) {
                previous = previous->next();
            }
            if (n->next() != nullptr) {
                n->next(previous->next());
            }
            if (n->next() != nullptr) {
                n->next()->prev(n);
            }
            previous->next(n);
            size_++;
        }
    }  // insere na posição

    //! Método insert_sorted
    /*! O método insert_sorted insere dados em ordem na lista. */
    void insert_sorted(const T& data) {
        if (empty() || head->data() > data) {
            push_front(data);
        } else {
            Node *n = head;
            while ((n != nullptr) && (n->next() != nullptr)
               && (data > n->next()->data())) {
                n = n->next();
            }
            n->next(new Node(data, n->next()));
            size_++;
        }
    }  // insere em ordem

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
            if (del->next() != nullptr) {
                del->next()->prev(previous);
            }
            size_--;
            delete del;
        }
        return back;
    }  // retira da posição

    //! Método pop_back
    /*! O método pop_back remove dados do fim da lista. */
    T pop_back() {
        return pop(size_-1);
    }  // retira do fim

    //! Método pop_front
    /*! O método pop_front remove dados do inicio da lista. */
    T pop_front() {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        }
        Node *out = head;
        T back = out->data();
        head = out->next();
        if (head != nullptr) {
            head->prev(nullptr);
        }
        size_--;
        delete out;
        return back;
    }  // retira do início

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
    }  // retira específico

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
    }  // acesso a um elemento (checando limites)

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
    }  // getter constante a um elemento

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
    }  // posição de um dado

    //! Método size
    /*! O método size retorna o tamanho da lista. */
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

        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            prev_ = prev;
            next_ = next;
        }

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
