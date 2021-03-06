# Conditionals and loops

## 1. Conditional statements

> In computer science, **conditional statements**, conditional expressions and conditional constructs are features of a programming language, which perform different computations or actions depending on whether a programmer-specified boolean condition evaluates to true or false. Apart from the case of branch predication, this is always achieved by selectively altering the control flow based on some condition.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Conditional_(computer_programming))

The "if" statement is most one of most frequently used conditional statements. In Easypt `if` is `BlockCallable` method and it has following syntax:

```c
if (condition, {
    # execute when condition is true #
});
```

For instance:

```c
auto x.=("abc");
if (x.==("abc"), {
    log("x is equal to abc");
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
auto a.=(6);
auto b.=(9);
if (a.>(b), {
    log("a is greater than b");
}, {
    log("a is less or equal to b");
});
```

## 2. Logical expressions

`Boolean` type provides few binary logical operators:

- `&&` (AND) performs logical and, returns new `Boolean`
- `||` (OR) performs logical or, returns new `Boolean`
- `==` (in fact NEGATED XOR) compares two logical values, returns new `Boolean`
- `!=` (in fact XOR) compares two logical values, returns new `Boolean`

and one unary logical operator:

- `!` negates value of this, returns new `Boolean`

See in reference: [`Boolean`](docs..Root.Boolean.md)

## 3. While loops

> In most computer programming languages, a **while loop** is a control flow statement that allows code to be executed repeatedly based on a given Boolean condition. The while loop can be thought of as a repeating if statement.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/While_loop)

In Easypt `while` is `BlockCallable` method and it has following syntax:

```c
while (condition, {
    # execute while condition is true #
});
```
Example:

```c
auto condition.=(true);
auto i.=(0);
while (condition, {
    log(i.++());
    if (i.==(10), { condition.=(false); });
});
```

## 4. For loops

> In computer science, a **for loop** [...] is a control flow statement for specifying iteration, which allows code to be executed repeatedly.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/For_loop)


In Easypt `for` is `BlockCallable` method and it has following syntax (**`for` syntax is different in Easypt than in other common languages!**):

```c
for (i.comparator, someValue, change, {
    # execute while i.comparator(someValue) is true after each iteration call change() #
});
```

Example of `Int` based `for`:

```c
for (auto i.=(0).<, 10, i.++, {
    log(i);
});
```

Example of `ArrayIterator` based `for`:

```c
auto arr.=(Array());
arr.pushBack(1, 7, 3.14, "abc", "def");
for (auto it.=(arr.begin()).!=, arr.end(), it.++, {
    log(it.get());
});
```

Example of `StringIterator` based `for`:

```c
auto str.=("Hello world!");
for (auto it.=(str.begin()).!=, str.end(), it.++, {
    log(it.get());
});
```

Oops! I didn't tell you that `String` has some functionality like `Array` (both inherits from `Container`, `Container` inherits from `Iterable`). `String` has `begin` and `end` methods and read operator (`[]`) as well.

---

[Next lesson (Classes)](classes.md)

[Table of contents](tutorial.md)