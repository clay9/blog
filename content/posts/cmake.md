+++
title = "cmake"
date = 2021-10-08T13:44:00+08:00
lastmod = 2021-10-09T18:32:36+08:00
tags = ["cmake"]
draft = false
+++

cmake

<!--more-->


## options {#options}

-S path\_to\_source
-B path\_to\_build
-G generator-name


## question {#question}

1.  err:

    ```text
    Tell CMake where to find the compiler by setting either the environment
    variable "CXX" or the CMake cache entry CMAKE_CXX_COMPILER to the full path
    to the compiler, or to the compiler name if it is in the PATH.
    ```

    sln:

    -   sudo apt install gcc
    -   sudo apt install g++