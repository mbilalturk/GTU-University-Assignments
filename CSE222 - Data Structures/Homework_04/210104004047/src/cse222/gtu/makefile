JC = javac
JFLAGS = -classpath
JD = javadoc
JDFLAGS = -protected -split index -use -author -version -d ./javadoc
RM = rm
JR = java

CLASSES = src/*.java

run: all
	@$(JR) -cp target/ cse222.gtu.Main

all:
	@$(JC) -d target -sourcepath . Main.java File.java Directory.java FileSystem.java FileSystemElement.java