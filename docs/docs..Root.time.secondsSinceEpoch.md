# `secondsSinceEpoch`

#### `..Root.time.secondsSinceEpoch`

Returns a number of seconds that have elapsed since 00:00:00 Thursday, 1 January 1970 ([_see explanation on Wikipedia_](https://en.wikipedia.org/wiki/Return_statement))

_Interesting fact - [Year 2038 problem](https://en.wikipedia.org/wiki/Year_2038_problem)._

* **Return value:** new `Int` 

## Child of:

[`time`](docs..Root.time.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("time");
log(time.secondsSinceEpoch());
time.sleep(2000);
log(time.secondsSinceEpoch());
```