# More on classes

### **Warning:** This is not tutorial for learning object-oriented programming. 

## 1. Revision: constructor

```c
auto Bird.=(Class(
    Object,
    var color,
    {
        color.=(args[0].get());
    }.setName("Bird"),
    {
        log("tweet");
    }.setName("sing")
));
```

Usage:

```c
auto bird.=(Bird("black"));
bird.sing();
```

## 2. Destructor

> In object-oriented programming, a **destructor** (sometimes abbreviated dtor) is a method which is automatically invoked when the object is destroyed. It can happen when its lifetime is bound to scope and the execution leaves the scope, when it is embedded in another object whose lifetime ends, or when it was allocated dynamically and is released explicitly. Its main purpose is to free the resources (memory allocations, open files or sockets, database connections, resource locks, etc.) which were acquired by the object during its life and/or deregister from other entities which may keep references to it.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Destructor_(computer_programming))


In Easypt destructors are declared with name "`~~`". Additionally, destructors have no parameters. A destructor for an object is called whenever the object's lifetime ends (there are no references to object). Constructor with destructor definition:

```c
auto Bird.=(Class(
    Object,
    var color,
    {
        color.=(args[0].get());
    }.setName("Bird"),
    {
        log("tweet");
    }.setName("sing"),
    {
        log("bird died");
    }.setName("~~")
));
```

Example:

```c
auto bird.=(Bird("black"));
bird.sing();
```

Output:

```
tweet
bird died
```

Why one bird died?! What about temporary object `Bird("black")`? Was it destroyed after line `auto bird.=(Bird("black"));`? Easypt interpreter optimized assignment to move operation (`Bird("black")` was moved to `bird`, such optimization occurs when right operand of `=` has no parent).

## 3. Inheritance

> In object-oriented programming, **inheritance** is the mechanism of basing an object or class upon another object (prototype-based inheritance) or class (class-based inheritance), retaining similar implementation. Also defined as deriving new classes (sub classes) from existing ones (super class or base class) and forming them into a hierarchy of classes. In most class-based object-oriented languages, an object created through inheritance (a "child object") acquires all the properties and behaviors of the parent object [...]. Inheritance allows programmers to create classes that are built upon existing classes, to specify a new implementation while maintaining the same behaviors (realizing an interface), to reuse code and to independently extend original software via public classes and interfaces. The relationships of objects or classes through inheritance give rise to a directed graph. [...]
>
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Inheritance_(object-oriented_programming))

Base class constructors are available only in constructor of inherited class, they must be called explicitly.

Example:

```c
auto Bird.=(Class(
    Object,
    var color,
    {
        color.=(args[0].get());
    }.setName("Bird"),
    {
        log("tweet");
    }.setName("sing"),
    {
        log("bird died");
    }.setName("~~")
));

auto Crow.=(Class(
    Bird,
    var color,
    {
        Bird(args[0].get());
    }.setName("Crow"),
    {
        log("caw");
    }.setName("sing"),
    {
        log("crow died");
    }.setName("~~")
));

auto bird.=(Crow("black"));
bird.sing();
```

## 4. Abstract classes (interfaces)

> In a language that supports inheritance, an **abstract class**, [...] is a class that cannot be instantiated because it is either labeled as abstract or it simply specifies abstract methods [...]. An abstract class may provide implementations of some methods, and may also specify virtual methods via signatures that are to be implemented by direct or indirect descendants of the abstract class. Before a class derived from an abstract class can be instantiated, all abstract methods of its parent classes must be implemented by some class in the derivation chain.
>
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Class_(computer_programming)#Abstract_and_concrete)

In Easypt there are plenty of abstract classes. For example `Container` or `Iterator`. Dive into language reference to search for more!

This allows you to e.g. treat both `ArrayIterator` and `StringIterator` as `Iterator` not worrying about exact type. See `algorithm.iterator.forEach` (check in [reference](docs..algorithm.iterator.forEach.md)) from `algorithm.ez`:

```c
iterator.var forEach.=({
    auto fun.=(args[2].get());
    for (auto it.=(args[0].get()).!=, args[1].get(), it.++, {
        fun(it.get());
    });
    return(args[1].get());
});
```
And then you could write:

```c
import("algorithm");

auto a.=(Array());
a.pushBack("w", "a", "z", "f", "c", "d");
algorithm.iterator.forEach(a.begin(), a.end(), log);

auto b.=("014753");
algorithm.iterator.forEach(b.begin(), b.end(), log);
```

Example of "abstractness failure":

```c
auto it.=(Iterator());
it.get();
```

Expected output:

```
Exception at: ..Root.import
Exception at: ..Root.my_file
Exception at: ..Root.my_file.callOperator
Exception at: ..Root.my_file.it.get
InvalidValueException: Object ..Root.my_file.it.get is abstract function
```


---

[Next lesson (Files, exceptions and extras)](extras.md)

[Table of contents](tutorial.md)