#Compile the code
# if the file densemult exits then remove it
cmd=recur
hwnumber=1
if [ -f ${cmd} ]; then
    rm ${cmd}
fi
g++ -std=c++11 *.cpp -o ${cmd}
# if the file densemult does not exit then exit the test
if [ ! -f ${cmd} ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi

# clean
for casenum in `seq 1 1 9`; do
    if [ -f ${casenum}.out ]; then
    rm ${casenum}.out
    fi
    if [ -f ${casenum}.stderr ]; then
    rm ${casenum}.stderr
    fi
    if [ -f ${casenum}.stdcout ]; then
    rm ${casenum}.stdcout
    fi
done

for casenum in `seq 1 1 9`; do
	./${cmd} "input=input${hwnumber}${casenum}.txt;output=output${hwnumber}${casenum}.txt" 1>${casenum}.stdcout 2>${casenum}.stderr
# compare 1.out with 1.ans, output the difference to 1.diff
	diff -iEBwu ans${hwnumber}${casenum}.txt output${hwnumber}${casenum}.txt > ${casenum}.diff
# if diff returns nothing, it means you pass the test case (Your ourput file 1.out is correct)
	if [ $? -ne 0 ]; then
    # display "test case 1 FAILED" to the screen. The word "FAILED" is highlighted in Red color
    		echo -e "Test case ${casenum}    \033[1;91mFAILED.\033[0m"
	else
    # display "test case 1 PASSED" to the screen. The word "PASSED" is highlighted in Green color
    		echo -e "Test case ${casenum}    \033[1;92mPASSED.\033[0m"
    # remove the file *.diff
    		rm -f ${casenum}.diff
            rm -f ${casenum}.stderr
            rm -f ${casenum}.stdcout
	fi
done

