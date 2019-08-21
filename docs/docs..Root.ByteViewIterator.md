# `ByteViewIterator`

#### `..Root.ByteViewIterator`

Constructs a new `ByteViewIterator`, this constructor exists only for internal `ByteView` purposes. `ByteViewIterator` is not memory safe (not aware of `ByteView` size). For creating `ByteViewIterator` pointing to data use `ByteView.begin()` and `ByteView.end()`.

### `ByteViewIterator` type signatures:

`Object`, `Iterator`, `ByteViewIterator` 

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`, `Class`

## Members:

- `++` 
  
  Increments `ByteViewIterator` instance (equivalent of `it.=(it.+(1))`).

  **Return value:** reference to this (increments) `ByteViewIterator`

- `--`
  
  Decrements `ByteViewIterator` instance (equivalent of `it.=(it.-(1))`).

  **Return value:** reference to this (decremented) `ByteViewIterator`

- `==`
  
  Checks if two instances of `ByteViewIterator` are pointing to same byte.

  **Parameters:** another `ByteViewIterator`

  **Return value:** new `Boolean`

- `get`
  
  Gets wrapper of byte pointed by iterator.

  **Return value:** new `ByteWrapper`

- `>`
  
  Checks if this `ByteViewIterator` is pointing after another `ByteViewIterator`.

  **Parameters:** another `ByteViewIterator`

  **Return value:** new `Boolean`
  
- `<`
  
  Checks if this `ByteViewIterator` is pointing before another `ByteViewIterator`.

  **Parameters:** another `ByteViewIterator`

  **Return value:** new `Boolean`

- `>=`
  
  Checks if this `ByteViewIterator` is pointing after or to the same byte as another `ByteViewIterator`.

  **Parameters:** another `ByteViewIterator`

  **Return value:** new `Boolean`

- `<=`
  
  Checks if this `ByteViewIterator` is pointing before or to the same byte as another `ByteViewIterator`.

  **Parameters:** another `ByteViewIterator`

  **Return value:** new `Boolean`

- `+`
  
  Returns new `ByteViewIterator` moved forward by arguments value;

  **Parameters:** `Int`

  **Return value:** new `ByteViewIterator`

- `-`
  
  Returns new `ByteViewIterator` moved backward by arguments value;
  
  **Parameters:** `Int`

  **Return value:** new `ByteViewIterator`

- `distance`
  
  Gets distance from another iterator as new `Int`.

  **Parameters:** another `ByteViewIterator` 

  **Return value:** new `Int`

## Example:

```c
import("memory");

auto str.=("\122\123\124");
auto a.=(ByteView(str));

for (auto it.=(a.begin()).!=, a.end(), it.++, {
    log(it.get().toInt());
});
```

#### Expected output:

```
122
123
124
```