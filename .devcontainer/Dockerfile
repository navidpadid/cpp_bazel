# Dev Container Dockerfile derived from project root Dockerfile
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    git \
    lcov \
    python3 \
    python3-pip \
    sudo \
    unzip \
    wget \
    zip \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y apt-transport-https curl gnupg \
    && curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor >bazel-archive-keyring.gpg \
    && mv bazel-archive-keyring.gpg /usr/share/keyrings \
    && echo "deb [signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list \
    && apt-get update && apt-get install -y bazel \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install buildifier for Bazel file formatting and linting
RUN wget -O /usr/local/bin/buildifier https://github.com/bazelbuild/buildtools/releases/download/v7.3.1/buildifier-linux-amd64 \
    && chmod +x /usr/local/bin/buildifier

# Create ubuntu user with sudo privileges
RUN groupadd --gid 1000 ubuntu 2>/dev/null || true \
    && useradd --uid 1000 --gid 1000 -m -s /bin/bash ubuntu 2>/dev/null || usermod -l ubuntu $(id -un 1000) \
    && echo "ubuntu ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Create the default workdir used by devcontainers
WORKDIR /workspaces/cpp_bazel
