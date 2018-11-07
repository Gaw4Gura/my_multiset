#include <iostream>
#include <cstdlib>

namespace my_multiset {
  template <class T>
  struct Node {
    Node *ch[2];
    T v;
    int r, s, w;
    
    Node() { srand(10086); }
    Node(T v) : v(v) {
      ch[0] = ch[1] = NULL;
      r = rand();
      s = w = 1;
    }

    inline bool operator < (const Node& rhs) const {
      return r < rhs.r;
    }

    inline int cmp(T x) const {
      if (x == v) return -1;
      return x < v ? 0 : 1;
    }

    inline void maintain() {
      s = w;
      if (ch[0]) s += ch[0] -> s;
      if (ch[1]) s += ch[1] -> s;
    }

    inline int dir(T x) const {
      int sz = w;
      if (ch[0]) sz += ch[0] -> s;
      if (sz - w + 1 <= x && x <= sz) return -1;
      if (x <= sz - w) return 0;
      return 1;
    }
  };

  template <class T> inline void rotate(Node<T>* &o, int d) {
    Node<T> *k = o -> ch[d ^ 1];
    o -> ch[d ^ 1] = k -> ch[d];
    k -> ch[d] = o;
    o -> maintain(); k -> maintain();
    o = k;
  }

  template <class T> inline void insert(Node<T>* &o, T v) {
    if (!o) {
      o = new Node<T>(v);
      return;
    } else {
      int d = o -> cmp(v);
      if (d == -1) ++(o -> w);
      else {
	insert(o -> ch[d], v);
	if (o < o -> ch[d]) rotate(o, d ^ 1);
      }
    }
    o -> maintain();
  }

  template <class T> inline void erase(Node<T>* &o, T v) {
    if (!o) return;
    int d = o -> cmp(v);
    if (d == -1) {
      if (o -> w > 1) --(o -> w);
      else if (o -> ch[0] && o -> ch[1]) {
	int d2 = 0;
	if (o -> ch[1] < o -> ch[0]) d2 = 1;
	rotate(o, d2);
	erase(o -> ch[d2], v);
      } else {
	if (o -> ch[0]) o = o -> ch[0];
	else o = o -> ch[1];
      }
    } else
      erase(o -> ch[d], v);
    if (o) o -> maintain();
  }

  template <class T> inline void remove(Node<T>* &o) {
    if (!o) return;
    if (o -> ch[0]) remove(o -> ch[0]);
    if (o -> ch[1]) remove(o -> ch[1]);
    delete o;
    o = NULL;
  }

  template <class T> inline T find(Node<T>* &o, T x) {
    if (!o) return 0;
    int d = o -> cmp(x);
    if (d == -1) return o -> w;
    return find(o -> ch[d], x);
  }

  template <class T> inline T kth(Node<T>* o, int k) {
    int d = o -> dir(k), sz = o -> w;
    if (o -> ch[0]) sz += o -> ch[0] -> s;
    if (d == -1) return o -> v;
    if (d == 0) return kth(o -> ch[0], k);
    return kth(o -> ch[1], k - sz);
  }

  template <class T> inline int rank(Node<T>* o, T x) {
    if (!o) return 0;
    int d = o -> cmp(x), sz = o -> w;
    if (o -> ch[0]) sz += o -> ch[0] -> s;
    if (d == -1) return sz - (o -> w);
    else if (d == 0) return rank(o -> ch[0], x);
    else return rank(o -> ch[1], x) + sz;
  }

  template <class T> inline T decrease(Node<T>* o, T x) {
    int sz = rank(o, x);
    return kth(o, sz);
  }

  template <class T> inline T increase(Node<T>* o, T x) {
    int sz = rank(o, x);
    sz += find(o, x) + 1;
    return kth(o, sz);
  }

  template <class T> inline void print(Node<T>* o) {
    if (!o) return;
    print(o -> ch[0]);
    std::cout << o -> v << " ";
    print(o -> ch[1]);
  }
} using namespace my_multiset;

#include <cstdio>

Node<int> *s;

int main()
{
  s = NULL;
  printf("This is a multiset by using Treap.\n");
  printf("Writer : Shuoyu 'LoliconAutomaton' Wang.\n");
  printf("We now show you its feature.\n");
  printf("After insert Key 1 and Key 3 : \n");
  insert(s, 1); insert(s, 3); print(s); putchar('\n');
  printf("After insert Key 5 and Key 2 : \n");
  insert(s, 5); insert(s, 2); print(s); putchar('\n');
  printf("After erase Key 2 : \n");
  erase(s, 2); print(s); putchar('\n');
  printf("After insert Key 1 and count 1 : ");
  insert(s, 1); printf("count(1) = %d\n", find(s, 1));
  printf("3th element is : ");
  printf("%d\n", kth(s, 3));
  printf("rank 4 is : ");
  printf("%d\n", rank(s, 4));
  printf("before 3 is : ");
  printf("%d\n", decrease(s, 3));
  printf("After 3 is : ");
  printf("%d\n", increase(s, 3));
  printf("Detail usage please read the readme.pdf\n");
  return 0;
}
