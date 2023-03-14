# Jupyter - data science notebook
To run Jupter in the PWD, as a user with uid=1000:gid=1000 issue the command:
```bash
sudo docker run -it --rm -p 8888:8888 --user 1000:1000 -v "${PWD}":/home/jovyan/work jupyter/datascience-notebook:2023-02-28
```
To run Jupyter with access to the local xserver, issue the command in the following fashion:
```bash
sudo docker run --rm -it --network host -e DISPLAY=$DISPLAY -v $HOME/.Xauthority:/home/<containerUser>/.Xauthority -v /tmp/.X11-unix:/tmp/.X11-unix <container>
```
For example, using custom image `wp-jupyter`:
```bash
sudo docker run -ti --rm -p 8888:8888 --user 1000:1000 -v "${PWD}":/home/jovyan/work -w /home/jovyan/work -e DISPLAY=$DISPLAY -v $HOME/.Xauthority:/home/jovyan/.Xauthority -v /tmp/.X11-unix:/tmp/.X11-unix wp-jupyter
```
