Getting Started on Linux
------------------------

Dependencies On Ubuntu & Debian
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    sudo apt-get install qttools5-dev-tools \
                         qttools5-dev \
                         qtbase5-dev \
                         qt5-qmake \
                         libqt5help5 \
                         libqt5opengl5-dev \
                         libqt5svg5-dev \
                         libqt5x11extras5-dev \
                         libqwt-qt5-dev \
                         libudev-dev \
                         libxml2-dev \
                         libsdl2-dev \
                         libavahi-compat-libdnssd-dev \
                         python-dev \
                         libboost-python-dev \
                         doxygen \
                         cmake \
                         g++ \
                         git \
                         make \
 
Building Aseba
~~~~~~~~~~~~~~

::

    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF ..
    make

A note about permissions
~~~~~~~~~~~~~~~~~~~~~~~~

If you will be connecting to your robot through a serial port, you might
need to add yourself to the group that has permission for that port. In
many distributions, this is the "dialout" group and you can add yourself
to that group and use the associated permissions by running the
following commands:

::

    sudo usermod -a -G dialout $USER
    newgrp dialout

## Building packages

### Debian-based
On Debian-based distributions (Debian, Ubuntu, etc.), you can build *deb* packages.
First, install the necessary build scripts:

    sudo apt-get install build-essential devscripts equivs
    
Then, install the build dependencies for Dashel and Enki, build them as packages and install them, install the additional build dependencies for Aseba, and build the Aseba package.

    # build Dashel package and install it
    cd dashel
    sudo mk-build-deps -i         # install dependencies
    debuild -i -us -uc -b         # build package
    cd ..
    sudo dpkg -i libdashel*.deb   # install package
    # build Enki package and install it
    cd enki
    sudo mk-build-deps -i         # install dependencies
    debuild -i -us -uc -b         # build package
    cd ..
    sudo dpkg -i libenki*.deb     # install package
    # build Aseba package
    cd aseba
    apsudo mk-build-deps -i         # install dependencies
    debuild -i -us -uc -b         # build package
    cd ..
