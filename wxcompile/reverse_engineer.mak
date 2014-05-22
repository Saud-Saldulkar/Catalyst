
all: saud.exe

saud.exe: saud_main.o saud_my_rc.o saud_db.o head.h db.h process.h
	g++ -o saud.exe saud_main.o saud_my_rc.o saud_db.o -mthreads -LC:\wx\lib\gcc_lib -Wl,--subsystem,windows -mwindows -g   -lwxmsw28d_core -lwxbase28d -lwxtiffd -lwxjpegd -lwxpngd -lwxzlibd -lwxregexd -lwxexpatd -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lole32 -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32 -lodbc32

saud_my_rc.o: my.rc
	windres --use-temp-file -imy.rc -osaud_my_rc.o  --define HAVE_W32API_H  --define __WXDEBUG__ --define __WXMSW__ --include-dir C:\wx\lib\gcc_lib\mswd --include-dir C:\wx/include

saud_db.o: sqlite3.c sqlite3.h
	gcc -c sqlite3.c -o saud_db.o
	
saud_main.o: main.cpp
	g++ -c -o saud_main.o -DHAVE_W32API_H  -D__WXDEBUG__ -D__WXMSW__ -IC:\wx\lib\gcc_lib\mswd -IC:\wx\include -g   -MTsaud_main.o -MFsaud_main.o.d -MD -MP main.cpp
	

clean:
	rm *.o
	rm *.d
	
# g++ -c -o saud_main.o -DHAVE_W32API_H  -D__WXDEBUG__ -D__WXMSW__ -IC:\wx\lib\gcc_lib\mswd -IC:\wx\include -g   -MTsaud_main.o -MFsaud_main.o.d -MD -MP main.cpp

# windres --use-temp-file -imy.rc -osaud_my_rc.o  --define HAVE_W32API_H  --define __WXDEBUG__ --define __WXMSW__ --include-dir C:\wx\lib\gcc_lib\mswd --include-dir C:\wx/include

# g++ -o saud.exe saud_main.o saud_my_rc.o  -mthreads -LC:\wx\lib\gcc_lib -Wl,--subsystem,windows -mwindows -g   -lwxmsw28d_core -lwxbase28d -lwxtiffd -lwxjpegd -lwxpngd -lwxzlibd -lwxregexd -lwxexpatd -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lole32 -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32 -lodbc32
