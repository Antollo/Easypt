# Conditionals and loops

## 1. Conditional statements

> In computer science, conditional statements, conditional expressions and conditional constructs are features of a programming language, which perform different computations or actions depending on whether a programmer-specified boolean condition evaluates to true or false. Apart from the case of branch predication, this is always achieved by selectively altering the control flow based on some condition.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Conditional_(computer_programming))

The if statement is most one of most frequently used conditional statements. In Easypt `if` is `BlockCallable` method and it has following syntax:

```c
if (condition, {
    # execute when condition is true #
});
```

For instance:

```c
var x.=("abc");
if (x.==("abc"), {
    basicOut("x is equal to abc");
});
```

`if` also supports if-else functionality:

```c
if (condition, {
    # execute when condition is true #
}, {
    # execute when condition is false #
});
```

For example:

```c
var a.=(6);
var b.=(9);
if (a.>(b), {
    basicOut("a is greater than b");
}, {
    basicOut("a is less or equal than b");
});
```

## 2. Logical expressions


## 3. While loops

> In most computer programming languages, a while loop is a control flow statement that allows code to be executed repeatedly based on a given Boolean condition. The while loop can be thought of as a repeating if statement.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/While_loop)

In Easypt `if` is `BlockCallable` method and it has following syntax:

```c
while (condition, {
    # execute while condition is true #
});
```
Example:

```c
var condition.=(1.toBoolean() #true# );
var i.=(0);
while (condition, {
    basicOut(i.++());
    if (i.==(10), { condition.=(0.toBoolean() #false# ); });
});
```

## 4. For loops

> In computer science, a for-loop (or simply for loop) is a control flow statement for specifying iteration, which allows code to be executed repeatedly.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/For_loop)


In Easypt `for` is `BlockCallable` method and it has following syntax (**`for` syntax is different in Easypt than in other common languages**):

```c
for (i.comperator, someValue, change, {
    # 
     execute while i.comperator(someValue) is true
     after each iteration call change()
    #
});
```

Example of `Int` based `for`:

```c
for (var i.=(0).<, 10, i.++, {
    basicOut(i);
});
```

Example of `ArrayIterator` based `for`:

```c
var arr.=(Array());
arr.pushBack(1, 7, 3.14, "abc", "def");
for (var it.=(arr.begin()).!=, arr.end(), it.++, {
    basicOut(it.get());
});
```

Example of `StringIterator` based `for`:

```c
var str.=("Hello world!");
for(var it.=(str.begin()).!=, str.end(), it.++, {
    basicOut(it.get());
});
```

Oops! I didn't tell you that `String` has some functionality like `Array` (both inherits from `Container`, `Container` inherits from `Iterable`). `String` has `begin` and `end` methods and read operator (`[]`) as well.

---

[Next lesson (Classes)](classes.md)

[Table of contents](tutorial.md)