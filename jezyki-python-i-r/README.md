# Jezyki programowania Python i R
---
## Run Python script with docker
Example:
```bash
$ sudo docker run -it --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp python python foo.py
```
For more instructions, refer to the (instructions)[https://hub.docker.com/_/python].
