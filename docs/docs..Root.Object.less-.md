# `<-`

#### `..Root.Object.<-`

_(reference assign operator)_

Makes `thisParent.thisName` (`this.getParent().getChild(this.getName())`) a reference to another object.

* **Parameters:** `Object` another object

* **Return value:** reference to another

## Child of:

[`Object`](docs..Root.Object.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var a;
a.var b;
var c;

a.b.<-(c);
basicOut(c.===(a.b));
```