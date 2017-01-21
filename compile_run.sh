gcc -fPIC -W -std=c99 -o main.o oslo.c -lm
echo "Complilation complete. Running program:"
time ./main.o $1
python analysis.py
