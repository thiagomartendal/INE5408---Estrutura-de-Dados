#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

//! Classe ArrayStack
/*! A Classe ArrayStack é uma pilha de dados genérica. */

template<typename T>
class ArrayStack {
 private:
    T* contents;
    int top_;
    std::size_t max_size_;
    static const auto DEFAULT_SIZE = 10u;

 public:
    ArrayStack() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        top_ = -1;
    }

    explicit ArrayStack(std::size_t max) {
        // param o parametro max define o tamanho genérico da pilha.
        max_size_ = max;
        contents = new T[max_size_];
        top_ = -1;
    }

    ~ArrayStack() {
        delete[] contents;
    }

    //! Método push
    /*! O metódo push empilha os dados enquanto a pilha não estiver cheia. */
    void push(const T& data) {
        if (full()) {
            throw(std::out_of_range("A pilha está cheia."));  // excecao
        }
        top_++;
        contents[top_] = data;
    }  // empilha

    //! Método pop
    /*! O método pop desempilha os dados até que a pilha fique vazia. */
    T pop() {
        if (empty()) {
            throw(std::out_of_range("A pilha está vazia."));  // excecao
            return 0;
        }
        top_--;
        return contents[top_+1];
    }  // desempilha

    //! Método top
    /*! O método top retorna o dado que estiver no topo. */
    T& top() {
        if (empty()) {
            throw("A pilha está vazia.");  // excecao
        } else {
            return contents[top_];
        }
    }

    //! Método clear
    /*! O método clear limpa a pilha. */
    void clear() {
        top_ = -1;
    }  // limpa

    //! Método size
    /*! O método size retorna a quantidade de dados existentes da pilha. */
    std::size_t size() {
       return top_+1;
    }  // tamanho

    //! Método max_size
    /*! O método max_size retorna o tamanho total da pilha. */
    std::size_t max_size() {
        return max_size_;
    }

    //! Método empty
    /*! O método empty verifica se a pilha está vazia. */
    bool empty() {
        if (top_ == -1) {
            return true;
        }
        return false;
    }  // vazia

    //! Método full
    /*! O método full verifica se a pilha está cheia. */
    bool full() {
        if (top_ == static_cast<int>(max_size_)-1) {
            return true;
        }
        return false;
    }  // cheia
};

}  // namespace structures

#endif
