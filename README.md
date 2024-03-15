# Setup

Ensure you have [docker](https://docker.io) and [docker-compose](https://docs.docker.com/compose/)
installed.

# Running Examples

## With Docker (recommended)

To run unit tests, just execute

```
docker-compose up
```

As you edit the source code the project should compile automatically.

# Without docker

Ensure you have cmake and entr installed (and a C++ compiler, of course).

```
mkdir build
cd build
cmake ..
make
./lib_tests
```

