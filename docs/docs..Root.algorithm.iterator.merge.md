# `merge`

#### `..Root.algorithm.iterator.merge`

Merges two sorted ranges [first1, last1) and [first2, last2) into one sorted rage starting at destination using order described by comparison.

* **Parameters:** `Iterator` first1, `Iterator` last1, `Iterator` first2, `Iterator` last2, `Iterator` destination, `Callable` comparison

* **Return value:** reference to destination

## Child of:

[`iterator`](docs..Root.algorithm.iterator.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("algorithm");

auto mergeSort.=({
    auto begin.=(args[0].get());
    auto end.=(args[1].get());
    auto cmp.=(args[2].get());
    auto size.=(begin.distance(end));
    if(size.<(2), {
    }, {
        auto pivot.=(begin.+(size./(2)));
        iterator.sort(begin, pivot, cmp);
        iterator.sort(pivot, end, cmp);

        auto temp.=(Array());
        temp.resize(size);
        iterator.merge(begin, pivot, pivot, end, temp.begin(), cmp);
        iterator.move(temp.begin(), temp.end(), begin);
    });
    return(end);
});
```