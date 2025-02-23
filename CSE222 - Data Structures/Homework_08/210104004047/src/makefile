JC = javac
JFLAGS = -g 
TARGET = Main
SOURCES = Main.java Person.java SocialNetworkGraph.java

default: $(TARGET)

$(TARGET): $(SOURCES)
	@$(JC) $(JFLAGS) $^
	@java $(TARGET)

clean:
	rm -f *.class

doc:
	javadoc -encoding UTF-8 -charset UTF-8 -d Javadoc *.java

.PHONY: clean default 
