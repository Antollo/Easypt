# `searchRegex`

#### `..Root.String.searchRegex`

Search for all substrings matching regular expression and returns an array of these substrings.

* **Parameters:** `String` regex

* **Return value:** new `Array`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
basicOut("ab bcd efghIjk".searchRegex("[a-z]+"));
```

#### Expected output:

```
ab
bcd
efgh
jk
```