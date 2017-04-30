#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

//! Classe ArrayList
/*! A classe ArrayList implementa uma lista de dados genérica. */

template<typename T>
class ArrayList {
 public:
    ArrayList() {
        max_size_ = DEFAULT_MAX;
        contents = new T[max_size_];
        size_ = 0;
    }

    explicit ArrayList(std::size_t max_size) {
        // param O parametro max_size define o tamanho genérico da lista.
        max_size_ = max_size;
        contents = new T[max_size_];
        size_ = 0;
    }

    ~ArrayList() {
        delete[] contents;
    }

    //! Método clear
    /*! O método clear elimina os dados da lista. */
    void clear() {
        size_ = 0;
    }

    //! Método push_back
    /*! O método push_back insere dados na ultima posição da lista. */
    void push_back(const T& data) {
        if (full()) {
            throw(std::out_of_range("A lista está cheia."));
        } else {
            contents[size_++] = data;
        }
    }

    //! Método push_front
    /*! O método push_front insere dados na primeira posição da lista. */
    void push_front(const T& data) {
        if (full()) {
            throw(std::out_of_range("A lista está cheia."));
        } else if (empty()) {
            contents[size_++] = data;
        } else {
            for (int i = size_; i >= 1; i--) {
                contents[i] = contents[i-1];
            }
            contents[0] = data;
            size_++;
        }
    }

    //! Método insert
    /*! O método insert adiciona um dado em uma determinada posição da lista. */
    void insert(const T& data, std::size_t index) {
        if (full()) {
            throw(std::out_of_range("A lista está cheia."));
        } else if ((index > max_size_-1) || (index < 0)) {
            // excecao
            throw(std::out_of_range("A posição não existe na lista."));
        } else {
            int atl = size_;
            while (atl != index) {
                contents[atl] = contents[atl-1];
                atl--;
            }
            contents[index] = data;
            size_++;
        }
    }

    //! Método insert_sorted
    /*! O método insert_sorted insere um dado conforme uma especificação. */
    void insert_sorted(const T& data) {
        if (full()) {
            throw(std::out_of_range("A lista está cheia."));
        } else if (empty()) {
            contents[size_++] = data;
        } else {
            int atl = 0;
            while ((atl != size_) && (data > contents[atl])) {
                atl++;
            }
            insert(data, atl);
        }
    }

    //! Método pop
    /*! O método pop retira um dado de uma determinada posição. */
    T pop(std::size_t index) {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        } else if ((index < 0) || index >= size_) {
            throw(std::out_of_range("O índice é inválido."));
        }
        T val = contents[index];
        for (int i = index; i != size_-1; i++) {
            contents[i] = contents[i+1];
        }
        size_--;
        return val;
    }

    //! Método pop_back
    /*! O método pop_back retira dados da ultima posição da lista. */
    T pop_back() {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        }
        size_--;
        return contents[size_];
    }

    //! Método pop_front
    /*! O método pop_front retira dados do começo da lista. */
    T pop_front() {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        }
        T val = contents[0];
        for (int i = 0; i < size_-1; i++) {
            contents[i] = contents[i+1];
        }
        size_--;
        return val;
    }

    //! Método remove
    /*! O método remove exclui um dado da lista. */
    void remove(const T& data) {
        if (empty()) {
            throw(std::out_of_range("A lista está vazia."));
        } else {
            for (int i = 0; i < size_; i++) {
                if (contents[i] == data) {
                    pop(i);
                }
            }
        }
    }

    //! Método full
    /*! O método full verifica se a lista está cheia. */
    bool full() const {
        return (size_ == max_size_);
    }

    //! Método empty
    /*! O método empty verifica se a lista está vazia. */
    bool empty() const {
        return (size_ == 0);
    }

    //! Método contains
    /*! O método contains verifica se um elemento está contido na lista. */
    bool contains(const T& data) const {
        for (int i = 0; i < size_; i++) {
            if (data == contents[i]) {
                return true;
            }
        }
        return false;
    }

    //! Método find
    /*! O método find retorna a posição do dado na lista. */
    std::size_t find(const T& data) const {
        for (int i = 0; i < size_; i++) {
            if (data == contents[i]) {
                return i;
            }
        }
        return size_;
    }

    //! Método size
    /*! O método size retorna o total de dados existentes na lista. */
    std::size_t size() const {
        return size_;
    }

    //! Método max_size
    /*! O método max_size retorna o tamanho total da lista. */
    std::size_t max_size() const {
        return max_size_;
    }

    //! Método at
    /*! O método at remove um dado de uma determinada posição. */
    T& at(std::size_t index) {
        if (index >= size_) {
            throw(std::out_of_range("A posição não existe."));
        }
        return contents[index];
    }

    //! Método operator
    /*! O método operator acessa um elemento da lista. */
    T& operator[](std::size_t index) {
        return contents[index];
    }

    //! Método at
    /*! O método at remove um dado de um indice sem alterar o objeto. */
    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw(std::out_of_range("A posição não existe."));
        }
        return contents[index];
    }

    //! Método operator
    /*! O método operator acessa um elemento da lista sem modificar o objeto. */
    const T& operator[](std::size_t index) const {
        return contents[index];
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif
