gcc -fPIC -W -std=c99 -o main.o oslo.c
echo "Complilation complete. Running program:"
time ./main.o $1 $2
python analysis.py
