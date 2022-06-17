FROM --platform=linux/amd64 ubuntu:20.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y jq build-essential

ADD . /liblucy
WORKDIR /liblucy
RUN make bin/lucyc

RUN mkdir -p /deps
RUN ldd /liblucy/bin/lucyc | tr -s '[:blank:]' '\n' | grep '^/' | xargs -I % sh -c 'cp % /deps;'

FROM ubuntu:20.04 as package

COPY --from=builder /deps /deps
COPY --from=builder /liblucy/bin/lucyc /liblucy/bin/lucyc
ENV LD_LIBRARY_PATH=/deps
