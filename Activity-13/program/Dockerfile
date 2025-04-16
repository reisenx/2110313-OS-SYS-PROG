FROM alpine:latest
RUN apk add --no-cache gcc libc-dev

WORKDIR /app
COPY main.c .
RUN gcc -o app main.c
CMD ["./app"]