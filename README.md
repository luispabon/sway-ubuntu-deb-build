# Sway builds for ubuntu 19.04

Ubuntu 19.04 build system for sway and related tools. Docker based. 

You do need `docker.io` and `make` installed, and your user on the docker group (otherwise you need to sudo the make commands).

## TL;DR

```shell
make yolo
```

## Otherwise...

I'm going to assume you know what you're doing with git and stuff.

How to:
  * `sudo -f install docker.io make`
  * Clone this repo. Ensure you pull submodules too.
  * `make build-image` to get the docker image for builds done

The makefile targets will require `sudo` to fix permissions - docker will be running as root and files created from it will be owned by root as well.

I keep forks of each project to add the required `debian` folder. Master branches always have it, and for releases sometimes I make a branch, sometimes not. Before you build anything, make sure the branch you're checking out from my fork (`origin`, not `upstream`) has the debian folder. The commits the submodules are pinned to are the versions of the apps I'm currently using myself, so these are a good bet.

Things that you need to build first: `json-c`, (version in Ubuntu repos is too old for sway, 0.12 instead of 0.13), `scdoc` and `wlroots`, as they're build deps for other apps. After that build whatever you need in whichever order you need. There's a `make build-everything` you can use to build all the projects. You don't need to install `scdoc` in your computer as it's a build dep for manpages. `json-c` 0.13 and `wlroots` are mandatory deps for sway though, so make sure you install these.

After you build something, the .deb package will be at the root of this project (together with other debian build files like build info, ddeb etc). You can install these with `dpkg -i`. If you're missing dependencies that aren't built here, do `apt -f install` to pull them from ubuntu's repo.
