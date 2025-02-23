JC = javac
JFLAGS = -g 
TARGET = Main
SOURCES = AVLTree.java Command.java GUIVisualization.java Main.java Stock.java StockDataManager.java

default: $(TARGET)

$(TARGET): $(SOURCES)
	$(JC) $(JFLAGS) $^
	java -Xint $(TARGET)

clean:
	rm -f *.class

doc:
	javadoc -encoding UTF-8 -charset UTF-8 -d Javadoc *.java

.PHONY: clean default 
