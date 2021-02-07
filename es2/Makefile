JCC = javac
JV = java

JFLAGS = -d bin
CLASSPATH = Resources/Java/JUnit/junit-4.12.jar:Resources/Java/JUnit/hamcrest-core-1.3.jar:bin

default: app

test: createdir compile_test; $(JV) -cp $(CLASSPATH) org.junit.runner.JUnitCore test.EditDistTest
app: createdir compile_app; $(JV) -cp $(CLASSPATH) app.AppMain

createdir: 
	mkdir -p bin 
	mkdir -p data


bin/lib/EditDist.class: src/lib/EditDist.java
	$(JCC) $(JFLAGS) src/lib/EditDist.java

compile_test: bin/lib/EditDist.class
	$(JCC) $(JFLAGS) -cp $(CLASSPATH) src/test/EditDistTest.java

compile_app: bin/lib/EditDist.class
	$(JCC) $(JFLAGS) -cp $(CLASSPATH) src/app/AppMain.java


clean: 
	$(RM) bin/lib/*.class bin/test/*.class
