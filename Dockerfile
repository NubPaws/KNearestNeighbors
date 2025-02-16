FROM ubuntu:22.04 AS builder

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app
COPY . /app

# Build the project
RUN mkdir -p build && cd build && cmake .. && make

# Use a minimal runtime image
FROM ubuntu:22.04 AS runtime

# Set working directory
WORKDIR /app

# Copy the built binaries from builder stage
COPY --from=builder /app/bin/server /app/server

# Expose the port used by the server
EXPOSE 8080

# Run the server
CMD ["/app/server", "8080"]
