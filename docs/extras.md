# Files, exceptions and extras

## 1. Files

> A computer **file** is a computer resource for recording data discretely in a computer storage device. Just as words can be written to paper, so can information be written to a computer file.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Computer_file)

A file must be opened before you can use it. `File` object may be use to read from it or write to it. Example:

```c
import("file");
auto testFile.=(File());

testFile.open("test.txt");
```

Let's write some contents to this file:

```c
import("file");
auto testFile.=(File());

testFile.open("test.txt");

testFile.clear();
testFile.write("alpha beta\ngamma");
```

And print it to console:

```c
import("file");
auto testFile.=(File());

testFile.open("test.txt");
testFile.clear();

testFile.write("alpha beta\ngamma");

basicOut(testFile.read());
basicOut(testFile.read());
basicOut(testFile.read());
```

And write and read again:

```c
import("file");
auto testFile.=(File());

testFile.open("test.txt");
testFile.clear();

testFile.write("alpha beta\ngamma");

basicOut(testFile.read());
basicOut(testFile.read());
basicOut(testFile.read());

testFile.write("delta");
basicOut(testFile.read());
```

Expected output is:

```
alpha
beta
gamma
alpha
```

Why did the last block print "alpha" instead of "delta"? It's time yo answer the question! Dive into language reference:

- [`Root.File`](docs..Root.File.md)
- [`Root.File.read`](docs..Root.File.read.md)
- [`Root.File.write`](docs..Root.File.write.md)

Hint: _read position indicator_


---

>## TODO: exceptions, tasks and extras