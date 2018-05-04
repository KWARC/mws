### Dockerfile for MathWebSearch

## Builder Image
FROM debian:stretch-slim as builder

# Install dependencies
RUN apt-get update && apt-get -y install \
        cmake \
        g++ \
        make \
        pkg-config \
        libmicrohttpd-dev \
        libxml2-dev \
        libleveldb-dev \
        libsnappy-dev \
        libjson-c-dev \
        libhtmlcxx-dev \
        libgnutls28-dev \
        libicu-dev \
        libcurl4-gnutls-dev \
        doxygen \
        netcat \
        curl \
    && apt-get clean

## Setup file structure under /mws
ADD analytics/ /mws/analytics
ADD config/ mws/config
ADD scripts/ mws/scripts
ADD src /mws/src
ADD test/ mws/test
ADD third_party/ mws/third_party/

ADD .arcconfig /mws/
ADD .arclint /mws/
ADD .clang-format /mws/
ADD CMakeLists.txt /mws/
ADD Makefile /mws/

# Build and install into /install
WORKDIR /mws/
RUN make all
RUN mkdir -p /install/usr/ \
    && make install DESTDIR=/install PREFIX=/usr


## 
## add a runtime image
FROM debian:stretch-slim

# Install runtime libraries
RUN apt-get update && apt-get --no-install-recommends -y install \
        libmicrohttpd12 \
        libxml2 \
        libleveldb1v5 \
        libsnappy1v5 \
        libjson-c3 \
        libhtmlcxx3v5 \
        libgnutlsxx28 \
        libicu57 \
        libcurl3-gnutls \
    && apt-get clean

## Setup file structure under /mws
ADD config/ mws/config
ADD scripts/ mws/scripts
ADD README.md /mws
ADD LICENSE /mws/
COPY --from=builder /install/usr/local/bin/ /mws/bin

## And expand the path variable
ENV HOST="0.0.0.0"
ENV PATH="/mws/bin:${PATH}"