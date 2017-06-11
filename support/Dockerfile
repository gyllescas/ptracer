FROM ubuntu:zesty
MAINTAINER Eric Missimer <missimer@gmail.com>

WORKDIR ptracer

RUN apt-get update && \
    apt-get install -yq gcc libcmocka-dev make python git uncrustify \
            libdwarf-dev
