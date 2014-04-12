high dynamic range effects
==========================

dependencies
------------

This project uses cmake, glfw, and rgbe (library developed by Greg Ward), it has been developed using OpenGL 3.2 and GLSL 1.5.

#### mac osx

Download and install [CMake](http://www.cmake.org/cmake/resources/software.html)
if you don't already have it. 
To simplify installation you may use [Homebrew](http://brew.sh):

```bash
brew install cmake
```

#### linux (ubuntu)

```bash
sudo apt-get install cmake
```

build and run
-------------

```bash
cd build
cmake .. && make
```

usage
-----

While running, use the following keys to move/modify render parameters:

* mouse : look around
* Z : move forward
* S : move backward
* D : move right
* Q : move left
* B : activate/desactivate bloom effect
* T : activate/desactivate tone mapping effect
* L : activate/desactivate lens flare effect
* R : activate/desactivate cubic lens distortion
* X : activate/desactivate noise added to the bloom effect
* N : increase bright threshold associated to both lens flare and bloom effect
* J : decrease bright threshold
* V : increase bloom factor
* G : decrease bloom factor
* C : increase the number of blur pass assoaciated to the bloom effect
* F : decrease the number of blur pass assoaciated to the bloom effect

article 
-------

This project comes with the following [article](http://www.karim.naaji.fr/documents/naaji13-hdreffects.pdf). You can also check the [page](http://www.karim.naaji.fr/projects/hdreffects) of the project for some more informations.

example
--------

![example](http://www.karim.naaji.fr/images/lensflare-bloom.png)

licence
======= 

      This program is an implementation of the technique of high dynamic 
      range (HDR) image based lightning (IBL) in real time. 
      
      Copyright (C) 2013 Naaji Karim (karim.naaji@gmail.com)
      
      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.
      
      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.
      
      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>.
