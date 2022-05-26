FROM --platform=linux/amd64 ubuntu:20.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y jq build-essential

ADD . /liblucy
WORKDIR /liblucy
RUN make bin/lucyc
