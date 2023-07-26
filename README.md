<div align="center">

# Bot Training

Small bot launcher allowing to load symbols from a shared library to test algorithms.

</div>

## Requirements

- `CMake 3.16 and above`
- A `C++/C` compiler

## Usage

1) Clone the repo using: 
```
git clone --recurse-submodules --depth 1 git@github.com:louvtt/mx-bot-training
```

2) Build
```
cmake -B build
cmake --build build
```
> You can specify a launcher in the first command (i.e `-G Ninja`)

3) Launch

```
./build/apps/mxlauncher
```


## Libraries

- glad
- glfw
- imgui
- spdlog