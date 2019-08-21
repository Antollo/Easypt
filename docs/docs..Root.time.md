# `time`

#### `..Root.time`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`Object`

## Members:

- [`sleep`](docs..Root.time.sleep.md)
- [`secondsSinceEpoch`](docs..Root.time.secondsSinceEpoch.md)


## Example:

```c
import("time");
log(time.secondsSinceEpoch());
time.sleep(2000);
log(time.secondsSinceEpoch());
```