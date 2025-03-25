FROM alpine:latest as compile-image
LABEL builder=true
RUN apk add --no-cache build-base cmake ninja git
COPY .. tbamud
WORKDIR tbamud
RUN mkdir -p build && rm -rf build/*
WORKDIR build
RUN cmake -GNinja ../src && ninja && cp circle ../bin

FROM alpine:latest as runtime-image
LABEL builder=false
RUN mkdir -p /app/bin
RUN mkdir -p /app/etc
RUN mkdir -p /app/lib
RUN mkdir -p /app/lib.org
RUN mkdir -p /app/log
COPY --from=compile-image /tbamud/bin /app/bin
COPY --from=compile-image /tbamud/lib /app/lib.org
COPY run.sh /app
EXPOSE 4000/tcp
CMD ["/bin/sh","/app/run.sh"]
