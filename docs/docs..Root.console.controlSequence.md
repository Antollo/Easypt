# `controlSequence`

#### `..Root.console.controlSequence`

Writes [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code) starting with `ESC` and `[` (CSI sequence) to the standard output.

* **Parameters:** any number of `String` instances

* **Return value:** reference to this function

## Child of:

[`console`](docs..Root.console.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:

```c
import("console");

console.writeLine("Normal text");
console.controlSequence("1m", "4m", "44m", "91m");
console.writeLine("Bold, underlined text with red font and blue background");
console.controlSequence("0m");
console.writeLine("Again normal text");
```

# CSI cheat sheet

## Some of CSI sequences

>The `ESC [` (Control Sequence Introducer) is followed by any number (including none) of "parameter bytes" in the range 0x30–0x3F (ASCII `0–9:;<=>?`), then by any number of "intermediate bytes" in the range 0x20–0x2F (ASCII space and `!"#$%&'()*+,-./`), then finally by a single "final byte" in the range 0x40–0x7E (ASCII `@A–Z[\]^_`a–z{|}~`).
>
>All common sequences just use the parameters as a series of semicolon-separated numbers such as `1;2;3`. Missing numbers are treated as `0` (`1;;3` acts like the middle number is `0`, and no parameters at all in `ESC[m` acts like a `0` reset code). Some sequences (such as CUU) treat `0` as `1` in order to make missing parameters useful. Bytes other than digits and semicolon seem to not be used.
>
>
> | Code        | Name                               | Effect                                                                                                                                                                                                                                                                                                                                                                                                  |
> |-------------|------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
> | CSI n A     | CUU – Cursor Up                    | Moves the cursor n (default 1) cells in the given direction. If the cursor is already at the edge of the screen, this has no effect.                                                                                                                                                                                                                                                                    |
> | CSI n B     | CUD – Cursor Down                  |                                                                                                                                                                                                                                                                                                                                                                                                         |
> | CSI n C     | CUF – Cursor Forward               |                                                                                                                                                                                                                                                                                                                                                                                                         |
> | CSI n D     | CUB – Cursor Back                  |                                                                                                                                                                                                                                                                                                                                                                                                         |
> | CSI n E     | CNL – Cursor Next Line             | Moves cursor to beginning of the line n (default 1) lines down. (not ANSI.SYS)                                                                                                                                                                                                                                                                                                                          |
> | CSI n F     | CPL – Cursor Previous Line         | Moves cursor to beginning of the line n (default 1) lines up. (not ANSI.SYS)                                                                                                                                                                                                                                                                                                                            |
> | CSI n G     | CHA – Cursor Horizontal Absolute   | Moves the cursor to column n (default 1). (not ANSI.SYS)                                                                                                                                                                                                                                                                                                                                                |
> | CSI n ; m H | CUP – Cursor Position              | Moves the cursor to row n, column m. The values are 1-based, and default to 1 (top left corner) if omitted. A sequence such as CSI ;5H is a synonym for CSI 1;5H as well as CSI 17;H is the same as CSI 17H and CSI 17;1H                                                                                                                                                                               |
> | CSI n J     | ED – Erase in Display              | Clears part of the screen. If n is 0 (or missing), clear from cursor to end of screen. If n is 1, clear from cursor to beginning of the screen. If n is 2, clear entire screen (and moves cursor to upper left on DOS ANSI.SYS). If n is 3, clear entire screen and delete all lines saved in the scrollback buffer (this feature was added for xterm and is supported by other terminal applications). |
> | CSI n K     | EL – Erase in Line                 | Erases part of the line. If n is 0 (or missing), clear from cursor to the end of the line. If n is 1, clear from cursor to beginning of the line. If n is 2, clear entire line. Cursor position does not change.                                                                                                                                                                                        |
> | CSI n S     | SU – Scroll Up                     | Scroll whole page up by n (default 1) lines. New lines are added at the bottom. (not ANSI.SYS)                                                                                                                                                                                                                                                                                                          |
> | CSI n T     | SD – Scroll Down                   | Scroll whole page down by n (default 1) lines. New lines are added at the top. (not ANSI.SYS)                                                                                                                                                                                                                                                                                                           |
> | CSI n ; m f | HVP – Horizontal Vertical Position | Same as CUP                                                                                                                                                                                                                                                                                                                                                                                             |
> | CSI n m     | SGR – Select Graphic Rendition     | Sets the appearance of the following characters, see SGR parameters below.                                                                                                                                                                                                                                                                                                                              |
> | CSI 5i      | AUX Port On                        | Enable aux serial port usually for local serial printer                                                                                                                                                                                                                                                                                                                                                 |
> | CSI 4i      | AUX Port Off                       | Disable aux serial port usually for local serial printer                                                                                                                                                                                                                                                                                                                                                |
> | CSI 6n      | DSR – Device Status Report         | Reports the cursor position (CPR) to the application as (as though typed at the keyboard) ESC[n;mR, where n is the row and m is the column.)                                                                                                                                                                                                                                                            |
> | CSI s       | SCP – Save Cursor Position         | Saves the cursor position/state.                                                                                                                                                                                                                                                                                                                                                                        |
> | CSI u       | RCP – Restore Cursor Position      | Restores the cursor position/state.                                                                                                                                                                                                                                                                                                                                                                     |
>
> [_From Wikipedia_](https://en.wikipedia.org/wiki/ANSI_escape_code)

## Graphic parameters (Select Graphic Rendition)

> SGR sets display attributes. Several attributes can be set in the same sequence, separated by semicolons. Each display attribute remains in effect until a following occurrence of SGR resets it. If no codes are given, `CSI m` is treated as `CSI 0 m` (reset / normal).
> 
> ### Styles (format `CSI` + code + `m`):
> 
> | Code    | Effect                                                    | Note                                                   |
> |---------|-----------------------------------------------------------|--------------------------------------------------------|
> | 0       | Reset / Normal                                            | all attributes off                                     |
> | 1       | Bold or increased intensity                               |                                                        |
> | 2       | Faint (decreased intensity)                               |                                                        |
> | 3       | Italic                                                    | Not widely supported. Sometimes treated as inverse.    |
> | 4       | Underline                                                 |                                                        |
> | 5       | Slow Blink                                                | less than 150 per minute                               |
> | 6       | Rapid Blink                                               | MS-DOS ANSI.SYS; 150+ per minute; not widely supported |
> | 7       | reverse video                                             | swap foreground and background colors                  |
> | 8       | Conceal                                                   | Not widely supported.                                  |
> | 9       | Crossed-out                                               | Characters legible, but marked for deletion.           |
> | 10      | Primary(default) font                                     |                                                        |
> | 11–19   | Alternative font                                          | Select alternative font {\displaystyle n-10}           |
> | 20      | Fraktur                                                   | Rarely supported                                       |
> | 21      | Doubly underline or Bold off                              | Double-underline per ECMA-48.[22] See discussion       |
> | 22      | Normal color or intensity                                 | Neither bold nor faint                                 |
> | 23      | Not italic, not Fraktur                                   |                                                        |
> | 24      | Underline off                                             | Not singly or doubly underlined                        |
> | 25      | Blink off                                                 |                                                        |
> | 27      | Inverse off                                               |                                                        |
> | 28      | Reveal                                                    | conceal off                                            |
> | 29      | Not crossed out                                           |                                                        |
> | 30–37   | Set foreground color                                      | See color table below                                  |
> | 38      | Set foreground color                                      | Next arguments are 5;n or 2;r;g;b, see below           |
> | 39      | Default foreground color                                  | implementation defined (according to standard)         |
> | 40–47   | Set background color                                      | See color table below                                  |
> | 48      | Set background color                                      | Next arguments are 5;n or 2;r;g;b, see below           |
> | 49      | Default background color                                  | implementation defined (according to standard)         |
> | 51      | Framed                                                    |                                                        |
> | 52      | Encircled                                                 |                                                        |
> | 53      | Overlined                                                 |                                                        |
> | 54      | Not framed or encircled                                   |                                                        |
> | 55      | Not overlined                                             |                                                        |
> | 60      | ideogram underline or right side line                     | Rarely supported                                       |
> | 61      | ideogram double underline ordouble line on the right side |                                                        |
> | 62      | ideogram overline or left side line                       |                                                        |
> | 63      | ideogram double overline ordouble line on the left side   |                                                        |
> | 64      | ideogram stress marking                                   |                                                        |
> | 65      | ideogram attributes off                                   | reset the effects of all of 60–64                      |
> | 90–97   | Set bright foreground color                               | aixterm (not in standard)                              |
> | 100–107 | Set bright background color                               | aixterm (not in standard)                              |
>
> ### Color list:
>
> | Name           | FG Code | BG Code |
> |----------------|---------|---------|
> | Black          | 30      | 40      |
> | Red            | 31      | 41      |
> | Green          | 32      | 42      |
> | Yellow         | 33      | 43      |
> | Blue           | 34      | 44      |
> | Magenta        | 35      | 45      |
> | Cyan           | 36      | 46      |
> | White          | 37      | 47      |
> | Bright Black   | 90      |         |
> | Bright Red     | 91      | 101     |
> | Bright Green   | 92      | 102     |
> | Bright Yellow  | 93      | 103     |
> | Bright Blue    | 94      | 104     |
> | Bright Magenta | 95      | 105     |
> | Bright Cyan    | 96      | 106     |
> | Bright White   | 97      | 107     |
>
> [_From Wikipedia_](https://en.wikipedia.org/wiki/ANSI_escape_code)

## Learn more: [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code)