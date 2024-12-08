FROM ubuntu:22.04

# Install dependencies.
RUN apt-get update && apt-get install -y \
	g++ \
	cmake \
	make \
	libpthread-stubs0-dev \
	&& rm -rf /var/lib/apt/lists/*

# Set the working directory.
WORKDIR /app
COPY . /app
RUN mkdir -p build
RUN cd build
RUN cmake ..
RUN make

# Expose the port the server listens on.
EXPOSE 8080

CMD ["./bin/server", "8080"]
