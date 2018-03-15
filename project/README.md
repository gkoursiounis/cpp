# Role playing game

## Description

The game is about battles between heroes and monsters. Heroes use items (weapons, armors) and spells. Both sides leave in a world displayed by a grid. Except for battling, heroes can buy or sell items and spells from the market. At the end of every battle, heroes gain experience and money. If they gain enough experience they can upgrade their level and get their skills increased. Also, they can move around the map and engage into battle for as long time as they desire. The game ends if the player quits.

## Methodology & Steps
* The game provides the player with its own maps. Market exists one time in the one and multiple times in the other. Access to the market can be acheived throught every gird's market square when plenty. 
* Custom map can be selected if desired. Type **d** for default map ([5x10map.txt]( )) or **c** for custom.
* The grid consists of squares. Heroes move within the grid's limits as a team (1 to 3 heroes). At start, they are placed on the top left corner of the map. We carry no responsibility if a custom map cages the heroes team in any way.
* Heroes battle the same number of monsters. As a result, money and experience is given per level.
* Heroes hace levels (1 to 4). Every monster has a level close to the level og the hero it battles against (level-1,level,level+1). 
* Monsters are created every time a battle begins. Some monsters might have the same name. For more information enter the "info" option.
* Market contains a limited amount of items and spells. That's why we decided to include its information directly in the code (default). 
* Market is an independent class and a hero can access it without the grid's existence. This is because in a potential extension of the game we migth wish to have direct access to the market from every square of the grid.
* Heroes exist independently from the grid.
* Monsters.damageRange value is an abs() distance of the random() monsters damage.
* All heroes attack to a monster and vice versa. So, if the player decides to attack then all heroes attack to the first available monster which is the one with the smaller number in the array and it has life (PassOut()==0) 
* castSpell: perform a spell to a monster. Some as above.
* We also decided to use an array for the items and spells hero's inventory and avoid adding a list because we considered that items and spells are limited. 
* No GUI so...colours! Colours are displayed only in linux.

## Contributing

Team partner: Maria Karamina

## How to run
Compile:
```
g++ -o game Grid.cpp Living.cpp Market.cpp main.cpp
```
Run:
```
./game
```
