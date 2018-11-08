# `debugTree`

#### `..Root.Object.debugTree`

Prints subtree of variables tree with this object as its root.

* **Return value:** reference to this `Object`

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var father;
father.var son.=("I'm son");
father.debugTree();
```

#### Possible output:

```
Name:       father
Location:   15846948
Parent:     sc2
Signatures: Object
Children:
{
    Nickname:   debugTree
    Name:       debugTree
    Location:   15845540
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   =
    Name:       =
    Location:   15846068
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   <-
    Name:       <-
    Location:   15847036
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   merge
    Name:       merge
    Location:   15846332
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   getParent
    Name:       getParent
    Location:   15847212
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   getChild
    Name:       getChild
    Location:   15846156
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   getChildrenArray
    Name:       getChildrenArray
    Location:   15845628
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   hasChild
    Name:       hasChild
    Location:   15846244
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   addChild
    Name:       addChild
    Location:   15847740
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   getName
    Name:       getName
    Location:   15849148
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   copy
    Name:       copy
    Location:   15848708
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   !=
    Name:       !=
    Location:   15849500
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   ===
    Name:       ===
    Location:   15849236
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   sameSignatures
    Name:       sameSignatures
    Location:   15848796
    Parent:     father
    Signatures: NativeCallable Callable

    Nickname:   son
    Name:       son
    Location:   15837356
    Parent:     father
    Signatures: Object Basic String Iterable Container
    Children:
    {
        Nickname:   debugTree
        Name:       debugTree
        Location:   15838500
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   =
        Name:       =
        Location:   15838676
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   <-
        Name:       <-
        Location:   15837180
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   merge
        Name:       merge
        Location:   15838764
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   getParent
        Name:       getParent
        Location:   15836036
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   getChild
        Name:       getChild
        Location:   15837268
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   getChildrenArray
        Name:       getChildrenArray
        Location:   15836212
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   hasChild
        Name:       hasChild
        Location:   15837444
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   addChild
        Name:       addChild
        Location:   15837532
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   getName
        Name:       getName
        Location:   15837620
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   copy
        Name:       copy
        Location:   15836564
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   !=
        Name:       !=
        Location:   15837708
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   ===
        Name:       ===
        Location:   15977676
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   sameSignatures
        Name:       sameSignatures
        Location:   15976004
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   toString
        Name:       toString
        Location:   15977324
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   toInt
        Name:       toInt
        Location:   15976268
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   toDouble
        Name:       toDouble
        Location:   15975828
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   toBoolean
        Name:       toBoolean
        Location:   15976092
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   begin
        Name:       begin
        Location:   15975916
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   end
        Name:       end
        Location:   15976180
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   ==
        Name:       ==
        Location:   15977764
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   readOperator
        Name:       readOperator
        Location:   15976444
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   size
        Name:       size
        Location:   15976708
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   +
        Name:       +
        Location:   15976356
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   find
        Name:       find
        Location:   15977852
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   empty
        Name:       empty
        Location:   15976532
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   resize
        Name:       resize
        Location:   15976620
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   clear
        Name:       clear
        Location:   15977148
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   substring
        Name:       substring
        Location:   15975740
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   insert
        Name:       insert
        Location:   15976796
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   erase
        Name:       erase
        Location:   15976972
        Parent:     son
        Signatures: NativeCallable Callable

        Nickname:   pushBack
        Name:       pushBack
        Location:   15976884
        Parent:     son
        Signatures: NativeCallable Callable

    }
}
```