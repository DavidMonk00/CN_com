gcc -fPIC -W -std=c99 -o ./C/main.o ./C/oslo.c -lm -lpthread
echo "Complilation complete. Running program:"
time ./C/main.o $1 $2
python Python/analysis.py
