gcc -fPIC -W -std=c99 -o ./C/main.o ./C/oslo.c -lm -lpthread
echo "Complilation complete. Running program..."
time ./C/main.o $1 $2 | awk '/grain/ {print $5 > "temp";print $0}'
echo "Run complete. Starting analysis..."
python Python/analysis.py
