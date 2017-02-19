gcc -fPIC -W -std=c99 -o ./C/main.o ./C/oslo_a.c -lm -lpthread
echo "Complilation complete. Running program..."
time ./C/main_a.o $1
echo "Run complete. Starting analysis..."
python ./Python/analysis_a.py
