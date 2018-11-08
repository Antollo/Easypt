# `pushBack`

#### `..Root.String.pushBack`

Same functionality as `str.=(str+.(character[0].get()))` but faster.

* **Parameters:** `String` character

* **Return value:** reference to this `String`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
var n.=(10);
var str.=(String());
var condition.=(n.--().toBoolean());
while(condition, {
    str.pushBack("a");
    condition.=(n.--().toBoolean());
});
basicOut(str);
```

#### Expected output:

```
aaaaaaaaaa
```