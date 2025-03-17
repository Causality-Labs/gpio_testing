FROM debian:11

ENV TZ UTC

RUN apt-get update && \
    apt-get install -y --no-install-recommends build-essential git gem ruby make gcc vim && \
    apt-get clean && rm -rf /var/cache/apt/archives/* && \
    rm -rf /var/lib/apt/lists/* && \
    cd /tmp/ && \
    git clone --recursive --depth=1 --single-branch --branch v0.31.0  https://github.com/ThrowTheSwitch/Ceedling.git ceedling && \
    cd ceedling && \
    gem build ceedling.gemspec && \
    gem install ceedling-*.gem && \
    cd /root/ && \
    rm -rf /tmp/ceedling

CMD bash