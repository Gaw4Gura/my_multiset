# my_multiset

### Overview

This is a `std::multiset` based on the data struct "Treap". "Treap" is a kind of an useful data struct named "binary search tree, a.k.a BST". It manages to finish the operations : 

- insert a key
- erase a key
- remove the tree
- count a key
- find the kth key
- rank a key
- find the largest key before key $x$
- find the smallest key after key $x$

in $O(logn)$ time instead of using array in $O(n)$ time. Furthermore, all the elements are sorted once it has been inserted, this feature is much more better than array's, which costs at least $O(n)$ time to sort the elements everytime.



### Introduction to namespace my_multiset

`my_multiset` in this program is a namespace like `std`, it has a template struct `Node`, which stand for the datatype of the nodes in the Treap. "template struct" means you can use any struct you like, but notice that your type **must has operand "<" and ostream "<<"**, the former is because Treap is based on operation "compare", and the latter is due to we need to print detail message of the nodes. For example, you can use `my_multiset::Node<int> *s` to get a Treap, and the datatype of it is `int`, just like `std::multiset<int> s`. Don't forget to initialize the Treap by `s = NULL;`

Let's have a look at the struct `Node` then, it has some members including :

- Node *ch[2] : the left and the right sons of the node
- v : the key value of the node
- r : the priority of the node, Treap is constructed by the random priority XD
- s : the size of the subtree
- w : the sum of the element, we need this because this is a multiset

Then, we define the operator "<" to compare the priority between two nodes to build the tree. We will use the functions `cmp(x)` and `dir(x)` after to realize some operations. As for the function `maintain()`, we use it to maintain the details of the tree. Finally, an important operation of Treap is `rotate`, we need this to ensure the tree is "balance".

Here comes to the features mentioned before : 

- `insert(o, v)` : insert value v into the set, and keep the set sorted. If the set is empty, we new a node. Otherwise, we insert it by recursiving in the left and the right subtrees. Once the balance is broken, we  `rotate` . And we maintain the set to accomplish the process
- `erase(o, v)` : erase (one of the) value v from the set, just like how we insert it
- `remove(o)` : delete the entire tree, or you can regard it as make the set empty
- `find(o, x)` : find the key $x$, if it doesn't exist, return 0. Otherwise, return the sum of key $x$
- `kth(o, k)` : return the kth element of the set, taking the repeated element in to account
- `rank(o, x)` : rank the key $x$, i.e. print the rank where $x$ is after sorting, including some items not exsit in the set
- `decrease(o, x)` and `increase(o, x)` : find the largest key before key $x$ and find the smallest key after key $x$ by using `rank`,  `kth` and `find`. After all, in STL, they use oprand `++` and `--` to do this, I try to do the same thing but failed. So these two operations are realized not so beautifully
- `print(o)` : visit the set by order. Thus, visit the tree in preorder



### Debug

Testing result seems that it works well :![sample](sample output/sample.png)

you can find the picture in folder "sample-output"



### Talk is free, show me your code

Sure, you can see it in folder "src". I'm sorry to say that because my computer platform is macOS Mojave, so I can't give you a `.exe` file, you need to compile and build it yourself

Anyone who find the bug is welcomed to contact me, my email address is 2723418900@qq.com

There are also some other operations I've not done, like `lower_bound` and `upper_bound`



### Acknowledgement and Reference

[1]刘汝佳，陈锋.算法竞赛入门经典:训练指南.[M].北京：清华大学出版社，2012：230-239