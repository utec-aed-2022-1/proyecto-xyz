{ pkgs ? import <nixpkgs> { } }:

with pkgs;

mkShell {
  buildInputs = [ ];

  nativeBuildInputs = [
    clang_14
    gcc

    cgdb
    clang-tools
    cling
    gdb
    valgrind

    cmake
    just
    meson
    ninja
    pkg-config
  ];
}
