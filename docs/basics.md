# Basics

## 1. Hello world!

Create new `*.ez` source file (e.g. `source.ez`). Open it with VS Code. Paste following code to that file:

```c
basicOut("Hello world!");
```

 Create `tasks.json` as described in [prepare environment](environment.md). Run file with `Ctrl+Shift+B`. You wil see output in VS Code integrated terminal, something like this:

```
> Executing task: D:\Easypt\bin\easypt.exe -file source.ez <

Hello world!

Press any key to close the terminal.
```

Congrats, you have created your first Easypt script! Alternatively you can run it from shell with command:

```
easypt -file source.ez
```

Understand the code:

- `basicOut` is function which print `Basic` (`String`, `Int`, `Double` or `Boolean`, you will learn about it later) arguments to console, each argument in new line.
- `"Hello world!"` is `String` literal.
- In Easypt each statement must end with semicolon (`;`).

## 2. Comments

> In computer programming, a comment is a programmer-readable explanation or annotation in the source code of a computer program. They are added with the purpose of making the source code easier for humans to understand, and are generally ignored by compilers and interpreters. The syntax of comments in various programming languages varies considerably.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Comment_(computer_programming))

Easypt support multi-line comments, all comments are ignored by Easypt interpreter. Comment start and and with hash sign (`#`).

Example:

```c
# Comment in single line. #

#
Comment in three lines.
#

basicOut("Hello", # Comment inside statement! # "world!");

```

## 3. Variables

> In computer programming, a variable or scalar is a storage location (identified by a memory address) paired with an associated symbolic name (an identifier), which contains some known or unknown quantity of information referred to as a value. The variable name is the usual way to reference the stored value, in addition to referring to the variable itself, depending on the context. This separation of name and content allows the name to be used independently of the exact information it represents. The identifier in computer source code can be bound to a value during run time, and the value of the variable may thus change during the course of program execution.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Variable_(computer_science))

In Easypt variables have names, types and values. Some types examples:

- `Object`: nearly everything
- `Int`: for integers such as `12` or `-7`
- `Double`: for floating-point or real numbers such as `3.14`
- `String`: for texts such as `"Have a nice day!"`

You can create variable and assign it a value like this:

```c
var myText.=("This is my first variable");
```

Understand the code:

- `var` is keyword which take following token and create variable (of `Object` type) in current context.
- `=` is `Object`'s method (member function) that assign copy of passed argument to owner and return a [reference](https://en.wikipedia.org/wiki/Reference_(computer_science)) to owner.

## 4. Math operators

Easypt's `Int` and `Double` provide a rich set of methods for maths expressions.

`Int`:

- `+` addition
- `-` subtraction
- `*` multiplication
- `/` division
- `%` modulo

`Double`:

- `+` addition
- `-` subtraction
- `*` multiplication
- `/` division

Example:

```c
var a.=(2.+(5));
basicOut(a);

a.=(a.-(1));
basicOut(a);

a.=(a.*(2));
basicOut(a);

a.=(a./(3));
basicOut(a);

a.=(a.%(3));
basicOut(a);

var b.=(-70.0);
basicOut(b);

b.=(b./(3.0));
basicOut(b);
```

## 5. Increment and decrement

> Increment and decrement operators are unary operators that add or subtract one from their operand, respectively. They are commonly implemented in imperative programming languages.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/B_(programming_language))

Basically (for `Int` and `Double` numbers) `x.++()` is equivalent of `x.=(x.+(1))`. Example:

```c
var a.=(6);
a.++();
basicOut(a);
basicOut(a.--());
```

Understand the code:

- `var` is keyword which take following token and create variable (of `Object` class) in current context.
- In this case `++` is `Int`'s method (member function) equivalent to `a.=(a.+(1))`
- `--` is similar to `++`.

## 6. Adding Strings

The `+` method adds them together to make a new `String`.

```c
var text.=("Hello");
basicOut(text.+(" world!"));
```

---

[Next lesson (Arrays)](arrays.md)

[Table of contents](tutorial.md)