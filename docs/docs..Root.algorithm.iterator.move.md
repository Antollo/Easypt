# `move`

#### `..Root.algorithm.iterator.move`

Moves the elements in the range [first, last) to destination.

* **Parameters:** `Iterator` first, `Iterator` last, `Iterator` destination

* **Return value:** reference to destination

## Child of:

[`iterator`](docs..Root.algorithm.iterator.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("algorithm");

var mergeSort.=({
    var begin.=(args[0].get());
    var end.=(args[1].get());
    var cmp.=(args[2].get());
    var size.=(begin.distance(end));
    if(size.<(2), {
    }, {
        var pivot.=(begin.+(size./(2)));
        iterator.sort(begin, pivot, cmp);
        iterator.sort(pivot, end, cmp);

        var temp.=(Array());
        temp.resize(size);
        iterator.merge(begin, pivot, pivot, end, temp.begin(), cmp);
        iterator.move(temp.begin(), temp.end(), begin);
    });
    return(end);
});
```