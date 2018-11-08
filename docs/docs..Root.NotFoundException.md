# `NotFoundException`

#### `..Root.NotFoundException`

Constructs new `NotFoundException` which is thrown when a resource was not found.

* **Parameters:** any number of `String` type variables

* **Return value:** new `NotFoundException`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Examples:

```c
sth.fun();
```

#### Expected output:

[...]

```
NotFoundException: Cannot find sth in .
```

---

```c
basicOut(Object().getName());
```

#### Expected output:

[...]

```
NotFoundException: Object Anonymous1234 has no parent, how sad
```