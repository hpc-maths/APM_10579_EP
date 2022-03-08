[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/hpc-maths/MAP586/main)

This repository contains all the material for a course entitled "Algorithms and Software Design Principles for Applied Mathematics in Modern C++" given at the Ecole Polytechnique.

# Synopsis

Research in applied mathematics has seen major advances in recent years thanks to the rapid evolution of computing resources (GPUs, multi-core, massively parallel architectures). This implies an almost continuous adaptation of data structures and algorithms in order to fully exploit the available resources. These developments respond to the need to simulate and predict the behavior of increasingly complex systems, as close as possible to reality, in many scientific fields. These advances also contribute to innovation in the industrial field and in particular in SMEs and start-ups.

Furthermore, software and the infrastructures on which it is deployed are becoming more and more strategic for companies and research laboratories. As a result, today's engineer/researcher can no longer be satisfied with implementing algorithms for their own needs, independently of the objectives of the entity in which they work. He/She must be able to quickly integrate new software bricks into a complex architecture while ensuring its maintainability, portability and scalability. This requires not only a basic knowledge of algorithms and programming, but also solid knowledge of software design.

The originality of this teaching module is to start from concrete problems that we find in industrial and Open Source scientific computing codes and then to go back to the algorithms and their implementations. These problems will illustrate a set of numerical methods (numerical analysis of PDEs, statistical learning, stochastic computation, etc.) that require the choice of advanced algorithms and to present an elegant, modular and efficient implementation in modern C++. This course will be very interactive and will allow to experiment different improvements of existing solutions while analyzing their potential integration in complex systems.

To do so, we will first use Jupyter and the xeus-cling kernel to write C++ in notebooks, then we will move on to a more traditional project structuring to illustrate the architecture of a software (tree structure, creation of libraries and executables, etc.).

At the end of the course, a solid knowledge of algorithms will allow students to more easily understand the implementation of new numerical methods. Thanks to their knowledge of C++, they will be able to read most of the codes written in this language and to serenely consider all its potentialities. Finally, the notions of software engineering will allow them to understand the complex software architectures found in the research field as well as in industries.

# Content

The slides of the different sessions are available [online](https://hpc-maths.github.io/MAP586/).

## Courses

1. [The basics](https://hpc-maths.github.io/MAP586/courses/basics)
2. [Functional programming](https://hpc-maths.github.io/MAP586/courses/functional_stl)
3. [Compilation and code organization](https://hpc-maths.github.io/MAP586/courses/compilation)
4. [Object Oriented Programming](https://hpc-maths.github.io/MAP586/courses/oop)
5. [Value semantics](https://hpc-maths.github.io/MAP586/courses/value_semantics)
6. [Memory and pointers](https://hpc-maths.github.io/MAP586/courses/memory)
7. [Polymorphism](https://hpc-maths.github.io/MAP586/courses/polymorphism)
8. [Templates](https://hpc-maths.github.io/MAP586/courses/templates)

## Practical sessions

1. [The basics](https://github.com/gouarin/MAP586/tree/readme/courses/basics/notebooks)
1. [Functional programming](https://github.com/gouarin/MAP586/tree/readme/courses/functional_stl/notebooks)
1. [Compilation and code organization](https://github.com/gouarin/MAP586/tree/readme/courses/compilation/notebooks)

# Authors

- [Loic Gouarin](https://github.com/gouarin), [CNRS](https://www.cnrs.fr/en) research engineer in scientific computing at [CMAP](https://portail.polytechnique.edu/cmap/en). He has been developing Open Source software for many years ([pylbm](https://github.com/gouarin/pylbm), [samurai](https://github.com/hpc-maths/samurai), [xtensor-sparse](https://github.com/xtensor-stack/xtensor-sparse), ...). He is also co-developer of the [xeus-cling](https://github.com/jupyter-xeus/xeus-cling) kernel. His favorite languages are Python and C++.

- [Johan Mabille](https://github.com/JohanMabille), software engineer specialized in scientific computing. He works at [QuantStack](https://quantstack.net/), a French company specialized in open source development for scientific computing. He is the co-author of [xtensor](https://github.com/xtensor-stack/xtensor) and [xeus](https://github.com/jupyter-xeus) and is very involved in the development of [Jupyter](https://jupyter.org/) (protocol, kernels, debugger).
