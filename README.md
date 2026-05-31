# CS Fundamentals

C implementations of core data structures from scratch, written during an intensive C/C++ embedded systems bootcamp at Experis Academy.

All implementations use manual memory management and generic programming patterns in C via `void*`, without relying on any standard library containers.

## Data Structures

| Folder | Description |
|--------|-------------|
| `vector` | Dynamic array with automatic resizing |
| `GenericVector` | Generic dynamic array using `void*` — works with any data type |
| `genDoubleLinkedList` | Generic doubly linked list |
| `genQueue` | Generic queue built on top of the linked list |
| `HashMap` | Hash map with chaining for collision resolution |
| `BinaryHeap` | Binary heap (min/max) for priority queue operations |
| `BinaryTree` | Binary search tree with insert, search, and traversal |

## Key Concepts Demonstrated

- **Manual memory management** — explicit `malloc`/`free`, no garbage collection
- **Generic programming in C** — using `void*` and function pointers to build reusable, type-agnostic data structures
- **Pointer arithmetic** — direct memory manipulation for performance
- **Modular design** — each data structure is self-contained with its own header and implementation

## Building

Each folder contains its own `makefile`. To build a specific module:

```bash
cd GenericVector
make
```

## Notes

These implementations were written in C as part of a bootcamp focused on systems programming and computer science fundamentals. The goal was to understand how standard library containers work under the hood by building them from scratch.