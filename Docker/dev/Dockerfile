FROM eotio/builder
ARG branch=master

RUN git clone -b $branch https://github.com/eotIO/eot.git --recursive \
    && cd eot && echo "$branch:$(git rev-parse HEAD)" > /etc/eotio-version \
    && cmake -H. -B"/opt/eotio" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/opt/eotio  -DSecp256k1_ROOT_DIR=/usr/local -DBUILD_MONGO_DB_PLUGIN=true \
    && cmake --build /opt/eotio --target install \
    && mv /eot/Docker/config.ini / && mv /opt/eotio/contracts /contracts && mv /eot/Docker/nodeotd.sh /opt/eotio/bin/nodeotd.sh \
    && rm -rf /eot

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl && rm -rf /var/lib/apt/lists/*
ENV eotIO_ROOT=/opt/eotio
RUN chmod +x /opt/eotio/bin/nodeotd.sh
ENV LD_LIBRARY_PATH /usr/local/lib
VOLUME /opt/eotio/bin/data-dir
ENV PATH /opt/eotio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
