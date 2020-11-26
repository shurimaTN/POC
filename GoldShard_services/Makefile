SUBDIR = libfinance service_accounting test_lib tests launcher

all:
	@for i in $(SUBDIR); 	do  (echo "--------------------- $$i ---------------------"; cd $$i; make); done		
clean:
	@rm -f xml_test/*.acct
	@find . -name "*.gcov" -delete
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete
	@find . -name "*.info" -delete
	@find . -name "*.html" -delete
	@for i in $(SUBDIR); 	do  (echo "--------------------- $$i ---------------------"; cd $$i; make clean); done		


debug:
	@rm -f xml_test/*.acct
	@for i in $(SUBDIR); 	do  (echo "--------------------- $$i ---------------------"; cd $$i; make DEBUG=1); done		

coverage:
	@for i in $(SUBDIR); 	do  (echo "--------------------- $$i ---------------------"; cd $$i; make DEBUG=2); done		
	cd bin ; valgrind --tool=memcheck --leak-check=full --show-reachable=yes -s  test_lib
	gcovr -r . --exclude-unreachable-branches --html --html-details -o coverage.html -e service_accounting/tools.h -e libfinance/tools.h -e service_accounting/service.h -e service_accounting/trade.h -e test_lib/service.h 
	#gcovr -r . --exclude-unreachable-branches --html --html-details -o coverage.html -e service_accounting/tools.h  -e service_accounting/service.h -e service_accounting/trade.h -e test_lib/service.h 
	

gdb:
	cd bin ; nemiver test_lib

run:	
	cd bin ; test_lib


