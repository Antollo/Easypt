# `+`

#### `..Root.ArrayIterator.+`

Returns new `ArrayIterator` moved forward by arguments value;

* **Parameters:** `Int`

* **Return value:** new `ArrayIterator`

## Child of:

[`ArrayIterator`](docs..Root.ArrayIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto arr.=(Array());
arr.pushBack("abc", "def");

auto numbers.=(Array().pushBack(1, 2, 3, 4, 5, 6, 7));

arr.insert(arr.begin(), numbers.begin(), numbers.begin().+(2));
basicOut(arr);
```