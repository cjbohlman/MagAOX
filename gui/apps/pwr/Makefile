
#############################
# The qt5 qmake 
#
# On a system where qt5 qmake is the one in the bath, then no
# argument is needed.  If not, then invoke with, e.g., `make QMAKE=qmake-qt5`

QMAKE?=qmake

##############################


all: $(TARGET)

.PHONY: $(TARGET)
$(TARGET):
	$(QMAKE) -makefile $(TARGET).pro
	$(MAKE) -f makefile.$(TARGET)

#install: $(TARGET)
#	install bin/$(TARGET) /usr/local/bin

clean:
	rm -f obj/*.o *~
	rm -f moc/moc_* res/qrc_* forms/ui_*
	rm -f makefile.$(TARGET)
	rm -f bin/$(TARGET)
