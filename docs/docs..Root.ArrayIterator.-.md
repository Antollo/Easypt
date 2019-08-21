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
auto arr.=(Array());
arr.pushBack("abc", "def");
for (auto it.=(arr.end()).!=, arr.begin(), it.--, {
    log(it.-(1).get());
});