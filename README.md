# C++ Cheatsheet
This repo contains material I've covered when learning & reviewing C++.

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

### Note: Don't write the main function
`xeus-cling` works like a script language, you just write the code that should be evaluated. So, don't wrap your code in a `main()` function. ([source: stackoverflow](https://stackoverflow.com/questions/62751544/jupyter-notebook-error-for-c-kernelcling))

## Run C++ locally
```bash
g++ -std=c++17 main.cpp && ./a.out
```
