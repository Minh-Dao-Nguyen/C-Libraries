#include <cstddef>    // size_t
#include <functional> // std::hash
#include <ios>
#include <utility> // std::pair
#include <iostream>

#include "primes.h"

template <typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class UnorderedMap
{
public:
    using key_type = Key;
    using mapped_type = T;
    using const_mapped_type = const T;
    using hasher = Hash;
    using key_equal = Pred;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

private:
    struct HashNode
    {
        HashNode *next;
        value_type val;

        HashNode(HashNode *next = nullptr) : next{next} {}
        HashNode(const value_type &val, HashNode *next = nullptr) : next{next}, val{val} {}
        HashNode(value_type &&val, HashNode *next = nullptr) : next{next}, val{std::move(val)} {}
    };

    size_type _bucket_count;
    HashNode **_buckets;

    HashNode *_head;
    size_type _size;

    Hash _hash;
    key_equal _equal;

    static size_type _range_hash(size_type hash_code, size_type bucket_count)
    {
        return hash_code % bucket_count;
    }

public:
    template <typename pointer_type, typename reference_type, typename _value_type>
    class basic_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = _value_type;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        const UnorderedMap *_map;
        HashNode *_ptr;

        explicit basic_iterator(UnorderedMap const *map, HashNode *ptr) noexcept
        { /* TODO */
            _map = map;
            _ptr = ptr;
        }

    public:
        basic_iterator()
        { /* TODO */
            _map = nullptr; 
            _ptr = nullptr;
        };

        basic_iterator(const basic_iterator &) = default;
        basic_iterator(basic_iterator &&) = default;
        ~basic_iterator() = default;
        basic_iterator &operator=(const basic_iterator &) = default;
        basic_iterator &operator=(basic_iterator &&) = default;
        reference operator*() const
        { /* TODO */
            return _ptr->val;
        }
        pointer operator->() const
        { /* TODO */
            return &(_ptr->val);
        }
        basic_iterator &operator++()
        { /* TODO */
            if (_ptr->next)
            {
                _ptr = _ptr->next;
            }
            else
            {

                size_type index = _map->_bucket(_ptr->val) + 1;
                for (size_type i = index; i < _map->_bucket_count; i++)
                {
                    if (_map->_buckets[i])
                    {
                        _ptr = _map->_buckets[i];
                        return *this;
                    }
                }
                _ptr = nullptr;
                // size_type _ptr = _map->_bucket(_ptr->val.first) + 1;
            }
            return *this;
        }
        basic_iterator operator++(int)
        { /* TODO */
            auto temp = *this;
            if (_ptr->next)
            {
                _ptr = _ptr->next;
            }
            else
            {
                size_type index = _map->_bucket(_ptr->val) + 1;
                for (size_type i = index; i < _map->_bucket_count; i++)
                {
                    if (_map->_buckets[i])
                    {
                        _ptr = _map->_buckets[i];
                        return temp;
                    }
                }
                _ptr = nullptr;
            }
            return temp;
        }
        bool operator==(const basic_iterator &other) const noexcept
        { /* TODO */
            return _ptr == other._ptr;
        }
        bool operator!=(const basic_iterator &other) const noexcept
        { /* TODO */
            return _ptr != other._ptr;
        }
    };

    using iterator = basic_iterator<pointer, reference, value_type>;
    using const_iterator = basic_iterator<const_pointer, const_reference, const value_type>;

    class local_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const key_type, mapped_type>;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        HashNode *_node;

        explicit local_iterator(HashNode *node) noexcept
        { /* TODO */
            _node = node;
        }

    public:
        local_iterator()
        { /* TODO */
            _node = nullptr;
        }

        local_iterator(const local_iterator &) = default;
        local_iterator(local_iterator &&) = default;
        ~local_iterator() = default;
        local_iterator &operator=(const local_iterator &) = default;
        local_iterator &operator=(local_iterator &&) = default;
        reference operator*() const
        { /* TODO */
            return _node->val;
        }
        pointer operator->() const
        { /* TODO */
            return &(_node->val);
        }
        local_iterator &operator++()
        { /* TODO */
            _node = _node->next;
            return *this;
        }
        local_iterator operator++(int)
        { /* TODO */
            auto temp = *this;
            _node = _node->next;
            return temp;
        }

        bool operator==(const local_iterator &other) const noexcept
        { /* TODO */
            return _node == other._node;
        }
        bool operator!=(const local_iterator &other) const noexcept
        { /* TODO */
            return _node != other._node;
        }
    };

