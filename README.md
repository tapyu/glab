# glab

Interactive educational multipurpose package to process and analyse GNSS data. 

**Context**: The gLAB installation process is not an easy task. On the one hand, the GUI part of [the gLAB version availabe along with the GNSS tutorial material (v5.2.0)][1] didn't work on Linux, but it contains the computational homeworks. On the other hand, the latest version of gLAB at the time of writing it (v5.5.1) worked perfectly on Linux, but it didn't have the computational homeworks, only the source code. Moreover, the directory structure of both versions is completely different. You can find the download link for all gLAB versions [here][6].
  
Therefore, in order to create a straightfoward path to use gLAB with the computation homeworks, I've created a git submodule at `./gLAB/`, which contains both the version v5.5.1 for Linux and the tutorial material. In the future, newer versions may be easier to install it and `./gLAB/` will no longer be necessary.

## Installing

- To install `glab`, run `./install.sh`. It should generate `gLAB_linux` and `gLAB_linux_multithread`.
- For 64-bits arch, use `gLAB_64`.

## Directory structure

- `FILES/`: Contains the backup gzip files for each tutorial in `TUTX/`. You should not remove these files as `ntpd_tutX.sh` decompresses them to create new `WORK/TUTX/` directories with the simulation results.
- `HTML/`:
- `PROG/`:
  - Contains the core source code for gLAB (`src/gLAB_src/`, in C), in addition to Fortran77 (in `src/F77_src/`) and Octave/Matlab (in `src/OCT_src`) for implementation of a more elaborated task.
  - Each `TUTX/` directory just contains configuration plus symlink to gLAB executable.
  - `Makefile` is the main buider that must be run to install gLAB (ignore the Makefiles under `/src/gLAB_src/`).
- `WORK/`: Contains the unzipped files and the simulation results for each tutorial in `TUTX`. This directory is ignored by git as it contains large files that are result of simulation. Possible file types that you might find in each `TUTX/` dir:
  - RINEX -> `<sta><Doy>0.<yy><type>`
    - `<sta>`: Station name.
    - `<Doy>`: Day of year.
    - `<yy>`: Year.
    - `<type>`: `o` -> observation RINEX file; `n` -> navigation RINEX file
    Example: `amc3030.03o` is the observation RINEX file for the `amc` station, on October 30th, 2003.
  - precise orbits & clocks -> `.sp3` extension
  - Antenna Phase Center (APC) -> `.atx.`
  - Precise receiver coordinates -> `.snx.`
- `ntpd_tutX.sh`: Unix Shell script to run tutorial X. It basically creates `WORK/TUTX/`, and copies the config files from `PROG/TUTX/` and data files from `FILES/TUTX/` to it.

[here]: https://gage.upc.edu/en/learning-materials/software-tools/glab-tool-suite-links/glab-download
[1]: https://gage.upc.edu/486/gage/en/en/learning-materials/software-tools/glab-tool-suite-links/glab-tutorials/gnss-tutorials
[6]: https://gage.upc.edu/en/learning-materials/software-tools/glab-tool-suite-links/glab-download
