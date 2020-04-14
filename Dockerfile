FROM debian

RUN apt-get update
RUN apt-get install -y git
RUN apt-get install -y g++
RUN apt-get install -y make

WORKDIR /root
RUN git clone git@github.com:touatily/IPv4.git

WORKDIR IPv4
RUN cp ipv4 /usr/local/include/
RUN make lib
RUN cp libipv4.a /usr/local/lib/
