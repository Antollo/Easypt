# Functions

> A function is a group of statements that perform particular task.

>**Advantages**
>
>The advantages of breaking a program into subroutines [functions] include:
>- Decomposing a complex programming task into simpler steps: this is one of the two main tools of structured programming, along with data structures.
>- Reducing duplicate code within a program.
>- Enabling reuse of code across multiple programs.
>- Dividing a large programming task among various programmers, or various stages of a project.
>- Hiding implementation details from users of the subroutine.
>- Improving readability of code by replacing a block of code with a function call where a descriptive function name serves to describe the block of code. This makes the calling code concise and readable even if the function is not meant to be reused.
>- Improving traceability [...] by not decomposing the code into subroutines, debugging would be severely impaired.
>
>**Disadvantages**
>- Invoking a subroutine (versus using in-line code) imposes some computational overhead in the call mechanism.
>- A subroutine typically requires standard housekeeping code – both at entry to, and exit from [...].
>
>[_From Wikipedia_](https://en.wikipedia.org/wiki/Subroutine)

## 1. What we call a function in Easypt

Basically we can call everything of `Callable` type. `NativeCallable` is type of function provided by the Easypt interpreter or native libraries. `BlockCallable` is type of function defined in `*.ez` source code.

## 2. Defining function

Let's begin with function literal (unnamed function):

```c
{
    basicOut("I am BlockCallable literal!");
};
```

Nothing happened. We need to call it (by call operator - `()`).

```c
{
    basicOut("I am BlockCallable literal!");
}();
```

(Code called like this above has no access to current context.)

Let's give our function a name;:

```c
var fun.=({
    basicOut("I am fun!");
});
fun();
```

## 3. Parameters

> In computer programming, a parameter  [...] is a special kind of variable, used in a subroutine [function] to refer to one of the pieces of data provided as input to the subroutine. [...] Argument in computer science is the actual input expression passed/supplied to a function.
>
>[_From Wikipedia_](https://en.wikipedia.org/wiki/Parameter_(computer_programming))

In Easypt argumets are provided as `Array` of [references](https://en.wikipedia.org/wiki/Evaluation_strategy#Call_by_reference) to arguments named `args`. See the example:

```c
var print.=({
    basicOut(args[0].get(), args[1].get());
});
print(7, 3.14);
```

Expected output is:

```
7
3.14
```

Try to run:

```c
var print.=({
    basicOut(args[0].get(), args[1].get());
});
print(7);
```

You will see out of range exception:

```
Exception at: ..Root.import
Exception at: ..Root.my_source_file
Exception at: ..Root.my_source_file.callOperator
Exception at: ..Root.my_source_file.print
Exception at: ..Root.my_source_file.print.callOperator
Exception at: ..Root.my_source_file.print.args
Exception at: ..Root.my_source_file.print.args.readOperator
OutOfRangeException: Out of range while calling ..Root.my_source_file.print.args.readOperator
```

But 

```c
print(7, 7, 7, 7, 7);
```

works fine as you expected. So what are those "references"? Run this:

```c
var myIncrement.=({
    args[0].get().++();
});
var myInt.=(5)
myIncrement(myInt);
basicOut(myInt);
```

Output is `6`. If you don't want to pass a reference, you will have to use `Object`'s `copy` method:

```c
var myIncrement.=({
    args[0].get().++();
});
var myInt.=(5)
myIncrement(myInt.copy());
basicOut(myInt);
```

Now output is `5`.

You will learn about variable number of arguments while learning about loops.

## 4. Return

>In computer programming, a return statement causes execution to leave the current subroutine [function] and resume at the point in the code immediately after where the subroutine was called [...]. Return statements in many languages allow a function to specify a return value to be passed back to the code that called the function.
>
>[_From Wikipedia_](https://en.wikipedia.org/wiki/Return_statement)


In Easypt `return` is `BlockCallable`'s method. Calling return makes execution to leave the current function and `return`'s argument is the value of function call (if no value is passed new `Object` will be returned). Example:

```c
var fun.=({
    return(5);
});
basicOut(fun());
```

## 5. Exercise "Birthday Project"

Your exercise is to analyze following code:

```c
var makeGreetingsString.=({
    var str.=("Happy ");
    str.=(str.+(args[0].get().toString()));
    str.=(str.+(" birthday "));
    str.=(str.+(args[1].get()));
    str.=(str.+("!"));
    return(str);
});
basicOut(makeGreetingsString(51, "John"));
```

Output:

```
Happy 51 birthday John!
```

Understand the code:

- `toString` is `Basic`'s method that return new `String` object created from owner value.

---

[Next lesson (Conditionals and loops)](conditionals_and_loops.md)

[Table of contents](tutorial.md)