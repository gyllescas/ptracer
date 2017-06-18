#!/bin/bash

set -e

DOCKER_ARGS="--rm --user=`id -u`:`id -g` -i -v $PWD:/ptracer -t ptracer-build"

docker build -t ptracer-build support/
#docker run $DOCKER_ARGS ./support/uncrustify-pass
docker run --security-opt seccomp:unconfined $DOCKER_ARGS /usr/bin/make ptracer tests
