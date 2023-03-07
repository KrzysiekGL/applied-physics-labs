# Jupyter - data science notebook
To run Jupter in the PWD, as a user with uid=1000:gid=1000 issue the command:
```bash
sudo docker run -it --rm -p 8888:8888 --user 1000:1000 -v "${PWD}":/home/jovyan/work jupyter/datascience-notebook:2023-02-28

```
