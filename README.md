# Minecraft Hunger Games Sans 3d

Theodore Peters and Jonathan Singer -- pd. 3

Our project is a multiplayer procedurally generated head to head vs. game. Players can connect to a server, and they will be spawned into a map along with other players, useful items, and enemies. From there, players will hunt down and kill each other until only one is left standing.

The project uses SDL to render graphics and (sort of uses) SDL_ttf to render text. These can be installed with

```bash
apt-get install libsdl2-dev
```

and

```bash
apt-get intall libsdl2-ttf
```

To run the project, first launch the server with `make run_server`, and run clients with `make run_client`.

On startup of clients you might get an SDL library warning or 2, just ignore those, although this might be ssh specific, we don't know.

A screen renders with a player (who is a rabbit) and enemies (skeletons) and equipment.
2 players are needed for the game to start, although this can be changed by changing the preprocessor instructions in both gameloop.c and player.h. Only 2 player games are guaranteed to work as we've had mixed results with 3 and 4 player games, although again, this may be ssh specific. The port and host can be changed in fs/sockets.h.

Originally this was supposed to be a 4+ player battle royale, however we found that that was slow, so we turned it into a 2 player head to head.

We also scrapped A* pathfinding in favor of random enemy movement because A* pathfinding would make the game too dificult and require more processing time.

There is an alternate dungeon generation algorithm using a least spanning tree implemented and functional, but we decided that dungeons generated using cellular automata were more interesting and unique so chose to use those in the server process.
