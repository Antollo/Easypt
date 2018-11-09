# `-`

#### `..Root.ArrayIterator.-`

Returns new `ArrayIterator` moved backward by arguments value;

* **Parameters:** `Int`

* **Return value:** new `ArrayIterator`

## Child of:

[`ArrayIterator`](docs..Root.ArrayIterator.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var arr.=(Array());
arr.pushBack("abc", "def");
for (var it.=(arr.end()).!=, arr.begin(), it.--, {
    basicOut(it.-(1).get());
});