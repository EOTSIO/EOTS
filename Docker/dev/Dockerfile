FROM eotio/builder
ARG branch=master

RUN git clone -b $branch https://github.com/eotIO/EOTS.git --recursive \
    && cd EOTS && echo "$branch:$(git rev-parse HEAD)" > /etc/eotio-version \
    && cmake -H. -B"/opt/eotio" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/opt/eotio  -DSecp256k1_ROOT_DIR=/usr/local -DBUILD_MONGO_DB_PLUGIN=true \
    && cmake --build /opt/eotio --target install \
    && mv /EOTS/Docker/config.ini / && mv /opt/eotio/contracts /contracts && mv /EOTS/Docker/nodeotd.sh /opt/eotio/bin/nodeotd.sh \
    && rm -rf /EOTS

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl && rm -rf /var/lib/apt/lists/*
ENV eotIO_ROOT=/opt/eotio
RUN chmod +x /opt/eotio/bin/nodeotd.sh
ENV LD_LIBRARY_PATH /usr/local/lib
VOLUME /opt/eotio/bin/data-dir
ENV PATH /opt/eotio/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
