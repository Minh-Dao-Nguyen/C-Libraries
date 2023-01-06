#pragma once
#include <iostream>
#include <cstddef>     // size_t
#include <iterator>    // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if
using namespace std;
template <class T>
class List
{
private:
    struct Node
    {
        Node *next, *prev;
        T data;
        explicit Node(Node *prev = nullptr, Node *next = nullptr)
            : next{next}, prev{prev} {}
        explicit Node(const T &data, Node *prev = nullptr, Node *next = nullptr)
            : next{next}, prev{prev}, data{data} {}
        explicit Node(T &&data, Node *prev = nullptr, Node *next = nullptr)
            : next{next}, prev{prev}, data{std::move(data)} {}
    };

    template <typename pointer_type, typename reference_type>
    class basic_iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = pointer_type;
        using reference = reference_type;

    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node *node;

        explicit basic_iterator(Node *ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node *ptr) noexcept : node{const_cast<Node *>(ptr)} {}

    public:
        basic_iterator()
        { /* TODO */
            node = nullptr;
        };
        basic_iterator(const basic_iterator &) = default;
        basic_iterator(basic_iterator &&) = default;
        ~basic_iterator() = default;
        basic_iterator &operator=(const basic_iterator &) = default;
        basic_iterator &operator=(basic_iterator &&) = default;

        reference operator*() const
        {
            // TODO
            return node->data;
        }
        pointer operator->() const
        {
            // TODO
            return &(node->data);
        }

        // Prefix Increment: ++a
        basic_iterator &operator++()
        {
            // TODO
            node = node->next;
            return *this;
        }
        // Postfix Increment: a++
        basic_iterator operator++(int)
        {
            // TODO
            auto temp = *this;
            node = node->next;
            return temp;
        }
        // Prefix Decrement: --a
        basic_iterator &operator--()
        {
            // TODO
            node = node->prev;
            return *this;
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int)
        {
            // TODO
            auto temp = *this;
            node = node->prev;
            return temp;
        }

        bool operator==(const basic_iterator &other) const noexcept
        {
            // TODO
            return node == other.node;
        }
        bool operator!=(const basic_iterator &other) const noexcept
        {
            // TODO
            return node != other.node;
        }
    };

public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = basic_iterator<pointer, reference>;
    using const_iterator = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    size_type _size;

