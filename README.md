🧭 Zork - A Text Adventure Tribute
This repository contains a small replica of the classic text-based adventure game Zork, originally released in 1977.
Your ultimate goal? Enter the Troll Room, defeat its fearsome inhabitant, and step into the chamber that opens before you...

The game is entirely played through the command line interface, using the following set of commands:

🎮 Game Commands
go {direction} – Move in a direction (e.g., north, south, west, east, up, down)

look – Inspect your surroundings

take {item} – Pick up an item

drop {item} – Drop an item from your inventory

equip {item} – Equip an item

unequip {item} – Unequip an item

open {container/exit} – Open a container or exit

close {container/exit} – Close a container or exit

put {item} into {container} – Place an item into a container

inventory – Check your inventory

equipment – Check your currently equipped items

stats – View your character stats

help – Show available commands

quit – Exit the game

🃏 Easter Egg Commands: bar, Zork, jump, shout, hello

🛠️ Design Notes
One key aspect of this implementation is its pattern-based command recognition system.
For example, in the command put leaflet into mailbox, the system identifies that "put" is at args[0] and "into" is at args[2].
This approach makes it easy to extend with new commands without relying on a massive switch or if-else block.


Coming from a Unity development background, I’m more familiar with component-based architecture.
Shifting to a more polymorphism-oriented design in pure C++ required a change in mindset—and possibly led me away from a more "clean" solution. Still, it was a rewarding learning experience.

👤 Author
Miquel Barbarà Garrido

📜 License
Free to use



