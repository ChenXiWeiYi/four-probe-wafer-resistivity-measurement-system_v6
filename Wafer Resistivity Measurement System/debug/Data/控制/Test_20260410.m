clear all
data = load('Current_f_2026-04-10_14-08-37.txt');

xx = 1000;
A = 1e3;

aaa(1,:) = data(1:xx);
bbb = reshape(aaa,10,[]);
ccc = mean(bbb,1);
ddd = data(1:end);

y1 = zeros(xx/10,1);
y1(:) = ( 2.5 * (1 + 0.005e-2));
y2 = zeros(xx/10,1);
y2(:) = ( 2.5 * (1 - 0.005e-2));

subplot(2,1,1)
plot(ddd);
subplot(2,1,2);
ccc = ccc' * A;
plot(ccc(2:end));
hold on ;
plot(y1);
hold on 
plot(y2);



% data = load('Current_f_2026-03-20_15-06-50.txt');  Kp = 750 Ti = 20 , 增幅振荡
% data = load('Current_f_2026-03-20_15-14-40.txt');  Kp = 750 Ti = 50 , 不振荡
% data = load('Current_f_2026-03-20_15-22-21.txt');  Kp = 1000 Ti =50, 小振
% data = load('Current_f_2026-03-20_15-25-22.txt');  Kp忘了,Ti忘了, 不振
% data = load('Current_f_2026-03-20_15-36-15.txt');  Kp = 500 Ti = 100, 非常好