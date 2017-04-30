#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

//! Classe ArrayQueue
/*! A Classe ArrayQueue é uma fila de dados genérica. */

template<typename T>
class ArrayQueue {
 private:
    T* contents;
    int beg_, end_;
    std::size_t max_size_;
    static const auto DEFAULT_SIZE = 10u;

 public:
    ArrayQueue() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        beg_ = -1;
        end_ = -1;
    }

    explicit ArrayQueue(std::size_t max) {
        // param o parametro max define o tamanho genérico da fila.
        max_size_ = max;
        contents = new T[max_size_];
        beg_ = -1;
        end_ = -1;
    }

    ~ArrayQueue() {
        delete[] contents;
    }

    //! Método enqueue
    /*! O método enqueue insere dados na fila. */
    void enqueue(const T& data) {
        if (full()) {
            throw(std::out_of_range("A fila está cheia."));  // excecao
        }
        end_++;
        contents[end_] = data;
    }  // insere

    //! Método dequeue
    /*! O método dequeue retira dados da fila. */
    T dequeue() {
        if (empty()) {
            throw(std::out_of_range("A fila está vazia."));  // excecao
        }
        beg_++;
        return contents[beg_];
    }  // retira

    //! Método back
    /*! O método back retorna o dado primeiro dado da fila. */
    T& back() {
        if (empty()) {
            throw(std::out_of_range("A fila está vazia."));  // excecao
        } else {
            return contents[end_];
        }
    }

    //! Método clear
    /*! O método clear limpa a fila. */
    void clear() {
        beg_ = -1;
        end_ = -1;
    }  // limpa

    //! Método size
    /*! O método size retorna o total de dados existentes na fila. */
    std::size_t size() {
        return (end_-beg_);
    }

    //! Método max_size
    /*! O método max_size retorna o tamanho total da fila. */
    std::size_t max_size() {
        return max_size_;
    }

    //! Método empty
    /*! O método empty verifica se a fila está vazia. */
    bool empty() {
        if (beg_ == end_) {
            return true;
        }
        return false;
    }  // vazia

    //! Método full
    /*! O método full verifica se fila está cheia. */
    bool full() {
        if (end_-beg_ == static_cast<int>(max_size_)) {
            return true;
        }
        return false;
    }  // cheia
};

}  // namespace structures

#endif
