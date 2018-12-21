# `expect`

#### `..Root.except`

If condition is false throw the result of invoking the callable object f with rest of arguments as f's arguments.

* **Parameters:** `Basic` condition, `Callable` f, any number of variables of any type

* **Return value:** reference to condition

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
except(false, Exception, "Message");
```

### Expected output

```
Exception at: ..Root.import
Exception at: ..Root.my_source_name
Exception at: ..Root.my_source_name.callOperator
Exception at: ..Root.except
Exception: Message
```