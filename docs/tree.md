# This is tree!

### **Warning:** This is not tutorial for learning data structures. 

## 1. Tree

> In computer science, a tree is a widely used abstract data type (ADT)—or data structure implementing this ADT—that simulates a hierarchical tree structure, with a root value and subtrees of children with a parent node, represented as a set of linked nodes. A tree data structure can be defined recursively (locally) as a collection of nodes (starting at a root node), where each node is a data structure consisting of a value, together with a list of references to nodes (the "children"), with the constraints that no reference is duplicated, and none points to the root. Alternatively, a tree can be defined abstractly as a whole (globally) as an ordered tree, with a value assigned to each node. Both these perspectives are useful: while a tree can be analyzed mathematically as a whole, when actually represented as a data structure it is usually represented and worked with separately by node (rather than as a set of nodes and an adjacency list of edges between nodes, as one may represent a digraph, for instance). For example, looking at a tree as a whole, one can talk about "the parent node" of a given node, but in general as a data structure a given node only contains the list of its children, but does not contain a reference to its parent (if any).
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Tree_(data_structure))

## 2. Tree in Easypt

Generally all variables, functions and namespaces are nodes in one big Easypt tree. The best explanation is output of following line:

```c
Root.debugTree();
```

Output:

_`something way too long too publish here`_

(Skip reading whole output if you get the idea.)

Output should have approx. 1300 lines. Pretty big tree. `debugTree` is `Object` method so printing any subtree of whole tree is possible. Additionally, some variables (freshly created by constructors) might not be connected to tree. 

## 3. Tree operations on `Object`

`Object` provide following methods for manipulating the tree:

- `debugTree`
  - prints subtree with calling `Object` as root
  - _no parameters_
  - _return value:_ calling `Object`
- `getParent`
  - _no parameters_
  - _return value:_ reference to parent of calling `Object`
- `hasChild`
  - checks if calling `Object` has child named as first argument value
  - _parameters:_ `String` (name of child to check)
  - _return value:_ new `Boolean`
- `getChild`
 value
  - _parameters:_ `String` (name of child to return)
  - _return value:_ reference to child
- `addChild`
  - 1 parameter:
    - adds reference to given object as child to calling `Object` with given object's name
    - _parameters:_ object of any type
    - _return value:_ calling `Object`
  - 2 parameters: 
    - adds reference to given object as child to calling `Object` with given name
    - _parameters:_ `String` (name), object of any type
    - _return value:_ calling `Object`

## 4. Example of small subtree

### **Warning:** This is not tutorial for learning family relationships.

Code:

```
var mother;
var father;

#
Here the "weirdest" syntax comes,
It not also attach son as child to
mother, but also attach mother
as parent to son.
#
mother.var son;
father.var daughter;

# Adds reference to father's daughter as step-daughter #
mother.addChild("step-daughter", father.getChild("daughter"));
# same as: mother.var step-daughter.<-(father.daughter); #

mother.addChild(Object());

var childrenArray.=(mother.getChildrenArray());
for (var it.=(childrenArray.begin()).!=, childrenArray.end(), it.++, {
    if (instanceOf(it.get(), Object), {
        basicOut(it.get().getName());
    });
});

mother.debugTree();
```

---

[Next lesson (Libraries)](library.md)


[Table of contents](tutorial.md)