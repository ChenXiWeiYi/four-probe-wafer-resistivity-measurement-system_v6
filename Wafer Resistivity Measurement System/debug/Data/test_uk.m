clear all
data1 = load('delta_uk_f_2026-04-10_10-06-04.txt');
data2 = load('uk_f_2026-04-10_10-06-04.txt');

data = data2 - data1;
