# Minecraft Hunger Games Sans 3d

Theodore Peters and Jonathan Singer -- pd. 3

Our project was intended to be a multiplayer procedurally generated battle royale game. Players can connect to a server, and they will be spawned into a map along with other players, useful items, and enemies. From there, players will hunt down and kill each other until only one is left standing.

The project uses SDL to render graphics and SDL_ttf to render text. These can be installed with

```bash
apt-get install libsdl2-dev
```

and

```bash
apt-get intall libsdl2-ttf
```

To run the project, first launch the server with `make run_server`, and run clients with `make run_client`.

What currently works is a screen renders with a player (who is a rabbit) and perhaps enemies (skeletons) and equipment (chests). All this information comes from the server via sockets.
In the coming few days we plan to get input working, we are very sorry we couldn't get it working yet.
4 players are needed for the game to start.