public:
    List() : head{}, tail{}, _size{0}
    {
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
    }
    List(size_type count, const T &value) : head{}, tail{}, _size{0}
    {
        // TODO - Don't forget the list initialier
        // std::cout << "size: " << _size << std::endl;
        // if (_size == 0)
        // {
        //     head.next = &tail;
        //     tail.prev = &head;
        // }
        // else
        // {
        //     Node *firstNode = new Node(value);
        //     Node *prePointer = firstNode;
        //     head.next = firstNode;
        //     firstNode->prev = &head;
        //     for (size_type i = 1; i < _size; i++)
        //     {
        //         // make a new Node
        //         Node *newNode = new Node(value, prePointer);

        //         prePointer->next = newNode;
        //         prePointer = newNode;

        //         tail.prev = newNode;
        //         newNode->next = &tail;
        //     }
        // }
        head.next = &tail;
        tail.prev = &head;
        for (size_type i = 0; i < count; i++)
        {
            /*
            auto itr = cbegin();
            insert(itr, value);
            */
           push_back(value);
        }
    }
    explicit List(size_type count) : head{}, tail{}, _size{0}
    {
        // TODO - Don't forget the list initialier
        // if (_size == 0)
        // {
        //     head.next = &tail;
        //     tail.prev = &head;
        // }
        // else
        // {
        //     Node *firstNode = new Node();
        //     Node *prePointer = firstNode;
        //     head.next = firstNode;
        //     firstNode->prev = &head;
        //     for (size_type i = 1; i < _size; i++)
        //     {
        //         // make a new Node
        //         Node *newNode = new Node(prePointer);

        //         prePointer->next = newNode;
        //         prePointer = newNode;

        //         tail.prev = newNode;
        //         newNode->next = &tail;
        //     }
        // }
        head.next = &tail;
        tail.prev = &head;

        for (size_type i = 0; i < count; i++)
        {
            /*
            auto itr = cbegin();
            insert(itr, T());
            */
           push_back(T());
        }
    }
    List(const List &other) : head{}, tail{}, _size{0}
    {
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;

        auto itr = iterator(other.head.next);

        for (size_type i = 0; i < other._size; i++)
        {
            push_back(*itr);
            itr++;
        }
    }
    List(List &&other) : head{}, tail{}, _size{other._size}
    {
        if (other.empty())
        {
            head = tail;
        }
        else
        {
            // TODO - Don't forget the list initialier
            head.next = (other.head).next;
            tail.prev = (other.tail).prev;

            (head.next)->prev = &head;
            (tail.prev)->next = &tail;

            (other.head).next = &(other.tail);
            (other.tail).prev = &(other.head);
            other.head.prev = nullptr;
            other.tail.next = nullptr;
            other._size = 0;
        }
    }
    ~List()
    {
        // TODO
        clear();
    }
    List &operator=(const List &other)
    {
        // TODO
        if (other.head.next == head.next)
        {
            return *this;
        }
        clear();

        auto itr = iterator(other.head.next);

        for (size_type i = 0; i < other._size; i++)
        {
            push_back(*itr);
            itr++;
        }

        return *this;
    }
    List &operator=(List &&other) noexcept
    {
        // TODO
        if (other.head.next == head.next)
        {
            return *this;
        }
        clear();
        if (other.empty())
        {
            head = tail;
        }
        else
        {
            head.next = (other.head).next;
            tail.prev = (other.tail).prev;

            (head.next)->prev = &head;
            (tail.prev)->next = &tail;

            (other.head).next = &(other.tail);
            (other.tail).prev = &(other.head);
            other.head.prev = nullptr;
            other.tail.next = nullptr;

            _size = other._size;
            other._size = 0;
        }

        return *this;
    }

    reference front()
    {
        // TODO
        return (head.next)->data;
    }
    const_reference front() const
    {
        // TODO
        return (head.next)->data;
    }

    reference back()
    {
        // TODO
        return (tail.prev)->data;
    }
    const_reference back() const
    {
        // TODO
        return (tail.prev)->data;
    }

    iterator begin() noexcept
    {
        // TODO
        return iterator(head.next);
    }
    const_iterator begin() const noexcept
    {
        // TODO
        return const_iterator(head.next);
    }
    const_iterator cbegin() const noexcept
    {
        // TODO
        return const_iterator(head.next);
    }

    iterator end() noexcept
    {
        // TODO
        return iterator(&tail);
    }
    const_iterator end() const noexcept
    {
        // TODO
        return const_iterator(&tail);
    }
    const_iterator cend() const noexcept
    {
        // TODO
        return const_iterator(&tail);
    }

    bool empty() const noexcept
    {
        // TODO
        return _size == 0;
    }

    size_type size() const noexcept
    {
        // TODO
        return _size;
    }

    void clear() noexcept
    {
        // TODO
        /*
        for (size_type i = 0; i < _size; i++)
        {
            head.prev = head.next;
            head.next = (head.next)->next;
            delete head.prev;
        }
        head.next = &tail;
        tail.prev = &head;
        _size = 0;
        */

       iterator current(head.next); 
       for(size_t i = 0; i < _size; i++){
            ++current;
            delete current.node->prev; 

       }
        head.next = &tail; 
        tail.prev = &head; 
        _size = 0;
    }

    iterator insert(const_iterator pos, const T &value)
    {
        // TODO
        
        Node *newNode = new Node(value);
        Node *prevNode = pos.node->prev;
        newNode->next = pos.node;
        newNode->prev = prevNode;

        prevNode->next = newNode;
        pos.node->prev = newNode;

        ++_size;
        return iterator(newNode);
    }
    iterator insert(const_iterator pos, T &&value)
    {
        // TODO
        Node *newNode = new Node(std::move(value));
        Node *prevNode = pos.node->prev;

        newNode->next = pos.node;
        newNode->prev = prevNode;

        prevNode->next = newNode;
        pos.node->prev = newNode;

        ++_size;
        return iterator(newNode);

    }

    iterator erase(const_iterator pos)
    {
        // TODO
        Node *removeNode = pos.node;

        Node *preNode = pos.node->prev;
        Node *nextNode = pos.node->next;

        preNode->next = nextNode;
        nextNode->prev = preNode;

        removeNode->next = nullptr;
        removeNode->prev = nullptr;
        delete pos.node;

        _size--;

        return iterator(nextNode);
    }

    void push_back(const T &value)
    {
        // TODO
        Node *newNode = new Node(value);

        newNode->next = &tail;
        newNode->prev = tail.prev;

        newNode->prev->next = newNode;
        tail.prev = newNode;

        ++_size;
    }
    void push_back(T &&value)
    {
        // TODO
        Node *newNode = new Node(std::move(value));

        newNode->next = &tail;
        newNode->prev = tail.prev;

        newNode->prev->next = newNode;
        tail.prev = newNode;

        ++_size;
    }

    void pop_back()
    {
        // TODO
        auto itr = cend(); 
        erase(--itr); 
    }

    void push_front(const T &value)
    {
        // TODO
        insert(cbegin(), value); 
    }
    void push_front(T &&value)
    {
        // TODO
        insert(cbegin(), std::move(value));
    }

    void pop_front()
    {
        // TODO
        erase(cbegin()); 
    }

    /*
      You do not need to modify these methods!

      These method provide the non-const complement
      for the const_iterator methods provided above.
    */
    iterator insert(iterator pos, const T &value)
    {
        return insert((const_iterator &)(pos), value);
    }

    iterator insert(iterator pos, T &&value)
    {
        return insert((const_iterator &)(pos), std::move(value));
    }

    iterator erase(iterator pos)
    {
        return erase((const_iterator &)(pos));
    }
};

/*
    You do not need to modify these methods!

    These method provide a overload to compare const and
    non-const iterators safely.
*/

namespace
{
    template <typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator,
            Iter>{} &&
            std::is_same<
                typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
                ConstIter>{},
        T>::type;
}

template <typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator &lhs, const ConstIter &rhs)
{
    return (const ConstIter &)(lhs) == rhs;
}

template <typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter &lhs, const Iterator &rhs)
{
    return (const ConstIter &)(rhs) == lhs;
}

template <typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator &lhs, const ConstIter &rhs)
{
    return (const ConstIter &)(lhs) != rhs;
}

template <typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter &lhs, const Iterator &rhs)
{
    return (const ConstIter &)(rhs) != lhs;
}