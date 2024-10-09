FROM ubuntu:latest

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get install -y build-essential && \
    apt-get install -y

RUN apt-get install -y vim cmake gdb libgtest-dev libgmock-dev catch2

COPY . /src/toyrobot/

WORKDIR /src/toyrobot/

CMD [ "bash" ]