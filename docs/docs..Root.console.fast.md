# `fast`

#### `..Root.console.fast`

Provides the fastest IO operations.

## Child of:

[`console`](docs..Root.console.md)

## Signatures:

`Object`

## Members:

**Return value of all following:** reference to itself

- `writeInt` **Parameters:** `Int`
- `writeDouble` **Parameters:** `Int`
- `writeString` **Parameters:** `String`
- `scanInt` **Parameters:** `Int`
- `scanDouble` **Parameters:** `Int`
- `scanString16` **Parameters:** `String`, reads at most 16 characters
- `scanString256` **Parameters:** `String`, reads at most 256 characters

## Example:

```c
import("console");

auto a.=(Int());
auto b.=(Double());
auto c.=(String());
console.fast.scanInt(a);
console.fast.scanDouble(b);
console.fast.scanString16(c);
console.fast.writeInt(a);
console.fast.writeDouble(b);
console.fast.writeString(c);
```





