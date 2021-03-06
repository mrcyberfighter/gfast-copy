========================
gfast-copy and fast-copy
========================

-----
About
-----

:author: Brüggemann Eddie <mrcyberfighter@gmail.com>

:version: 1.0

:release: 22/10/2017.

:license: GPLv3.

----------
gfast-copy
----------

.. image:: ./gfast-copy_icon.png

**gfast-copy** provide an *easy to use graphical interface* to the underlying

**copy algorithm** describe below.

By copying the program **display a progress-bar** and

some part of the interface are frozen.

**Gtk+-3.0** is used as **H.M.I** (Human Machine Interface) in a fancy way:

You can switch between the *light* and *dark* (if installed at your site)

**themes**.

You can choose the **delete the source file** and the destination

*file-selector* will ask you if you choose and existing file

for **overwriting**.

---------
fast-copy
---------

**fast-copy** is a command line tool for copying a single big file

at the same time,

as fast as it can (Faster than the O.S, especially on MacOSX).

You must at minimal provide an *input file* and an *output file*.

**fast-copy** use per default ``FILE`` streams for copying the file.

But you can use the system calls ``open()``, ``read()``, ``write()``, ``close()``, ``fsync()``

instead by giving the ``-s`` option on the command line.

**fast-copy** will output the *source file-path* and the *destination file-path*.

**fast-copy** will output the *file size* in the right unit.


And if the source file is greater than **16** *Mio* (for a *buffer* size of **8192**)

it will display **a progress-bar** during the *copy operation*.

~~~~~~~~~~~~~~~~~~
The copy algorithm
~~~~~~~~~~~~~~~~~~

At first it will check for the **best buffer size**.

  + Using ``FILE`` streams: it will look up the ``BUFSIZ`` constant if it’s great enough
                        else the program set it to **8192** *octets*.

  + Using **syscalls** it will look up the the **st_blocksize** from the ``stat()`` function
    and set it as *buffer* size.

Then it will define a buffer with the optimal size.

It will copy the *source file* to the *destination* in a loop using the defined **buffer**.

Finally it will synchronize the file-system using ``fflush()`` or ``fsync()``.

~~~~~~~~~~~~~~
fast-copy help
~~~~~~~~~~~~~~

::

  fast-copy - a fast chunk file copy program.

  Usage : fast-copy -r input-file -w output-file [-o] [-s] [-e] [-h]

  -r Read from file (required).
  -w Write to file  (required).
  -o Overwrite destination file (optional).
  -e Erase source file (optional).
  -s Use syscalls instead of streams (optional only UNIX).
  -h Print this help message.

- Copyright (©) 2017 Brüggemann Eddie <mrcyberfighter@gmail.com> GPLv3.

~~~~~~~~~~~~~~
Wrapper script
~~~~~~~~~~~~~~

You can build a wrapper script around the ``fast-copy`` command-line tool,

per example using ``zenity``, ``xclip`` or like, to get the first argument.

And for the second you need a tool which provides a file-chooser.

As like this one, using zenity and nautilus-action:

.. code-block:: bash

  #! /bin/bash

  ###############################################################
  # Wrapper for fast-copy using zenity and nautilus-actions for #
  # speed up the file copying.                                  #
  ###############################################################

  function usage() {

    echo "usage $(basename $0) -r input-file -w output-file [-o] [-s] [-e] [-h]" ;

    exit 1 ;
  }

  if [[ $# -ne 1 ]] ; then

    # The first argument is given from nautilus-actions.

    usage ;

  fi

  destination=`zenity --file-selection --save --confirm-overwrite --filename="$(basename "${1}")"`

  # Here the source file comes from nautilus action i.e
  # the contextual gnome-desktop add-on nautilus-actions
  source_filepath=${1}

  if [[ -n "${destination}" ]] ; then

    fast-copy -r "${source_filepath}" -w "${destination}" -o

    zenity --info --text="Copy completed" --no-wrap --no-markup

  fi

  exit 0




------------
Compatiblity
------------

**gfast-copy** and **fast-copy** works on

+ ``GNU/Linux`` as \*.deb, \*.rpm and tarball packages.

+ ``MacOSX``, using the tarball which makes an entry into the /Applications folder.

+ ``Windows``

  into the **MSYS2** or **Cygwin** environment using the tarball.

  and is provides as auto-extractable \*.exe file.

You can find all this files at: <http://www.open-source-projects.net/gfast-copy/gfast-copy>

-------
Credits
-------

Thanks to my beloved mother, my family and to the doctors.

Stay away from drugs: drugs destroy your brain and your life.

---

Special thanks to the gnome-bugzilla team,

without their help them I would not be able to distribute an

auto-extractable \*.exe file for Windows.

-------
License
-------

::

  (g)fast-copy - a fast single chunk file copy program.

  Copyright (C) 2017 Brüggemann Eddie.

  This file is part of (g)fast-copy.
  (g)fast-copy is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  (g)fast-copy is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with (g)fast-copy. If not, see <http://www.gnu.org/licenses/>


