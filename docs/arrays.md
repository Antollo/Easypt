# Arrays

> Language support for **array** types may include certain built-in array data types, some syntactic constructions (array type constructors) that the programmer may use to define such types and declare array variables, and special notation for indexing array elements.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Array_data_type)

> In computer science, a **dynamic array**, growable array, resizable array, dynamic table, mutable array, or array list is a random access, variable-size list data structure that allows elements to be added or removed. It is supplied with standard libraries in many modern mainstream programming languages. Dynamic arrays overcome a limit of static arrays, which have a fixed capacity that needs to be specified at allocation.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Dynamic_array)

## 1. Creating `Array`

It's really simple:

```c
auto arr.=(Array());
```

See in reference: [`Array`](docs..Root.Array.md).

## 2. Resizing and adding elements

`Array` has `size` method that returns array's size as new `Int` and `resize` method that takes an `Int` an resize array to argument's value. See it in action:

```c
auto arr.=(Array());
log(arr.size());
arr.resize(5);
log(arr.size());
```

`Array` has also `pushBack` method that appends array with passed arguments. Example:

```c
auto arr.=(Array());
log(arr.size());
arr.pushBack(3.14);
log(arr.size());
arr.pushBack(7, "x", 0.01);
log(arr.size());
```

## 3. Array iterators and accessing stored references

> In computer science, a reference is a value that enables a program to indirectly access a particular datum, such as a variable's value or a record, in the computer's memory or in some other storage device. The reference is said to refer to the datum, and accessing the datum is called dereferencing the reference.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Reference_(computer_science))

> In computer programming, an iterator is an object that enables a programmer to traverse a container, particularly lists. Various types of iterators are often provided via a container's interface. Though the interface and semantics of a given iterator are fixed, iterators are often implemented in terms of the structures underlying a container implementation and are often tightly coupled to the container to enable the operational semantics of the iterator. An iterator performs traversal and also gives access to data elements in a container.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Iterator)

`Array` is indexed from `0`. To access something stored in `Array` use read operator (`[]`, taking as argument one `Int`) that returns `ArrayIterator` to it. To get stored reference from iterator use `ArrayIterator.get` method. Example:

```c
auto arr.=(Array());
arr.pushBack(7, "x", 0.01);

log(arr[0].get(), arr[1].get(), arr[2].get());
```

Now understand what reference is:

```c
auto text.=("Hello");
auto arr.=(Array());
arr.resize(1);

# Assign reference to text to arr[0], it is ArrayIterator.<- #
arr[0].<-(text);
log(arr[0].get());

# Modify text using reference stored in arr[0], it is Object.= #
arr[0].get().=("Good morning");
log(arr[0].get(), text);
```

There are also `Array.begin` method equivalent to `Array[0]` and `Array.end` method equivalent to `Array[Array.size()]`. Let's try running following code:

```c
auto arr.=(Array());
arr.pushBack(7, "x", 0.01);

log(arr[10000].get());
```

Output should look like this:

```
Exception at: ..Root.import
Exception at: ..Root.my_file_name
Exception at: ..Root.my_file_name.callOperator
Exception at: ..Root.my_file_name.arr
Exception at: ..Root.my_file_name.arr.readOperator
OutOfRangeException: Out of range while calling ..Root.my_file_name.arr.readOperator
```
This is exception, it describes what happened clearly.

## 4. Array constructors

You will learn what constructor is in following lessons, now you need to know that it's that "`Array()`" thing. `Array` has also a constructor that takes one argument - its new size and a constructor that takes two arguments - its new size and value that will be copied to all elements. Example:

```c
auto arr.=(Array(20));
log(arr.size());
```

```c
auto arr.=(Array(4, "some text"));
log(arr.size());
log(arr[0].get(), arr[1].get(), arr[2].get(), arr[3].get());
```

---

[Next lesson (functions)](functions.md)

[Table of contents](tutorial.md)

