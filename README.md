
# File Zipper

File Zipper command line application using huffman coding algorithm (C++).


## Features

- Compress and Decompress file of any type
- Can compress file upto 50-60 %
- Compressed files are save with '.apzip' extension


## Getting Started

### Installation
1. Clone the project

```bash
  git clone https://github.com/akshaypatel67/File-Zipper.git
```

2. Go to the project directory

```bash
  cd File-Zipper
```

### Compiling Program

```bash
  g++ main.cpp HuffmanCode/HuffmanCode.cpp Node/Node.cpp FrequencyCounter/FrequencyCounter.cpp -o file-zipper
```
## Usage

Compress File

```bash
  file-zipper compress filename
```

Decompress File

```bash
  file-zipper decompress filename
```