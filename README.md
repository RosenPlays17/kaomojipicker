This is a small kaomoji picker for Linux, written in QT. The picked kaomoji is copied to the clipboard. The program
searches for kaomoji files in `/kaomojipicker/kaomoji` in the usual data locations, `/usr/share`, `/usr/local/share`
and `~/.local/share`. To expand the list of available kaomoji, simply edit the existing files or add new files to add
new categories.

# Building
```shell
cmake -DCMAKE_BUILD_TYPE=Release -B build
cmake --build build
```