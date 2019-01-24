# pumi-intro
Beginner's Guide to using the PUMI libraries

#contents
*.cc - source code
*.dmg - geometric model
*.smb - meshes
CMakeLists.txt - cmake file for building the examples
README_FEP.md - this file
setup.sh - setup script, see below
build.sh - build script, see below
run.sh - run script, see below

#setup - run this once
./setup.sh

#build - run this when you need to rebuild the code
./build.sh pcu1
./build.sh pcu2
./build.sh pumi1
./build.sh pumi2
./build.sh pumi3

#run - run the exectuable via SLURM
sbatch ./run.sh ./build/pcu1  4
sbatch ./run.sh ./build/pcu2  4
sbatch ./run.sh ./build/pumi1 1
sbatch ./run.sh ./build/pumi2 1
sbatch ./run.sh ./build/pumi3 2

