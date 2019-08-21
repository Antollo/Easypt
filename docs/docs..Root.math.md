# `math`

#### `..Root.math`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`Object`

## Members:

`Double` numbers:

- `e` (2.71828182845904523536)
- `pi` (3.14159265358979323846)

Functions returning `Int`:

- `random` Returns a pseudo-random integer between ​0​ and at least 32767.

Functions taking one `Double` or `Int` and returning `Double`:

- `abs` Returns the absolute value of a number.
- `ceil` Returns the smallest integer greater than or equal to a number.
- `floor` Returns the largest integer less than or equal to a number.
- `round` Returns the value of a number rounded to the nearest integer.
- `sin` Returns the sine of a number.
- `cos` Returns the cosine of a number.
- `tan` Returns the tangent of a number.
- `acos` Returns the arccosine of a number.
- `asin` Returns the arcsine of a number.
- `atan` Returns the arctangent of a number.
- `exp` Returns Euler's constant to the exponent power
- `log` Returns the natural logarithm (ln) of a number.
- `log10` Returns the base 10 logarithm of a number.
- `log2` Returns the base 2 logarithm of a number.
- `sqrt` Returns the square root of a number.
- `cbrt` Returns the cube root of a number.

Functions taking two `Double`s or `Int`s and returning `Double`:

- `atan2` Returns the 2-argument arctangent of a numbers.
- `pow` Returns base to the exponent power.

## Example:

```c
import("math");

log(math.log(math.pow(math.e, 2)));
log(math.cos(math.pi));
log(math.asin(1));
log(math.atan2(1, 1));
log(math.random());
```

#### Possible output:

```
2
-1
1.5708
0.785398
1804
```