+++
title = "github"
date = 2021-09-23T21:43:00+08:00
lastmod = 2021-09-28T18:35:23+08:00
tags = ["github"]
categories = ["tool"]
draft = false
+++

github记录

<!--more-->


## workflow -- hugo {#workflow-hugo}

```text
workflow中所有缩进必须是空格, 不能是tab
```

name: github page

on:

push:
  branches:

-   master  # Set a branch to deploy

pull\_request:

jobs:

deploy:

runs-on: ubuntu-20.04

steps:

-   uses: actions/checkout@v2
    with:
      submodules: true  # Fetch Hugo themes (true OR recursive)
      fetch-depth: 0    # Fetch all history for .GitInfo and .Lastmod

<!--listend-->

-   name: Setup Hugo

    uses: peaceiris/actions-hugo@v2
    with:
      hugo-version: 'latest'

<!--listend-->

-   name: Build
    run: hugo --minify

<!--listend-->

-   name: Deploy
    uses: peaceiris/actions-gh-pages@v3

    if: github.ref == 'refs/heads/master'

    with:
      github\_token: ${{ secrets.HUGO\_PUBLISH\_TOKEN }}
      publish\_dir: ./public


## workflow -- server-kernel {#workflow-server-kernel}

name: build-kernel

on:
  push:
    branches:

-   master  # Set a branch to deploy

jobs:
  build:
    runs-on: ubuntu-20.04
    steps:

-   uses: actions/checkout@v2
-   name: step 1 test

run: echo "step 1"

shell: bash

-   name: step 2 make
    run: make

<!--listend-->

-   name: step 3 deploy

    run: echo "step 3"

    shell: bash


## workflow {#workflow}

name: build-kernel

on:
  push:
    branches:

-   master  # Set a branch to deploy

jobs:
  build:
    runs-on: ubuntu-20.04
    steps:

-   uses: actions/checkout@v2
-   name: step-1
    run: echo ${env:PATH}
    shell: bash
-   name: step 2 make
    uses: docker://alpine:3.8

  protobuf:
run: make

-   name: step 3 deploy
    run: echo "step 3"
    shell: bash