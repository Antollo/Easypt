# Files, exceptions and extras

## 1. Files

> You were expecting quote from Wikipedia? I'm sure you know what file is.

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
testFile.write("afpha beta\ngamma");
```

And print it to console:

```c
import("file");
auto testFile.=(File());

testFile.open("test.txt");
testFile.clear();

testFile.write("afpha beta\ngamma");

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

testFile.write("afpha beta\ngamma");

basicOut(testFile.read());
basicOut(testFile.read());
basicOut(testFile.read());

testFile.write("delta");
basicOut(testFile.read());
```