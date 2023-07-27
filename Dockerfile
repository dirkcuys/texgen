FROM debian:bookworm
RUN apt-get update \
	&& apt-get install -y \
        build-essential \
        cmake \
        libsdl2-dev \
        libglew-dev \
	&& rm -rf /var/lib/apt/lists/*
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
CMD ["./myapp"]
