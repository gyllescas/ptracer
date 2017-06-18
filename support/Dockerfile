FROM ubuntu:zesty
MAINTAINER Eric Missimer <missimer@gmail.com>

WORKDIR ptracer

RUN apt-get update && apt-get install -y \
    gcc libcmocka-dev make python git uncrustify \
    libdwarf-dev libelf-dev \
 && rm -rf /var/lib/apt/lists/*
