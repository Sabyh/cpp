# C++ Cheatsheet
This repo contains material I've covered when learning & reviewing C++. 

## Table of Contents
* [C++ Basics](https://github.com/kkufieta/cpp/blob/master/C%2B%2B%20Basics.ipynb)
* [Writing Multifile Programs](https://github.com/kkufieta/cpp/blob/master/Writing%20Multifile%20Programs.ipynb)
* [Building an OpenStreetMap Route Planner](https://github.com/kkufieta/cpp/blob/master/Building%20an%20OpenStreetMap%20Route%20Planner.ipynb)
* [A* algorithm - step by step](https://github.com/kkufieta/cpp/blob/master/A*%20algorithm%20-%20step%20by%20step.ipynb)
  * Link to Project Repo: [OpenStreetMap Route Planner using A*](https://github.com/kkufieta/openstreetmap_routeplanner_astar)

## Sources
The two sources for the material are:
* Online Course: [C++ Nanodegree from Udacity](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)
* Book: [A Tour of C++ by Bjarne Stroustrup](https://www.amazon.com/Tour-2nd-Depth-Bjarne-Stroustrup/dp/0134997832)

## C++ in Jupyter Notebooks
Some of the code is written in Jupyter Notebooks. This is possible using `xeus-cling`. 

### Install xeus-cling and set up the environment
Here is the [tutorial](https://www.learnopencv.com/xeus-cling-run-c-code-in-jupyter-notebook/) I used to set up the environment.

#### In case C++ doesn't show up in the dropdown menu
When I installed `xeus-cling` according to the tutorial above, C++ didn't show up in the drop-down menu when I tried to create a new file. [This solution](https://github.com/jupyter-xeus/xeus-cling/issues/217) fixed my issue.

### Start coding
Activate the environment and start jupyter notebook:
```bash
source activate xeus-cling
jupyter-notebook
```

### Notes: xeus-cling quirks 
#### Don't write the main function
`xeus-cling` works like a script language, you just write the code that should be evaluated. So, don't wrap your code in a `main()` function. ([source: stackoverflow](https://stackoverflow.com/questions/62751544/jupyter-notebook-error-for-c-kernelcling))

#### Defining a function in a cell has to happen at the top of it
A function doesn't seem to be allowed to be defined in a cell anywhere else but at the top of it.

That means you can only define one function per cell, and it has to be the first thing that happens in the cell.

## Run C++ locally
```bash
g++ -std=c++17 main.cpp && ./a.out
```
