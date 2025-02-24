# C++ Adventure Game

A simple game about exploring rooms and avoiding dangerous enemies and zombies to reach the winning room. The game features collecting items in order to open locked doors or fight back against any enemies.

---

## Requirements

To run the game you will need:

- A C++ compiler such as `g++`.
- The `nlohmann/json` library for JSON parsing, which is included in the repository.
- A terminal for command prompts.

---

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/cpp-adventure-game.git
   cd cpp-adventure-game
   ```
   
2. **Compile the game**:
   Use the provided `Makefile` to compile the game via the command:
   ```bash
   make
   ```

3. **Run the game**:
   To run the game with any maps downloaded or created, use the following command:
   ```bash
   /main maps/[name of map file].json
   ```

---

## Game Commands

- go [direction]: Moves to a room located in that direction.
- take [item]: Picks up an item in the current room.
- look: Views the description of the current room and any items or enemies.
- quit: Exit the game.

---

## Example Map

The game includes two maps as examples of how each map's rooms, items, and enemies work:

```bash
json
Copy
{
    "objective": {
        "type": "room",
        "what": ["winning_room"]
    },
    "rooms": [
        {
            "id": "start_room",
            "desc": "You are in a dimly lit room. There is a door to the north.",
            "exits": { "north": "locked_room" }
        },
        {
            "id": "locked_room",
            "desc": "This room is locked. You need a key to proceed.",
            "locked": true,
            "requiredItems": ["key"],
            "exits": { "south": "start_room", "east": "deadly_room" }
        },
        {
            "id": "deadly_room",
            "desc": "This room is filled with poisonous gas. You die instantly.",
            "isDeadly": true
        },
        {
            "id": "winning_room",
            "desc": "You have reached the winning room! Congratulations!",
            "exits": { "west": "locked_room" }
        }
    ],
    "objects": [
        {
            "id": "key",
            "desc": "A rusty old key.",
            "initialroom": "start_room"
        }
    ],
    "enemies": [],
    "player": {
        "initialroom": "start_room"
    }
}
```
