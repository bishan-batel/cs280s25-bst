#ifndef BSTMAP_H
#include "bst-map.h"
#endif

#ifndef BSTMAP_CPP
#define BSTMAP_CPP

#include <iostream>

namespace CS280 {

  // static data members
  template<typename K, typename V>
  typename BSTmap<K, V>::iterator BSTmap<K, V>::end_it{nullptr};

  template<typename K, typename V>
  typename BSTmap<K, V>::const_iterator BSTmap<K, V>::const_end_it{nullptr};

  // in implementation file
  // method's name and return value have to be fully qualified with
  // all required namespace and class names (like BSTmap<K,V>::BSTmap)
  // but the argument list does not have to be:
  // function argument list automatically falls into the method's namespace
  // (Koenig lookup)
  template<typename K, typename V>
  BSTmap<K, V>::BSTmap(const BSTmap& rhs) {
    // ...
  }

  ////////////////////////////////////////////////////////////
  // typename is used to help compiler to parse
  template<typename K, typename V>
  auto BSTmap<K, V>::begin() -> iterator {
    return pRoot ? iterator{pRoot->first()} : end_it;
  }

  ////////////////////////////////////////////////////////////
  // do not change this code from here to the end of the file
  /* figure out whether node is left or right child or root
   * used in print_backwards_padded
   */
  template<typename K, typename V>
  auto BSTmap<K, V>::getedgesymbol(const Node* node) const -> char {
    const Node* parent = node->parent;

    if (parent == nullptr) {
      return '-';
    }

    return parent->left == node ? '\\' : '/';
  }

  /* this is another "ASCII-graphical" print, but using
   * iterative function.
   * Left branch of the tree is at the bottom
   */
  template<typename K, typename V>
  auto operator<<(std::ostream& os, const BSTmap<K, V>& map) -> std::ostream& {
    map.print(os);
    return os;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::print(std::ostream& os, bool print_value) const -> void {
    if (pRoot) {
      BSTmap<K, V>::Node* b = pRoot->last();
      while (b) {
        int depth = getdepth(b);
        int i;
        /* printf(b); */

        char edge = getedgesymbol(b);
        switch (edge) {
          case '-':
            for (i = 0; i < depth; ++i) {
              std::printf("       ");
            }
            os << b->key;
            if (print_value) {
              os << " -> " << b->value;
            }
            os << std::endl;
            break;
          case '\\':
            for (i = 0; i < depth; ++i) {
              std::printf("       ");
            }
            os << edge << std::endl;
            for (i = 0; i < depth; ++i) {
              std::printf("       ");
            }
            os << b->key;
            if (print_value) {
              os << " -> " << b->value;
            }
            os << std::endl;
            break;
          case '/':
            for (i = 0; i < depth; ++i) {
              std::printf("       ");
            }
            os << b->key;
            if (print_value) {
              os << " -> " << b->value;
            }
            os << std::endl;
            for (i = 0; i < depth; ++i) {
              std::printf("       ");
            }
            os << edge << std::endl;
            break;
        }
        b = b->decrement();
      }
    }
    std::printf("\n");
  }
} // namespace CS280

#endif
