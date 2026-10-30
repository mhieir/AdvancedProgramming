# Advanced Programming

C++ coursework and projects from **Advanced Programming** at the **University of Tehran**.

The repository progresses from standalone algorithmic exercises to multi-file object-oriented applications: a car-wash simulator, a Plants vs. Zombies-style game, and a university web application. An additional TA project explores logical-expression structures.

## Projects

| Folder | Project | Main concepts |
| --- | --- | --- |
| [` A1/`](%20A1/) | Course-selection checks using course information, prerequisites, and previous grades | Structured data, vectors, strings, and input processing |
| [A2](A2/) | Standalone exercises involving string arithmetic, hierarchical text output, and a transit-network graph | Recursion, string manipulation, graph modeling, and traversal |
| [A3](A3/) | Shared-expense processing and balance settlement | CSV parsing, expense-allocation rules, and settlement calculations |
| [A4](A4/) | Car-wash management simulator | Classes, simulation state, workers, service stages, queues, and event reporting |
| [A5](A5/) | Plants vs. Zombies-style graphical game | Inheritance, polymorphism, event handling, animation, collision logic, and SFML |
| [A6](A6/) | University management and social web application | Domain modeling, HTTP handlers, authentication, course management, profiles, and posts |
| [AP-TA-Project-main](AP-TA-Project-main/) | Logical-expression project | Node hierarchies, AND/OR/XOR operations, parsing, and tree processing |

The first assignment's directory is named **` A1` with a leading space**. The links and commands here preserve that filename.

## A4: Car-wash simulator

A command-driven simulation that models cars moving through requested service stages. It maintains workers and queues, advances simulation state, and records events and stage statistics.

**Entry point:** [`src/main.cpp`](A4/src/main.cpp)

**Domain classes:** [`car.hpp`](A4/include/car.hpp), [`worker.hpp`](A4/include/worker.hpp), [`stage.hpp`](A4/include/stage.hpp), and [`carwash.hpp`](A4/include/carwash.hpp).

### Build and run

From the repository root:

```bash
cd A4
mkdir -p obj
make clean
make
./CarWashManager /path/to/stages.csv /path/to/workers.csv
```

The two CSV arguments are required, in the order **stages, workers**. The repository does not include example CSV files for A4; prepare inputs matching the parser in [`src/input.cpp`](A4/src/input.cpp). Commands are read from standard input, with processing implemented in [`src/process.cpp`](A4/src/process.cpp).

`mkdir -p obj` ensures the object directory exists before compilation, since this Makefile does not create it automatically.

## A5: Graphical tower-defense game

An SFML game inspired by Plants vs. Zombies. The source separates game control from plant, zombie, projectile, collectible, and interface classes. Examples include sunflower and pea-shooter plants, different zombie types, and lawn cleaners.

**Entry point:** [`src/main.cpp`](A5/src/main.cpp)

**Game control:** [`System.cpp`](A5/src/System.cpp)

**Class-design notes:** [`class_defines.pdf`](A5/roadmap_ideas/class_defines.pdf).

### Requirements and build

- A C++20 compiler and Make.
- **SFML 2.x**, including graphics, window, system, and audio libraries. The checked-in Makefile references SFML **2.6.1**.

Before building, update [`A5/Makefile`](A5/Makefile) for your installation:

1. Set `SFML_INCLUDE_DIR` to the directory containing the `SFML/` headers.
2. Set `SFML_LIBRARY_DIR` to the directory containing the SFML libraries.
3. Add `-I$(SFML_INCLUDE_DIR)` to `CXXFLAGS` if the headers are not on the compiler's default search path. The current compile rule does not use `SFML_INCLUDE_DIR` automatically.

Then run:

```bash
cd A5
make clean
make
./pvz.out
```

Run from `A5/` so the relative paths to `files/` and `setting.txt` resolve correctly. The existing Makefile contains a Homebrew path from the original development machine; that path will need adjustment on other installations. SFML 3 is not a drop-in replacement for these SFML 2 APIs.

## A6: University web application

A university application built around students, professors, majors, courses, course offerings, and user accounts. HTTP handlers connect the domain model to HTML pages for login, course operations, personal pages, profile changes, and sharing posts.

The repository includes the HTTP server and utility source alongside the application.

**Entry point:** [`code/src/main.cpp`](A6/code/src/main.cpp)

**Domain initialization:** [`University.cpp`](A6/code/src/University.cpp)

**Request handlers:** [`handlers.cpp`](A6/code/src/handlers.cpp).

### Build and run

From the repository root:

```bash
cd A6
make clean
make
./utms.out majors.csv students.csv courses.csv teachers.csv
```

The argument order is significant: **majors, students, courses, teachers**. The entry point accesses these paths directly, so provide all four arguments.

Open **http://localhost:8080/** in a browser. Run the executable from `A6/` so its CSV, static-page, image, and template paths resolve correctly. The sample account data is in the supplied CSV files.

## Earlier assignments

A1, A2, and A3 are standalone C++ programs. Compile each file separately rather than combining their `main` functions.

For example, from the repository root:

```bash
g++ -std=c++20 " A1/A1-810102550.cpp" -o a1
./a1

g++ -std=c++20 A3/A3-810102550.cpp -o a3
./a3 /path/to/users.csv /path/to/expenses.csv
```

A1 and A2 read exercise-specific input from standard input. A3 expects two CSV filenames. Consult each program's input parser for the required structure; assignment specifications and complete sample inputs are not included for every exercise.

Some early files may need explicit standard-library includes on stricter compilers. For example, `A2/Q1.cpp` uses `std::reverse` without including `<algorithm>`.

## Additional TA project

[`AP-TA-Project-main/`](AP-TA-Project-main/) contains an object-oriented logical-expression project with AND, OR, and XOR node classes and a sample input file.

```bash
cd AP-TA-Project-main
make clean
make
./MK.out < input
```

See [`io.cpp`](AP-TA-Project-main/src/io.cpp) for the input grammar and [`LICENSE`](AP-TA-Project-main/LICENSE) for that project's license.

## General build notes

- The larger projects' Makefiles select **C++20** and enable sanitizers. Use a compiler and runtime that support those options.
- Build each project from its own directory.
- Rebuild from source for your platform; committed executables and object files may come from a different development environment.
- The commands above document the source and Makefile interfaces; they do not imply that every project has been tested on every platform.

## Author

[Mahdis Mirzaei](https://github.com/mhieir) · Computer Engineering, University of Tehran

Refer to individual project materials for any additional attribution. The HTTP framework and game assets are included dependencies and resources, rather than claims of original authorship of every repository file.
