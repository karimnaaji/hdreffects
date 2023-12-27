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
./hdr.out
```

usage
-----

While running, use the following keys to move around and modify render parameters:

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
* C : increase the number of blur pass associated to the bloom effect
* F : decrease the number of blur pass associated to the bloom effect

results
-------

![example](http://karim.naaji.fr/images/lens_flare_low.gif)

      GNU General Public License for more details.
      
      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>.