private:
    size_type _bucket(size_t code) const
    { /* TODO */
        return _range_hash(code, _bucket_count);
    }
    size_type _bucket(const Key &key) const
    { /* TODO */
        return _bucket(_hash(key));
    }
    size_type _bucket(const value_type &val) const
    { /* TODO */
        return _bucket(val.first);
    }

    HashNode *&_find(size_type code, size_type bucket, const Key &key)
    { /* TODO */
        HashNode **temp = &_buckets[bucket];
        while (*temp)
        {
            if (_equal((*temp)->val.first, key))
            {
                return *temp;
            }
            temp = &((*temp)->next);
        }
        return *temp;
    }

    HashNode *&_find(const Key &key)
    { /* TODO */
        return _find(_hash(key), _bucket(key), key);
    }

    HashNode *_insert_into_bucket(size_type bucket, value_type &&value)
    { /* TODO */
        HashNode*& temp = _buckets[bucket];
        HashNode *newNode = new HashNode(std::move(value), temp);
        temp = newNode;
        // new Head
        if ((!_head) || (_bucket(_head->val.first) >= bucket))
        {
            _head = newNode;
        }
        _size++;

        return newNode;
    }

    void _move_content(UnorderedMap &src, UnorderedMap &dst)
    { /* TODO */
    }

