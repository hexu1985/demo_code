FROM ubuntu:20.04
COPY sources.list /etc/apt
RUN apt update; \
        apt install -y vim make gcc g++ gdb; \
        apt clean;

# add user if need
RUN useradd -ms /bin/bash hexu
RUN mkdir /home/hexu/corefile
USER hexu
WORKDIR /home/hexu


