echo foo > redirect_mixed_1.tmp
cat < redirect_mixed_1.tmp > redirect_mixed_2.tmp
cat > redirect_mixed_3.tmp < redirect_mixed_1.tmp
tr a-z A-Z < redirect_mixed_3.tmp > redirect_mixed_4.tmp
cat redirect_mixed_1.tmp
cat redirect_mixed_2.tmp
cat redirect_mixed_3.tmp
cat redirect_mixed_4.tmp
rm redirect_mixed_1.tmp redirect_mixed_2.tmp redirect_mixed_3.tmp redirect_mixed_4.tmp
