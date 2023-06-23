# printAscii
![Ascii Art Piaktchu](https://i.imgur.com/y3mM7FM.png)

## How to use:
#### Build the c program :
```console
$ gcc printAscii.c -o printAscii -Wall -lm
```
#### Run :
```console
$ ./printAscii [options] [image] AsciiBi2.txt
```
- The order of the arguments must be as specified 
### Available options:
- `-i` : inverses the resulting Ascii image colors.
- `-a 0..255` : converts pixels with 0 alpha to the value specified.
- `-t 0..255` : changes the threshold for converting pixels to black or white.
- `-o [output file]` : prints the Ascii art in a file instead of the terminal.

## Image loading library :
- https://github.com/nothings/stb
