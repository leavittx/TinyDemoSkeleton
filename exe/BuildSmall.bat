SET PATH=C:\Program Files (x86)\Windows Kits\8.1\Lib\winv6.3\um\x86;C:\Program Files (x86)\Windows Kits\8.1\bin\x86;C:\Program Files (x86)\Windows Kits\8.0\Lib\win8\um\x86;C:\Windows\System32;..\tools
crinkler.exe /OUT:Intro.exe /HASHTRIES:500 /SUBSYSTEM:WINDOWS /COMPMODE:SLOW /ORDERTRIES:5000 /TRUNCATEFLOATS:16 /HASHSIZE:500 /PRINT:IMPORTS /ENTRY:entrypoint /PRINT:LABELS /REPORT:report.html /RANGE:d3d11.dll kernel32.lib user32.lib opengl32.lib winmm.lib Gdi32.lib main_rel.obj

