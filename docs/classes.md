# Classes

### **Warning:** This is not tutorial for learning object-oriented programming. 

## 1. Object

> This definition is not about `Object` class but object in general.

> In computer science, an object can be a variable, a data structure, a function, or a method, and as such, is a value in memory referenced by an identifier. In the class-based object-oriented programming paradigm, object refers to a particular instance of a class, where the object can be a combination of variables, functions, and data structures. In relational database management, an object can be a table or column, or an association between data and a database entity (such as relating a person's age to a specific person).
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Object_(computer_science))

## 2. Object-oriented programming

> Object-oriented programming (OOP) is a programming paradigm based on the concept of "objects", which may contain data, in the form of fields, often known as attributes; and code, in the form of procedures, often known as methods. A feature of objects is that an object's procedures can access and often modify the data fields of the object with which they are associated [...]. In OOP, computer programs are designed by making them out of objects that interact with one another. There is significant diversity of OOP languages, but the most popular ones are class-based, meaning that objects are instances of classes, which typically also determine their type.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Object-oriented_programming)

## 3. Constructor

> In class-based object-oriented programming, a constructor (abbreviation: ctor) is a special type of subroutine called to create an object. It prepares the new object for use, often accepting arguments that the constructor uses to set required member variables. A constructor resembles an instance method, but it differs from a method in that it has no explicit return type, it is not implicitly inherited and it usually has different rules for scope modifiers. Constructors often have the same name as the declaring class. They have the task of initializing the object's data members and of establishing the invariant of the class, failing if the invariant is invalid. A properly written constructor leaves the resulting object in a valid state. Immutable objects must be initialized in a constructor.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Constructor_(object-oriented_programming))

## 4. Example of class

`Bird` class:

```c
var Bird.=({
    var color.=(args[0].get());
    var tweet.=({ basicOut("tweet"); });
    var tweetNTimes.=({
        for (var i.=(0).<, args[0], i.++, {
            tweet();
        });
    });
    var getColor.=({
        # current workaround to return reference #
        addChild("return", color);
    });
    var return;
    return.addChild(color);
    return.addChild(tweet);
    return.addChild(tweetNTimes);
    return.addChild(getColor);
});
```

Usage of `Bird` class:

```c
var crow.=(Bird("black"));
crow.tweet();
basicOut(crow.getColor());
```

---

[Next lesson (This is tree!)](tree.md)

[Table of contents](tutorial.md)