public:
    explicit UnorderedMap(size_type bucket_count, const Hash &hash = Hash{},
                          const key_equal &equal = key_equal{})
    { /* TODO */
        _bucket_count = next_greater_prime(bucket_count);
        _buckets = new HashNode *[_bucket_count] {};
        _head = nullptr;
        _size = 0;
        _hash = hash;
        _equal = equal;
    }

    ~UnorderedMap()
    { /* TODO */
        clear();
        _bucket_count = 0;
        delete[] _buckets;
    }

    UnorderedMap(const UnorderedMap &other)
    { /* TODO */
        _bucket_count = other._bucket_count;
        _hash = other._hash;
        _equal = other._equal;
        _buckets = new HashNode *[_bucket_count] {};
        _size= 0;
        _head = nullptr;
        auto it = other.cbegin();
        while(it != other.cend()){
            insert(*it);
            it++; 
        }
    }

    UnorderedMap(UnorderedMap &&other)
    { /* TODO */
        _bucket_count = other._bucket_count;
        _buckets = other._buckets; 
        _head = other._head; 
        _size= other._size;
        _hash = other._hash;
        _equal = other._equal;
        //change other elements
        other._buckets = new HashNode *[_bucket_count] {};
        other._size = 0; 
        other._head = nullptr;
    }

    UnorderedMap &operator=(const UnorderedMap &other)
    { /* TODO */
        if(this == &other){
            return *this; 
        }
        clear();
        delete [] _buckets; 
        _bucket_count = other._bucket_count;
        _hash = other._hash;
        _equal = other._equal;
        _buckets = new HashNode *[_bucket_count] {};
        _size= 0;
        _head = nullptr;
        auto it = other.cbegin();
        while(it != other.cend()){
            insert(*it);
            it++; 
        }
        return *this; 
    }

    UnorderedMap &operator=(UnorderedMap &&other)
    { /* TODO */
        if(this == &other){
            return *this; 
        }
        clear();
        delete[] _buckets; 
        _bucket_count = other._bucket_count;
        _buckets = other._buckets; 
        _head = other._head; 
        _size= other._size;
        _hash = other._hash;
        _equal = other._equal;
        //change other elements
        other._buckets = new HashNode *[_bucket_count] {};
        other._size = 0; 
        other._head = nullptr;

        return *this; 
    }

    void clear() noexcept
    { /* TODO */
        for (size_type i = 0; i < _bucket_count; i++)
        {
            if (_buckets[i])
            {
                HashNode *temp = _buckets[i];
                while (temp)
                {
                    HashNode *temp2 = temp->next;
                    delete temp;
                    temp = temp2;
                }
                _buckets[i] = nullptr;
            }
        }
        _head = nullptr; 
        _size = 0;
    }

    size_type size() const noexcept
    { /* TODO */
        return _size;
    }

    bool empty() const noexcept
    { /* TODO */
        return (_size == 0);
    }

    size_type bucket_count() const noexcept
    { /* TODO */
        return _bucket_count;
    }

    iterator begin()
    { /* TODO */
        return iterator(this, _head);
    }
    iterator end()
    { /* TODO */
        return iterator(this, nullptr);
    }

    const_iterator cbegin() const
    { /* TODO */
        return const_iterator(this, _head);
    };
    const_iterator cend() const
    { /* TODO */
        return const_iterator(this, nullptr);
    };

    local_iterator begin(size_type n)
    { /* TODO */
        return local_iterator(_buckets[n]);
    }
    local_iterator end(size_type n)
    { /* TODO */
        return local_iterator(nullptr);
    }

    size_type bucket_size(size_type n)
    { /* TODO */
        size_type size = 0;
        HashNode *ptr = _buckets[n];
        while (ptr)
        {
            size++;
            ptr = ptr->next;
        }
        return size;
    }

    float load_factor() const
    { /* TODO */
        return ((float)_size) / _bucket_count;
    }

    size_type bucket(const Key &key) const
    { /* TODO */
        return _bucket(key);
    }

    std::pair<iterator, bool> insert(value_type &&value)
    { /* TODO */
        HashNode * findNode = _find(value.first);
        if (findNode)
        {
            return std::pair<iterator, bool>(iterator(this, findNode), false);
        }
        size_type index = _bucket(value.first);
        HashNode *insertNode = _insert_into_bucket(index, std::move(value));
        return std::pair<iterator, bool>(iterator(this, insertNode), true);
    }

    std::pair<iterator, bool> insert(const value_type &value)
    { /* TODO */
        HashNode *findNode = _find(value.first);
        if (findNode)
        {
            return std::pair<iterator, bool>(iterator(this, findNode), false);
        }
        size_type index = _bucket(value.first);
        value_type copyVal = value;
        HashNode *insertNode = _insert_into_bucket(index, std::move(copyVal));
        return std::pair<iterator, bool>(iterator(this, insertNode), true);
    }

    iterator find(const Key &key)
    { /* TODO */
        return iterator(this, _find(key));
    }

    T &operator[](const Key &key)
    { /* TODO */
        HashNode* Node = _find(key); 
        if(Node){
            return Node->val.second; 
        }
        else{
            value_type newVal(key,T());
            iterator it = insert(std::move(newVal)).first;
            return it->second; 
        }
    }

    iterator erase(iterator pos)
    { /* TODO */
        HashNode*& findNode = _find((*pos).first); 
        if(findNode){
            iterator it(this, findNode);
            ++it;

            if (_head == findNode)
            {
                _head = it._ptr;
            }

            HashNode* del = findNode;
            findNode = findNode->next; 
            delete del;
            --_size;
            return it;
        }
        return end(); 
    }

    size_type erase(const Key &key)
    { /* TODO */
        HashNode* findNode = _find(key);
        if(findNode){
            iterator it(this, findNode);
            erase(it);
            return 1;
        }   
        return 0;
    }

    template <typename KK, typename VV>
    friend void print_map(const UnorderedMap<KK, VV> &map, std::ostream &os);
};

template <typename K, typename V>
void print_map(const UnorderedMap<K, V> &map, std::ostream &os = std::cout)
{
    using size_type = typename UnorderedMap<K, V>::size_type;
    using HashNode = typename UnorderedMap<K, V>::HashNode;

    for (size_type bucket = 0; bucket < map.bucket_count(); bucket++)
    {
        os << bucket << ": ";

        HashNode const *node = map._buckets[bucket];

        while (node)
        {
            os << "(" << node->val.first << ", " << node->val.second << ") ";
            node = node->next;
        }

        os << std::endl;
    }
}
