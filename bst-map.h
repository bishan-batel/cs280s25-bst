#ifndef BSTMAP_H
#define BSTMAP_H

#include <ostream>

namespace CS280 {

  template<typename K, typename V>
  class BSTmap {
  public:
    class Node {
    public:
      Node(K k, V val, Node *p, int h, int b, Node *l, Node *r);

      Node(const Node &) = delete;

      auto operator=(const Node &) -> Node & = delete;

      K const &Key() const; // return a const reference

      V &Value(); // return a reference

      [[nodiscard]] Node *first(); // minimum - follow left as far as possible

      Node *last(); // maximum - follow right as far as possible

      Node *increment(); // successor

      Node *decrement(); // predecessor

      void print(std::ostream &os) const;

    private:
      K key;
      V value;
      int height, balance; // optional
      Node *parent;
      Node *left;
      Node *right;

      friend class BSTmap;
    };

  private:
    class BSTmap_iterator {
      Node *p_node;

    public:
      BSTmap_iterator(Node *p = nullptr);
      BSTmap_iterator &operator=(const BSTmap_iterator &rhs);
      BSTmap_iterator &operator++();
      BSTmap_iterator operator++(int);
      Node &operator*();
      Node *operator->();
      bool operator!=(const BSTmap_iterator &rhs);
      bool operator==(const BSTmap_iterator &rhs);
      friend class BSTmap;
    };

    class BSTmap_iterator_const {
      Node *p_node;

    public:
      BSTmap_iterator_const(Node *p = nullptr);

      auto operator=(const BSTmap_iterator_const &rhs) -> BSTmap_iterator_const &;

      auto operator++() -> BSTmap_iterator_const &;

      auto operator++(int) -> BSTmap_iterator_const;

      auto operator*() -> const Node &;

      auto operator->() -> const Node *;

      auto operator!=(const BSTmap_iterator_const &rhs) -> bool;

      auto operator==(const BSTmap_iterator_const &rhs) -> bool;

      friend class BSTmap;
    };

    // BSTmap implementation
    Node *pRoot = nullptr;
    unsigned int size_ = 0;
    // end iterators are same for all BSTmaps, thus static
    // make BSTmap_iterator a friend
    // to allow BSTmap_iterator to access end iterators
    static BSTmap_iterator end_it;
    static BSTmap_iterator_const const_end_it;

  public:
    BSTmap();

    BSTmap(const BSTmap &rhs);

    BSTmap &operator=(const BSTmap &rhs);

    virtual ~BSTmap();

    unsigned int size();

    // value setter and getter
    V &operator[](K const &key);

    // next method doesn't make sense
    // because operator[] inserts a non-existing element
    // which is not allowed on const maps
    // V operator[](int key) const;

    // standard names for iterator types
    typedef BSTmap_iterator iterator;
    typedef BSTmap_iterator_const const_iterator;

    // BSTmap methods dealing with non-const iterator
    auto begin() -> BSTmap_iterator;

    auto end() -> BSTmap_iterator;

    auto find(const K &key) -> BSTmap_iterator;

    auto erase(BSTmap_iterator it) -> void;

    // BSTmap methods dealing with const iterator
    auto begin() const -> BSTmap_iterator_const;

    auto end() const -> BSTmap_iterator_const;

    auto find(const K &key) const -> BSTmap_iterator_const;

    // do not need this one (why)
    // BSTmap_iterator_const erase(BSTmap_iterator& it) const;

    auto print(std::ostream &os, bool print_value = false) const -> void;

    auto sanityCheck() -> bool;

    // inner class (BSTmap_iterator) doesn't have any special priveleges
    // in accessing private data/methods of the outer class (BSTmap)
    // so need friendship to allow BSTmap_iterator to access private "BSTmap::end_it"
    // BTW - same is true for outer class accessing inner class private data
    friend class BSTmap_iterator;
    friend class BSTmap_iterator_const;

  private:
    // ...
  };

  // notice that it doesn't need to be friend
  template<typename K, typename V>
  std::ostream &operator<<(std::ostream &os, BSTmap<K, V> const &map);
} // namespace CS280

#include "bst-map.cpp"
#endif
