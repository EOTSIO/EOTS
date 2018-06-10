# Run in docker

Simple and fast setup of EOTS.IO on Docker is also available.

## Install Dependencies

- [Docker](https://docs.docker.com) Docker 17.05 or higher is required
- [docker-compose](https://docs.docker.com/compose/) version >= 1.10.0

## Docker Requirement

- At least 7GB RAM (Docker -> Preferences -> Advanced -> Memory -> 7GB or above)
- If the build below fails, make sure you've adjusted Docker Memory settings and try again.

## Build EOTS image

```bash
git clone https://github.com/eotIO/EOTS.git --recursive  --depth 1
cd EOTS/Docker
docker build . -t eotio/EOTS
```

The above will build off the most recent commit to the master branch by default. If you would like to target a specific branch/tag, you may use a build argument. For example, if you wished to generate a docker image based off of the dawn-v4.0.0 tag, you could do the following:

```bash
docker build -t eotio/EOTS:dawn-v4.0.0 --build-arg branch=dawn-v4.0.0 .
```

## Start nodeot docker container only

```bash
docker run --name nodeot -p 8888:8888 -p 9876:9876 -t eotio/EOTS nodeotd.sh arg1 arg2
```

By default, all data is persisted in a docker volume. It can be deleted if the data is outdated or corrupted:

```bash
$ docker inspect --format '{{ range .Mounts }}{{ .Name }} {{ end }}' nodeot
fdc265730a4f697346fa8b078c176e315b959e79365fc9cbd11f090ea0cb5cbc
$ docker volume rm fdc265730a4f697346fa8b078c176e315b959e79365fc9cbd11f090ea0cb5cbc
```

Alternately, you can directly mount host directory into the container

```bash
docker run --name nodeot -v /path-to-data-dir:/opt/eotio/bin/data-dir -p 8888:8888 -p 9876:9876 -t eotio/EOTS nodeotd.sh arg1 arg2
```

## Get chain info

```bash
curl http://127.0.0.1:8888/v1/chain/get_info
```

## Start both nodeot and keotd containers

```bash
docker volume create --name=nodeot-data-volume
docker volume create --name=keotd-data-volume
docker-compose up -d
```

After `docker-compose up -d`, two services named `nodeotd` and `keotd` will be started. nodeot service would expose ports 8888 and 9876 to the host. keotd service does not expose any port to the host, it is only accessible to cleot when running cleot is running inside the keotd container as described in "Execute cleot commands" section.

### Execute cleot commands

You can run the `cleot` commands via a bash alias.

```bash
alias cleot='docker-compose exec keotd /opt/eotio/bin/cleot -u http://nodeotd:8888 --wallet-url http://localhost:8888'
cleot get info
cleot get account inita
```

Upload sample exchange contract

```bash
cleot set contract exchange contracts/exchange/exchange.wast contracts/exchange/exchange.abi
```

If you don't need keotd afterwards, you can stop the keotd service using

```bash
docker-compose stop keotd
```

### Develop/Build custom contracts

Due to the fact that the eotio/EOTS image does not contain the required dependencies for contract development (this is by design, to keep the image size small), you will need to utilize the eotio/EOTS-dev image. This image contains both the required binaries and dependencies to build contracts using eotiocpp.

You can either use the image available on [Docker Hub](https://hub.docker.com/r/eotio/EOTS-dev/) or navigate into the dev folder and build the image manually.

```bash
cd dev
docker build -t eotio/EOTS-dev .
```

### Change default configuration

You can use docker compose override file to change the default configurations. For example, create an alternate config file `config2.ini` and a `docker-compose.override.yml` with the following content.

```yaml
version: "2"

services:
  nodeot:
    volumes:
      - nodeot-data-volume:/opt/eotio/bin/data-dir
      - ./config2.ini:/opt/eotio/bin/data-dir/config.ini
```

Then restart your docker containers as follows:

```bash
docker-compose down
docker-compose up
```

### Clear data-dir

The data volume created by docker-compose can be deleted as follows:

```bash
docker volume rm nodeot-data-volume
docker volume rm keotd-data-volume
```

### Docker Hub

Docker Hub image available from [docker hub](https://hub.docker.com/r/eotio/EOTS/).
Create a new `docker-compose.yaml` file with the content below

```bash
version: "3"

services:
  nodeotd:
    image: eotio/EOTS:latest
    command: /opt/eotio/bin/nodeotd.sh
    hostname: nodeotd
    ports:
      - 8888:8888
      - 9876:9876
    expose:
      - "8888"
    volumes:
      - nodeot-data-volume:/opt/eotio/bin/data-dir

  keotd:
    image: eotio/EOTS:latest
    command: /opt/eotio/bin/keotd
    hostname: keotd
    links:
      - nodeotd
    volumes:
      - keotd-data-volume:/opt/eotio/bin/data-dir

volumes:
  nodeot-data-volume:
  keotd-data-volume:

```

*NOTE:* the default version is the latest, you can change it to what you want

run `docker pull eotio/EOTS:latest`

run `docker-compose up`

### Dawn 4.0 Testnet

We can easily set up a Dawn 4.0 local testnet using docker images. Just run the following commands:

Note: if you want to use the mongo db plugin, you have to enable it in your `data-dir/config.ini` first.

```
# pull images
docker pull eotio/EOTS:latest
docker pull mongo:latest
# create volume
docker volume create --name=nodeot-data-volume
docker volume create --name=keotd-data-volume
docker volume create --name=mongo-data-volume
# start containers
docker-compose -f docker-compose-dawn4.0.yaml up -d
# get chain info
curl http://127.0.0.1:8888/v1/chain/get_info
# get logs
docker-compose logs nodeotd
# stop containers
docker-compose -f docker-compose-dawn4.0.yaml down
```

The `blocks` data are stored under `--data-dir` by default, and the wallet files are stored under `--wallet-dir` by default, of course you can change these as you want.

### About MongoDB Plugin

Currently, the mongodb plugin is disabled in `config.ini` by default, you have to change it manually in `config.ini` or you can mount a `config.ini` file to `/opt/eotio/bin/data-dir/config.ini` in the docker-compose file.
