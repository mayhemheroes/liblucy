FROM --platform=linux/amd64 ubuntu:20.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y jq build-essential clang

COPY . /liblucy
WORKDIR /liblucy
RUN make bin/lucyc
RUN clang /liblucy/mayhem/fuzz_string_list_append.cpp -fsanitize=fuzzer,address /liblucy/src/core/string_list.c -o /fuzz

FROM ubuntu:20.04 as package
COPY --from=builder /liblucy/bin/lucyc /liblucy/bin/lucyc
COPY --from=builder /fuzz /fuzz_string_list_append

