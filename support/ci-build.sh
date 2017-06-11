#!/bin/bash

set -e

docker build -t ptracer-build support/
docker run --rm --user=`id -u`:`id -g` -i -v $PWD:/ptracer -t ptracer-build ./support/uncrustify-pass
docker run --rm --user=`id -u`:`id -g` -i -v $PWD:/ptracer -t ptracer-build /usr/bin/make ptracer tests
