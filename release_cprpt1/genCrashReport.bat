@REM EXCEPTION_STACK_BUFFER_OVERRUN
.\minidump_stackwalk.exe -m ".\29196.dmp" ".\symbols\" > crashRpt-29196-m.log
.\minidump_stackwalk.exe -s ".\29196.dmp" ".\symbols\" > crashRpt-29196-s.log
.\minidump_stackwalk.exe -c ".\29196.dmp" ".\symbols\" > crashRpt-29196-c.log

@REM EXCEPTION_ACCESS_VIOLATION_WRITE
.\minidump_stackwalk.exe -m ".\database\reports\7f8f803f-3e74-4f68-9b67-4c8b90e267f0.dmp" ".\symbols\" > crashRpt-7f8f8-m.log
.\minidump_stackwalk.exe -s ".\database\reports\7f8f803f-3e74-4f68-9b67-4c8b90e267f0.dmp" ".\symbols\" > crashRpt-7f8f8-s.log
.\minidump_stackwalk.exe -c ".\database\reports\7f8f803f-3e74-4f68-9b67-4c8b90e267f0.dmp" ".\symbols\" > crashRpt-7f8f8-c.log