function Bpsk_Signal = Bpsk_Signal_generater(symbol_rate,bits_per_symbol,snr_dB,signal_percentage)

num_symbols = floor(256*signal_percentage); % Ҫ���͵ķ������������ı������������������1024��������ֻ��Ҫ256�����ż���
% ���������������
data = randi([0 1], 1, num_symbols * bits_per_symbol);

% BPSK����
symbols = 2 * data - 1;

% ����ʱ���źţ������źŷ��ŵ�ʱ�䲽���϶��ǲ����ʵĵ�����
t_signal = 0:1/symbol_rate:(num_symbols*bits_per_symbol/symbol_rate - 1/symbol_rate);

% ���ɵ����źţ�
bpsk_signal = symbols .* cos(2 * pi * symbol_rate * t_signal);

% �������ź�Ƭ�Σ�Ϊ0����
signal_front = floor(rand * (256 - num_symbols));
signal_back = 256 - num_symbols - signal_front;
bpsk_signal_combine = [zeros(1,signal_front),bpsk_signal,zeros(1,signal_back)];

% ��Ӹ�˹����
noise_power = 10^(-snr_dB/10);
noise = sqrt(noise_power/2) * (randn(1, length(bpsk_signal_combine)) + 1i * randn(1, length(bpsk_signal_combine)));
received_signal = bpsk_signal_combine + noise;
Bpsk_Signal = received_signal;
t = 0:1/symbol_rate:(length(bpsk_signal_combine)/symbol_rate - 1/symbol_rate);
% ��ʾ�����źźͽ����ź�
figure;

subplot(3,1,1);
plot(t, bpsk_signal_combine);
title('BPSK�����ź�');

subplot(3,1,2);
plot(t, received_signal);
title('BPSK�����ź�');

subplot(3,1,3);
plot(t, real(received_signal), 'r');
hold on;
plot(t, imag(received_signal), 'b');
title('�����źţ���ɫ��ʵ������ɫ���鲿��');
legend('ʵ��', '�鲿');
end