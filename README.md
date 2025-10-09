# project32_68010782
ระบบจัดการข้อมูลการทำบุญ
# how to compile and run
--- main.c ---
compile : gcc donation.c main.c -o donation
run : ./donation.exe
--- test_e2e.c ---
compile : gcc donation.c test_e2e.c -o test_e2e
run : ./test_e2e.exe
--- test_function_unit_test ---
compile : gcc donation.c test_<FUNTIONNAME>.c -o test_<FUNTIONNAME>.exe
run : ./test_<FUNTIONNAME>.exe
