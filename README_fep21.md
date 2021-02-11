#contents
This directory contains C++ PUMI examples, latex source code used to generate
the pumi-intro document, and build systems for them.

## C++ PUMI examples
pcu*.c - pcu examples
pumi*.cc - pumi api examples
CMakeLists.txt - CMake build system file
cube.dmg - geometric model
*.smb - meshes
setup.sh - setup script, see below
build.sh - build script, see below
run.sh - run script, see below

## latex
README.md
pumi_intro.tex
select_nodes.png
gear.png
latexmkrc.linux
latexmkrc.osx
updateSkim.sh
openSkim.sh

#connect - do this each time you start work
ssh erp14

#setup - run this once
./setup.sh

#build - run this when you need to rebuild the code
./build.sh pcu1
./build.sh pcu2
./build.sh pumi1
./build.sh pumi2
./build.sh pumi3

#run - run the exectuable via SLURM
sbatch -n 4 ./run.sh ./build/pcu1
sbatch -n 4 ./run.sh ./build/pcu2
sbatch -n 1 ./run.sh ./build/pumi1
sbatch -n 1 ./run.sh ./build/pumi2
sbatch -n 2 ./run.sh ./build/pumi3

