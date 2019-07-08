CXX = g++-5
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
EXEC = cc3k
OBJECTS = subject.o object.o tile.o grid.o textdisplay.o chamber.o position.o \
item.o potion.o poisonhealth.o woundatk.o wounddef.o restorehealth.o boostdef.o \
boostatk.o treasure.o merchantGold.o smallGold.o normalGold.o dragonHoard.o \
character.o enemy.o hero.o dwarf.o goblin.o human.o dragon.o elf.o halfling.o \
merchant.o shade.o troll.o drow.o orc.o vampire.o controller.o test.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
