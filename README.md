# Tutorials

This branch contains the tutorial datafiles contained in the [GNSS tutorial link][1] (see `Software and Data Files [Linux]`). At the time I am writing it, it contains gLAB v5.2 + Datafiles, and is used for education purposes. Here, I separed only the datafiles so that the tutorial datafiles be used with any gLAB version.

## Directory structure

- `FILES/`: Contains the backup gzip files for each tutorial in `TUTX/`. You should not remove these files as `ntpd_tutX.sh` decompresses them to create new `WORK/TUTX/` directories with the simulation results.
- `HTML/`:
- `PROG/`:
  - Contains the core source code for gLAB (`src/gLAB_src/`, in C), in addition to Fortran77 (in `src/F77_src/`) and Octave/Matlab (in `src/OCT_src`) for implementation of a more elaborated task.
  - Each `TUTX/` directory just contains configuration plus symlink to gLAB executable.
  - `Makefile` is the main buider that must be run to install gLAB (ignore the Makefiles under `/src/gLAB_src/`).
- `WORK/`: Contains the unzipped files and the simulation results for each tutorial in `TUTX`. This directory is ignored by git as it contains large files that are result of simulation. Possible file types that you might find in each `TUTX/` dir:

[1]: https://gage.upc.edu/486/gage/en/en/learning-materials/software-tools/glab-tool-suite-links/glab-tutorials/gnss-tutorials
