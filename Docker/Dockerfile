FROM eotio/builder as builder
ARG branch=master

RUN git clone -b $branch https://github.com/eotIO/eot.git --recursive \
    && cd eot && echo "$branch:$(git rev-parse HEAD)" > /etc/eotio-version \
    && cmake -H. -B"/tmp/build" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/tmp/build  -DSecp256k1_ROOT_DIR=/usr/local -DBUILD_MONGO_DB_PLUGIN=true \
    && cmake --build /tmp/build --target install && rm /tmp/build/bin/eotiocpp


FROM ubuntu:18.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl && rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/lib/* /usr/local/lib/
COPY --from=builder /tmp/build/bin /opt/eotio/bin
COPY --from=builder /tmp/build/contracts /contracts
COPY --from=builder /eot/Docker/config.ini /
COPY --from=builder /etc/eotio-version /etc
COPY --from=builder /eot/Docker/nodeotd.sh /opt/eotio/bin/nodeotd.sh
ENV eotIO_ROOT=/opt/eotio
RUN chmod +x /opt/eotio/bin/nodeotd.sh
ENV LD_LIBRARY_PATH /usr/local/lib
VOLUME /opt/eotio/bin/data-dir
ENV PATH /opt/eotio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
