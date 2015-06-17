Speech Recognition
==================

I made this public, because I have no more private repo.
Project for EPITA.

*If any questions, open an issue...*

### Authors:

- Alexis Yang
- Marius Tanawa
- Emmanuel Andriot
- And me

Inspired by https://github.com/Phorce/RAPCS

### Dependencies

- libsndfile
- gnuplot

#### Installation OS X

```bash
brew install libsndfile
brew install gnuplot
```

#### Installation ubuntu
```bash
sudo apt-get install libsndfile1 libsndfile1-dev gnuplot clang
```

### Usage

For the gui, you need [nwjs](https://github.com/nwjs/nw.js/).

On my OS X:

```bash
make distance # Compile dtw binary
make feature  # Compile feature extraction binary
cd gui
 ~/Downloads/nwjs-v0.12.2-osx-x64/nwjs.app/Contents/MacOS/nwjs .
```

**Good :four_leaf_clover:**
