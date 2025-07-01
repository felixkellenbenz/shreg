# shreg

shreg is a simple regex engine that allows you to test if a given string 
matches a given regex.

## Building

If you are on Linux (It should work on Linux) simply clone the repository and
use the Makefile of the repository. 
Then you can run shreg like
```
shreg regexp string1 [string2 ...]
```
This will cause shreg to check if the given strings match the 
regular expression `regexp`
