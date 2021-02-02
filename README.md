# pumi-intro
Beginner's Guide to using the PUMI libraries

# build with cmake
Note, only in-source builds are supported.
```
#setup environment via modules etc.
cmake -DSCOREC_PREFIX=/path/to/scorec/install
make
```

# build with latexmk

```
latexmk -r latexmk.linux
```

#clean up
To delete all untracked files run the following command.
```
git clean -fd
```
