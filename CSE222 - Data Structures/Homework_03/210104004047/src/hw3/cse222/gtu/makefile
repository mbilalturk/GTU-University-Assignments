JC = javac
JFLAGS = -classpath
JD = javadoc
JDFLAGS = -protected -split index -use -author -version -d ./javadoc
RM = rm
JR = java

CLASSES = src/*.java

run: all
	@$(JR) -cp target/ hw3.cse222.gtu.Main

all:
	@$(JC) -d target -sourcepath . Device.java TV.java Computer.java Headphone.java Inventory.java Smartphone.java Keyboard.java Main.java