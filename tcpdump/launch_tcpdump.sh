#!/bin/bash

IMAGE_NAME="ttt"
CONTAINER_NAME=$IMAGE_NAME

docker build ./ -t $IMAGE_NAME
docker images
docker ps -a
docker run -d -p 6667:6667 --name $CONTAINER_NAME $IMAGE_NAME
docker exec -it $CONTAINER_NAME tcpdump -Aqq port 6667

